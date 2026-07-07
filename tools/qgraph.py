#!/usr/bin/env python3
"""qgraph — build a knowledge graph for any q/kdb+ repository, locally.

One command, no data leaves the machine: structural (AST) extraction via
tree-sitter-q, graph build, community detection, HTML + report. Semantic
(LLM) extraction is deliberately NOT part of this tool — for proprietary
code run it only through an approved channel (see PACKAGING.md).

Usage:
    python3 tools/qgraph.py /path/to/proprietary/repo
    python3 tools/qgraph.py /path/to/repo --out /tmp/graphdir
    python3 tools/qgraph.py /path/to/repo --include-gitignored

Output (in <repo>/graphify-out/ unless --out given):
    graph.html        interactive visualization (self-contained option: --inline-js)
    graph.json        GraphRAG-ready nodes/edges/communities
    GRAPH_REPORT.md   god nodes, surprising connections, cohesion audit
"""
from __future__ import annotations

import argparse
import json
import os
import re
import subprocess
import sys
import urllib.request
from pathlib import Path

HERE = Path(__file__).resolve().parent

VIS_CDN = "https://unpkg.com/vis-network@9.1.6/standalone/umd/vis-network.min.js"


def graphify_python() -> str:
    r = subprocess.run(["uv", "tool", "dir"], capture_output=True, text=True)
    if r.returncode == 0 and r.stdout.strip():
        cand = Path(r.stdout.strip()) / "graphifyy" / "bin" / "python"
        if cand.exists():
            return str(cand)
    return sys.executable


def check_q_support(python: str) -> None:
    r = subprocess.run(
        [python, "-c",
         "from graphify.detect import CODE_EXTENSIONS;"
         "from graphify.extract import extract_q;"
         "assert '.q' in CODE_EXTENSIONS"],
        capture_output=True, text=True,
    )
    if r.returncode != 0:
        print("q support missing in graphify — running patcher...")
        subprocess.run([sys.executable, str(HERE / "patch_graphify.py"),
                        "--python", python], check=True)


def run_py(python: str, code: str, cwd: Path) -> str:
    r = subprocess.run([python, "-c", code], capture_output=True, text=True, cwd=cwd)
    if r.returncode != 0:
        sys.exit(f"pipeline step failed:\n{r.stderr[-2000:]}")
    return r.stdout


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("repo", help="path to the repository to graph")
    ap.add_argument("--out", help="output dir (default <repo>/graphify-out)")
    ap.add_argument("--include-gitignored", action="store_true",
                    help="graph files even if .gitignore excludes them "
                         "(writes a .graphifyignore negation file at repo root)")
    ap.add_argument("--inline-js", action="store_true",
                    help="inline the vis-network library into graph.html "
                         "(fully offline / air-gapped viewing)")
    args = ap.parse_args()

    repo = Path(args.repo).resolve()
    if not repo.is_dir():
        sys.exit(f"not a directory: {repo}")
    out = Path(args.out).resolve() if args.out else repo / "graphify-out"
    out.mkdir(parents=True, exist_ok=True)

    python = graphify_python()
    check_q_support(python)
    print(f"graphify python: {python}")
    print(f"repo:            {repo}")
    print(f"output:          {out}")

    if args.include_gitignored:
        gi = repo / ".graphifyignore"
        if not gi.exists():
            gi.write_text("!**\n")
            print("wrote .graphifyignore negation (repo is gitignored-heavy)")

    # graphify writes to <cwd>/graphify-out; run with cwd=repo, then move if --out
    workdir = repo

    # 1. detect
    print("\n[1/4] detect")
    det = run_py(python, f"""
import json
from graphify.detect import detect
from pathlib import Path
r = detect(Path({str(repo)!r}))
Path({str(out / '.detect.json')!r}).write_text(json.dumps(r, ensure_ascii=False))
print(r['total_files'], 'files,', r['total_words'], 'words')
for k, v in r['files'].items():
    if v: print(' ', k, len(v))
""", workdir)
    print(det.strip())
    detect = json.loads((out / ".detect.json").read_text())
    if detect["total_files"] == 0:
        sys.exit("no supported files found — if the repo's files are gitignored, "
                 "rerun with --include-gitignored")

    # 2. AST extraction (deterministic, local)
    print("\n[2/4] AST extraction (local, no LLM)")
    print(run_py(python, f"""
import json
from graphify.extract import collect_files, extract
from pathlib import Path
det = json.loads(Path({str(out / '.detect.json')!r}).read_text())
files = []
for f in det['files']['code']:
    p = Path(f)
    files.extend(collect_files(p) if p.is_dir() else [p])
res = extract(files, cache_root=Path({str(workdir)!r}))
Path({str(out / '.extract.json')!r}).write_text(json.dumps(res, ensure_ascii=False))
print('AST:', len(res['nodes']), 'nodes,', len(res['edges']), 'edges')
""", workdir).strip())

    # 3. build + cluster + report + json
    print("\n[3/4] graph build + clustering")
    print(run_py(python, f"""
import json
from graphify.build import build_from_json
from graphify.cluster import cluster, score_all
from graphify.analyze import god_nodes, surprising_connections, suggest_questions
from graphify.report import generate
from graphify.export import to_json
from pathlib import Path

extraction = json.loads(Path({str(out / '.extract.json')!r}).read_text())
detection  = json.loads(Path({str(out / '.detect.json')!r}).read_text())
G = build_from_json(extraction)
communities = cluster(G)
cohesion = score_all(G, communities)
gods = god_nodes(G)
surprises = surprising_connections(G, communities)
labels = {{cid: 'Community ' + str(cid) for cid in communities}}
questions = suggest_questions(G, communities, labels)
tokens = {{'input': 0, 'output': 0}}
report = generate(G, communities, cohesion, labels, gods, surprises, detection, tokens, '.', suggested_questions=questions)
Path({str(out / 'GRAPH_REPORT.md')!r}).write_text(report)
to_json(G, communities, {str(out / 'graph.json')!r})
labpath = Path({str(out / '.labels.json')!r})
labpath.write_text(json.dumps({{str(k): v for k, v in labels.items()}}))
print('graph:', G.number_of_nodes(), 'nodes,', G.number_of_edges(), 'edges,', len(communities), 'communities')
""", workdir).strip())

    # 4. HTML export (graphify CLI writes <cwd>/graphify-out/graph.html)
    print("\n[4/4] HTML export")
    r = subprocess.run([python, "-m", "graphify", "export", "html"],
                       capture_output=True, text=True, cwd=workdir)
    print((r.stdout + r.stderr).strip()[-300:])
    default_html = workdir / "graphify-out" / "graph.html"
    html_target = out / "graph.html"
    if default_html.exists() and default_html.resolve() != html_target.resolve():
        html_target.write_bytes(default_html.read_bytes())

    if args.inline_js and html_target.exists():
        html = html_target.read_text()
        m = re.search(r'<script src="https://unpkg\.com/vis-network[^"]*"[\s\S]*?</script>', html)
        if m:
            lib = urllib.request.urlopen(VIS_CDN, timeout=60).read().decode()
            html = html.replace(m.group(0), "<script>\n" + lib + "\n</script>")
            html_target.write_text(html)
            print("vis-network inlined — graph.html is fully self-contained")

    for tmp in (".detect.json", ".extract.json", ".labels.json"):
        (out / tmp).unlink(missing_ok=True)

    print(f"\ndone. open {html_target}")
    print("NOTE: this run was 100% local (AST only). For semantic/LLM extraction "
          "on proprietary code, see PACKAGING.md before sending content anywhere.")


if __name__ == "__main__":
    main()
