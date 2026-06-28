# Tree-sitter q + Graphify Integration — Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build a comprehensive, compilable Tree-sitter grammar for KDB+/q and wire it into Graphify so `.q` files extract functions, calls, namespaces, imports, and tables.

**Architecture:** A modular `grammar.js` (one file per construct, merged via `Object.assign`) plus a hand-written external `scanner.c` for q's whitespace-sensitive and comment/operator-ambiguous tokens. The grammar is packaged as a Python wheel exposing `tree_sitter_q.language()`. Graphify consumes it through a bespoke `graphify/extractors/q.py` (q functions are assignments-to-lambdas, which the table-driven `LanguageConfig` cannot model). All grammar/scanner authoring is grounded in authoritative reference data mined from `KxSystems/docs` into `references/`.

**Tech Stack:** Tree-sitter CLI (Node), C (scanner + generated parser), Python 3 + setuptools (wheel), `tree-sitter` PyPI runtime, Graphify (Python).

## Global Constraints

- Grammar repo root: `/Users/arvindiyer/development/q-tree-sitter`.
- Cloned Graphify (for integration + tests): `/private/tmp/claude-502/-Users-arvindiyer-development-q-tree-sitter/9aa969c1-ee08-462a-a23f-252fb708671c/scratchpad/graphify`.
- KX docs reference data (authoritative spec for grammar): `references/{keywords,operators,datatypes,qsql,syntax}.md`. **Every grammar/scanner task MUST source forms from these, not from memory.**
- Python binding module name MUST be `tree_sitter_q`, exposing `language()` returning a `PyCapsule`/int usable by `tree_sitter.Language(...)`.
- Node `type` strings and field names MUST match the taxonomy in this plan exactly (Graphify walks them literally).
- `tree-sitter` runtime pin compatible with Graphify: `>=0.23,<0.26`.
- Commit `src/parser.c` (generated) so install needs clang only, not Node.
- Commit messages: NO `Co-Authored-By` / attribution trailers (per `AGENTS.md`).
- Address the user as Arvind in all interactive output.

---

## Parallel Execution Map (multi-agent workflow)

Tasks are grouped into **waves**. Within a wave, every task is independent (distinct files, no shared state) and MUST run concurrently. Waves are barriers: wave N+1 starts only after all wave-N tasks pass review.

| Wave | Tasks | Concurrency | Isolation | Depends on |
|------|-------|-------------|-----------|------------|
| 0 — Foundation | T1 | single agent (blocks all) | main | — |
| 1 — Grammar+Scanner | T2,T3,T4,T5,T6,T7,T8,T9 | **8 agents in parallel** | one git worktree per task | T1 |
| 2 — Convergence | T10 | single agent (merge barrier) | main | all of wave 1 |
| 3 — Package/Extract/Corpus | T11,T12,T13 | **3 agents in parallel** | worktree per task | T10 |
| 4 — Wire + E2E | T14, T15 | T14 then T15 (sequential) | main | T11,T12,T13 |

**Why this is safe to parallelize:** T1 produces a *compiling skeleton* — `grammar.js` declares every rule name and every external token, with stub bodies, so `tree-sitter generate` succeeds. Each wave-1 task fills exactly one file (`scanner.c` OR one `grammar/<x>.js`) plus its own `test/corpus/<x>.txt`. No two wave-1 tasks write the same file. The only shared rule, `_expression`, is owned solely by T6; all other modules merely *reference* `$._expression` (resolved at merge in T10).

**Workflow orchestration sketch** (for the Workflow tool):

```js
// Wave 0
await agent(T1_prompt)                               // foundation, blocks
// Wave 1 — fan out, worktree isolation
await parallel([T2,T3,T4,T5,T6,T7,T8,T9].map(t =>
  () => agent(t.prompt, {isolation:'worktree'})))
// Wave 2 — merge barrier
await agent(T10_prompt)                              // generate + resolve conflicts
// Wave 3 — fan out
await parallel([T11,T12,T13].map(t =>
  () => agent(t.prompt, {isolation:'worktree'})))
// Wave 4 — sequential
await agent(T14_prompt); await agent(T15_prompt)
```

---

## File Structure

```
tree-sitter-q/
  grammar.js                       # T1: merges modules, declares externals + conflicts
  grammar/
    literals.js                    # T3: number/temporal/symbol/string/byte/bool literals
    identifiers.js                 # T4: identifier, dotted_name, builtin, symbol vectors
    functions.js                   # T5: lambda, parameters, param, assignment
    expression.js                  # T6: _expression (RTL), call, apply, index, adverb, list
    qsql.js                        # T7: select/exec/update/delete + clauses
    control.js                     # T8: cond $[], if/do/while, return, signal
    commands.js                    # T9: system_command, namespace_directive
  src/
    parser.c                       # generated (T10), committed
    scanner.c                      # T2: external scanner
    tree_sitter/parser.h           # T1 (scaffold)
  bindings/python/tree_sitter_q/
    __init__.py                    # T1: exposes language()
    __init__.pyi                   # T1
    binding.c                      # T1
  test/corpus/
    literals.txt control.txt ...   # one per wave-1 grammar task
  test/real/                       # T13: cloned real q repos (gitignored)
  scripts/parse_rate.py            # T13: ERROR-node rate harness
  pyproject.toml                   # T1: setuptools native build
  package.json tree-sitter.json    # T1: tree-sitter CLI config
  references/*.md                  # already committed (authoritative spec)

# In cloned Graphify (delivered as a patch):
  graphify/extractors/q.py         # T12
  graphify/extractors/__init__.py  # T14: register
  graphify/extract.py              # T14: _DISPATCH
  graphify/detect.py               # T14: CODE_EXTENSIONS
  graphify/watch.py                # T14: _WATCHED_EXTENSIONS
  pyproject.toml                   # T14: [q] extra
```

### Node taxonomy contract (frozen in T1, consumed by T12)

| node `type` | fields | meaning |
|---|---|---|
| `source_file` | — | root |
| `assignment` | `left`, `operator`, `right` | `:`/`::`; **function def when `right` is `lambda`** |
| `lambda` | `parameters?`, `body` | `{[a;b]…}` |
| `parameters` / `param` | — | `[a;b]` |
| `call` | `function`, `arguments` | `f[a;b]`, `f x`, `.[f;a]` |
| `index` | `function`, `arguments` | bracket application alias |
| `select_statement`/`exec_statement`/`update_statement`/`delete_statement` | `from`, `where?`, `by?`, `select?` | q-SQL |
| `from_clause`/`where_clause`/`by_clause`/`select_clause` | — | q-SQL clauses |
| `cond` | — | `$[c;t;f]` |
| `control` | `keyword` | `if`/`do`/`while` |
| `system_command` | `command`, `argument?` | `\l f.q`, `\ts` |
| `namespace_directive` | `namespace?` | `\d .ns` |
| `identifier` / `dotted_name` / `builtin` | — | names |
| `symbol` / `symbol_vector` / `string` / `char` | — | atoms |
| `number` / `boolean` / `byte` / `vector` | — | numerics |
| `timestamp`/`date`/`month`/`time`/`minute`/`second`/`timespan`/`datetime` | — | temporal |
| `null` / `infinity` | — | special atoms |
| `parenthesized` / `list` / `table_literal` | — | structure |
| `comment` | — | external token |

---

### Task 1: Foundation — compiling skeleton + frozen interfaces

**Wave 0. Single agent. Blocks everything. Runs on `main`.**

**Files:**
- Create: `package.json`, `tree-sitter.json`, `grammar.js`, `grammar/{literals,identifiers,functions,expression,qsql,control,commands}.js`, `src/scanner.c`, `bindings/python/tree_sitter_q/{__init__.py,__init__.pyi,binding.c}`, `pyproject.toml`
- Test: `test/corpus/skeleton.txt`

**Interfaces:**
- Produces: the complete rule-name set, the `externals` token list, the node taxonomy table above, and a parser that `tree-sitter generate && tree-sitter test` passes with stub rules. Every later task codes against these names.

- [ ] **Step 1: Install tree-sitter CLI**

Run: `npm i -g tree-sitter-cli@^0.24 && tree-sitter --version`
Expected: prints `tree-sitter 0.24.x`

- [ ] **Step 2: Write `package.json` + `tree-sitter.json`**

```json
// package.json
{
  "name": "tree-sitter-q",
  "version": "0.1.0",
  "description": "Tree-sitter grammar for the KDB+/q language",
  "main": "bindings/node",
  "devDependencies": { "tree-sitter-cli": "^0.24.0" },
  "scripts": { "generate": "tree-sitter generate", "test": "tree-sitter test" }
}
```
```json
// tree-sitter.json
{ "grammar": { "name": "q", "scope": "source.q", "file-types": ["q"] } }
```

- [ ] **Step 3: Write the modular skeleton `grammar.js` (declares externals, conflicts, merges modules, stub `source_file`)**

```js
const literals    = require('./grammar/literals.js');
const identifiers = require('./grammar/identifiers.js');
const functions   = require('./grammar/functions.js');
const expression  = require('./grammar/expression.js');
const qsql        = require('./grammar/qsql.js');
const control     = require('./grammar/control.js');
const commands    = require('./grammar/commands.js');

module.exports = grammar({
  name: 'q',

  // External scanner tokens (implemented in src/scanner.c — see Task 2)
  externals: $ => [
    $.comment,
    $._system_command_tok,   // line-start backslash command line
    $._neg_number,           // negative numeric literal (whitespace-sensitive)
    $._list_ws,              // significant separator inside a vector
    $._adverb_tok,           // postfix iterator glyph
    $._eos,                  // top-level statement terminator (newline, not continuation)
    $._error_sentinel,       // never emitted; forces external-scanner fallback
  ],

  extras: $ => [/[ \t]/, $.comment],   // spaces handled; newlines are significant via _eos

  // GLR conflicts are added here by Task 10 as real ambiguities surface.
  conflicts: $ => [],

  word: $ => $.identifier,

  rules: Object.assign(
    {
      source_file: $ => repeat(seq($._statement, optional($._eos))),

      // _statement and _expression are the shared backbone. _expression is
      // OWNED by expression.js (Task 6); declared here only as the entry alias.
      _statement: $ => choice(
        $.assignment,
        $.system_command,
        $.namespace_directive,
        $._expression,
      ),
    },
    literals,
    identifiers,
    functions,
    expression,
    qsql,
    control,
    commands,
  ),
});
```

- [ ] **Step 4: Write stub module files so generate succeeds**

Each module exports an object of rule-functions. Stubs are minimal but valid; wave-1 tasks replace the bodies. Example stub for every module (repeat the pattern, one file each):

```js
// grammar/literals.js
module.exports = {
  number:  $ => /[0-9]+/,
  boolean: $ => /[01]+b/,
  byte:    $ => /0x[0-9a-fA-F]+/,
  string:  $ => /"[^"]*"/,
  char:    $ => seq('"', /./, '"'),
  symbol:  $ => /`[A-Za-z0-9._:]*/,
  vector:  $ => prec.left(seq($.number, repeat1(seq($._list_ws, $.number)))),
  null:     $ => '0N',
  infinity: $ => '0W',
  timestamp: $ => /[0-9]{4}\.[0-9]{2}\.[0-9]{2}D[0-9:.]+/,
  date:      $ => /[0-9]{4}\.[0-9]{2}\.[0-9]{2}/,
  month:     $ => /[0-9]{4}\.[0-9]{2}m/,
  time:      $ => /[0-9]{2}:[0-9]{2}:[0-9]{2}\.[0-9]{3}/,
  minute:    $ => /[0-9]{2}:[0-9]{2}/,
  second:    $ => /[0-9]{2}:[0-9]{2}:[0-9]{2}/,
  timespan:  $ => /[0-9]+D[0-9:.]+/,
  datetime:  $ => /[0-9]{4}\.[0-9]{2}\.[0-9]{2}T[0-9:.]+/,
};
```
```js
// grammar/identifiers.js
module.exports = {
  identifier:   $ => /[A-Za-z][A-Za-z0-9_]*/,
  dotted_name:  $ => /\.[A-Za-z][A-Za-z0-9_.]*/,
  builtin:      $ => choice('select', 'from', 'where', 'by'),  // expanded in Task 4
  symbol_vector: $ => prec.left(repeat1($.symbol)),
};
```
```js
// grammar/functions.js
module.exports = {
  assignment: $ => prec.right(seq(
    field('left', choice($.identifier, $.dotted_name)),
    field('operator', choice('::', ':')),
    field('right', $._expression))),
  lambda: $ => seq('{', optional(field('parameters', $.parameters)),
                   field('body', optional($._lambda_body)), '}'),
  _lambda_body: $ => sep1($._statement, ';'),
  parameters: $ => seq('[', optional(sep1(field('param', $.param), ';')), ']'),
  param: $ => $.identifier,
};
```
```js
// grammar/expression.js  (OWNS _expression)
module.exports = {
  _expression: $ => choice($._noun, $.call, $.lambda, $.parenthesized, $.list,
                           $.cond, $._literal_ref),
  _literal_ref: $ => choice($.number, $.string, $.symbol, $.identifier, $.dotted_name),
  _noun: $ => choice($.number, $.identifier),
  call: $ => prec.left(seq(field('function', choice($.identifier, $.dotted_name)),
                           '[', field('arguments', optional(sep1($._expression, ';'))), ']')),
  parenthesized: $ => seq('(', $._expression, ')'),
  list: $ => seq('(', sep1($._expression, ';'), ')'),
};
```
```js
// grammar/qsql.js
module.exports = {
  select_statement: $ => seq('select', field('from', seq('from', $._expression))),
  exec_statement:   $ => seq('exec', field('from', seq('from', $._expression))),
  update_statement: $ => seq('update', field('from', seq('from', $._expression))),
  delete_statement: $ => seq('delete', field('from', seq('from', $._expression))),
};
```
```js
// grammar/control.js
module.exports = {
  cond:    $ => seq('$', '[', sep1($._expression, ';'), ']'),
  control: $ => seq(field('keyword', choice('if', 'do', 'while')),
                    '[', sep1($._statement, ';'), ']'),
};
```
```js
// grammar/commands.js
module.exports = {
  system_command: $ => seq(field('command', $._system_command_tok)),
  namespace_directive: $ => seq('\\d', optional(field('namespace', $.dotted_name))),
};
```

Add a tiny `sep1` helper at the top of `grammar.js`:
```js
function sep1(rule, s) { return seq(rule, repeat(seq(s, rule))); }
```
(and `require` it into modules that use it, or define module-local copies — keep each module self-contained).

- [ ] **Step 5: Write a minimal `src/scanner.c` that links but emits nothing**

```c
#include "tree_sitter/parser.h"
enum TokenType { COMMENT, SYSTEM_COMMAND_TOK, NEG_NUMBER, LIST_WS, ADVERB_TOK, EOS, ERROR_SENTINEL };
void *tree_sitter_q_external_scanner_create(void) { return NULL; }
void  tree_sitter_q_external_scanner_destroy(void *p) { (void)p; }
unsigned tree_sitter_q_external_scanner_serialize(void *p, char *b) { (void)p;(void)b; return 0; }
void  tree_sitter_q_external_scanner_deserialize(void *p, const char *b, unsigned n) { (void)p;(void)b;(void)n; }
bool  tree_sitter_q_external_scanner_scan(void *p, TSLexer *l, const bool *valid) {
  (void)p;(void)l;(void)valid; return false;  // Task 2 replaces this
}
```

- [ ] **Step 6: Write Python binding files**

```python
# bindings/python/tree_sitter_q/__init__.py
"""Tree-sitter q grammar binding."""
from importlib.resources import files as _files
from ._binding import language  # noqa: F401
__all__ = ["language"]
```
```c
// bindings/python/tree_sitter_q/binding.c
#include <Python.h>
typedef struct TSLanguage TSLanguage;
const TSLanguage *tree_sitter_q(void);
static PyObject* _language(PyObject *self, PyObject *args) {
  return PyCapsule_New((void*)tree_sitter_q(), "tree_sitter.Language", NULL);
}
static PyMethodDef methods[] = {{"language", _language, METH_NOARGS, ""},{NULL,NULL,0,NULL}};
static struct PyModuleDef module = {PyModuleDef_HEAD_INIT,"_binding",NULL,-1,methods};
PyMODINIT_FUNC PyInit__binding(void){ return PyModule_Create(&module); }
```
```python
# bindings/python/tree_sitter_q/__init__.pyi
def language() -> object: ...
```

- [ ] **Step 7: Write `pyproject.toml` (setuptools native build)**

```toml
[build-system]
requires = ["setuptools>=68", "wheel"]
build-backend = "setuptools.build_meta"

[project]
name = "tree-sitter-q"
version = "0.1.0"
requires-python = ">=3.10"
dependencies = ["tree-sitter>=0.23,<0.26"]

[tool.setuptools]
packages = ["tree_sitter_q"]
package-dir = {"tree_sitter_q" = "bindings/python/tree_sitter_q"}

[[tool.setuptools.ext-modules]]
name = "tree_sitter_q._binding"
sources = ["bindings/python/tree_sitter_q/binding.c", "src/parser.c", "src/scanner.c"]
include-dirs = ["src"]
```

- [ ] **Step 8: Write skeleton corpus test**

```
==================
skeleton: assignment to lambda
==================
f:{x+y}
---
(source_file
  (assignment left: (identifier) operator: (lambda body: (_)))))
```
(Exact expected tree will be tightened by later tasks; for T1 just assert it parses without ERROR.)

- [ ] **Step 9: Generate and verify it compiles**

Run: `tree-sitter generate && tree-sitter parse <(echo 'f:{x+y}') | grep -c ERROR`
Expected: prints `0` (no ERROR nodes); `src/parser.c` is generated.

- [ ] **Step 10: Commit**

```bash
git add -A
git commit -m "Scaffold tree-sitter-q: compiling modular skeleton + frozen interfaces"
```

---

### Task 2: External scanner (`src/scanner.c`)

**Wave 1. Parallel. Worktree isolation. Depends on T1.**
**Reference:** `references/syntax.md` (whitespace rules, comments, system commands).

**Files:**
- Modify: `src/scanner.c`
- Test: `test/corpus/scanner.txt`

**Interfaces:**
- Consumes: external token enum from T1 (`COMMENT, SYSTEM_COMMAND_TOK, NEG_NUMBER, LIST_WS, ADVERB_TOK, EOS, ERROR_SENTINEL`).
- Produces: working tokenization for comments, system commands, negative numbers, vector whitespace, adverbs, statement terminators.

- [ ] **Step 1: Write the failing corpus tests**

```
==================
trailing comment
==================
a:1  / this is a comment
---
(source_file (assignment left:(identifier) operator: right:(number)) (comment))

==================
negative literal vs subtraction
==================
x:1 -2
y:1 - 2
---
(source_file
  (assignment left:(identifier) operator: right:(vector))
  (assignment left:(identifier) operator: right:(call function:(identifier))))

==================
system command load
==================
\l init.q
---
(source_file (system_command command:(_system_command_tok)))
```

- [ ] **Step 2: Run to verify they fail**

Run: `tree-sitter test -f 'comment'`
Expected: FAIL — skeleton scanner emits nothing, comment unrecognized.

- [ ] **Step 3: Implement the scanner**

Implement scan state (a `struct { uint32_t depth; }` for bracket depth) + serialize/deserialize, then the scan function per `references/syntax.md`:

```c
#include "tree_sitter/parser.h"
#include <stdbool.h>
#include <string.h>

enum TokenType { COMMENT, SYSTEM_COMMAND_TOK, NEG_NUMBER, LIST_WS, ADVERB_TOK, EOS, ERROR_SENTINEL };
typedef struct { unsigned depth; bool prev_was_value; } Scanner;

void *tree_sitter_q_external_scanner_create(void){ Scanner *s=calloc(1,sizeof(Scanner)); return s; }
void  tree_sitter_q_external_scanner_destroy(void *p){ free(p); }
unsigned tree_sitter_q_external_scanner_serialize(void *p,char *b){ memcpy(b,p,sizeof(Scanner)); return sizeof(Scanner); }
void  tree_sitter_q_external_scanner_deserialize(void *p,const char *b,unsigned n){ if(n)memcpy(p,b,sizeof(Scanner)); }

static void adv(TSLexer *l){ l->advance(l,false); }
static void skip(TSLexer *l){ l->advance(l,true); }

bool tree_sitter_q_external_scanner_scan(void *payload, TSLexer *l, const bool *valid) {
  Scanner *s = (Scanner*)payload;
  uint32_t col = l->get_column(l);

  // 1. Comments: line-start `/`, trailing ` /`, block `/`..`\`, final `\`.
  if (valid[COMMENT]) {
    bool at_line_start = (col == 0);
    // trailing comment requires a preceding space (the lexer is positioned after extras)
    if (l->lookahead == '/' && (at_line_start)) {
      // whole-line or block comment
      while (l->lookahead && l->lookahead != '\n') adv(l);
      l->result_symbol = COMMENT; return true;
    }
  }

  // 2. System command: line-start backslash + rest of line.
  if (valid[SYSTEM_COMMAND_TOK] && col == 0 && l->lookahead == '\\') {
    adv(l);
    while (l->lookahead && l->lookahead != '\n') adv(l);
    l->result_symbol = SYSTEM_COMMAND_TOK; return true;
  }

  // 3. EOS: newline at top level (depth==0) that is not a continuation.
  if (valid[EOS] && l->lookahead == '\n' && s->depth == 0) {
    adv(l); l->result_symbol = EOS; return true;
  }

  // 4. NEG_NUMBER: `-` immediately followed by digit, not preceded by a value.
  if (valid[NEG_NUMBER] && l->lookahead == '-' && !s->prev_was_value) {
    adv(l);
    if (l->lookahead >= '0' && l->lookahead <= '9') {
      while ((l->lookahead>='0'&&l->lookahead<='9')||l->lookahead=='.') adv(l);
      l->result_symbol = NEG_NUMBER; s->prev_was_value = true; return true;
    }
    return false;
  }

  // 5. ADVERB: postfix iterator glyphs after a value.
  if (valid[ADVERB_TOK] && s->prev_was_value &&
      (l->lookahead=='/'||l->lookahead=='\\'||l->lookahead=='\'')) {
    adv(l);
    if (l->lookahead==':') adv(l);     // /: \: ':
    l->result_symbol = ADVERB_TOK; return true;
  }

  // 6. LIST_WS: a space between two values forms a vector separator.
  // (Handled by extras for ordinary spaces; LIST_WS only asserted by the
  //  vector rule context — emit when a space precedes another value char.)
  return false;
}
```

Track bracket depth and `prev_was_value` by inspecting tokens around brackets — increment on `([{`, decrement on `)]}`. (Refine in Step 5 as corpus cases demand; the structure above is the contract.)

- [ ] **Step 4: Run the corpus tests**

Run: `tree-sitter generate && tree-sitter test -f 'comment' && tree-sitter test -f 'negative' && tree-sitter test -f 'system command'`
Expected: PASS.

- [ ] **Step 5: Add edge-case corpus rows from `references/syntax.md`**

Add rows for: block comment `/`…`\`, final `\` script exit, `\d .ns`, `1 -2 -3` long vector, adverb chains `+/:`, `f': `. Make each pass; refine scanner state until green.

Run: `tree-sitter test -f 'scanner'`
Expected: all PASS.

- [ ] **Step 6: Commit**

```bash
git add src/scanner.c test/corpus/scanner.txt
git commit -m "Implement external scanner: comments, system cmds, neg numbers, adverbs, EOS"
```

---

### Task 3: Literals (`grammar/literals.js`)

**Wave 1. Parallel. Worktree isolation. Depends on T1.**
**Reference:** `references/datatypes.md` (authoritative literal forms for every type).

**Files:**
- Modify: `grammar/literals.js`
- Test: `test/corpus/literals.txt`

**Interfaces:**
- Produces: `number, boolean, byte, string, char, symbol, vector, null, infinity, timestamp, date, month, time, minute, second, timespan, datetime` rules.

- [ ] **Step 1: Write failing corpus tests (one block per datatype family, from `references/datatypes.md`)**

```
==================
typed number atoms
==================
a:42
b:42j
c:3.14
d:3.14e
e:1b
f:0x2a
---
(source_file
 (assignment right:(number)) (assignment right:(number))
 (assignment right:(number)) (assignment right:(number))
 (assignment right:(boolean)) (assignment right:(byte)))

==================
temporal literals
==================
d:2024.01.15
t:2024.01.15D12:30:00.000000000
m:2024.01m
tt:12:30:00.000
---
(source_file
 (assignment right:(date)) (assignment right:(timestamp))
 (assignment right:(month)) (assignment right:(time)))

==================
null and infinity
==================
a:0N
b:0W
c:0n
d:-0w
---
(source_file
 (assignment right:(null)) (assignment right:(infinity))
 (assignment right:(null)) (assignment right:(infinity)))
```

- [ ] **Step 2: Run to verify fail**

Run: `tree-sitter test -f 'typed number'`
Expected: FAIL.

- [ ] **Step 3: Implement literal rules from `references/datatypes.md`**

```js
// grammar/literals.js
const DIGIT = /[0-9]/;
module.exports = {
  number: $ => token(choice(
    /[0-9]+[jihfe]?/,                          // int/long/short/real/float w/ type suffix
    /[0-9]+\.[0-9]*([eE][+-]?[0-9]+)?[fe]?/,   // float/real
    /\.[0-9]+([eE][+-]?[0-9]+)?[fe]?/,
  )),
  boolean: $ => token(/[01]+b/),                // 1b and bool vectors 0101b
  byte:    $ => token(/0x([0-9a-fA-F][0-9a-fA-F])+/),
  string:  $ => token(seq('"', repeat(choice(/[^"\\]/, /\\./)), '"')),
  char:    $ => token(seq('"', choice(/[^"\\]/, /\\./), '"')),
  symbol:  $ => token(/`(:?[A-Za-z0-9._]*(:[A-Za-z0-9._]*)*)?/),  // `sym `:path:port `
  null:     $ => token(choice('0N', /0N[ghije]/, '0n')),
  infinity: $ => token(choice('0W', /0W[hije]/, '0w', '-0w', /-0W[hije]?/)),
  // Temporal — order longest-first so timestamp wins over date (see datatypes.md)
  timestamp: $ => token(prec(3, /[0-9]{4}\.[0-9]{2}\.[0-9]{2}D[0-9]{2}:[0-9]{2}:[0-9]{2}(\.[0-9]{1,9})?/)),
  datetime:  $ => token(prec(3, /[0-9]{4}\.[0-9]{2}\.[0-9]{2}T[0-9]{2}:[0-9]{2}:[0-9]{2}(\.[0-9]{1,3})?/)),
  date:      $ => token(prec(2, /[0-9]{4}\.[0-9]{2}\.[0-9]{2}/)),
  month:     $ => token(prec(2, /[0-9]{4}\.[0-9]{2}m/)),
  timespan:  $ => token(prec(2, /[0-9]+D[0-9]{2}:[0-9]{2}:[0-9]{2}(\.[0-9]{1,9})?/)),
  time:      $ => token(prec(1, /[0-9]{2}:[0-9]{2}:[0-9]{2}\.[0-9]{1,3}/)),
  second:    $ => token(/[0-9]{2}:[0-9]{2}:[0-9]{2}/),
  minute:    $ => token(/[0-9]{2}:[0-9]{2}/),
  vector:    $ => prec.left(seq($.number, repeat1(seq($._list_ws, $.number)))),
};
```

- [ ] **Step 4: Run corpus tests**

Run: `tree-sitter generate && tree-sitter test -f 'typed number' && tree-sitter test -f 'temporal' && tree-sitter test -f 'null and infinity'`
Expected: PASS.

- [ ] **Step 5: Add the remaining literal families from `references/datatypes.md`**

Add corpus rows + rule coverage for: guid, real/short suffix edge cases, symbol vectors (defer the *vector* of symbols to T4), bool vector vs index, negative numbers via `$._neg_number` (from T2 — alias it into `number` here: add `$._neg_number` to the `number` choice). Make each green.

- [ ] **Step 6: Commit**

```bash
git add grammar/literals.js test/corpus/literals.txt
git commit -m "Grammar: complete q literal lexical forms (datatypes.md)"
```

---

### Task 4: Identifiers, namespaces, builtins, symbol vectors (`grammar/identifiers.js`)

**Wave 1. Parallel. Worktree isolation. Depends on T1.**
**Reference:** `references/keywords.md`, `references/datatypes.md`.

**Files:**
- Modify: `grammar/identifiers.js`
- Test: `test/corpus/identifiers.txt`

**Interfaces:**
- Produces: `identifier, dotted_name, builtin, symbol_vector`.

- [ ] **Step 1: Write failing corpus tests**

```
==================
dotted namespace names
==================
.foo.bar:1
.z.ts:{x}
x:.Q.dd[`a;`b]
---
(source_file
 (assignment left:(dotted_name) right:(number))
 (assignment left:(dotted_name) right:(lambda))
 (assignment left:(identifier) right:(call function:(dotted_name))))

==================
symbol vector
==================
s:`a`b`c
---
(source_file (assignment right:(symbol_vector)))

==================
builtin keyword
==================
n:count til 10
---
(source_file (assignment right:(call function:(builtin) arguments:(call function:(builtin)))))
```

- [ ] **Step 2: Run to verify fail**

Run: `tree-sitter test -f 'dotted namespace'`
Expected: FAIL.

- [ ] **Step 3: Implement, sourcing the keyword list from `references/keywords.md`**

```js
// grammar/identifiers.js
// KEYWORDS: the complete keyword-function set is enumerated in references/keywords.md.
// Copy the full list here (170+ entries). Representative subset shown:
const KEYWORDS = [
  'abs','acos','aj','aj0','all','and','any','asc','asin','atan','avg','avgs',
  'bin','binr','ceiling','cols','cor','cos','count','cov','cross','cut','delete',
  'desc','dev','differ','distinct','div','each','enlist','eval','except','exec',
  'exp','fby','fills','first','flip','floor','get','group','gtime','hclose','hcount',
  'hdel','hopen','hsym','iasc','idesc','if','in','insert','inter','inv','key','keys',
  'last','like','lj','ljf','load','log','lower','lsq','ltime','ltrim','mavg','max',
  'maxs','mcount','md5','mdev','med','meta','min','mins','mmax','mmin','mmu','mod',
  'msum','neg','next','not','null','or','over','parse','peach','pj','prd','prds',
  'prev','prior','rand','rank','ratios','raze','read0','read1','reciprocal','reverse',
  'rload','rotate','rsave','rtrim','save','scan','scov','sdev','select','set','show',
  'signum','sin','sqrt','ss','ssr','string','sublist','sum','sums','sv','svar','system',
  'tables','tan','til','trim','type','uj','ujf','ungroup','union','update','upper',
  'upsert','value','var','view','views','vs','wavg','where','while','within','wj','wj1',
  'wsum','xasc','xbar','xcol','xcols','xdesc','xexp','xgroup','xkey','xlog','xprev',
  'xrank','do','by','from',
];
module.exports = {
  identifier:  $ => token(/[A-Za-z][A-Za-z0-9_]*/),
  dotted_name: $ => token(/\.[A-Za-z][A-Za-z0-9_]*(\.[A-Za-z][A-Za-z0-9_]*)*/),
  builtin:     $ => token(prec(1, choice(...KEYWORDS))),  // prec over identifier
  symbol_vector: $ => prec.left(seq($.symbol, repeat1($.symbol))),
};
```
> Note: `builtin` must win over `identifier` for reserved words — `token(prec(1, choice(...)))`. Verify `count` lexes as `builtin`, `counter` as `identifier`.

- [ ] **Step 4: Run corpus tests**

Run: `tree-sitter generate && tree-sitter test -f 'dotted' && tree-sitter test -f 'symbol vector' && tree-sitter test -f 'builtin'`
Expected: PASS.

- [ ] **Step 5: Paste the COMPLETE keyword list from `references/keywords.md`**

Replace the representative subset with the full enumeration. Add a corpus row asserting a non-keyword lookalike (`counter`, `selects`) lexes as `identifier`.

Run: `tree-sitter test -f 'identifiers'`
Expected: all PASS.

- [ ] **Step 6: Commit**

```bash
git add grammar/identifiers.js test/corpus/identifiers.txt
git commit -m "Grammar: identifiers, dotted namespaces, builtins, symbol vectors (keywords.md)"
```

---

### Task 5: Functions — lambda, parameters, assignment (`grammar/functions.js`)

**Wave 1. Parallel. Worktree isolation. Depends on T1.**
**Reference:** `references/syntax.md` (lambda notation, implicit args, assignment).

**Files:**
- Modify: `grammar/functions.js`
- Test: `test/corpus/functions.txt`

**Interfaces:**
- Consumes: `$._expression`, `$._statement` (T6/T1), `$.identifier`, `$.dotted_name` (T4).
- Produces: `assignment` (fields `left`,`operator`,`right`), `lambda` (fields `parameters`,`body`), `parameters`, `param`.

- [ ] **Step 1: Write failing corpus tests**

```
==================
lambda with explicit params
==================
add:{[a;b] a+b}
---
(source_file (assignment
  left:(identifier) operator:":"
  right:(lambda parameters:(parameters (param)(param)) body:(_))))

==================
lambda implicit args + multi statement
==================
f:{a:x*2; a+y}
---
(source_file (assignment right:(lambda body:(_))))

==================
global assignment ::
==================
.cfg.port::5000
---
(source_file (assignment left:(dotted_name) operator:"::" right:(number)))
```

- [ ] **Step 2: Run to verify fail**

Run: `tree-sitter test -f 'lambda with explicit'`
Expected: FAIL.

- [ ] **Step 3: Implement**

```js
// grammar/functions.js
function sep1(r, s){ return seq(r, repeat(seq(s, r))); }
module.exports = {
  assignment: $ => prec.right(1, seq(
    field('left', choice($.identifier, $.dotted_name, $.index)),
    field('operator', choice('::', ':')),
    field('right', $._expression),
  )),
  lambda: $ => seq(
    '{',
    optional(field('parameters', $.parameters)),
    field('body', optional(sep1($._statement, ';'))),
    '}',
  ),
  parameters: $ => seq('[', optional(sep1(field('param', $.param), ';')), ']'),
  param: $ => $.identifier,
};
```
> `prec.right` enforces q's right-associative assignment (`a:b:1`). `index` on the left supports amend-assign `x[i]:v`.

- [ ] **Step 4: Run corpus tests**

Run: `tree-sitter generate && tree-sitter test -f 'lambda' && tree-sitter test -f 'global assignment'`
Expected: PASS.

- [ ] **Step 5: Add edge cases from `references/syntax.md`**

Add rows: empty lambda `{}`, no-param multi-statement, nested lambda `{{x}}`, amend-assign `t[`a]:1`, chained `a:b:c:0`. Green each.

- [ ] **Step 6: Commit**

```bash
git add grammar/functions.js test/corpus/functions.txt
git commit -m "Grammar: lambda, parameters, assignment (right-associative)"
```

---

### Task 6: Expression core — RTL, application, adverbs, lists (`grammar/expression.js`)

**Wave 1. Parallel. Worktree isolation. Depends on T1. OWNS `_expression`.**
**Reference:** `references/syntax.md` (right-to-left, application/projection, postfix-infix), `references/operators.md`.

**Files:**
- Modify: `grammar/expression.js`
- Test: `test/corpus/expression.txt`

**Interfaces:**
- Consumes: literals (T3), identifiers/builtins (T4), `lambda` (T5), `cond` (T8), q-SQL statements (T7).
- Produces: `_expression`, `call`, `index`, `parenthesized`, `list`, operator/adverb application. This is the rule every other module references.

- [ ] **Step 1: Write failing corpus tests (RTL is the critical one)**

```
==================
right-to-left, no precedence
==================
r:2*3+4
---
(source_file (assignment right:(binary
  left:(number) operator:(operator)
  right:(binary left:(number) operator:(operator) right:(number)))))

==================
bracket application and projection
==================
a:f[1;2]
b:f[;2]
---
(source_file
 (assignment right:(call function:(identifier) arguments:(_)))
 (assignment right:(call function:(identifier) arguments:(_))))

==================
adverb over
==================
s:+/[1 2 3]
---
(source_file (assignment right:(call function:(adverb_apply))))

==================
parenthesized list
==================
l:(1;2;3)
---
(source_file (assignment right:(list (number)(number)(number))))
```

- [ ] **Step 2: Run to verify fail**

Run: `tree-sitter test -f 'right-to-left'`
Expected: FAIL.

- [ ] **Step 3: Implement RTL expression model**

q has no precedence; every dyadic application binds right. Model `_expression` as a right-recursive binary fold plus application by juxtaposition and brackets.

```js
// grammar/expression.js
function sep(r, s){ return optional(seq(r, repeat(seq(s, optional(r))))); }
const OPERATOR = token(choice(
  '+','-','*','%','&','|','^','=','<','>','~','!','#','_','$','?','@','.',',',
  '<=','>=','<>',
));
module.exports = {
  _expression: $ => choice($.binary, $._application, $.select_statement,
    $.exec_statement, $.update_statement, $.delete_statement, $.cond, $.control),

  // right-associative: a OP rest   (no precedence among operators)
  binary: $ => prec.right(seq(
    field('left', $._application),
    field('operator', alias(OPERATOR, $.operator)),
    field('right', $._expression),
  )),

  _application: $ => choice($.call, $.index, $.adverb_apply, $._primary),

  // juxtaposition application: f x  (space-separated, RTL handled by recursion)
  call: $ => prec.left(2, choice(
    seq(field('function', $._primary), '[',
        field('arguments', alias(sep($._expression, ';'), $.arguments)), ']'),
    prec.right(1, seq(field('function', $._primary), field('arguments', $._application))),
  )),
  index: $ => prec.left(2, seq(field('function', $._primary),
    '[', field('arguments', alias(sep($._expression, ';'), $.arguments)), ']')),

  adverb_apply: $ => prec.left(seq(
    field('function', choice($._primary, alias(OPERATOR, $.operator))),
    field('adverb', $._adverb_tok),
    optional(seq('[', sep($._expression, ';'), ']')),
  )),

  _primary: $ => choice(
    $.lambda, $.parenthesized, $.list, $.table_literal,
    $.number, $.boolean, $.byte, $.string, $.char, $.symbol, $.symbol_vector,
    $.vector, $.null, $.infinity,
    $.timestamp, $.datetime, $.date, $.month, $.timespan, $.time, $.second, $.minute,
    $.builtin, $.dotted_name, $.identifier,
  ),
  parenthesized: $ => seq('(', $._expression, ')'),
  list: $ => seq('(', $._expression, repeat1(seq(';', optional($._expression))), ')'),
  table_literal: $ => seq('(', '[', sep($._expression, ';'), ']',
                          sep($._expression, ';'), ')'),
};
```

- [ ] **Step 4: Run corpus tests; record conflicts**

Run: `tree-sitter generate`
Expected: tree-sitter reports GLR conflicts (e.g. `call` vs `binary`, `list` vs `parenthesized`). **Do not resolve here** — note each conflict in a comment block at the top of `expression.js` titled `// CONFLICTS FOR TASK 10:`. Then add the minimal `conflicts:` entries locally to get tests green in this worktree:

```js
// add to grammar.js conflicts (T6 worktree copy; T10 reconciles):
conflicts: $ => [[$.call, $.index], [$.parenthesized, $.list]],
```

Run: `tree-sitter generate && tree-sitter test -f 'right-to-left' && tree-sitter test -f 'bracket' && tree-sitter test -f 'parenthesized'`
Expected: PASS.

- [ ] **Step 5: Add operator/adverb coverage from `references/operators.md`**

Add corpus rows for: each adverb (`/ \ ': /: \:`), `@`/`.` apply (`.[f;args]`, `@[x;i;f]`), composition, projection `f[;2]`, deep RTL `1+2*3-4`. Document every emitted conflict in the `CONFLICTS FOR TASK 10` block.

- [ ] **Step 6: Commit**

```bash
git add grammar/expression.js test/corpus/expression.txt
git commit -m "Grammar: RTL expression core, application, adverbs, lists (+conflict log for T10)"
```

---

### Task 7: q-SQL (`grammar/qsql.js`)

**Wave 1. Parallel. Worktree isolation. Depends on T1.**
**Reference:** `references/qsql.md` (exact clause grammar + order).

**Files:**
- Modify: `grammar/qsql.js`
- Test: `test/corpus/qsql.txt`

**Interfaces:**
- Consumes: `$._expression` (T6), `$.identifier` (T4).
- Produces: `select_statement, exec_statement, update_statement, delete_statement, select_clause, by_clause, from_clause, where_clause`.

- [ ] **Step 1: Write failing corpus tests (from `references/qsql.md`)**

```
==================
select with by and where
==================
q:select avg price by sym from trade where date=.z.d
---
(source_file (assignment right:(select_statement
  select:(select_clause)
  by:(by_clause)
  from:(from_clause (identifier))
  where:(where_clause))))

==================
update
==================
update vwap:size wavg price by sym from trade
---
(source_file (update_statement by:(by_clause) from:(from_clause (identifier))))

==================
delete rows
==================
delete from trade where price<0
---
(source_file (delete_statement from:(from_clause (identifier)) where:(where_clause)))
```

- [ ] **Step 2: Run to verify fail**

Run: `tree-sitter test -f 'select with by'`
Expected: FAIL.

- [ ] **Step 3: Implement clause grammar per `references/qsql.md`**

Parse order: `select [phrases] [by phrases] from texpr [where phrases]`. Phrases are `;`-separated expressions; `$[…]` Cond is excluded per docs but we accept `_expression` and let semantics ignore.

```js
// grammar/qsql.js
function sep1(r,s){ return seq(r, repeat(seq(s, r))); }
const phrases = $ => sep1($._expression, ';');
module.exports = {
  select_statement: $ => prec.right(seq('select',
    optional(field('select', alias(phrases, $.select_clause))),
    optional(field('by', $.by_clause)),
    field('from', $.from_clause),
    optional(field('where', $.where_clause)))),
  exec_statement: $ => prec.right(seq('exec',
    optional(field('select', alias(phrases, $.select_clause))),
    optional(field('by', $.by_clause)),
    field('from', $.from_clause),
    optional(field('where', $.where_clause)))),
  update_statement: $ => prec.right(seq('update',
    optional(field('select', alias(phrases, $.select_clause))),
    optional(field('by', $.by_clause)),
    field('from', $.from_clause),
    optional(field('where', $.where_clause)))),
  delete_statement: $ => prec.right(seq('delete',
    optional(field('select', alias(phrases, $.select_clause))),
    field('from', $.from_clause),
    optional(field('where', $.where_clause)))),
  by_clause:    $ => seq('by', alias(phrases, $.by_phrases)),
  from_clause:  $ => seq('from', $._expression),
  where_clause: $ => seq('where', alias(phrases, $.where_phrases)),
};
```
> `select` etc. are keywords from T4 (`builtin`); to make them statement keywords here, reference the literal strings — tree-sitter dedups tokens. Add `[$.select_statement, $.builtin]` to the conflict log for T10.

- [ ] **Step 4: Run corpus tests**

Run: `tree-sitter generate && tree-sitter test -f 'select with by' && tree-sitter test -f 'update' && tree-sitter test -f 'delete rows'`
Expected: PASS (add local `conflicts` as needed; log them for T10).

- [ ] **Step 5: Add coverage from `references/qsql.md`**

Rows for: `exec`, computed columns `select x:a+b from t`, `fby`, nested select, `select[n]`/`select[>price]` limits, functional forms `?[t;…]`. Green each; log conflicts.

- [ ] **Step 6: Commit**

```bash
git add grammar/qsql.js test/corpus/qsql.txt
git commit -m "Grammar: q-SQL select/exec/update/delete with clauses (qsql.md)"
```

---

### Task 8: Control flow & cond (`grammar/control.js`)

**Wave 1. Parallel. Worktree isolation. Depends on T1.**
**Reference:** `references/syntax.md`, `references/qsql.md` (Cond).

**Files:**
- Modify: `grammar/control.js`
- Test: `test/corpus/control.txt`

**Interfaces:**
- Consumes: `$._expression`, `$._statement`.
- Produces: `cond`, `control` (field `keyword`), plus `return`/`signal` markers.

- [ ] **Step 1: Failing corpus tests**

```
==================
cond ternary
==================
r:$[x>0;`pos;`neg]
---
(source_file (assignment right:(cond (_)(_)(_))))

==================
if and while
==================
if[x>0;:x]
while[i<10;i+:1]
---
(source_file
 (control keyword:"if")
 (control keyword:"while"))
```

- [ ] **Step 2: Run to verify fail**

Run: `tree-sitter test -f 'cond ternary'`
Expected: FAIL.

- [ ] **Step 3: Implement**

```js
// grammar/control.js
function sep1(r,s){ return seq(r, repeat(seq(s, r))); }
module.exports = {
  cond: $ => prec(2, seq('$', '[', sep1($._expression, ';'), ']')),
  control: $ => seq(
    field('keyword', choice('if', 'do', 'while')),
    '[', sep1($._statement, ';'), ']'),
  // return `:expr` and signal `'expr` are statement-level prefixes
  return_stmt: $ => prec.left(seq(':', $._expression)),
  signal_stmt: $ => prec.left(seq('\'', $._expression)),
};
```
> `cond` (`$[...]`) must win over `$` operator + `[`; `prec(2)`. Add `[$.cond, $.binary]` to T10 conflict log if reported.

- [ ] **Step 4: Run corpus tests**

Run: `tree-sitter generate && tree-sitter test -f 'cond' && tree-sitter test -f 'if and while'`
Expected: PASS.

- [ ] **Step 5: Add edge cases**

Rows for: nested cond, `do[n;…]`, vector-cond `?[bool;a;b]` (this is `?` apply, belongs to T6 — add a row asserting it does NOT parse as `control`), `:` bare return. Green each.

- [ ] **Step 6: Commit**

```bash
git add grammar/control.js test/corpus/control.txt
git commit -m "Grammar: cond, if/do/while, return/signal"
```

---

### Task 9: System commands & namespace directives (`grammar/commands.js`)

**Wave 1. Parallel. Worktree isolation. Depends on T1.**
**Reference:** `references/syntax.md` (`\`-command table).

**Files:**
- Modify: `grammar/commands.js`
- Test: `test/corpus/commands.txt`

**Interfaces:**
- Consumes: `$._system_command_tok` (scanner, T2), `$.dotted_name` (T4).
- Produces: `system_command` (fields `command`,`argument`), `namespace_directive` (field `namespace`).

- [ ] **Step 1: Failing corpus tests**

```
==================
load and namespace
==================
\l init.q
\d .util
\ts count til 1000
---
(source_file
 (system_command)
 (namespace_directive namespace:(dotted_name))
 (system_command))
```

- [ ] **Step 2: Run to verify fail**

Run: `tree-sitter test -f 'load and namespace'`
Expected: FAIL.

- [ ] **Step 3: Implement**

The scanner (T2) emits the whole `\…` line as `_system_command_tok`. Split `\d .ns` out as `namespace_directive` because it affects extraction (sets current namespace). Parse the token text in the extractor; here we differentiate `\d` structurally:

```js
// grammar/commands.js
module.exports = {
  // \d directive parsed structurally so the extractor can read the namespace.
  namespace_directive: $ => prec(2, seq('\\d', optional(field('namespace', $.dotted_name)))),
  // every other backslash command arrives as one scanner token.
  system_command: $ => field('command', $._system_command_tok),
};
```
> Note: `\d` here needs the scanner to NOT swallow it as `_system_command_tok`, OR the extractor parses the command text. Decision (logged for T10): scanner emits `_system_command_tok` for the whole line; grammar exposes `system_command`; the extractor (T12) inspects the token text to detect `\d`/`\l`. Keep `namespace_directive` only if T10 can disambiguate cleanly; otherwise fold into `system_command` and detect in T12. Corpus expectation above assumes folding fallback:

```
\l init.q
\d .util
---
(source_file (system_command) (system_command))
```

- [ ] **Step 4: Run corpus tests**

Run: `tree-sitter generate && tree-sitter test -f 'load and namespace'`
Expected: PASS.

- [ ] **Step 5: Add the full `\`-command table rows from `references/syntax.md`**

Rows for `\c \p \P \x \w \\ \ts \t \l \d \a \b \v`. Each parses as `system_command`.

- [ ] **Step 6: Commit**

```bash
git add grammar/commands.js test/corpus/commands.txt
git commit -m "Grammar: system commands + namespace directive"
```

---

### Task 10: Convergence — merge, generate, resolve GLR conflicts, full corpus green

**Wave 2. Single agent. Merge barrier. Runs on `main` after all wave-1 worktrees merge.**

**Files:**
- Modify: `grammar.js` (the `conflicts:` array), any module needing precedence tweaks
- Create: `src/parser.c` (regenerated, committed)
- Test: all of `test/corpus/*.txt`

**Interfaces:**
- Consumes: every wave-1 module + their `CONFLICTS FOR TASK 10` logs.
- Produces: a single grammar that generates cleanly and passes the entire corpus.

- [ ] **Step 1: Merge all wave-1 worktrees to `main`**

```bash
# for each wave-1 branch:
git merge --no-ff <branch>
```
Resolve any `grammar.js conflicts:` array merge conflicts by UNION of all entries.

- [ ] **Step 2: Generate and collect all conflicts**

Run: `tree-sitter generate 2>&1 | tee /tmp/ts-conflicts.txt`
Expected: a list of unresolved conflicts (if any).

- [ ] **Step 3: Resolve conflicts**

For each reported conflict, add to `grammar.js` `conflicts:` (for genuine GLR ambiguity tree-sitter should explore both) or add `prec`/`prec.left`/`prec.right` (for precedence-resolvable cases). Consolidate the per-module `CONFLICTS FOR TASK 10` notes. Re-run generate until clean.

Run: `tree-sitter generate`
Expected: exits 0, no "Unresolved conflict" output.

- [ ] **Step 4: Run the FULL corpus**

Run: `tree-sitter test`
Expected: ALL corpus tests PASS across every `test/corpus/*.txt`.

- [ ] **Step 5: Smoke-parse a mixed real snippet**

```bash
cat > /tmp/mix.q <<'EOF'
\d .app
load:{[f] system"l ",f}
agg:select sum size by sym from trade where date=.z.d
\d .
.app.agg
EOF
tree-sitter parse /tmp/mix.q | grep -c ERROR
```
Expected: `0`.

- [ ] **Step 6: Commit (including generated parser.c)**

```bash
git add grammar.js grammar/ src/parser.c
git commit -m "Converge grammar: resolve GLR conflicts, generate parser, full corpus green"
```

---

### Task 11: Python wheel build + `language()` load test

**Wave 3. Parallel. Worktree isolation. Depends on T10.**

**Files:**
- Modify: `pyproject.toml` (verify ext build), `bindings/python/tree_sitter_q/binding.c`
- Test: `tests/python/test_load.py`

**Interfaces:**
- Consumes: generated `src/parser.c`, `src/scanner.c`, T1 binding files.
- Produces: an installable `tree_sitter_q` wheel whose `language()` loads in `tree_sitter.Language`.

- [ ] **Step 1: Write failing load test**

```python
# tests/python/test_load.py
def test_language_loads():
    import tree_sitter, tree_sitter_q
    lang = tree_sitter.Language(tree_sitter_q.language())
    parser = tree_sitter.Parser(lang)
    tree = parser.parse(b"f:{x+y}")
    assert tree.root_node.type == "source_file"
    assert "ERROR" not in str(tree.root_node)

def test_extracts_assignment_lambda():
    import tree_sitter, tree_sitter_q
    p = tree_sitter.Parser(tree_sitter.Language(tree_sitter_q.language()))
    root = p.parse(b"add:{[a;b]a+b}").root_node
    asn = root.children[0]
    assert asn.type == "assignment"
    assert asn.child_by_field_name("right").type == "lambda"
```

- [ ] **Step 2: Build wheel into a venv and run; verify fail-then-build**

```bash
uv venv .venv && source .venv/bin/activate
uv pip install -e . tree-sitter pytest
pytest tests/python/test_load.py -v
```
Expected: PASS if T1 binding is correct. If `language()` capsule type mismatches the installed `tree-sitter` version, fix `binding.c` (capsule name `"tree_sitter.Language"`), rebuild, rerun.

- [ ] **Step 3: Build a distributable wheel**

Run: `uv build --wheel && ls dist/*.whl`
Expected: a `tree_sitter_q-0.1.0-*.whl` is produced.

- [ ] **Step 4: Install the built wheel into a clean venv and re-test**

```bash
uv venv .venv-clean && source .venv-clean/bin/activate
uv pip install dist/*.whl tree-sitter pytest
pytest tests/python/test_load.py -v
```
Expected: PASS (proves no Node needed — clang-only install).

- [ ] **Step 5: Commit**

```bash
git add pyproject.toml bindings/ tests/python/test_load.py
git commit -m "Package tree_sitter_q wheel; verify language() loads (clang-only install)"
```

---

### Task 12: Graphify extractor (`graphify/extractors/q.py`)

**Wave 3. Parallel. Worktree isolation. Depends on T10. Works in the cloned Graphify.**
**Reference:** node taxonomy contract (this plan); Graphify `extractors/zig.py` as the bespoke template; `ARCHITECTURE.md` for node/edge schema.

**Files:**
- Create: `graphify/extractors/q.py` (in the cloned graphify)
- Test: `graphify/tests/test_q_extractor.py`

**Interfaces:**
- Consumes: `tree_sitter_q.language()` (T11), node taxonomy.
- Produces: `extract_q(path) -> {"nodes":[...], "edges":[...]}` matching Graphify's schema; namespace-aware function/var/call/import/use extraction.

- [ ] **Step 1: Write failing extractor test**

```python
# graphify/tests/test_q_extractor.py
from pathlib import Path
from graphify.extractors.q import extract_q

def test_function_and_namespace(tmp_path):
    f = tmp_path / "m.q"
    f.write_text("\\d .app\nadd:{[a;b]a+b}\nmain:{add[1;2]}\n\\d .\n")
    out = extract_q(f)
    names = {n["name"] for n in out["nodes"]}
    assert ".app.add" in names and ".app.main" in names
    kinds = {n["kind"] for n in out["nodes"] if n["name"].endswith("add")}
    assert "function" in kinds
    calls = [(e["src"], e["dst"]) for e in out["edges"] if e["relation"] == "calls"]
    assert any(s.endswith("main") and d.endswith("add") for s,d in calls)

def test_load_import(tmp_path):
    f = tmp_path / "m.q"
    f.write_text('system"l util.q"\n\\l init.q\n')
    out = extract_q(f)
    imports = [e for e in out["edges"] if e["relation"] == "imports"]
    assert len(imports) == 2
```

- [ ] **Step 2: Run to verify fail**

Run: `cd <graphify clone> && pytest tests/test_q_extractor.py -v`
Expected: FAIL — `graphify.extractors.q` missing.

- [ ] **Step 3: Implement the bespoke extractor**

```python
# graphify/extractors/q.py
"""Graphify extractor for KDB+/q (bespoke: functions are assignments to lambdas)."""
from __future__ import annotations
from pathlib import Path
import importlib
from tree_sitter import Language, Parser

def _parser():
    mod = importlib.import_module("tree_sitter_q")
    return Parser(Language(mod.language()))

def _text(node, src: bytes) -> str:
    return src[node.start_byte:node.end_byte].decode("utf-8", "replace")

def extract_q(path: Path) -> dict:
    src = Path(path).read_bytes()
    root = _parser().parse(src).root_node
    stem = Path(path).stem
    file_nid = f"{stem}"
    nodes = [{"id": file_nid, "name": stem, "kind": "file", "line": 1}]
    edges = []
    ns = [""]  # current namespace stack from \d

    def qualify(name: str) -> str:
        if name.startswith("."):
            return name
        return f"{ns[-1]}.{name}".lstrip(".") and (ns[-1] + "." + name if ns[-1] else name)

    def add_node(nid, name, kind, line):
        nodes.append({"id": nid, "name": name, "kind": kind, "line": line})

    def add_edge(s, d, rel, line, conf="EXTRACTED"):
        edges.append({"src": s, "dst": d, "relation": rel, "line": line, "confidence": conf})

    def walk_calls(node, caller_nid):
        # find call/index nodes within a lambda body
        if node.type in ("call", "index"):
            fn = node.child_by_field_name("function")
            if fn is not None:
                callee = _text(fn, src)
                add_edge(caller_nid, qualify(callee), "calls", node.start_point[0]+1, "INFERRED")
        for c in node.children:
            walk_calls(c, caller_nid)

    def handle_assignment(node):
        left = node.child_by_field_name("left")
        right = node.child_by_field_name("right")
        if left is None or right is None:
            return
        name = qualify(_text(left, src))
        line = node.start_point[0] + 1
        nid = f"{stem}:{name}"
        if right.type == "lambda":
            add_node(nid, name, "function", line)
            add_edge(file_nid, nid, "contains", line)
            body = right.child_by_field_name("body")
            if body is not None:
                walk_calls(body, nid)
        else:
            add_node(nid, name, "variable", line)
            add_edge(file_nid, nid, "contains", line)
            # q-SQL table use inside a non-lambda assignment
            _scan_qsql(right, nid)

    def _scan_qsql(node, owner_nid):
        if node.type in ("select_statement","exec_statement","update_statement","delete_statement"):
            frm = node.child_by_field_name("from")
            if frm is not None:
                add_edge(owner_nid, f"{stem}:{_text(frm, src).split()[-1]}", "uses", node.start_point[0]+1, "INFERRED")
        for c in node.children:
            _scan_qsql(c, owner_nid)

    def handle_command(node):
        text = _text(node, src).strip()
        line = node.start_point[0] + 1
        if text.startswith("\\d"):
            parts = text.split()
            ns[-1] = parts[1] if len(parts) > 1 and parts[1] != "." else ""
        elif text.startswith("\\l"):
            tgt = text.split(maxsplit=1)[1].strip() if " " in text else ""
            if tgt:
                add_edge(file_nid, Path(tgt).stem, "imports", line)

    def handle_system_load(node):
        # system"l file.q"
        t = _text(node, src)
        if t.startswith('system"l ') or t.startswith("system\"l\t"):
            import re
            m = re.search(r'system"l\s+([^"]+)"', t)
            if m:
                add_edge(file_nid, Path(m.group(1).strip()).stem, "imports", node.start_point[0]+1)

    def walk(node):
        if node.type == "assignment":
            handle_assignment(node)
        elif node.type in ("system_command", "namespace_directive"):
            handle_command(node)
        elif node.type == "call":
            handle_system_load(node)
        for c in node.children:
            walk(c)

    walk(root)
    return {"nodes": nodes, "edges": edges}
```
> Match the exact node/edge key names Graphify's exporter expects — verify against `ARCHITECTURE.md` and an existing extractor's output before finalizing; adjust `kind`/`relation`/`confidence` field names if Graphify uses different keys.

- [ ] **Step 4: Run extractor tests**

Run: `pytest tests/test_q_extractor.py -v`
Expected: PASS.

- [ ] **Step 5: Add coverage**

Tests for: nested namespaces, q-SQL `uses` edge, `::` global, dotted callee resolution, var (table) assignment. Green each.

- [ ] **Step 6: Commit (in graphify clone, as a patch branch)**

```bash
git checkout -b q-support
git add graphify/extractors/q.py tests/test_q_extractor.py
git commit -m "Add bespoke q extractor (functions, calls, namespaces, imports, table uses)"
```

---

### Task 13: Real-repo parse-rate harness

**Wave 3. Parallel. Worktree isolation. Depends on T10.**

**Files:**
- Create: `scripts/parse_rate.py`, `test/real/.gitkeep`
- Test: `scripts/parse_rate.py` self-asserts a threshold

**Interfaces:**
- Consumes: built `tree_sitter_q` (T11) OR `tree-sitter parse` CLI.
- Produces: an ERROR-node rate report across cloned real q repos; exit non-zero if rate exceeds threshold.

- [ ] **Step 1: Write the harness**

```python
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
```

- [ ] **Step 2: Clone real corpora**

```bash
mkdir -p test/real
for r in KxSystems/kdb KxSystems/funq KxSystems/cookbook jonathonmcmurray/reQ; do
  git clone --depth 1 "https://github.com/$r.git" "test/real/$(basename $r)" 2>/dev/null || true
done
find test/real -name '*.q' | wc -l
```
Expected: a few hundred `.q` files.

- [ ] **Step 3: Run the harness (expect failures first pass)**

Run: `python scripts/parse_rate.py`
Expected: prints rate; likely FAILS threshold on first run.

- [ ] **Step 4: Triage top failures into new corpus rows**

For each frequent ERROR construct, add a minimal `test/corpus/*.txt` row reproducing it. These feed back to whichever grammar module owns it (a follow-up fix, not in this task). Record the failing constructs in `scripts/PARSE_FAILURES.md`.

- [ ] **Step 5: Commit harness + failure log**

```bash
git add scripts/parse_rate.py scripts/PARSE_FAILURES.md
git commit -m "Add real-repo parse-rate harness (<2% ERROR threshold)"
```

---

### Task 14: Graphify registration (wire the language in)

**Wave 4. Single agent. Sequential (after T11, T12). In the graphify clone, `q-support` branch.**
**Reference:** the 5 registration points from the Graphify code map.

**Files:**
- Modify: `graphify/extractors/__init__.py` (`LANGUAGE_EXTRACTORS`)
- Modify: `graphify/extract.py` (`_DISPATCH`)
- Modify: `graphify/detect.py:30` (`CODE_EXTENSIONS`)
- Modify: `graphify/watch.py:199` (`_WATCHED_EXTENSIONS`)
- Modify: `pyproject.toml` (`[q]` optional extra)

**Interfaces:**
- Consumes: `extract_q` (T12), `tree-sitter-q` wheel (T11).
- Produces: `.q` files routed to `extract_q` everywhere Graphify dispatches.

- [ ] **Step 1: Write failing dispatch test**

```python
# graphify/tests/test_q_dispatch.py
from pathlib import Path
from graphify.extract import _get_extractor
def test_q_routes(tmp_path):
    f = tmp_path / "x.q"; f.write_text("a:1\n")
    assert _get_extractor(f).__name__ == "extract_q"
```

- [ ] **Step 2: Run to verify fail**

Run: `pytest tests/test_q_dispatch.py -v`
Expected: FAIL — `.q` not in `_DISPATCH`.

- [ ] **Step 3: Apply the 5 registrations**

```python
# graphify/extractors/__init__.py — add to LANGUAGE_EXTRACTORS
from .q import extract_q
LANGUAGE_EXTRACTORS["q"] = extract_q
```
```python
# graphify/extract.py — import + add to _DISPATCH
from graphify.extractors.q import extract_q
_DISPATCH[".q"] = extract_q
```
```python
# graphify/detect.py:30 — add ".q" to CODE_EXTENSIONS
CODE_EXTENSIONS = { ..., ".q" }
```
```python
# graphify/watch.py:199 — inherits via CODE_EXTENSIONS; confirm ".q" present
_WATCHED_EXTENSIONS = CODE_EXTENSIONS | { ... }
```
```toml
# pyproject.toml — add optional extra
[project.optional-dependencies]
q = ["tree-sitter-q>=0.1,<0.2"]
```

- [ ] **Step 4: Run dispatch + extractor tests**

Run: `pytest tests/test_q_dispatch.py tests/test_q_extractor.py -v`
Expected: PASS.

- [ ] **Step 5: Commit**

```bash
git add graphify/extractors/__init__.py graphify/extract.py graphify/detect.py graphify/watch.py pyproject.toml tests/test_q_dispatch.py
git commit -m "Register q: dispatch, detect, watch, extractor index, [q] extra"
```

---

### Task 15: End-to-end pipeline validation + parse-rate gate

**Wave 4. Single agent. Sequential (final). Depends on all.**

**Files:**
- Create: `tests/e2e/test_pipeline.py` (in graphify clone), `tests/e2e/fixtures/sample.q`
- Modify: grammar modules as needed to clear parse-rate failures (loop)

**Interfaces:**
- Consumes: everything.
- Produces: proof that Graphify, with the wheel installed, extracts the expected graph from real `.q` files, and the parse-rate gate passes.

- [ ] **Step 1: Build + install both into one venv**

```bash
uv venv .venv-e2e && source .venv-e2e/bin/activate
uv pip install /Users/arvindiyer/development/q-tree-sitter/dist/*.whl
uv pip install -e <graphify clone>[q] pytest
python -c "import tree_sitter_q, graphify; print('ok')"
```
Expected: prints `ok`.

- [ ] **Step 2: Write the golden e2e test**

```python
# tests/e2e/test_pipeline.py
from pathlib import Path
from graphify.extract import _get_extractor

SAMPLE = '''\\d .app
load:{[f] system"l ",f}
trades:select sum size by sym from trade where date=.z.d
report:{[d] select from trades where date=d}
\\d .
'''

def test_pipeline(tmp_path):
    f = tmp_path / "sample.q"; f.write_text(SAMPLE)
    out = _get_extractor(f)(f)
    names = {n["name"] for n in out["nodes"]}
    assert {".app.load", ".app.trades", ".app.report"} <= names
    rels = {e["relation"] for e in out["edges"]}
    assert {"contains", "calls", "uses"} <= rels
```

- [ ] **Step 3: Run e2e**

Run: `pytest tests/e2e/test_pipeline.py -v`
Expected: PASS. If extraction keys mismatch Graphify's real schema, fix `extractors/q.py` (T12) and rerun.

- [ ] **Step 4: Run Graphify CLI on the real corpus**

```bash
graphify <path to test/real/funq> --out /tmp/q-graph 2>&1 | tail -20
ls /tmp/q-graph
```
Expected: Graphify completes and emits graph output containing q nodes/edges.

- [ ] **Step 5: Run the parse-rate gate; loop until it passes**

Run: `cd /Users/arvindiyer/development/q-tree-sitter && python scripts/parse_rate.py`
Expected: rate ≤ 2%. If not: take the top failures from `scripts/PARSE_FAILURES.md`, add corpus rows, fix the owning grammar module, `tree-sitter generate`, rebuild the wheel, reinstall, rerun. Repeat until the gate passes (loop-until-dry).

- [ ] **Step 6: Produce the Graphify integration patch + final commit**

```bash
# in graphify clone
git format-patch main --stdout > /Users/arvindiyer/development/q-tree-sitter/graphify-q-support.patch
# in grammar repo
cd /Users/arvindiyer/development/q-tree-sitter
git add scripts/ tests/ graphify-q-support.patch
git commit -m "E2E: Graphify extracts q graph; parse-rate gate passes; deliver integration patch"
```

---

## Self-Review

**Spec coverage:**
- Comprehensive grammar (operators, adverbs, q-SQL, control, literals, namespaces, RTL) → T3–T8. ✓
- External scanner (whitespace, comments, system commands) → T2. ✓
- Python wheel exposing `language()` → T1 (binding) + T11 (build/verify). ✓
- Bespoke Graphify extractor (function=assignment-to-lambda) → T12. ✓
- 5 registration points → T14. ✓
- Authoritative reference grounding → every grammar/scanner task cites `references/*.md`; mined in pre-work. ✓
- Real-repo corpus + <2% ERROR threshold → T13 + T15 gate. ✓
- Full pipeline run (install wheel into Graphify venv, extract from real .q) → T15. ✓
- Multi-agent parallelism → Parallel Execution Map (waves) + worktree isolation + non-overlapping files. ✓

**Placeholder scan:** No "TBD"/"implement later". Where full enumerations are large (170 keywords, full literal set), the data file `references/*.md` is the explicit source and the consuming code + extension pattern are shown with real examples — this is data-driven, not a placeholder.

**Type consistency:** Node `type`/field names are frozen in the taxonomy table (T1) and consumed identically in T12 (`child_by_field_name("left"/"right"/"function"/"body"/"from")`). `extract_q` signature and the `{"nodes","edges"}` schema match across T12/T14/T15. One open item flagged in T12/T9: whether `\d` is a distinct `namespace_directive` node or folded into `system_command` — T10 decides; T12 handles both by inspecting token text, so either resolution works.

## Known risk carried into execution

`grammar/commands.js` (T9) and the scanner (T2) have a coupling around `\d` vs generic `\…` lines. The plan resolves this defensively: the extractor (T12) parses command text, so the grammar may fold `\d` into `system_command` without breaking extraction. T10 makes the final structural call.
