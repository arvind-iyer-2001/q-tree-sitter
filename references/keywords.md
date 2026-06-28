# q Keywords / Reserved Words

Authoritative lists extracted from the KX docs. This is the spec for the lexer/parser.

Sources:
- `ref/ref.csv` (master keyword list with category + map-class)
- `ref/kwds.txt`, `ref/kwdcat.txt`, `ref/ref0.txt` (rendered keyword tables)
- `basics/qsql.md`, `ref/select.md`, `ref/exec.md`, `ref/update.md`, `ref/delete.md`
- `basics/control.md`, `ref/do.md`, `ref/if.md`, `ref/while.md`, `ref/exit.md`
- `basics/syntax.md` (control words, special constructs)

> Note: a "keyword" in q is a built-in word that names a function (verb) or is a reserved
> control/template word. Keywords are ordinary names in the `.q` namespace EXCEPT the
> q-SQL template words and control words, which have **special parse rules** and are NOT
> first-class values. See category (a) and (b) below.

---

## (a) q-SQL template words

These are NOT functions/values. They introduce the q-SQL query templates with their own
syntax (see `qsql.md`). Source: `basics/qsql.md`.

```
select
exec
update
delete
```

Associated sub-clause / structural words that appear only inside these templates
(also reserved within the template grammar — they are not standalone keywords):

```
by          / introduces the By phrase
from        / introduces the From phrase (required)
where       / introduces the Where phrase
distinct    / limit word, valid only in `exec` (and `select distinct`)
fby         / filter-by; a keyword function used in Where phrases (ref/fby.md)
```

> `fby` is listed in `ref.csv` under category `query`, so it is also a keyword function
> (callable), but in practice appears within q-SQL Where phrases.

> The virtual column `i` (row index) is reserved inside q-SQL phrases (`basics/qsql.md`
> §"Virtual column i"). It is not a global keyword.

---

## (b) Control words

These are NOT functions and do not return a result (they return the generic null `::`).
They use bracket-list syntax `word[e1;e2;…]`. Source: `basics/control.md`, `basics/syntax.md`.

```
do      [n; expr; …]        repeat expr/s n times          (ref/do.md)
if      [test; expr; …]     evaluate expr/s if test holds  (ref/if.md)
while   [test; expr; …]     evaluate expr/s while test     (ref/while.md)
```

`exit` is documented alongside control flow (`basics/control.md` §exit, `ref/exit.md`)
but is an ordinary keyword **function** (`exit 0`), category `control` in `ref.csv`.

> Conditional evaluation `$[test;et;ef;…]` (Cond) is NOT a keyword — it is the `$` glyph
> immediately followed by `[` (see operators.md / syntax.md). Likewise `do/if/while`
> are distinguished by the word appearing immediately before `[`.

---

## (c) Keyword functions / verbs

The complete set of built-in keyword functions, taken verbatim from `ref/ref.csv`
(format: `keyword, doc-file, description, category, map-class`). Some entries name
**multiple keywords** sharing one doc page (e.g. `aj aj0`, `bin binr`, `lj ljf`).

Total: 170 CSV rows; multi-word rows expand the keyword count further (see "Aliases" note).

### By category

**control**: `do`, `exit`, `if`, `while`

**env**: `getenv`, `gtime`, `ltime`, `setenv`

**interpret**: `eval`, `parse`, `reval`, `show`, `system`, `value`

**io**: `dsave`, `get`, `hclose`, `hcount`, `hdel`, `hopen`, `hsym`, `load`, `read0`,
`read1`, `rload`, `rsave`, `save`, `set`

**iterate**: `each`, `over`, `peach`, `prior`, `scan`

**join**: `aj`, `aj0`, `ajf`, `ajf0`, `asof`, `ej`, `ij`, `ijf`, `lj`, `ljf`, `pj`,
`uj`, `ujf`, `wj`, `wj1`

**list**: `count`, `cross`, `cut`, `enlist`, `except`, `fills`, `first`, `flip`,
`group`, `in`, `inter`, `last`, `mcount`, `next`, `prev`, `raze`, `reverse`, `rotate`,
`sublist`, `sv`, `til`, `union`, `vs`, `where`, `xprev`

**logic**: `all`, `and`, `any`, `not`, `or`

**math**: `abs`, `acos`, `asin`, `atan`, `avg`, `avgs`, `ceiling`, `cor`, `cos`, `cov`,
`deltas`, `dev`, `div`, `ema`, `exp`, `floor`, `inv`, `log`, `lsq`, `mavg`, `max`,
`maxs`, `mdev`, `med`, `min`, `mins`, `mmax`, `mmin`, `mmu`, `mod`, `msum`, `neg`,
`prd`, `prds`, `rand`, `ratios`, `reciprocal`, `scov`, `sdev`, `signum`, `sin`, `sqrt`,
`sum`, `sums`, `svar`, `tan`, `var`, `wavg`, `within`, `wsum`, `xexp`, `xlog`

**meta**: `attr`, `null`, `tables`, `type`, `view`, `views`

**query** (q-SQL keyword functions; see also category (a)): `delete`, `exec`, `fby`,
`select`, `update`

**sort**: `asc`, `bin`, `binr`, `desc`, `differ`, `distinct`, `iasc`, `idesc`, `rank`,
`xbar`, `xrank`

**table**: `cols`, `csv`, `fkeys`, `insert`, `key`, `keys`, `meta`, `ungroup`, `upsert`,
`xasc`, `xcol`, `xcols`, `xdesc`, `xgroup`, `xkey`

**text**: `like`, `lower`, `ltrim`, `md5`, `rtrim`, `ss`, `ssr`, `string`, `trim`, `upper`

### Alphabetical (flattened, all keywords expanded from multi-word rows)

```
abs acos aj aj0 ajf ajf0 all and any asc asin asof atan attr avg avgs
bin binr ceiling cols cor cos count cov cross csv cut
delete deltas desc dev differ distinct div do dsave
each ej ema enlist eval except exec exit exp
fby fills first fkeys flip floor
get getenv group gtime
hclose hcount hdel hopen hsym
iasc idesc if ij ijf in insert inter inv
key keys
last like lj ljf load log lower lsq ltime ltrim
mavg max maxs mcount md5 mdev med meta min mins mmax mmin mmu mod msum
neg next not null
or over
parse peach pj prd prds prev prior
rand rank ratios raze read0 read1 reciprocal reval reverse rload rotate rsave rtrim
save scan scov sdev select set setenv show signum sin sqrt ss ssr string sublist
sum sums sv svar system
tables tan til trim type
uj ujf ungroup union update upper upsert
value var view views vs
wavg where while within wj wj1 wsum
xasc xbar xcol xcols xdesc xexp xgroup xkey xlog xprev xrank
```

### map-class annotations (from `ref.csv` column 5)

Useful for grammar semantics but not lexing. `ref.csv` tags some keywords:
- `atomic`: `abs acos asin atan ceiling cos div exp floor log mod neg not null
  reciprocal signum sin sqrt tan xexp xlog or` (and others)
- `aggregate`: `all and any avg count dev first last max med min prd sum sums svar
  var wavg wsum`
- `uniform`: `asc avgs deltas desc differ fills in like lower mavg maxs mcount mdev
  mins mmax mmin msum next prev ratios reverse rotate upper within xasc xdesc xprev`

> Quirk: `ref.csv` has a couple of malformed rows: `rank` has an extra empty field
> (`sort,,uniform`) and `vs` has two map-class fields (`list,text,`). Treat the
> keyword name (column 1) as authoritative.

---

## Reserved-word caveats for a parser

1. **Keywords are not lexically reserved at the namespace level.** They live in `.q`.
   A user *can* shadow many of them (e.g. `count:5`), though doing so is bad practice
   and some are protected. For a Tree-sitter grammar, treat them as a closed keyword
   set but still allow them to appear in name-binding positions (LHS of `:`).

2. **Template / control words ARE structurally special.** `select exec update delete`
   and `do if while` change the grammar of what follows. They must be matched as
   keywords, not as generic identifiers, when followed by their constructs.

3. **`distinct`, `by`, `from`, `where`** are meaningful only inside q-SQL templates.

4. The `.Q`, `.q`, `.h`, `.j`, `.z` namespaces define many more dotted built-ins
   (e.g. `.Q.fmt`, `.z.p`, `.h.html`). These are dotted names, not bare keywords —
   handle them under the name/namespace rules in `syntax.md`.
