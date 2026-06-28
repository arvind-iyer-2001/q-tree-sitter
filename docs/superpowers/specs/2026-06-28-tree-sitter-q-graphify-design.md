# Design: Tree-sitter grammar for KDB+/q + Graphify integration

**Date:** 2026-06-28
**Status:** Approved (brainstorming complete)
**Owner:** Arvind Iyer

## Goal

Make `.q` (KDB+/q) source files parseable and analyzable by [Graphify](https://github.com/safishamsi/graphify). Graphify's static analysis is driven by Tree-sitter, and no mature q grammar exists. We build a comprehensive, compilable Tree-sitter grammar for q, package it as a Python wheel exposing `language()`, and wire it into Graphify so q files produce nodes/edges (functions, calls, namespaces, imports, tables).

## Scope & decisions

- **Deliverable scope:** Grammar **and** Graphify integration (end-to-end: q files parse and extract in Graphify).
- **Fidelity:** Comprehensive q — full operator/adverb set, q-SQL, control words, literal zoo, namespaces, right-to-left semantics. k-dialect fragments tolerated as opaque, not first-class.
- **Validation corpus:** Real-world public q repositories plus hand-written edge-case fixtures.
- **Done criteria:** Full pipeline — grammar compiles, corpus tests pass, wheel installs into a Graphify venv, and Graphify extracts nodes/edges from real `.q` files (verified against golden output).

## How Graphify consumes a grammar (constraints we must satisfy)

From analysis of the Graphify codebase:

- Graphify is **Python**. It uses the PyPI `tree-sitter` runtime (`>=0.23,<0.26`) plus per-language native grammar **wheels** named `tree_sitter_<lang>`. No WASM, no Node bindings, no Tree-sitter CLI at runtime.
- Grammar load mechanism (`graphify/extract.py:2366-2391`): `importlib.import_module(config.ts_module)` then `Language(mod.language())` then `Parser(language)`. **Our wheel must expose `tree_sitter_q.language()`.**
- Graphify does **not** use `.scm` query files. It walks the AST manually: recursive `walk(node)` comparing `node.type` against string sets, reading children via `node.child_by_field_name(...)`. **So our grammar must emit stable, predictable node `type` strings and field names.**
- Two ways to add a language: (a) a table-driven `LanguageConfig` dataclass (`extract.py:434-476`), or (b) a bespoke `extract_<lang>` in `graphify/extractors/`. q requires **bespoke** because a q "function" is not a dedicated node — it is an assignment whose right-hand side is a lambda, which the table-driven `name_field`/`body_field` model cannot express.
- Registration points: `pyproject.toml` deps; `graphify/extractors/__init__.py` `LANGUAGE_EXTRACTORS`; `graphify/extract.py` `_DISPATCH` suffix map; `graphify/detect.py:30` `CODE_EXTENSIONS`; `graphify/watch.py:199` `_WATCHED_EXTENSIONS`.

## Why q is hard (problems the design must solve)

1. **Whitespace is semantic.** `1 - 2` (subtract) vs `1 -2` (two-item list) vs `f -1` (apply to negative). Requires an external scanner.
2. **No precedence, strict right-to-left evaluation.** `2*3+4` = 14. All verbs same precedence, right-associative. Expression grammar is a right fold.
3. **Overloaded glyphs / valence.** `- # $ . @ !` are monadic or dyadic by context. Grammar parses structure only; valence left to semantics.
4. **Adverbs** `/ \ ': /: \: '` applied postfix to verbs (`+/`, `,/:`).
5. **Comments collide with operators.** `/` is division, adverb, and comment (space-preceded or line-start). Block comments `/`…`\`, trailing comments, final `\`-to-EOF block. Requires external scanner.
6. **System/backslash commands.** `\l f.q`, `\d .ns`, `\ts`, line-start, own syntax.
7. **q-SQL DSL.** `select…by…from…where…`, `update`, `delete`, `exec` clause forms.
8. **Functions are anonymous lambdas assigned to names.** `f:{[a;b]a+b}`. Namespaces via `.ns.f:…` and `\d .ns`.
9. **Dense literal zoo.** dates/times/timestamps/timespans/months/minute/second/datetime, typed numbers (`1j 1i 1h 1f 1e 0x01 1b`), nulls/infinities (`0N 0W 0n 0w`), symbols `` `a`b`c ``, `` `:path:port ``, bool vectors `0101b`, strings/chars.

## Chosen approach: A — External-scanner GLR grammar + bespoke Graphify extractor

Rejected alternatives:
- **B (pure grammar.js + LanguageConfig):** cannot handle whitespace semantics or `/` comments, and the table model cannot express function-as-assignment-to-lambda.
- **C (minimal extractor-oriented grammar, opaque bodies):** insufficient for "comprehensive." Retained only as a per-subtree fallback when a construct blocks full parsing.

## Architecture

### Repo layout (`/Users/arvindiyer/development/q-tree-sitter`)

```
tree-sitter-q/
  grammar.js
  src/parser.c            # generated, committed (install needs clang only, no node)
  src/scanner.c           # hand-written external scanner
  src/tree_sitter/parser.h
  bindings/python/tree_sitter_q/__init__.py   # exposes language()
  bindings/python/tree_sitter_q/__init__.pyi
  bindings/{node,rust,c}/ # scaffolded, low effort
  queries/tags.scm        # hygiene only; Graphify ignores
  test/corpus/*.txt       # input -> expected tree
  test/real/              # cloned real-world q repos (gitignored)
  pyproject.toml          # setuptools builds native extension
  package.json            # tree-sitter CLI config
```

### External scanner (`scanner.c`) tokens

- `COMMENT` — trailing `/ …` (space/line-start preceded), block `/`…`\`, whole-line `/`, final `\`-to-EOF block.
- `SYSTEM_COMMAND` — line-start `\` + command (`\l \d \ts \c \p \x …`).
- `NEG_NUMBER` vs `MINUS` — disambiguate negative literal from subtraction verb via leading whitespace + preceding-token class.
- `LIST_WS` — significant whitespace forming vectors (`1 2 3`, `` `a`b`c ``).
- `ADVERB` — `/ \ ': /: \:` when post-verb (not comment/division).
- `END_OF_STMT` — top-level newline that is not a continuation; suppressed inside `{} [] ()`.
- String/symbol edge tokens where grammar regex is insufficient (`` `:path:port ``, multiline strings).

Scanner state: bracket-depth counter; previous-token class (for valence and negative-number disambiguation).

### Grammar node taxonomy (consumed by extractor)

- `assignment` — fields: `left`, `operator` (`:`/`::`), `right`. **Core: function defs.**
- `lambda` — fields: `parameters` (optional `[a;b]`), `body`. Implicit args `x y z` when no list.
- `parameters`, `param`.
- `call` — fields: `function`, `arguments`. Covers `f[a;b]`, juxtaposition `f x`, `.[f;args]`.
- q-SQL: `select_statement`, `exec_statement`, `update_statement`, `delete_statement`; clause children `select_clause`, `by_clause`, `from_clause`, `where_clause`.
- `control` — `$[c;t;f]`, `if`, `do`, `while`, `:` (return), `'` (signal).
- `system_command` — fields: `command`, `argument`.
- `namespace_directive` — `\d .ns`.
- Identifiers: `identifier`, `dotted_name` (`.foo.bar`), `builtin` (reserved words, `.Q.`, `.z.`).
- Literals: `number`, typed numbers, `boolean`, `byte`, temporal types, `symbol`, `symbol_vector`, `string`, `char`, `null`, `infinity`, `vector`.
- Structure: `parenthesized`, `list` (`(a;b;c)`), `table_literal` (`([k]c:…)`).

### Graphify extractor (`graphify/extractors/q.py`, bespoke)

Emits Graphify nodes/edges:
- **function** node ← `assignment` whose `right` is `lambda`; name = `left`, qualified by current `\d` namespace + dotted prefix.
- **variable/global** node ← `assignment` with non-lambda right (tables, vars).
- **namespace** node ← `\d .ns`.
- **contains** edge: file → function/var; namespace → function.
- **calls** edge: within lambda body, each resolved `call`/juxtaposition → caller→callee (cross-file `INFERRED`).
- **imports** edge: `\l file.q` and `system"l file.q"` → file→file load dependency.
- **uses** edge: q-SQL `from_clause` table refs → function→table.

Registration (5 points): `pyproject.toml` (`[q]` extra dep on `tree-sitter-q`); `extractors/q.py`; `extractors/__init__.py` `LANGUAGE_EXTRACTORS`; `extract.py` `_DISPATCH` (`".q": extract_q`); `detect.py:30` `CODE_EXTENSIONS` + `watch.py:199` `_WATCHED_EXTENSIONS` add `.q`.

Integration delivered as a **git patch/diff** against the cloned Graphify, validated in a local venv.

### Build / packaging

- Install tree-sitter CLI: `npm i -g tree-sitter-cli`.
- `tree-sitter generate` → `src/parser.c` (committed).
- `tree-sitter test` runs corpus tests.
- `uv build` / `pip install .` compiles the native extension via clang → importable `tree_sitter_q`.
- End-to-end: fresh venv, `pip install ./tree-sitter-q` + Graphify, run `graphify` on real `.q` files, inspect node/edge JSON.

## Test plan

1. **Corpus tests** (`test/corpus/`): input→expected-tree for each construct — lambdas, q-SQL, adverbs, every literal type, comments, system commands, RTL precedence, whitespace cases (`1 -2` vs `1 - 2`).
2. **Real-repo parse-rate:** clone `KxSystems/kdb`, `KxSystems/funq`, `qutil`, embedPy examples; assert ERROR-node rate below threshold (**target: <2% of files contain ERROR nodes**); track per file; failures feed grammar/scanner fixes (loop until dry).
3. **q oracle:** use the local `q` binary (`~/.kx/bin/q`) + q-run skill to confirm tricky snippets are valid q, so tests check real semantics.
4. **Graphify e2e:** run installed Graphify on fixtures; assert it emits function/call/namespace/import nodes for known inputs (golden output comparison).

## Risks & mitigations

- **RTL expression + juxtaposition application** is the hardest part; GLR conflicts expected. Mitigation: external scanner pre-resolves valence; accept structurally-valid-but-semantically-loose trees; degrade a blocking subtree to opaque token-soup (Option C) rather than fail the whole parse.
- **k-dialect fragments** in `.q` files: out of scope; tolerated as opaque.
- **Python 3.14 build env:** use a dedicated venv; pin compatible `tree-sitter` runtime.

## Acceptance

- `tree-sitter generate` + `tree-sitter test` pass.
- Real-repo parse-rate meets <2% ERROR-file threshold.
- `tree_sitter_q` wheel installs and `language()` loads in a Graphify venv.
- Graphify produces expected function/call/namespace/import nodes on golden fixtures.

## Out of scope

- Full k-dialect grammar.
- Editor highlighting beyond a courtesy `tags.scm`.
- Upstream PR merge to Graphify (we deliver a reviewable patch; submission is the user's call).
