#!/usr/bin/env python3
"""Categorize ERROR nodes across the real corpus into named construct buckets.

For each failing file, extract the source text under every ERROR/MISSING node
(plus its line for context), classify against known q construct patterns, and
report buckets ranked by number of *files* affected (fixing a bucket that
touches 30 files beats one that touches 2).

Usage: python3 scripts/categorize_errors.py [root]   (default test/real)
"""
import os, re, signal, subprocess, sys, pathlib, collections

root = pathlib.Path(sys.argv[1] if len(sys.argv) > 1 else "test/real")
node_re = re.compile(r'\((ERROR|MISSING)\s+\[(\d+),\s*(\d+)\]\s*-\s*\[(\d+),\s*(\d+)\]')

# (bucket, regex over the error fragment + its full line) — first match wins.
# Patterns target the *construct*, not the symptom character.
RULES = [
    ("non-ascii/binary",      lambda frag, line: any(ord(c) > 127 for c in frag)),
    ("adverb-on-bracket-call",lambda frag, line: re.search(r"\]\s*['\\/]:?\s*\[", line)),
    ("adverb-chain",          lambda frag, line: re.search(r"['\\/]:?['\\/]:?", frag)),
    ("each-tick",             lambda frag, line: frag.startswith("'") or re.search(r"\w'(\[|\w)", frag)),
    ("over-scan",             lambda frag, line: frag in ("/", "\\", "/:", "\\:") or frag.startswith(("/", "\\"))),
    ("neg-number-juxt",       lambda frag, line: re.match(r"^-\d", frag) or frag == "-"),
    ("proj-leading-elide",    lambda frag, line: re.search(r"[\[;]\s*;", frag) or re.search(r"@\[\s*;", line)),
    ("zero-colon-io",         lambda frag, line: re.search(r"0:|1:|2:", frag) or re.search(r'\)\s*0:', line)),
    ("colon-colon",           lambda frag, line: "::" in frag),
    ("amend-assign-op",       lambda frag, line: re.search(r"[+\-*%,&|^]:", frag)),
    ("cond-dollar",           lambda frag, line: frag.startswith("$[") or frag == "$"),
    ("do-while-if",           lambda frag, line: frag in ("do", "while", "if") or frag.startswith(("do[", "while[", "if["))),
    ("attr-hash",             lambda frag, line: re.search(r"`\w*#", frag) or re.search(r"`[gsup]#", line)),
    ("brace-close",           lambda frag, line: frag in ("}", "]", ")")),
    ("bare-colon-op",         lambda frag, line: frag == ":"),
    ("comment-text",          lambda frag, line: re.match(r"^[A-Z][a-z]+ ", line) and "/" not in line[:2]),
]

def classify(frag, line):
    for name, pred in RULES:
        try:
            if pred(frag, line):
                return name
        except Exception:
            pass
    return "OTHER"

bucket_files = collections.defaultdict(set)     # bucket -> {files}
bucket_count = collections.Counter()            # bucket -> total ERROR nodes
bucket_examples = collections.defaultdict(list) # bucket -> [(file, lineno, frag, line)]
file_buckets = collections.defaultdict(set)     # file -> {buckets}
failing = []

for f in sorted(root.rglob("*.q")):
    try:
        p = subprocess.Popen(["tree-sitter", "parse", str(f)],
                             stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                             text=True, start_new_session=True)
        try:
            out, _ = p.communicate(timeout=15)
        except subprocess.TimeoutExpired:
            os.killpg(os.getpgid(p.pid), signal.SIGKILL); p.communicate(); continue
    except Exception:
        continue
    src = f.read_text(errors="replace").splitlines()
    hits = list(node_re.finditer(out))
    if not hits:
        continue
    failing.append(str(f))
    for m in hits:
        r0, c0, r1, c1 = map(int, m.groups()[1:])
        if r0 >= len(src):
            continue
        line = src[r0]
        frag = (line[c0:c1] if r0 == r1 else line[c0:c0 + 60]).strip() or line.strip()[:60]
        b = classify(frag, line)
        bucket_files[b].add(str(f))
        bucket_count[b] += 1
        if len(bucket_examples[b]) < 5:
            bucket_examples[b].append((str(f), r0 + 1, frag[:40], line.strip()[:90]))
        file_buckets[str(f)].add(b)

print(f"=== {len(failing)} failing files ===\n")
print("=== BUCKETS ranked by files affected ===")
for b in sorted(bucket_files, key=lambda k: -len(bucket_files[k])):
    print(f"\n[{b}]  files={len(bucket_files[b])}  errors={bucket_count[b]}")
    for fn, ln, frag, line in bucket_examples[b]:
        print(f"    {fn}:{ln}  frag={frag!r}")
        print(f"        {line}")

# Files whose ONLY bucket is X — fixing X fully cleans these files.
print("\n=== SOLE-CAUSE files (fixing that one bucket cleans the file) ===")
sole = collections.Counter()
for fn, bs in file_buckets.items():
    if len(bs) == 1:
        sole[next(iter(bs))] += 1
for b, c in sole.most_common():
    print(f"  {b}: {c} files")
