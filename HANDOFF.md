# Handoff — 2026-07-07

## State
Tree-sitter grammar for KDB+/q, oracle-validated, packaged for use on arbitrary
(incl. proprietary) repos. Parse rate 98.9% on the 90-file real corpus (1 known
failure), 23/23 shape-oracle match vs q's `-3!parse`, corpus tests green.
Pushed to **github.com/arvind-iyer-2001/q-tree-sitter (private)** — clonable,
4-command setup on a fresh machine (see PACKAGING.md).

## Done this session
- Expression-core rewrite on k/q noun-verb model + 5 corpus-driven fix rounds:
  60/90 → 1/90 ERROR files (13c4621..a49a172)
- Shape oracle added and passing 23/23; whitespace-gated NEG token (a0fb101)
- Wheel rebuilt cp314, verified in clean venv (1d847f7)
- Graphify full-corpus rebuild: 3,375 nodes / 5,472 edges / 214 communities,
  hosted at https://arvind-iyer-2001.github.io/q-corpus-graph/
- Packaging: `tools/qgraph.py` (local AST-only pipeline for any repo),
  `tools/patch_graphify.py` (idempotent q-wiring installer), PACKAGING.md
  (762597d, 3356932)
- Repo pushed private; fresh-clone verified; graphify-out untracked

## In progress
- none (session ended at a clean point)

## Open tasks
| # | Task | Priority | Area |
|---|------|----------|------|
| 1 | CI gates workflow (.github/workflows: generate→test→parse_rate→shapes) | high | infra |
| 2 | `/grammar-fix` skill (repro→fix→gates→grow shape oracle→re-bless) | high | skills |
| 3 | `grammar-guard` reviewer agent (checks 8 invariants + runs gates) | med | agents |
| 4 | Release workflow: cibuildwheel matrix on tag | med | infra |
| 5 | `/corpus-add <repo>` skill (clone→test/real→rate→categorize) | med | skills |
| 6 | PostToolUse hook: auto-run patch_graphify.py after graphify upgrade | low | hooks |
| 7 | tick/ssl.q last parse failure (`cond x 40 131 o` in _nn context) | low | grammar |
| 8 | deliverables/*.patch stale vs upstream graphify — only if upstreaming PR | low | deliverables |

Tasks 1–6 = production-readiness plan Arvind approved exploring (order: 1→2→3→4→5→6).

## Constraints & assumptions
- Address user as Arvind; no commit trailers; restate constraints before multi-step refactors (AGENTS.md)
- 8 DO-NOT-BREAK grammar/scanner invariants: `docs/handoffs/2026-07-06-archived.md`
  §Invariants (shared `-` token, `_nn` allows positives, scanner branch order,
  no prev_was_value gating, `/`-family-only token.immediate, LIST_WS before NEG,
  dynamic precs on binary/vector, three regression gates)
- qgraph.py stays AST-only — LLM/semantic extraction on proprietary code only
  via approved channels (PACKAGING.md data-boundary section)
- `test/real/` corpus is gitignored (vendored KX/reQ code) — needs
  `test/real/.graphifyignore` with `!**` for graphify detect; not in the repo,
  re-fetch corpus upstream on new machines
- graphify installed via uv tool; after ANY graphify upgrade rerun
  `python3 tools/patch_graphify.py`
- Python 3.14 only on this machine; wheel is cp314/macOS-arm64
- Inline/sequential execution preferred over agent fan-out (memory), EXCEPT
  graphify skill's extraction subagents (explicitly sanctioned, Sonnet)

## Gotchas
- `uv tool run graphifyy python` no longer resolves interpreter — use
  `uv tool dir` + `graphifyy/bin/python` (fixed in tools/, don't regress)
- graphify honors .gitignore: gitignored corpora detect as 0 files → need
  `.graphifyignore` negation (`!**`) or qgraph `--include-gitignored`
- htmlpreview.github.io can't render HTML with CDN scripts / large files —
  inline vis-network (qgraph `--inline-js`) or use real hosting (Pages)
- githack 403s secret gists; public publishing needs explicit user approval
  (auto-mode classifier blocks `gh repo create --public` / `gh gist --public`)
- tree-sitter parse runaway: ALWAYS `pkill -9 -f 'tree-sitter parse'`, never kill
- Scratchpad is EPHEMERAL — wiped between some turns; put durable work in repo
- `tree-sitter test --update` blesses whatever parses — eyeball diffs before
  committing (a wrong `3-4` shape nearly got blessed this session)

## Commands
- gates: `tree-sitter generate && tree-sitter test && python3 scripts/parse_rate.py test/real/ && python3 scripts/diff_oracle.py --shapes`
- graph any repo: `python3 tools/qgraph.py <path> --inline-js`
- wire graphify: `python3 tools/patch_graphify.py`
- wheel: `python3 -m pip wheel . --no-deps -w dist/`
- oracle needs q at `~/.kx/bin/q` (override: `Q=` env)
