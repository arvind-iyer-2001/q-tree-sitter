# q Lexical & Grammatical Syntax Rules

The parsing-relevant rules: evaluation order, lambdas, application, whitespace
sensitivity, comments, statement separation, assignment, namespaces, and system
(backslash) commands. Spec for the grammar.

Sources:
- `basics/syntax.md` (the master syntax page — copied closely)
- `basics/function-notation.md` (lambdas, implicit args, rank, return)
- `basics/control.md` (control words, Cond)
- `basics/namespaces.md`, `basics/syntax.md §Names and namespaces`
- `basics/syscmds.md` (system / backslash commands)
- `ref/overloads.md` (`: ::` and comment glyphs)

---

## 1. Right-to-left evaluation, no precedence (syntax.md §Precedence)

- **All functions have equal precedence.** Evaluation is strictly **right-to-left**.
  `a * b + c` == `a*(b+c)`, NOT `(a*b)+c`.
- **Long right scope**: the right argument of an infix/unary function is the result of
  evaluating everything to its right (subject to parentheses). The left argument of an
  infix function is the single value immediately to its left.
  - `count first (2 3 4;5 6)` → arg of `count` is `first (2 3 4;5 6)` = `2 3 4`.
  - `2 3 * 4 5 - 6 7` → `2 3 * (4 5 - 6 7)` = `2 3 * -2 -2`.
- Within compound expressions: index/argument expressions also evaluate right→left, BUT
  **function bodies, conditional `$[…]`, and control statements evaluate left→right**
  (top→bottom across lines).

```
q)x:10
q)(x+5; x:20; x-5)   / right-to-left across list items
25 20 5
q)f:{a:10; :x+a; a:20}   / left-to-right inside a lambda
q)f[5]
15
```

---

## 2. Lambda / function notation (function-notation.md, syntax.md §Function notation)

```
{[name1;name2;…;nameN] expr1; expr2; … }
```
- Braces `{ }` delimit a lambda. Optional **signature** `[a;b;…]` (up to **8** names)
  as the first element; then zero or more `;`-separated expressions.
- **Implicit args**: a lambda of rank ≤3 may omit the signature and use default names
  `x` (1st), `y` (2nd), `z` (3rd). E.g. `{x+y*10}` rank 2, `{x+z*10}` rank 3.
- Rank = number of signature names; for unsigned, the highest of `x`/`y`/`z` used.
- Result = value of the last expression, OR an explicit return `:expr`.
- Signatures may use **patterns** (pattern.md) since recent versions.
- A lambda may span multiple lines in a script (continuation lines indented ≥1 space).
- Empty `{}` is the identity-like rank-? function; `{[]…}` is rank 0.

### Explicit return (syntax.md §Colon, function-notation.md)
- Inside a lambda, `:value` terminates the function and returns `value`.
  ```
  if[type[x]<0; :x];   / early return
  ```
- `:` for return is distinguished from `:` for assignment by the absence of a name to
  its immediate left (i.e. statement-initial `:`).

---

## 3. Application forms (syntax.md §Prefix/infix/postfix, application)

```
f[x]      bracket notation (args / indexes), `;`-separated, may be empty f[]
f x       prefix (unary apply, or list-indexing "abc" 1 0)
x + y     infix (binary operators / derived functions)
f\        postfix (ONLY iterators apply postfix)
```
- `f[a;b;c]` applies `f` to 3 args; `m[0;0]` indexes a matrix; `m[]`/`f[]` = all items /
  no-arg call. Bracket lists need NOT contain a `;` (one or zero expressions allowed).
- Operators may be used infix or in bracket form: `+[a;b]` == `a+b`.
- **Projection**: supplying some but not all args/indexes, or eliding with `;`:
  - `3+` is "3 plus" (left-arg projection of an operator).
  - `f[a;;c]` projects over the elided 2nd arg.
  - Trailing elision: `t[1]` (drop trailing indexes).
- **Apply / Index operators**: `.[f;args]` (Apply, deep index), `@[f;arg]` (Apply At,
  rank-1 index). Also amend/trap forms — see operators.md.
- **Juxtaposition**: prefix application and vector notation both use juxtaposition; vector
  items bind MORE tightly than function application. `{x-2} 5 6` applies to the vector
  `5 6`, not to `5` then `6`.

### Postfix yields infix (syntax.md §Postfix yields infix; iterators.md)
- An iterator applied postfix to a value derives a function that **has infix syntax,
  regardless of rank** (e.g. `count'` is unary but infix). To apply such a derived
  function non-infix, parenthesize it (`(count')txt`) or use brackets (`count'[txt]`).
- Parentheses around an infix function capture it as a value: `(+\)`, `(,/)`, `(*)`.

---

## 4. Whitespace sensitivity (syntax.md §Spaces) — CRITICAL for the lexer

Generally spaces between tokens are optional. The **exceptions** (no space allowed):
- Within iterator tokens: `':`, `\:`, `/:` (the two glyphs must be adjacent).
- Between a digit and `:` in file ops like `0:`.
- Between the two `:` in `::` (global assign / view).
- Between an iterator glyph and the value/iterator immediately to its left
  (postfix & composition).
- Between an operator glyph and a `:` to its right that denotes assignment (`+:` k-form).

Spaces REQUIRED:
- A `/` meant as a **comment** must be preceded by a space or newline; otherwise it is
  read as part of an iterator (`f/`).
- `_` and `.` default to being part of a name; a space is needed on either side to use
  them as the Drop/Cut (`_`) or Apply/Index (`.`) operator next to a name.
- At least one space between neighboring numeric constants in vector notation
  (`2 3 4` is a vector; `234` is one number).

### Negative numbers vs subtraction (syntax.md §Spaces — `-`)
`-` is part of a negative constant only if adjacent to a positive constant AND the token
to its left is NOT a name, constant, `)`, or `]` (with no space). Examples:
```
x-1        / x minus 1            (- is Subtract: left token is a name)
x -1       / x applied to -1      (-1 is a negative literal)
3.5-1      / 3.5 minus 1
3.5 -1     / 2-element numeric list  (-1 is a literal)
x[1]-1     / x[1] minus 1         (left token is ])
(a+b)- 1   / (a+b) minus 1        (left token is ))
```
> This rule needs left-context, not pure character lookahead — a classic Tree-sitter
> external-scanner case.

---

## 5. Comments (syntax.md §Comments, overloads.md §slash)

- **Trailing comment**: ` / …` — a `/` PRECEDED BY A SPACE (or newline) comments the rest
  of the line. `2+2 / note`.
- **Line comment**: a `/` at the start of a line → whole line ignored.
- **Multiline comment**: a line containing a **solitary `/`** begins a block comment;
  terminated by a line with a solitary `\` OR end of script.
  ```
  /
    block comment
  \
  ```
- **Script exit `\`**: a solitary `\` NOT closing a block comment **exits the script** —
  everything after it is ignored.
- **Final comment**: text after `\\` (quit) is ignored — used for trailing notes.
- A `/` inside a string or right after a system command is NOT a comment
  (`count"2/3"` → 3; `\l /data/files`).

---

## 6. Statement separation (syntax.md §List notation, multiline)

- Expressions are separated by `;` inside compound expressions `(…)`, `[…]`, `{…}`.
- At top level / in a script, a **newline** separates statements (each line is an
  expression), EXCEPT continuation: an expression may span multiple lines if broken
  after a `;` and the continuation lines are indented by ≥1 space.
  ```
  (a + b;
    ;
    c - d)        / the 3-item list (a+b;;c-d)
  ```
- **Empty expression**: an empty slot between `;` (or all-blanks) denotes the null atom
  `::`. `(a+b;;c-d;)` has empty 2nd and 4th items.
- Inside brackets, multiline is allowed freely (the bracket stays open).

---

## 7. Lists / vectors / tables literal notation (syntax.md)

- **List notation**: `(e1;e2;…)` — `;`-separated, parenthesized. `()` is the empty list;
  at least one `;` required otherwise (`(e)` is just a parenthesized subexpression).
- **Vector notation**: same-type items juxtaposed with spaces (numbers) or no spaces
  (booleans `0101b`, symbols `` `a`b`c ``, chars `"abc"`). See datatypes.md.
- **Table notation**: `([keycols] col1:vals; col2:vals; …)`; empty `[]` = simple
  (unkeyed) table. Column names default to variable names if values given as bare names.
- **Dictionary**: `keys!values`.

---

## 8. Assignment (syntax.md §Colon, §Colon colon; ref/assign.md)

- `name:value` — assign (name a value). Most common use of `:`.
- `name::value`:
  - inside a lambda → **global assignment** (assign to a global, not local).
  - at top level → **define a view** (dependency): `v::select … from t`.
- Amend-style assignment operators exist: `+:`, `-:`, `,:` etc. via Amend; e.g. `x+:1`.
- `:value` at the start of a statement inside a lambda → explicit return (§2).
- Indexed/typed assignment: `x[i]:y`, `@[x;i;:;y]`, etc.

---

## 9. Names and namespaces (syntax.md §Names and namespaces, namespaces.md)

- A **name** = letters `A-Za-z`, digits `0-9`, dot `.`, underscore `_`. First char may
  NOT be a digit or underscore.
- Underscores in names are **strongly deprecated** (collide with Drop): `foo_bar`.
- **Compound (dotted) names**: segments separated by `.`, e.g. `.foo.bar`, `a.b.c`.
  Two dots cannot be adjacent. A leading dot = **absolute** name (`.foo`); otherwise
  relative.
- **Namespaces** identified by a leading dot. One-char namespaces are reserved for KX:
  `.h .j .q .Q .z`. The default namespace is `.` (the root K-tree).
- `\d name` switches the current namespace/directory (see §11). Objects defined in a new
  namespace create it.

---

## 10. Conditional & control constructs (syntax.md §Conditional…, control.md)

A `;`-separated bracket list preceded immediately by a special token:
```
$[a;b;c]        Cond           ( `$` immediately before `[` )
do[a;b;c]       control word
if[a;b;c]       control word
while[a;b;c]    control word
```
- Cond / control statements evaluate their expression list **left→right**.
- Control words return the generic null `::`; they are NOT functions and have no value.
- `$[test;then;else]`; with more args, if/elseif chains: `$[t1;e1;t2;e2;else]`.
- The distinction `$[` (Cond) vs `$ [` (Cast applied with brackets) and word-vs-name for
  `do/if/while` depends on the token IMMEDIATELY before `[` with no space.

---

## 11. System / backslash commands (basics/syscmds.md)

Form: `\cmd [params]`. At the start of a line/statement. With params omitted, value-
setting commands display the current value. `system "cmd"` is the programmatic equivalent
(string, no leading backslash).

Complete list (from syscmds.md):

| cmd | argument syntax | meaning |
|---|---|---|
| `\a` | `\a` / `\a ns` | list tables (in namespace) |
| `\b` | `\b` / `\b ns` | list dependencies (views) |
| `\B` | `\B` / `\B ns` | list pending views |
| `\c` | `\c` / `\c r c` | console size (rows cols) |
| `\C` | `\C` / `\C r c` | HTTP display size |
| `\cd` | `\cd` / `\cd fp` | get/set current directory |
| `\d` | `\d` / `\d ns` | get/set current namespace (directory) |
| `\e` | `\e` / `\e mode` | error-trap mode (0/1/2) |
| `\E` | `\E` | TLS server mode (display) |
| `\f` | `\f` / `\f ns` | list functions |
| `\g` | `\g` / `\g mode` | garbage-collection mode (0/1) |
| `\l` | `\l name` / `\l .` | load file/dir; reload current dir |
| `\o` | `\o` / `\o n` | UTC offset (hours, or minutes if abs>23) |
| `\p` | `\p [rp,][host:][port\|service]` | listening port |
| `\P` | `\P` / `\P n` | display precision (0..17) |
| `\r` | `\r` (primary) / `\r src dst` (rename) | replication primary / rename file |
| `\s` | `\s` / `\s N` | secondary threads (N<0 = processes) |
| `\S` | `\S` / `\S n` | random seed |
| `\t` | `\t` / `\t N` / `\t expr` / `\t:n expr` | timer interval / time an expr / time n reps |
| `\T` | `\T` / `\T n` | client timeout (seconds) |
| `\ts` | `\ts expr` / `\ts:n expr` | time AND space of an expr |
| `\u` | `\u` | reload user password file |
| `\v` | `\v` / `\v ns` | list variables |
| `\w` | `\w` / `\w 0\|1` / `\w n` | memory usage / interned syms / set mem limit |
| `\W` | `\W` / `\W n` | week offset (0=Saturday, default 2=Monday) |
| `\x` | `\x .z.p*` | expunge a `.z.*` callback (restore default) |
| `\z` | `\z` / `\z 0\|1` | date-parse format (0=mm/dd/yyyy, 1=dd/mm/yyyy) |
| `\1` | `\1 filename` | redirect stdout |
| `\2` | `\2 filename` | redirect stderr |
| `\_` | `\_` / `\_ scriptname` | client write-access check / make runtime script |
| `\` | `\` | clear one debug stack level / toggle q↔k / abort |
| `\\` | `\\` | quit session (in a func: `value"\\\\"` or `exit 0`) |

Notes:
- `\t` is overloaded: integer → set timer; non-integer expr → time it; `:n` prefix → n
  repetitions. Same `:n` form for `\ts`.
- `\1`/`\2` take a filename; `\\` with trailing text → text ignored (final comments).
- **OS escape**: if a `\…` line is NOT a recognized system command, it is passed to the
  OS shell (e.g. `\ls`). Typos can therefore reach the OS.
- Ctrl-C = interrupt; Ctrl-Z = kill session (nothing saved).

---

## 12. Special constructs outside ordinary expressions (syntax.md §Special constructs)

`/ \ : '` have special meanings outside ordinary expressions — system commands and
debugging controls. In the debugger:
- `\` clears one stack level,
- `'` re-signals / `'msg` signals,
- `.` pushes the stack.

---

## Tree-sitter challenge summary (the hard parts)

1. **No precedence + right-to-left**: expression grammar is flat; bind right arg as the
   whole remaining right expression. Easy to get wrong if you assume left-assoc infix.
2. **Whitespace-sensitive tokens** (need an external scanner):
   - `-` negative-literal vs Subtract (depends on LEFT token + no-space).
   - ` /` trailing comment vs `f/` iterator (depends on preceding space).
   - `_`/`.` as operator vs name-character (depends on surrounding spaces).
   - `':` `\:` `/:` `::` `0:` must be lexed as single tokens (no internal space).
3. **Glyph overloading by rank/type**: `$ # ! ? @ . _ ' / \` mean different things at
   different ranks — generally not resolvable at lex time (see operators.md).
4. **Comment forms**: solitary-`/`…`\` block, solitary-`\` script-exit, `\\` quit-with-
   trailing-text — all line-structure dependent (external scanner).
5. **`\` ambiguity**: system command vs OS escape vs script-exit vs q/k toggle.
6. **q-SQL templates** (`select/exec/update/delete`) inject a sub-grammar with reversed
   parse-vs-eval order (see qsql.md).
7. **Postfix-yields-infix**: derived functions are infix regardless of rank; parenthesized
   captures change application — affects how application is parsed.
8. **Temporal/symbol/byte literals** embed operator characters (`. : D T` backtick) and
   must be single greedy tokens (see datatypes.md).
9. **Multiline continuation** inside brackets and via leading-space indentation.
