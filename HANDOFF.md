# Handoff — 2026-07-09

## Environment (THIS machine: WSL2 Ubuntu, linux/amd64 — differs from the Mac handoff)
- tree-sitter CLI 0.24.7 via npm global (`npm i -g tree-sitter-cli@0.24.7`)
- q at `~/.kx/bin/q` — oracle works
- wheel: `dist/tree_sitter_q-0.1.0-cp310-cp310-linux_x86_64.whl` (system python 3.10)
- graphify: **pip install in python3.10 user site** (`/home/aiyer/.local/lib/python3.10/site-packages/graphify`),
  NOT the uv tool — `uv tool install graphifyy` collides with the existing
  `graphify` executable. `tools/patch_graphify.py` targets `/usr/bin/python3`
  and works; tree_sitter_q installed with `pip install --user` (uv pip hits
  /usr/local permission error)
- this graphify version has NO `export` command → qgraph falls back to
  `tools/qgraph_html.py` (community overview → graph.html + graph-hubs.html)
- pypdf 6.x present (needed by the new doc extractor)
- `test/real/` re-fetched (cookbook/kdb/reQ), gates green:
  97/97 corpus tests, 89/90 parse rate (known: tick/ssl.q), 23/23 shapes

## What this session was
Ran the parser + graphify against the real KX Sensors codebase
(`~/kxs-graphify/kxs-v3`, 18 repos, ~230k lines q) and iteratively fixed the
extraction pipeline until the graph answers architecture questions.

Working corpus: `~/kxs-graphify/corpus-core-amat/` = kxs-core + kxs-amat +
runbook PDFs (copies, no .git). Output in its `graphify-out/`
(16,808 nodes / 45,435 edges / 274 communities). Rebuild:
`python3 tools/qgraph.py ~/kxs-graphify/corpus-core-amat --inline-js`

## Done this session (commit 11e5f0d + this one)
- Extractor v2: junk callee nodes 9,225→0, typed defs (function/variable/
  table/file/external), compound-assign → `modifies`, per-node ERROR gate
- qgraph: stub→def merge (src>test), namespace hubs, HTML fallback
- NEW local doc pipeline (`tools/graphify_q/docs.py`): PDFs/markdown →
  doc-section nodes with text + `mentions` edges to code. Picked up both the
  runbook PDFs AND kxs-core's own `docs/content/*.md`
- Acceptance: "What is the RT?" answered from graph (rt.md text + .rt.pub/
  .rt.sub externals wrapped in src/msg/ems.q). Data-flow mermaid derived
  from graph verified vs runbook `01_Architectural_Overview.pdf` (~80%
  right; wrong: GW→RP shape, ems↔sp bidirectionality, SM/RDB/HDB missing —
  process-level info, not in static call graph)
- parse_rate.py takes corpus root argv; kxs-v3 sweep: 154/689 files bad
  (22.35%), buckets in `~/kxs-graphify/ERROR_BUCKETS_kxs-v3.txt` and
  `~/kxs-graphify/PARSE_FAILURES_kxs-v3.md` (do NOT commit those — client paths)

## Open tasks
| # | Task | Priority | Area |
|---|------|----------|------|
| 1 | Grammar fixes for kxs failure buckets: each-tick compose `('[f;g])` 48 files, `//` line-start comment 18, brace-close 30 — use /grammar-fix, re-run kxs sweep after each | high | grammar |
| 2 | Graph explorer UI over graph.json (file → defs → calls → file:line, doc text on click) — Arvind's main pain: data good, graph.html doesn't show drill-down. Discussed morale-level 2026-07-09; build this BEFORE more pipeline work | high | tooling |
| 3 | Process-topology layer: GW→RP→services shape, RDB/HDB roles — needs config/bootstrap extraction, static calls can't see it | med | extraction |
| 4 | tick/ssl.q last public-corpus failure | low | grammar |
| 5 | Tag v0.1.0 (release.yml untested) | med | infra |
| 6 | Upstream candidate: dedup-prefer-definitions patch for graphify build.py | low | deliverables |

## Constraints & assumptions
- All prior invariants hold (docs/handoffs/2026-07-06-archived.md §Invariants)
- kxs corpora are PROPRIETARY: live outside repo, never committed; extraction
  local/AST-only; runbook PDFs were read in-session (sanctioned) but graphify
  semantic/LLM extraction still needs explicit approval (PACKAGING.md)
- scripts/PARSE_FAILURES.md is overwritten by every parse_rate run — restore
  via `git checkout` before committing if a proprietary sweep ran last
- after ANY graphify change rerun `python3 tools/patch_graphify.py`
  (installs extractors/{base,q,docs}.py)

## Gotchas (new, beyond archived list)
- graph.json edges: undirected serialization flips source/target — ALWAYS
  read `_src`/`_tgt` for direction
- wheel grammar emits `operator` field for plain `:` assignments (CLI parse
  of `b:1` doesn't) — never gate on field presence, check operator text
- q builtin whitelist lives in q.py `_Q_BUILTINS`; kxs aliases (enl, nnull)
  are NOT builtins — they're defined in gen.q and must stay resolvable
- doc mention regex catches URL fragments (`.docker.com`) — resolution layer
  drops unmatched dotted tokens, keep it that way
- graphify viz cap 5,000 nodes (`MAX_NODES_FOR_VIZ`), watch.py silently
  deletes stale graph.html above it

## Commands
- gates: `tree-sitter generate && tree-sitter test && python3 scripts/parse_rate.py test/real/ && python3 scripts/diff_oracle.py --shapes`
- kxs sweep: `python3 scripts/parse_rate.py /home/aiyer/kxs-graphify/kxs-v3`
  then `python3 scripts/categorize_errors.py /home/aiyer/kxs-graphify/kxs-v3`
- rebuild kxs graph: `python3 tools/qgraph.py ~/kxs-graphify/corpus-core-amat --inline-js`
- query graph: `graphify query "..." --graph ~/kxs-graphify/corpus-core-amat/graphify-out/graph.json`
  or `python3 ~/.claude/skills/graph-query/scripts/query.py <term> --dir ~/kxs-graphify/corpus-core-amat/graphify-out`
