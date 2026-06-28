# q-SQL Query Template Grammar

Exact grammar of `select`, `exec`, `update`, `delete`. These have their OWN syntax,
distinct from ordinary q. Spec for the parser.

Sources:
- `basics/qsql.md` (template syntax, phrases, evaluation order — copied closely)
- `ref/select.md`, `ref/exec.md`, `ref/update.md`, `ref/delete.md`
- `basics/funsql.md` (functional equivalents)
- `ref/fby.md`

---

## Template syntax (qsql.md §Template syntax)

Square brackets `[…]` mark OPTIONAL elements. (These are doc meta-brackets, not q
brackets.)

```
select [Lexp]      [ps] [by pb] from texp [where pw]
exec   [distinct]  [ps] [by pb] from texp [where pw]
update             ps   [by pb] from texp [where pw]
delete                          from texp [where pw]    / delete ROWS
delete             ps           from texp               / delete COLUMNS
```

Where:
- `Lexp` = Limit expression (select only)
- `ps`   = Select phrase  (the column expressions)
- `pb`   = By phrase      (grouping)
- `texp` = Table expression (the From phrase; REQUIRED in all four)
- `pw`   = Where phrase   (filter)

### Clause order & optionality
- `from texp` is **required** in all templates.
- `select`: `Lexp`, `ps`, `by pb`, `where pw` all optional. `select from t` is legal
  (returns whole table; no `*` wildcard needed).
- `exec`: only limit word allowed is `distinct`; `ps`, `by pb`, `where pw` optional.
- `update`: `ps` present (the assignments); `by pb`, `where pw` optional.
- `delete`: TWO forms —
  - `delete from t [where pw]` → delete rows (no select phrase)
  - `delete ps from t` → delete columns (`ps` = list of column names, NO where allowed)

### Keyword order in source
The literal token order is fixed:
`select`/`exec`/`update`/`delete` → [limit] → [select-phrase] → [`by` by-phrase] →
`from` → table-expr → [`where` where-phrase].

> The parser must accept the clauses ONLY in this order. `by` precedes `from`; `where`
> follows `from`. This is the reverse of execution order (below).

---

## Evaluation order (qsql.md — for semantics, NOT parse order)

```
1. From phrase        texp
2. Where phrase       pw
3. By phrase          pb
4. Select phrase      ps
5. Limit expression   Lexp   (select only)
```

---

## From phrase (qsql.md §From phrase)

`from texp` where `texp` is:
- a table or dictionary value (**call by value**), e.g. `from ([]a:1 2;b:3 4)`, `from t`
- a symbol atom naming a table/dictionary in memory or on disk (**call by name**),
  e.g. `` from `t ``, `` from `:path/to/db ``

Side effects: by value → returns modified table/dict; by name (update/delete) → amends
in place and returns the name.

---

## Where phrase (qsql.md §Where phrase)

- A comma-separated list of subphrases (constraints). Each is a boolean-list expression.
- Subphrases are **successive filters** applied left→right (NOT a single ANDed vector):
  `where c2>15,c3<3.0` filters by `c2>15` first, then tests `c3<3.0` on survivors.
  Different performance from `where (c2>15) and c3<3.0`.
- Can be a literal boolean list: `select from t where 101b`.
- Use `fby` (`ref/fby.md`) to filter on groups.

---

## By phrase (qsql.md / select.md §By phrase)

- `by pb`, a comma-separated list of subphrases producing grouping key column(s).
- Grouping columns become keys of the result table (for `select`).
- Named computed group keys allowed: `select … by c:a from t`.

---

## Select phrase (select.md §Select phrase) — column expressions

- Comma-separated list of subphrases, one per result column.
- Each subphrase is a q expression evaluated right-to-left in normal q syntax, but the
  list of subphrases is evaluated left→right.
- **Computed columns**: `colname:expr` names a column (the colon NAMES a result column,
  it does NOT assign a workspace variable). E.g. `select dbl:c3*2 from t`.
- Unnamed computed column → q names it after the leftmost term, else `x`; duplicate names
  get `1`,`2`,… suffixes. (V4.0+ throws `'dup names for cols/groups` for some collisions.)
- A computed column cannot be referenced by another subphrase in the same query.
- Absent select phrase → all columns returned (no `*`).
- **Join in a subphrase must be parenthesized**: `select (id,'4),val from tbl`
  (otherwise the comma is read as the phrase separator).

---

## Limit expression (select.md §Limit expression) — `select` only

```
select[n]            first n rows (last n if negative)
select[m n]          n rows starting at row m
select[order]        sort by a column/table: < ascending, > descending
select[n;order]      first/last n after ordering
select distinct      distinct rows
```
Example: `select[3;>price] from bids where sym=s,size>0`.
For `exec`, the only limit word is `distinct`.

---

## Name resolution in subphrases (qsql.md §Names in subphrases)

A name resolves (in order) as:
1. a column or key name of `texp` (or foreign-key-linked tables)
2. a local name / argument of the enclosing function
3. a global in the current working namespace

- Dot notation reaches foreign keys: `select sname:s.name, qty from sp`.
- Explicit namespace ref: `` select (`. `toplevel) x from t ``.
- Implicit args `x y z` are visible to the compiler ONLY outside the Select/By/Where
  phrases; the From phrase is NOT masked. (Affects functional/lambda use.)

---

## Virtual column `i` (qsql.md §Virtual column i)

- `i` = row index (0-based) of each record; available in any phrase.
- In a partitioned table, `i` is relative to the partition.
- Never appears as a result column name.
- `select i, c1 from t`, `select from t where i in 0 2`.

---

## Special / restricted constructs

- **Cond `$[…]` is NOT allowed** inside qSQL expressions (throws `'rank`). Wrap in a
  lambda `{$[x;…;…]}` or use **Vector Conditional** `?[…]` instead. (qsql.md §Cond)
- **No sorting clause**: use `xasc`/`xdesc` on the result (qsql.md §Sorting).
- **Special aggregation functions** recognized specially inside `select`/`exec`
  (qsql.md §Special functions): 
  ```
  avg  cor  count  cov  dev  first  last  max  med  min  prd  sum  var  wavg  wsum
  ```
  When wrapped inside another function, the special handling is lost.
- **Column names cannot be query parameters**; use functional qSQL for that.
- Any lambda/stored proc may be used in a phrase: `select stock, f amount from trade`.

---

## Functional forms (basics/funsql.md) — what the templates compile to

The interpreter translates templates into functional SQL. The functional operators:

```
?[t;c;b;a]            functional Select        (rank 4)
?[t;c;b;a;n]          Select with limit n      (rank 5)
?[t;c;b;a;n;(g;cn)]   Select grouped           (rank 6)
?[t;i;p]              Simple Exec              (rank 3)
![t;c;b;a]            functional Update / Delete (rank 4)
```
Where (overloads.md / funsql.md):
- `t` = table, `c` = where-specifications (list of constraint parse trees),
- `b` = group-by specifications (dict, or `0b`/`()` for none),
- `a` = select/aggregate specifications (dict of name→parse-tree),
- `n` = limit, `(g;cn)` = grouping function and column name.

> A Tree-sitter grammar normally parses the TEMPLATE form; the functional `?[…]`/`![…]`
> forms are just ordinary operator applications and need no special grammar.

---

## insert / upsert (related, not templates)

- `insert` (`ref/insert.md`) and `upsert` (`ref/upsert.md`) are ordinary keyword
  functions, not templates: `` `t insert (…)``, `t upsert (…)``, `` `:db/t upsert …``.
- `,:` (Join-Amend) and `upsert` are commonly used to append rows.

---

## Parser checklist for q-SQL
1. Trigger on leading keyword `select|exec|update|delete` (these are special words).
2. Enforce token order: `[limit] [select-phrase] [by by-phrase] from table-expr [where where-phrase]`.
3. Phrase = comma-separated subphrases; subphrase = q expression with `:` allowed as
   column-naming (not assignment).
4. `from` and (for delete) the two-form split are mandatory structural anchors.
5. Disallow / specially handle `$[…]` Cond inside phrases (optional — could be a lint).
6. `i`, the special aggregates, and `fby` are ordinary names within phrases.
