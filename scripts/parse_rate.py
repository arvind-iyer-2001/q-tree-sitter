# scripts/parse_rate.py
# Crash-safe parse-rate harness for the real-repo corpus under test/real/.
# Each file is parsed in its OWN process group with a hard timeout; on timeout
# the whole group is killed (tree-sitter CLI reparents to init otherwise and
# keeps looping at 99% CPU, eating swap — that is what crashed the laptop).
import os
import signal
import subprocess
import sys
import pathlib

# TARGET is the eventual quality bar (<2% of files with ERROR nodes). FLOOR is
# the current regression gate: the grammar is at ~70% bad on this real-world
# corpus today, so CI fails only on a REGRESSION past FLOOR. Drive FLOOR down
# toward TARGET as grammar modules gain coverage (see scripts/PARSE_FAILURES.md
# for the remaining failing constructs). Lower FLOOR whenever the rate improves.
TARGET = 0.02
FLOOR = 0.03          # regression gate — 1/90 (1.1%) after the 2026-07-05 rewrite
THRESHOLD = FLOOR     # CI uses FLOOR; flip to TARGET once coverage reaches it
TIMEOUT = 15          # seconds per file; a hang here means a parser bug

root = pathlib.Path("test/real")
qfiles = sorted(root.rglob("*.q"))

errors = []    # files whose parse tree contains ERROR / MISSING nodes
timeouts = []  # files that hung (parser pathology) — counted as failures
crashed = []   # non-zero exit, no usable output

for f in qfiles:
    try:
        p = subprocess.Popen(
            ["tree-sitter", "parse", str(f)],
            stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
            text=True, start_new_session=True,  # own process group
        )
        try:
            out, _ = p.communicate(timeout=TIMEOUT)
        except subprocess.TimeoutExpired:
            os.killpg(os.getpgid(p.pid), signal.SIGKILL)  # kill the whole group
            p.communicate()
            timeouts.append(str(f))
            continue
    except Exception as e:
        crashed.append((str(f), str(e)))
        continue

    if "ERROR" in out or "MISSING" in out:
        errors.append(str(f))
    elif p.returncode not in (0,):
        crashed.append((str(f), f"exit={p.returncode}"))

bad = errors + timeouts + [c[0] for c in crashed]
n = len(qfiles)
rate = len(bad) / n if n else 1.0
print(f"files={n} errors={len(errors)} timeouts={len(timeouts)} crashed={len(crashed)} bad={len(bad)} rate={rate:.3%}")
for b in errors[:50]:
    print("  ERROR:  ", b)
for b in timeouts:
    print("  TIMEOUT:", b)
for b, why in crashed:
    print("  CRASH:  ", b, why)

# Write the failure report
report = pathlib.Path("scripts/PARSE_FAILURES.md")
lines = [
    "# Real-repo parse failures",
    "",
    f"Corpus: {n} `.q` files under `test/real/`. "
    f"Target <{TARGET:.0%} bad; current regression floor <{FLOOR:.0%}.",
    f"Result: **{rate:.2%}** bad ({len(bad)}/{n}) — "
    + ("PASS (floor)" if rate <= FLOOR else "FAIL (regressed)") + ". "
    + f"Gap to target: {max(0.0, rate - TARGET):.0%}.",
    "",
    f"- ERROR-node files: {len(errors)}",
    f"- Timeouts (parser hang): {len(timeouts)}",
    f"- Crashes (non-zero exit): {len(crashed)}",
    "",
    "## ERROR-node files",
    "",
]
lines += [f"- `{b}`" for b in errors] or ["- (none)"]
lines += ["", "## Timeouts", ""]
lines += [f"- `{b}`" for b in timeouts] or ["- (none)"]
lines += ["", "## Crashes", ""]
lines += [f"- `{b}` — {why}" for b, why in crashed] or ["- (none)"]
report.write_text("\n".join(lines) + "\n")
print(f"wrote {report}")

sys.exit(0 if rate <= THRESHOLD else 1)
