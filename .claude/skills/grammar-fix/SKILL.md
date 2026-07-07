---
name: grammar-fix
description: Fix a q construct the grammar mishandles (ERROR node or wrong tree shape). Use when a snippet or corpus file parses wrong — encodes the repro→fix→gates→grow-oracle loop that took the parser from 33% to 98.9%.
---

# /grammar-fix <snippet or file path>

Fix ONE grammar/scanner defect end to end. Never skip a numbered step — each
exists because skipping it shipped a regression at least once.

## 0. Constraints (restate before touching anything)

Read the invariants section of the newest handoff (`HANDOFF.md` or
`docs/handoffs/*`). The non-negotiables:
- `-` stays ONE anonymous token shared by operator + negative-number rules
- `_nn` family blocks only LEADING negatives in juxt args (positives legal)
- scanner: EOS-before-comment order; comment branch skips newlines itself;
  continuation check falls through (no early `return false`)
- never gate scanner tokens on unknowable left context (prev_was_value class)
- only the `/` iterator family is `token.immediate`
- `prec.dynamic`: binary/binary_nn=1, vector=2, source_file separators=1

If a fix seems to require breaking one of these, STOP and discuss.

## 1. Minimal repro

Reduce the input to the smallest failing form. Then build the A/B matrix —
the same construct in ALL of these contexts (context-dependence is the #1
q-grammar failure mode):
```
<expr>                 # top level
f:{<expr>}             # inside lambda
a[x;<expr>]            # argument slot
$[c;<expr>;0]          # cond branch
r:<expr>               # assignment right
```
Record which contexts fail. `tree-sitter parse` each; keep the trees.

## 2. Diagnose

- ERROR at a token the lexer should not have chosen → suspect token-type
  collision (two token defs matching same text) or scanner branch order.
- Parses top-level, fails inside brackets → GLR fork dies under tighter
  follow-set; the "passing" parse may be an accident — check its SHAPE too.
- Wrong shape, no ERROR → missing conflict entry or wrong prec.dynamic.
- Scanner suspects: `tree-sitter parse --debug` and read `lex_external`
  lines; external valid-sets per state are in `src/parser.c`
  (`ts_external_scanner_states`).

## 3. Fix

Prefer, in order: grammar rule change → conflict entry + prec.dynamic →
scanner change. Scanner changes need the invariants check (step 0) TWICE.
Iterate `tree-sitter generate` until zero `Unresolved conflict` blocks;
add conflict entries the generator names, but comment WHY each exists.

## 4. Gates (all four, in this order)

```bash
tree-sitter generate                          # clean
tree-sitter test                              # corpus 0 failures
python3 scripts/parse_rate.py test/real/      # floor 3%, must not regress
python3 scripts/diff_oracle.py --shapes       # 23+/23+ — see step 5
```
Corpus failures that are SHAPE diffs: eyeball every diff before
`tree-sitter test --update` — a wrong shape nearly got blessed once
(`3-4` as call). Never bulk-bless.

## 5. Grow the shape oracle (mandatory)

Add the fixed construct to `SHAPE_CASES` in `scripts/diff_oracle.py` with the
expected top node, derived from the real q oracle:
```bash
echo '-3!parse "<construct>"' | ~/.kx/bin/q   # ground truth
```
A fix without a new oracle case is not done — that's how regressions return.

## 6. Finish

Commit grammar + scanner + corpus + oracle together, message explains the
construct and the mechanism (not just "fix X"). Run `/grammar-guard` (agent)
on the diff if the change touched scanner.c or conflict entries.
