# scripts/parse_rate.py
import subprocess, sys, pathlib
THRESHOLD = 0.02  # <2% of files may contain ERROR nodes
root = pathlib.Path("test/real")
qfiles = list(root.rglob("*.q"))
bad = []
for f in qfiles:
    out = subprocess.run(["tree-sitter","parse",str(f)], capture_output=True, text=True)
    if "ERROR" in out.stdout or out.returncode not in (0,):
        bad.append(str(f))
rate = len(bad)/len(qfiles) if qfiles else 1.0
print(f"files={len(qfiles)} errors={len(bad)} rate={rate:.3%}")
for b in bad[:50]: print("  ERROR:", b)
sys.exit(0 if rate <= THRESHOLD else 1)
