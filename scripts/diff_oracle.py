#!/usr/bin/env python3
"""Differential grammar tester: q's own `parse` (ground truth) vs tree-sitter.

For each snippet:
  - q oracle: run `-3!parse "<snip>"` in the real q interpreter. If q accepts it,
    we get the canonical functional-form AST; if not, an ERR (not valid q).
  - tree-sitter: parse and check for ERROR/MISSING nodes.

The actionable bucket is **q-OK but tree-sitter-FAIL** — real q the grammar
rejects. q's AST for each is printed as the spec for the fix.

Usage: python3 scripts/diff_oracle.py
Env:   Q=/path/to/q  (default ~/.kx/bin/q),  TS=tree-sitter on PATH
"""
import os
import re
import subprocess
import tempfile
import pathlib

Q = os.environ.get("Q", os.path.expanduser("~/.kx/bin/q"))

# Curated snippets covering the constructs analyze_errors.py flagged, in the
# minimal form that isolates each. (name, q-code)
SNIPPETS = [
    ("neg-float-vec",      "x:-.5 -.1 2"),
    ("neg-float-atom",     "x:-.5"),
    ("neg-int-vec",        "x:-5 -4 -3"),
    ("op-value-assign",    "@[x;i;:;y]"),
    ("op-value-amenddeep", ".[`a;();:;5]"),
    ("op-value-list",      "f:(+;-;*)"),
    ("colon-in-args",      "@[d;k;:;v]"),
    ("over-adverb",        "+/[1;2]"),
    ("each-both",          "a,'b"),
    ("each-adverb",        "f'[1;2;3]"),
    ("scan-adverb",        "+\\[1;2;3]"),
    ("amend-assign",       "counts[t]+:n"),
    ("amend-comma",        "B,:4"),
    ("cast-sym",           "x:`int$y"),
    ("cond",               "$[c;a;b]"),
    ("dollar-binary",      "a$b"),
    ("select-where",       "select sym,price from t where price>0"),
    ("select-by",          "select sum p by s from t"),
    ("exec",               "exec sym from t"),
    ("update",             "update p:p*2 from t where s=`a"),
    ("delete-rows",        "delete from t where p<0"),
    ("multiline-table",    "t:([]\n a:1 2;\n b:3 4)"),
    ("keyed-table",        "kt:([k:`a`b] v:1 2)"),
    ("empty-table-cols",   "t:([]a:`int$();b:`float$())"),
    ("dict",               "d:`a`b!1 2"),
    ("apply-dot",          ".[f;(1;2)]"),
    ("sys-load",           "system\"l util.q\""),
    ("projection-mid",     "f[a;;c]"),
    ("compose",            "f:avg count"),
    ("each-right",         "x f/:y"),
    ("each-left",          "x f\\:y"),
    ("if-control",         "if[x>0;:1]"),
    ("do-loop",            "do[10;x+:1]"),
    ("signal",             "'`err"),
    ("at-amend-fn",        "@[x;0;:;5]"),
    ("global-amend",       "x::5"),
    ("nested-index",       "m[0;1]"),
    ("vector-conditional", "?[b;x;y]"),
    # Round 2 — extracted from real-repo first-error lines
    ("neg-in-paren",       "y:(-.5+x)"),
    ("neg-in-bracket",     "r:exp[-.5*x]"),
    ("op-each-take",       "r:p#'q"),
    ("at-each",            "r:x@'i"),
    ("at-each-left",       "r:x@'\\:i"),
    ("set-attr",           "r:`g#x"),
    ("empty-dict",         "d:()!()"),
    ("proj-elided-first",  "@[;`sym;f]"),
    ("proj-attr-amend",    "@[`.;`sym;`g#]"),
    ("zero-colon",         "t:(\"SF\";enlist\",\")0:data"),
    ("colon-colon-value",  "@[e;k;::]"),
    ("each-on-fn-bracket", "(!)'[y]"),
    ("eachright-vs",       "0b vs/:til 4"),
    ("amend-in-lambda",    "a:{x-:1}"),
    ("global-amend-stmt",  "r::select from t where a>0"),
    ("compose-each-prior", "deltas':[x]"),
]


def run_q_oracle(snips):
    """Return {name: ('OK', ast) | ('ERR', msg)} from q's parse."""
    # Build a q script: a list of strings, parse each under protection.
    def qstr(s):
        return '"' + s.replace("\\", "\\\\").replace('"', '\\"').replace("\n", "\\n") + '"'
    lines = ["snips:(" + ";".join(qstr(c) for _, c in snips) + ");"]
    lines.append('f:{[i;s] r:@[{"OK\\t",-3!parse x};s;{"ERR\\t",x}]; -1 (string i),"\\t",r;};')
    lines.append("f'[til count snips; snips];")
    lines.append("exit 0")
    script = "\n".join(lines)
    with tempfile.NamedTemporaryFile("w", suffix=".q", delete=False) as fh:
        fh.write(script)
        p = fh.name
    try:
        out = subprocess.run([Q, p], stdin=subprocess.DEVNULL,
                             capture_output=True, text=True, timeout=30).stdout
    finally:
        os.unlink(p)
    res = {}
    for line in out.splitlines():
        m = re.match(r"^(\d+)\t(OK|ERR)\t(.*)$", line)
        if m:
            idx = int(m.group(1))
            res[snips[idx][0]] = (m.group(2), m.group(3))
    return res


def ts_parse(code):
    """Return True if tree-sitter parses with NO ERROR/MISSING node."""
    with tempfile.NamedTemporaryFile("w", suffix=".q", delete=False) as fh:
        fh.write(code + "\n")
        p = fh.name
    try:
        out = subprocess.run(["tree-sitter", "parse", p],
                             capture_output=True, text=True, timeout=15).stdout
    finally:
        os.unlink(p)
    return not re.search(r"ERROR|MISSING", out)


def main():
    oracle = run_q_oracle(SNIPPETS)
    rows = []
    for name, code in SNIPPETS:
        q_ok, q_ast = oracle.get(name, ("ERR", "no-output"))
        ts_ok = ts_parse(code)
        rows.append((name, code, q_ok, q_ast, ts_ok))

    gaps = [r for r in rows if r[2] == "OK" and not r[4]]
    both = [r for r in rows if r[2] == "OK" and r[4]]
    qbad = [r for r in rows if r[2] == "ERR"]

    print(f"=== SUMMARY: {len(rows)} snippets | both-ok={len(both)} | "
          f"GAPS (q-ok, ts-fail)={len(gaps)} | q-rejects={len(qbad)} ===\n")
    print(">>> GRAMMAR GAPS — real q the grammar rejects (q AST = the spec):")
    for name, code, _, ast, _ in gaps:
        print(f"  [{name}]\n    q : {code}\n    ast: {ast}\n    ts : ERROR")
    print("\n>>> OK in both:")
    print("   " + ", ".join(r[0] for r in both))
    if qbad:
        print("\n>>> q itself rejected (snippet bug, ignore):")
        for name, code, _, msg, _ in qbad:
            print(f"   [{name}] {code}  -> {msg}")


if __name__ == "__main__":
    main()

# ---------------------------------------------------------------------------
# Shape oracle (2026-07-06): accept/reject is necessary, not sufficient. For
# q's ambiguous constructs, assert tree-sitter's TOP NODE matches q's parse
# interpretation (derived by hand from `-3!parse`, shown in comments).
# Run: python3 scripts/diff_oracle.py --shapes
# ---------------------------------------------------------------------------
SHAPE_CASES = [
    # (snippet, expected top node)          # q -3!parse
    ("x-5",          "binary"),             # (-;`x;5)
    ("x - 5",        "binary"),             # (-;`x;5)
    ("x -5",         "call"),               # (`x;-5)  apply!
    ("f -5",         "call"),               # (`f;-5)
    ("2 -3",         "vector"),             # 2 -3
    ("1 -1",         "vector"),             # 1 -1
    ("1 2 3",        "vector"),             # 1 2 3
    ("count[x]-5",   "binary"),             # (-;(#:;`x);5)
    ("count[x] -5",  "call"),               # ((#:;`x);-5)
    ("n?-5 -4",      "binary"),             # (?;`n;-5 -4)
    ("2*3 -4",       "binary"),             # (*;2;3 -4)
    ("2*3-4",        "binary"),             # (*;2;(-;3;4))
    ("a,'b",         "binary"),             # ((';,);`a;`b)
    ("x f'y",        "binary"),             # ((';`f);`x;`y)
    ("f g'x",        "binary"),             # ((';`g);`f;`x)
    ("f each x",     "binary"),             # (each;`f;`x)
    ("x vs y",       "binary"),             # (vs;`x;`y)
    ("til 10",       "call"),               # (til;10)
    ('-1"msg"',      "call"),               # (-1;"msg")
    ("f x+1",        "call"),               # (`f;(+;`x;1))
    ('"abc" 1',      "call"),               # ("abc";1)
    ("t*-.35",       "binary"),             # (*;`t;-0.35)
    ("t* -.35",      "binary"),             # (*;`t;-0.35)
]


def ts_top_node(code):
    with tempfile.NamedTemporaryFile("w", suffix=".q", delete=False) as fh:
        fh.write(code + "\n")
        p = fh.name
    try:
        out = subprocess.run(["tree-sitter", "parse", p],
                             capture_output=True, text=True, timeout=15).stdout
    finally:
        os.unlink(p)
    lines = out.splitlines()
    top = lines[1].strip().split(" ")[0].strip("(") if len(lines) > 1 else "?"
    if re.search(r"ERROR|MISSING", out):
        top += "+ERR"
    return top


def shapes():
    bad = 0
    for code, want in SHAPE_CASES:
        got = ts_top_node(code)
        ok = got == want
        bad += not ok
        print(f"{'ok ' if ok else 'FAIL'}  {code:14s} want={want:7s} got={got}")
    print(f"\n{len(SHAPE_CASES)-bad}/{len(SHAPE_CASES)} shapes match")
    return bad


if __name__ == "__main__" and "--shapes" in os.sys.argv:
    raise SystemExit(shapes())
