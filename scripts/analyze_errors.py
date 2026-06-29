# scripts/analyze_errors.py — tally the source text under ERROR/MISSING nodes
# across the real corpus, to prioritise which grammar constructs to fix next.
import os, re, signal, subprocess, pathlib, collections

root = pathlib.Path("test/real")
qfiles = sorted(root.rglob("*.q"))
node_re = re.compile(r'\((ERROR|MISSING)\s+\[(\d+),\s*(\d+)\]\s*-\s*\[(\d+),\s*(\d+)\]')

samples = collections.Counter()
per_file_first = []

for f in qfiles:
    try:
        p = subprocess.Popen(["tree-sitter","parse",str(f)],
                             stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                             text=True, start_new_session=True)
        try:
            out,_ = p.communicate(timeout=15)
        except subprocess.TimeoutExpired:
            os.killpg(os.getpgid(p.pid), signal.SIGKILL); p.communicate(); continue
    except Exception:
        continue
    src = f.read_text(errors="replace").splitlines()
    first = None
    for m in node_re.finditer(out):
        r0,c0,r1,c1 = map(int, m.groups()[1:])
        if r0 < len(src):
            line = src[r0]
            frag = line[c0:c1] if r0==r1 else line[c0:c0+40]
            frag = frag.strip()
            if not frag:
                frag = line.strip()[:40]
            if first is None:
                first = (str(f), r0+1, line.strip()[:70])
            # normalise fragment to a coarse construct key
            samples[frag[:24]] += 1
    if first:
        per_file_first.append(first)

print("=== TOP ERROR FRAGMENTS (count) ===")
for frag,c in samples.most_common(30):
    print(f"{c:4d}  {frag!r}")
print("\n=== FIRST ERROR PER FILE (first 40) ===")
for fn,ln,txt in per_file_first[:40]:
    print(f"{fn}:{ln}: {txt}")
