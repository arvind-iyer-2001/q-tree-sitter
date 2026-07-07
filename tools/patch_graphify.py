#!/usr/bin/env python3
"""Idempotently wire q/kdb+ support into an installed graphify.

Run after installing or UPGRADING graphify (upgrades overwrite site-packages,
wiping previous runs of this script). Safe to run repeatedly.

What it does to the graphify package it finds:
  1. adds '.q' to detect.py CODE_EXTENSIONS
  2. installs extractors/{__init__,base,q}.py (canonical copies live next to
     this script in tools/graphify_q/)
  3. adds the extract_q import to extract.py
  4. ensures '.q': extract_q is in extract.py's _DISPATCH table
  5. installs the tree-sitter-q wheel into graphify's interpreter if
     tree_sitter_q is not importable there

Usage:
    python3 tools/patch_graphify.py                 # auto-detect graphify env
    python3 tools/patch_graphify.py --python /path/to/graphify/python
"""
from __future__ import annotations

import argparse
import re
import shutil
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
REPO = HERE.parent
Q_SRC = HERE / "graphify_q"


def find_graphify_python(explicit: str | None) -> str:
    if explicit:
        return explicit
    # uv tool install is the common case
    try:
        out = subprocess.run(["uv", "tool", "dir"], capture_output=True, text=True, timeout=60)
        if out.returncode == 0 and out.stdout.strip():
            cand = Path(out.stdout.strip()) / "graphifyy" / "bin" / "python"
            if cand.exists():
                return str(cand)
    except (FileNotFoundError, subprocess.TimeoutExpired):
        pass
    # fall back: shebang of the graphify binary
    gbin = shutil.which("graphify")
    if gbin:
        shebang = Path(gbin).read_text(errors="ignore").splitlines()[0].lstrip("#!")
        if shebang and Path(shebang).exists():
            return shebang
    return sys.executable


def site_dir(python: str) -> Path:
    out = subprocess.run(
        [python, "-c", "import graphify, pathlib; print(pathlib.Path(graphify.__file__).parent)"],
        capture_output=True, text=True,
    )
    if out.returncode != 0:
        sys.exit(f"graphify not importable from {python}:\n{out.stderr}")
    return Path(out.stdout.strip())


def patch_detect(site: Path) -> str:
    p = site / "detect.py"
    src = p.read_text()
    if re.search(r"CODE_EXTENSIONS\s*=\s*{[^}]*'\.q'", src):
        return "detect.py: already has .q"
    m = re.search(r"(CODE_EXTENSIONS\s*=\s*{[^}]*)}", src)
    if not m:
        sys.exit("detect.py: CODE_EXTENSIONS set not found — graphify layout changed, update this script")
    src = src.replace(m.group(0), m.group(1) + ", '.q'}", 1)
    p.write_text(src)
    return "detect.py: added .q"


def install_extractor(site: Path) -> str:
    ext = site / "extractors"
    ext.mkdir(exist_ok=True)
    init = ext / "__init__.py"
    if not init.exists():
        init.write_text('"""Bespoke per-language extractors."""\n')
    shutil.copy2(Q_SRC / "base.py", ext / "base.py")
    shutil.copy2(Q_SRC / "q.py", ext / "q.py")
    return "extractors/: base.py + q.py installed"


def patch_extract(site: Path) -> list[str]:
    p = site / "extract.py"
    src = p.read_text()
    msgs = []

    if "from .extractors.q import extract_q" not in src and \
       "from graphify.extractors.q import extract_q" not in src:
        # anchor on the last stdlib-ish relative import near the top
        for anchor in (
            "from .mcp_ingest import extract_mcp_config, is_mcp_config_path",
            "from .cache import load_cached, save_cached",
        ):
            if anchor in src:
                src = src.replace(anchor, anchor + "\nfrom .extractors.q import extract_q  # noqa: F401", 1)
                msgs.append("extract.py: import added")
                break
        else:
            sys.exit("extract.py: no known import anchor — graphify layout changed, update this script")
    else:
        msgs.append("extract.py: import already present")

    if '".q": extract_q' not in src and "'.q': extract_q" not in src:
        m = re.search(r"(_DISPATCH\s*:?[^=]*=\s*{\n)", src)
        if not m:
            sys.exit("extract.py: _DISPATCH table not found — graphify layout changed, update this script")
        src = src.replace(m.group(1), m.group(1) + '    ".q": extract_q,\n', 1)
        msgs.append("extract.py: dispatch entry added")
    else:
        msgs.append("extract.py: dispatch entry already present")

    p.write_text(src)
    return msgs


def ensure_wheel(python: str) -> str:
    ok = subprocess.run([python, "-c", "import tree_sitter_q"], capture_output=True)
    if ok.returncode == 0:
        return "tree_sitter_q: already importable"
    wheels = sorted((REPO / "dist").glob("tree_sitter_q-*.whl")) or \
             sorted((REPO / "bindings" / "python" / "tree_sitter_q").glob("tree_sitter_q-*.whl"))
    target = str(wheels[-1]) if wheels else str(REPO)  # fall back: build from source
    for cmd in (
        ["uv", "pip", "install", "--python", python, target],
        [python, "-m", "pip", "install", target],
    ):
        r = subprocess.run(cmd, capture_output=True, text=True)
        if r.returncode == 0:
            return f"tree_sitter_q: installed from {target}"
    sys.exit(f"could not install tree_sitter_q into {python} — install manually:\n"
             f"  uv pip install --python {python} {target}")


def clear_pycache(site: Path) -> None:
    for d in site.rglob("__pycache__"):
        shutil.rmtree(d, ignore_errors=True)


def verify(python: str) -> str:
    code = (
        "from graphify.detect import CODE_EXTENSIONS;"
        "from graphify.extract import extract_q;"
        "assert '.q' in CODE_EXTENSIONS;"
        "print('OK')"
    )
    r = subprocess.run([python, "-c", code], capture_output=True, text=True)
    if r.returncode != 0 or "OK" not in r.stdout:
        sys.exit(f"verification FAILED:\n{r.stderr}")
    return "verify: .q registered, extract_q importable"


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--python", help="graphify environment's python interpreter")
    args = ap.parse_args()

    python = find_graphify_python(args.python)
    site = site_dir(python)
    print(f"graphify python: {python}")
    print(f"graphify site:   {site}")

    print(" *", patch_detect(site))
    print(" *", install_extractor(site))
    for m in patch_extract(site):
        print(" *", m)
    print(" *", ensure_wheel(python))
    clear_pycache(site)
    print(" *", verify(python))
    print("done — graphify now extracts .q files")


if __name__ == "__main__":
    main()
