# Packaging: run the q knowledge-graph pipeline on any repository

Three moving parts, all in this repo:

| Part | What | Where |
|---|---|---|
| Parser wheel | tree-sitter-q (oracle-validated, 98.9% real-corpus clean) | `dist/*.whl`, source buildable via `pip wheel .` |
| graphify q-support | `.q` detection + bespoke extractor | `tools/graphify_q/` + `tools/patch_graphify.py` |
| Runner | one-command local pipeline | `tools/qgraph.py` |

## Setup (once per machine, and after every graphify upgrade)

```bash
# 1. graphify itself
uv tool install graphifyy            # or: pip install graphifyy

# 2. wire in q support + parser wheel (idempotent, rerun anytime)
python3 tools/patch_graphify.py
```

The patcher finds graphify's interpreter, registers `.q`, installs the
extractor, and installs the wheel from `dist/` (or builds from source if no
wheel matches your platform/Python).

**Rebuilding the wheel for another platform/Python:**
```bash
python3 -m pip wheel . --no-deps -w dist/
```
Requires a C compiler (parser.c + scanner.c). The grammar is committed as
generated `src/parser.c` — no tree-sitter CLI needed to build the wheel.

## Running on a proprietary repository

```bash
python3 tools/qgraph.py /path/to/private/repo
open /path/to/private/repo/graphify-out/graph.html
```

Flags:
- `--out DIR` — write outputs elsewhere (keep artifacts out of the repo)
- `--include-gitignored` — graph files that .gitignore excludes (graphify
  honors gitignore; vendored/generated q code is often ignored)
- `--inline-js` — embed vis-network into graph.html (air-gapped viewing;
  otherwise the HTML loads one script from unpkg.com when OPENED — the
  graph DATA is always local either way)

## Data-boundary guarantees (read this for proprietary code)

`qgraph.py` is **AST-only**: tree-sitter parses locally, graphify clusters
locally, nothing is transmitted. Explicitly NOT run:

- **Semantic (LLM) extraction** — the full `/graphify` skill sends doc/code
  content to a model. On proprietary repos, only do this via a channel your
  org approves (internal endpoint, Bedrock/Vertex tenancy, etc). The skill's
  Gemini path reads `GEMINI_API_KEY`; the Claude path runs through Claude
  Code subagents. Both TRANSMIT file content.
- **Hosting** — nothing is uploaded. The gist/Pages flows used for the demo
  corpus are manual, separate steps. Do not run them on private graphs.
- The one network touch: `--inline-js` fetches the vis-network LIBRARY
  (not your data) from unpkg once. Skip the flag and copy the lib manually
  for fully offline setups.

## Known limits

- Parse rate benchmarked at 98.9% on 90 real-world files (KX cookbook, kdb,
  reQ). Remaining known gap: one `cond x 40 131 o`-style construct
  (`HANDOFF_2026-07-06.md` → Open Items).
- `.k` files parse via the q grammar only where dialects overlap; heavy
  k-idiom files degrade to partial extraction (`k)` lines are opaque tokens).
- Wheel in `dist/` is cp314/macOS-arm64. Other targets: rebuild from source
  (see above).
- After `uv tool upgrade graphifyy`, RERUN `tools/patch_graphify.py` —
  upgrades wipe site-packages edits. The patcher fails loudly with a clear
  message if upstream's layout drifts beyond its anchors.

## Corpus expansion workflow

New q repos → drop under any directory → `qgraph.py` it. To also use them
as PARSER regression tests: copy into `test/real/`, run
`python3 scripts/parse_rate.py test/real/` (floor 3%), fix grammar gaps via
`scripts/categorize_errors.py` + `scripts/diff_oracle.py --shapes`.
