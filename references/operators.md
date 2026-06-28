# q Operators (Primitive Glyphs) and Iterators

Authoritative glyph inventory with valences and overloads. Spec for the lexer/parser.

Sources:
- `ref/overloads.md` (the master overload table — copied closely below)
- `basics/syntax.md` (tokens, multi-char glyphs, spaces, projection, postfix)
- `basics/comparison.md` (comparison operators)
- `ref/iterators.md` (the six iterator glyphs and their resolutions)
- individual `ref/*.md` pages (add, subtract, etc.)

> **Key fact (syntax.md §Precedence):** all functions have the *same* precedence and
> evaluation is strictly **right-to-left** (long right scope). There is NO operator
> precedence to encode. Infix binds left arg = value immediately to its left; right arg
> = everything to its right.

> **Valence/rank** of a glyph is resolved at *parse/eval time* by how it is applied
> (prefix → unary, infix → binary, bracket `[…]` → by arg count). Most operator glyphs
> are **overloaded** and are inherently *variadic* at the token level. The grammar
> generally cannot fix a glyph's arity from the token alone.

---

## Multi-character tokens (syntax.md §Tokens)

The only multi-character symbol tokens (besides names/constants):

```
<=    less-than-or-equal
>=    greater-than-or-equal
<>    not-equal
::    null / view / set-global / Identity
/:    each-right (iterator)
\:    each-left (iterator)
':    each-prior / each-parallel (iterator)
```

Also note `0:` `1:` `2:` etc. (a **digit immediately followed by `:`**) are I/O / IPC
file operators — see syntax.md §"Colons in names". And `-i!` (negative-int bang) is an
internal function. These require no-space lexing.

---

## Primitive operator glyphs — valences & overloads

Copied/condensed from `ref/overloads.md`. "rank" = number of arguments when applied;
many glyphs are **overloaded** across ranks and argument types.

### `+` plus — `ref/add.md`
| rank | form | meaning |
|---|---|---|
| 2 | `x+y` | Add |
(monadic `+:` Flip exists in k; deprecated in q)

### `-` dash — `ref/subtract.md`, `ref/neg.md`
| rank | form | meaning |
|---|---|---|
| — | `-3` (immediately left of a number) | **negative literal** (part of the constant) |
| 2 | `2-3` | Subtract |
**Overload / whitespace quirk:** `-` is part of a negative constant only when adjacent
to a positive constant AND the token to its left is NOT a name/constant/`)`/`]`.
Otherwise it is Subtract or a function value. (See syntax.md §Spaces; reproduced in syntax.md ref file.)

### `*` star — `ref/multiply.md`
| rank | form | meaning |
|---|---|---|
| 2 | `2*3` | Multiply |
| (iterator arg via `*/`) | | first/last-style via over — not an overload of `*` itself |

### `%` percent — `ref/divide.md`
| rank | form | meaning |
|---|---|---|
| 2 | `x%y` | Divide (float division) |
> `%` is division, NOT modulo. `%` is never a comment/format char.

### `$` dollar — `ref/overloads.md`
| rank | example | meaning |
|---|---|---|
| 3 | `$[x>10;y;z]` | **Cond** (conditional) — `$` immediately followed by `[` |
| 2 | `"h"$y`, `` `short$y``, `11h$y` | Cast |
| 2 | `"H"$y`, `-11h$y` | Tok (parse string → data) |
| 2 | `x$y` | Enumerate |
| 2 | `10$"abc"` | Pad |
| 2 | `(…f)$(…f)` | dot product / matrix multiply (mmu) |

### `#` hash — `ref/overloads.md`
| rank | example | meaning |
|---|---|---|
| 2 | `2 3#til 6` | Take / Reshape |
| 2 | `` `s#1 2 3`` | Set Attribute |
(monadic `#:` count, deprecated)

### `_` underscore — `ref/overloads.md`
| rank | example | meaning |
|---|---|---|
| 2 | `3_ til 10` | Cut / Drop |
**Quirk:** `_` is BOTH an operator and a legal name character. Default lexing = part of
a name. A space is required to use it as Drop/Cut next to a name. (syntax.md §Spaces)

### `!` bang — `ref/overloads.md`
| rank | form | meaning |
|---|---|---|
| 2 | `x!y` | Dict (make dictionary) |
| 2 | `i!ts` | Enkey (key a table) |
| 2 | `0!tk` | Unkey |
| 2 | `noasv!iv` | Enumeration from index |
| 2 | `sv!h` | Flip Splayed/Partitioned |
| 2 | `0N!y` | display y and return it |
| 2 | `-i!y` | internal function (negative int) |
| 4 | `![t;c;b;a]` | functional Update / Delete |

### `?` query — `ref/overloads.md`
| rank | example | meaning |
|---|---|---|
| 2 | `"abcdef"?"cab"` | Find (index of y in x) |
| 2 | `10?1000`, `5?01b` | Roll |
| 2 | `-10?1000` | Deal |
| 2 | `0N?1000` | Permute |
| 2 | `x?v` | Enum Extend |
| 3 | `?[bools;a;b]` | Vector Conditional |
| 3 | `?[t;i;p]` | Simple Exec (functional) |
| 4 | `?[t;c;b;a]` | functional Select / Exec |
| 5 | `?[t;c;b;a;n]` | functional Select |
| 6 | `?[t;c;b;a;n;(g;cn)]` | functional Select |

### `@` at — `ref/overloads.md`, `ref/apply.md`, `ref/amend.md`
| rank | form | meaning |
|---|---|---|
| 2 | `l@i`, `@[l;i]` | Index At |
| 2 | `f@y`, `@[f;y]` | Apply At |
| 3 | `@[f;y;e]` | Trap At |
| 3 | `@[d;i;u]` | Amend At |
| 4 | `@[d;i;m;my]` | Amend At |
| 4 | `@[d;i;:;y]` | Replace At |

### `.` dot — `ref/overloads.md`, `ref/apply.md`, `ref/amend.md`
| rank | form | meaning |
|---|---|---|
| 2 | `l . i`, `.[l;i]` | Index (deep) |
| 2 | `g . gx`, `.[g;gx]` | Apply |
| 3 | `.[g;gx;e]` | Trap |
| 3 | `.[d;i;u]` | Amend |
| 4 | `.[d;i;m;my]` | Amend |
| 4 | `.[d;i;:;y]` | Replace |
**Quirk:** `.` is also (a) the namespace/compound-name separator (`.foo.bar`, `.z.p`),
(b) the decimal point in floats, (c) the date separator (`2024.01.01`). Default lexing =
part of a name/number; needs surrounding spaces to be the Apply/Index operator.
In the debugger `.` pushes the stack.

### `^` caret — `ref/fill.md`, `ref/coalesce.md`
| rank | form | meaning |
|---|---|---|
| 2 | `x^y` | Fill (fill nulls in y with x) / Coalesce |

### `~` tilde — `ref/match.md`, `ref/not.md`
| rank | form | meaning |
|---|---|---|
| 2 | `x~y` | Match (strict equality, returns boolean atom) |
(monadic `~:` Not in k; in q use `not`)

### `=` equal — `ref/equal.md`, `ref/group.md`
| rank | form | meaning |
|---|---|---|
| 2 | `x=y` | Equal (atomic, type-tolerant) |
(monadic `=:` Group in k; in q use `group`)

### `<` less-than — `ref/less-than.md`, `ref/asc.md`
| rank | form | meaning |
|---|---|---|
| 2 | `x<y` | Less Than |
(monadic `<:` `iasc`/grade-up in k)

### `>` greater-than — `ref/greater-than.md`, `ref/desc.md`
| rank | form | meaning |
|---|---|---|
| 2 | `x>y` | Greater Than |
(monadic `>:` grade-down in k)

### `<=` / `>=` / `<>` — `ref/less-than.md`, `ref/greater-than.md`, `ref/not-equal.md`
| rank | form | meaning |
|---|---|---|
| 2 | `x<=y` | Up To (≤) |
| 2 | `x>=y` | At Least (≥) |
| 2 | `x<>y` | Not Equal (XOR for booleans) |

### `|` bar — `ref/greater.md`, `ref/or.md`
| rank | form | meaning |
|---|---|---|
| 2 | `x|y` | Greater (max) — also keyword `or` |

### `&` ampersand — `ref/lesser.md`, `ref/and.md`, `ref/where.md`
| rank | form | meaning |
|---|---|---|
| 2 | `x&y` | Lesser (min) — also keyword `and` |
(monadic `&:` `where` in k)

### `,` comma — `ref/join.md`, `ref/enlist.md`
| rank | form | meaning |
|---|---|---|
| 2 | `x,y` | Join (concatenate) |
**Note:** also the list/argument/element separator inside `()` `[]` `{}` is `;`, NOT `,`.
`,` is the Join operator; commas separate q-SQL phrase subphrases and vector-table
columns. A leading comma `,2` displays a 1-item list (made with `enlist`).

### `:` colon — `ref/assign.md`, `ref/overloads.md`
| form | meaning |
|---|---|
| `a:42` | Assign (name a value) |
| `:42` (inside a lambda) | Explicit return |
| `0:` `1:` `2:` (digit then `:`) | file/IPC operators |
| `#:` `_:` `@:` etc. (operator then `:`) | k unary forms, deprecated |

### `::` colon-colon — `ref/identity.md`, views
| form | meaning |
|---|---|
| `name::value` inside a lambda | global assignment |
| `name::expr` outside a lambda | define a view (dependency) |
| `::` | Identity (generic null atom) / Null |

---

## Iterator (adverb) glyphs — `ref/iterators.md`, `ref/overloads.md`

Six glyphs. Applied **postfix** to an applicable value to derive a new function.
**A function derived by postfix application is ALWAYS infix syntax, regardless of rank.**

| glyph | iterator(s) | resolution by value rank |
|---|---|---|
| `'`  | **Each** (`u'`), **Case** (`int'`), **Compose** (`'[u;v]`) | rank-1 → Each/Case; bracket `'[u;v]` → Compose |
| `':` | **Each Parallel** (unary value `u':`), **Each Prior** (binary value `b':`) | resolved by value rank |
| `/:` | **Each Right** | binary |
| `\:` | **Each Left** | binary |
| `/`  | **Over**: Converge (`u/`), Do (`n u/`), While (`t u/`), Reduce (`b/`) | resolved by value rank + left-arg type |
| `\`  | **Scan**: Converge, Do, While, Accumulate | mirror of `/` but returns all intermediate results |

Keyword aliases for iterators (these ARE keyword functions): `each over peach prior scan`.

### Overloads of `/` and `\` outside iterator context (overloads.md)
- `/` not preceded by a value, with a space before it → **trailing comment** (rest of line).
- `/` alone on a line → **comment line**; solitary `/` … `\` → **multiline comment**.
- `\` ends a multiline comment; solitary `\` → exit script / toggle q↔k / Abort in debugger.
These comment vs iterator decisions are **whitespace-sensitive** (see syntax.md ref file).

### Iterator composition (syntax.md §Iterator composition)
A string of iterator glyphs with an applicable value to its left and **no spaces**
between any glyph or between the value and the leftmost glyph composes one derived
function, read left→right, e.g. `+\/:\:`.

---

## Summary: glyph → all meanings (one-glance)

```
+   Add                                   (2)
-   negative-literal | Subtract           (—,2)
*   Multiply                              (2)
%   Divide                                (2)
$   Cond | Cast | Tok | Enumerate | Pad | mmu   (3,2,2,2,2,2)
#   Take | Set-Attribute                  (2,2)
_   Drop/Cut | name-char                  (2,—)
!   Dict | Enkey | Unkey | Enum | Flip-splayed | display(0N!) | internal(-i!) | functional-update  (2..4)
?   Find | Roll | Deal | Permute | EnumExtend | VectorCond | functional-exec/select  (2..6)
@   Index-At | Apply-At | Trap-At | Amend-At | Replace-At   (2..4)
.   Index | Apply | Trap | Amend | Replace | name-sep | decimal | date-sep   (2..4,—)
^   Fill / Coalesce                       (2)
~   Match                                 (2)
=   Equal                                 (2)
<   Less Than        <=  Up To            (2)
>   Greater Than     >=  At Least         (2)
<>  Not Equal                             (2)
|   Greater (max) / or                    (2)
&   Lesser (min) / and                    (2)
,   Join / list-separator-is-`;`-not-comma (2)
:   Assign | explicit-return | file-ops(0:)   
::  global-assign | view | Identity/Null
'   Each | Case | Compose | Signal('msg)
':  Each Parallel | Each Prior
/:  Each Right        \:  Each Left
/   Over (+comment forms)     \  Scan (+comment/exit/toggle forms)
```

> `'` also has a unary form `'msg` = **Signal** an error (overloads.md §quote).
