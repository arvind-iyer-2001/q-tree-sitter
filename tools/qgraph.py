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

# Local document extraction (PDF/md/txt) — sections + mention tokens, no LLM.
from graphify.extractors.docs import extract_docs
doc_files = [Path(f) for f in det['files'].get('document', [])]
dres = extract_docs(doc_files)
res['nodes'].extend(dres['nodes'])
res['edges'].extend(dres['edges'])
res['mentions'] = dres['mentions']
n_docs = sum(1 for n in dres['nodes'] if n.get('kind') == 'document')
n_secs = sum(1 for n in dres['nodes'] if n.get('kind') == 'doc-section')
print('docs:', n_docs, 'files,', n_secs, 'sections,', len(dres['mentions']), 'mention tokens')

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

# Merge q-extractor stub nodes (kind=external) into same-label definitions.
# Stubs carry the CALLING file's attribution; without this remap, every
# cross-file call edge points at a stub and flow analysis misattributes it.
defs = {{}}
def_files = {{}}
def is_test(sf):
    return '/test' in sf or sf.startswith('test')
for n in extraction['nodes']:
    if n.get('kind') in ('function', 'variable', 'table', 'file'):
        lbl = n.get('label')
        if not lbl:
            continue
        sf = n.get('source_file', '')
        # Prefer non-test definitions when the same global is defined in both
        # src and test trees (q has one runtime namespace, but src is canonical).
        if lbl not in defs or (is_test(def_files[lbl]) and not is_test(sf)):
            defs[lbl] = n['id']
            def_files[lbl] = sf
remap = {{}}
kept = []
for n in extraction['nodes']:
    if n.get('kind') == 'external' and n.get('label') in defs and n['id'] != defs[n['label']]:
        remap[n['id']] = defs[n['label']]
    else:
        kept.append(n)
if remap:
    extraction['nodes'] = kept
    for e in extraction['edges']:
        e['source'] = remap.get(e['source'], e['source'])
        e['target'] = remap.get(e['target'], e['target'])
    extraction['edges'] = [e for e in extraction['edges'] if e['source'] != e['target']]
    print('merged', len(remap), 'stub nodes into definitions')

# Namespace hub nodes (top-level q namespaces with >=3 function defs) so doc
# sections have a resolvable target and queries get a per-namespace entry point.
import collections
ns_members = collections.defaultdict(list)
for n in extraction['nodes']:
    if n.get('kind') in ('function', 'variable', 'table'):
        l = n.get('label', '')
        if l.startswith('.') and l.count('.') >= 2:
            ns_members['.' + l.split('.')[1]].append(n['id'])
ns_ids = {{}}
for ns, members in ns_members.items():
    if len(members) < 3:
        continue
    nid = 'ns:' + ns
    ns_ids[ns] = nid
    extraction['nodes'].append({{'id': nid, 'label': ns, 'file_type': 'code',
                                 'source_file': '', 'source_location': 'L1',
                                 'kind': 'namespace'}})
    for m in members:
        extraction['edges'].append({{'source': nid, 'target': m,
                                     'relation': 'contains',
                                     'confidence': 'EXTRACTED',
                                     'source_file': '', 'source_location': 'L1'}})

# Resolve doc mention tokens: exact definition label > namespace hub >
# top-namespace hub. Concept nodes are minted ONLY for the known process
# acronyms (PROC_NS values) — a dotted token that matches nothing in the
# code is likely a URL fragment or config literal from the PDF and is dropped.
from graphify.extractors.docs import PROC_NS
acronym_ns = set(PROC_NS.values())
concepts = {{}}
resolved_edges = dropped = 0
for sec_id, tok in extraction.pop('mentions', []):
    if tok in defs:
        tgt = defs[tok]
    elif tok in ns_ids:
        tgt = ns_ids[tok]
    else:
        top = '.' + tok.split('.')[1] if tok.count('.') >= 2 else tok
        if top in ns_ids:
            tgt = ns_ids[top]
        elif tok in acronym_ns:
            tgt = concepts.get(tok)
            if tgt is None:
                tgt = 'concept:' + tok
                concepts[tok] = tgt
                extraction['nodes'].append({{'id': tgt, 'label': tok,
                                             'file_type': 'code',
                                             'source_file': '',
                                             'source_location': 'L1',
                                             'kind': 'process'}})
        else:
            dropped += 1
            continue
    extraction['edges'].append({{'source': sec_id, 'target': tgt,
                                 'relation': 'mentions',
                                 'confidence': 'EXTRACTED',
                                 'source_file': '', 'source_location': 'L1'}})
    resolved_edges += 1
print('namespace hubs:', len(ns_ids), '| doc mentions resolved:', resolved_edges,
      '| process concepts:', len(concepts))

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

    # 4. HTML export. `graphify export html` exists only in some CLI versions
    # and refuses graphs over its 5,000-node viz cap — fall back to the
    # two-level aggregated views (community overview as graph.html + top-hub
    # subgraph) built by tools/qgraph_html.py.
    print("\n[4/4] HTML export")
    r = subprocess.run([python, "-m", "graphify", "export", "html"],
                       capture_output=True, text=True, cwd=workdir)
    print((r.stdout + r.stderr).strip()[-300:])
    default_html = workdir / "graphify-out" / "graph.html"
    html_target = out / "graph.html"
    if default_html.exists() and default_html.resolve() != html_target.resolve():
        html_target.write_bytes(default_html.read_bytes())
    if not html_target.exists():
        r = subprocess.run([python, str(HERE / "qgraph_html.py"), str(out)],
                           capture_output=True, text=True)
        print((r.stdout + r.stderr).strip()[-300:])
        comm_html = out / "graph-communities.html"
        if comm_html.exists():
            html_target.write_bytes(comm_html.read_bytes())

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
