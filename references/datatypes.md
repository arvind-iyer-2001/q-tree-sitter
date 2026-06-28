# q Datatypes and Literal Lexical Forms

The exhaustive datatype table plus literal syntax for every type. This drives the scanner.

Sources:
- `basics/datatypes.md` (the canonical type table — copied below)
- `ref/cast.md` (type number ↔ char code ↔ symbol name mapping)
- `basics/syntax.md` (vector notation, string escapes, symbol/temporal constants)
- `ref/tok.md` (upper-case codes / string parsing)

---

## Basic datatype table (datatypes.md)

```
n   c   name      sz  literal             null  inf   SQL
------------------------------------------------------------------
0   *   list                                                       (general/mixed list)
1   b   boolean   1   0b                                           
2   g   guid      16                       0Ng                     
4   x   byte      1   0x00                                         
5   h   short     2   0h                   0Nh   0Wh   smallint
6   i   int       4   0i                   0Ni   0Wi   int
7   j   long      8   0j   (also 0)        0Nj   0W    bigint    (0N is long null)
8   e   real      4   0e                   0Ne   0We   real
9   f   float     8   0.0  (also 0f)       0n    0w    float     (0Nf also)
10  c   char      1   " "                  " "                     
11  s   symbol        `                    `           varchar
12  p   timestamp 8   dateDtimespan        0Np   0Wp   
13  m   month     4   2000.01m             0Nm   0Wm   
14  d   date      4   2000.01.01           0Nd   0Wd   date
15  z   datetime  8   dateTtime            0Nz   0wz   timestamp  (DEPRECATED, use 12)
16  n   timespan  8   00:00:00.000000000   0Nn   0Wn   
17  u   minute    4   00:00                0Nu   0Wu   
18  v   second    4   00:00:00             0Nv   0Wv   
19  t   time      4   00:00:00.000         0Nt   0Wt   time
```

Columns: `n` = type number (short) from `type`; `c` = char code (lower-case for Cast,
upper-case for Tok / Load-CSV); `sz` = byte size.

Notes from datatypes.md:
- Default integer type is **long** (`7h`, `"j"`). (Before V3.0 it was int.)
- No string type: a "string" is a char vector (type `10h`).
- `0Wh` displays as `32767h`; there is no display for short infinity. Integer infinity
  arithmetic is undefined; float infinity arithmetic is IEEE754.
- Valid date range `0001.01.01` … `9999.12.31`.
- `15h` datetime is deprecated in favour of `12h` timestamp.

### type-number sign rule
`type` returns a short:
- `0h` for a **general list**
- **negative** for **atoms** of basic datatypes (e.g. a long atom is `-7h`)
- **positive** for **vectors** and everything else (e.g. a long vector is `7h`)

### char-code ↔ type ↔ symbol-name (cast.md)
```
1h "b" `boolean   2h "g" `guid     4h "x" `byte      5h "h" `short
6h "i" `int       7h "j" `long     8h "e" `real      9h "f" `float
10h "c" `char     12h "p" `timestamp  13h "m" `month  14h "d" `date
15h "z" `datetime 16h "n" `timespan  17h "u" `minute  18h "v" `second  19h "t" `time
```
`0h`/`"*"` = Identity. Upper-case letter or negative short = Tok (parse from string).

---

## Other datatypes (datatypes.md)

```
20-76   enums                       (`xxx$ enumerations; 20h reserved since V3.0)
77      anymap
78-96   77+t : mapped list of lists of type t  (78 boolean … 96 time)
97      nested sym enum  (`sym$ enumeration)
98      table
99      dictionary
100     lambda
101     unary primitive
102     operator
103     iterator
104     projection
105     composition
106     f'   (each-derived)
107     f/   (over-derived)
108     f\   (scan-derived)
109     f':  (each-prior/parallel-derived)
110     f/:  (each-right-derived)
111     f\:  (each-left-derived)
112     dynamic load
```

---

## Literal lexical forms (the scanner spec)

### Booleans
- Atom: `0b`, `1b`
- Vector: a run of `0`/`1` digits ending in `b`, e.g. `0b`, `1b`, `0101b`, `01110001b`.
- Null: there is no separate boolean null (booleans cannot be null).

### Byte
- Atom: `0x` followed by an even number of hex digits for a single byte → `0x00`, `0xff`, `0x1a`.
- Vector: `0x` followed by 2N hex digits → `0x010203`, `0x616263`. Hex digits `0-9 a-f` (and `A-F`).

### Integers (short / int / long)
- Long (default): bare integer `42`, or with `j` suffix `42j`. Negative `-42`.
- Int: `42i`.
- Short: `42h`.
- Vector: space-separated numbers with a **single trailing type char** applying to all:
  - `2 3 4 5 6h`  (short vector)
  - `2 3 4 5 6i`  (int vector)
  - `2 3 4 5 6`   (long vector, no suffix)
  - `2 3 4 5 6j`  (long vector)
- Null / inf: `0Nh 0Wh` (short), `0Ni 0Wi` (int), `0Nj/0N 0Wj/0W` (long), and negatives `-0Wh -0Wi -0W`.

### Real / Float
- Float (default for decimals): `0.0`, `3.14`, `0f` (explicit), `42f`, exponential `1.2e20`, `1.234568e+08`.
- Real (4-byte): `0e`, `3.14e`, `42e`.
- Vector: `2 3 4 5.6` (a single decimal makes the whole vector float), `2 3 4 5 6f`,
  `3.4 57 1.2e20`. Real vector `1 2 3e`.
- Null / inf: float `0n 0w -0w` ; real `0Ne 0We -0We` ; float-null also `0Nf`.

### Char and Strings
- Char atom: a single char in double quotes → `"a"`, `" "`.
- String (char vector): zero or 2+ chars in double quotes → `"abc"`, `""`.
- Escapes inside `"…"` (syntax.md §Strings): 
  ```
  \"     double quote
  \NNN   character with octal value NNN (exactly 3 octal digits)
  \\     backslash
  \n     newline
  \r     carriage return
  \t     horizontal tab
  ```
- Multibyte (UTF-8) chars occupy multiple bytes in the char vector.

### Symbols
- Atom: backtick + a string of name characters → `` `a ``, `` `ibm ``, `` `a.b_2 ``.
- Empty symbol: a lone backtick → `` ` ``.
- Vector: juxtaposed backtick-symbols, NO spaces → `` `ibm`aapl`msft ``.
- Symbols whose name isn't a valid token: build via cast, `` `$"hello world" `` (= `"S"$x`).
- File/handle symbols: a colon after the backtick → `` `:path/to/file ``, `` `:/abs/path ``,
  `` `:host:port `` (a hsym). These are "filepath" symbols (datatypes.md §Filepaths).

### Guid (type 2, 16 bytes)
- **No literal syntax.** Displayed/parsed as 8-4-4-4-12 hex:
  `337714f8-3d76-f283-cdc1-33ca89be59e9`.
- Created via `"G"$"…"`, `0x0 sv 16?0xff`, or Deal `-2?0Ng`.
- Null guid: `0Ng` (displays `00000000-0000-0000-0000-000000000000`).
- Only scalar primitives are `= < >` (like sym).

### Temporal literals (the trickiest part of the lexer)

Separators used: `.` (date), `D` (timestamp date↔time), `T` (datetime date↔time),
`:` (time fields), `m` (month suffix). Suffix type chars: `m d p z n u v t` overlap with
other meanings, so context is needed.

| type | literal grammar | examples |
|---|---|---|
| month (13) | `YYYY.MMm` | `2000.01m`, `2017.01`*(see note)*, `2003.07m` |
| date (14)  | `YYYY.MM.DD` | `2000.01.01`, `2012.09.15`, `2017.01.18` |
| timestamp (12) | `date``D``timespan` i.e. `YYYY.MM.DDDhh:mm:ss.fffffffff` | `2000.01.01D00:00:00.000000042`, `2024.10.07D20:00:00.000603286` |
| datetime (15) | `date``T``time` i.e. `YYYY.MM.DDThh:mm:ss.fff` | `2000.02.12T00:00:00.000` |
| timespan (16) | `[d``D``]hh:mm:ss.fffffffff` (9 fractional digits, optional day count) | `00:00:00.000000000`, `0D12:00:00.000000000`, `-106751D23:47:16.854775806` |
| minute (17) | `hh:mm` | `00:00`, `09:29`, `12:00` |
| second (18) | `hh:mm:ss` | `00:00:00`, `09:29:15`, `12:00:00` |
| time (19) | `hh:mm:ss.fff` (3 fractional digits) | `00:00:00.000`, `09:04:59.000`, `20:00t` |

Notes:
- A trailing lowercase suffix can disambiguate: `2017.01` is parsed as a **month**
  literal only when written with the `m` suffix (`2017.01m`); without it, `2017.01` is a
  float. (datatypes.md §Tokens shows `2017.01` listed as month, but the canonical literal
  carries `m`.) **Ambiguity to flag for the grammar.**
- `2018.05 2018.07 2019.01m` is a **month vector** (single trailing `m`).
- The `D` (timestamp) and `T` (datetime) separators are **upper-case** and case-significant.
- Day-count prefix on timespan: `0D12:00:00.000000000`, multi-digit days `106751D…`.
- Time vs minute vs second is determined by how many `:`/fraction fields are present.
- Temporal vectors: space-separated values, optional single trailing type char
  (`09:15:37 09:29:01` is a second/time vector by field shape).

### Null and infinity literals — complete set

Nulls (`0N` family):
```
0Nh  short null      0Ni int null     0N / 0Nj  long null
0Ne  real null       0n / 0Nf float null
0Ng  guid null
0Np  timestamp null  0Nm month null   0Nd date null    0Nz datetime null
0Nn  timespan null   0Nu minute null  0Nv second null  0Nt time null
```
(There is NO boolean null and NO byte null.)

Infinities (`0W` family), positive and negative `-0W…`:
```
0Wh -0Wh  short inf      0Wi -0Wi int inf     0W / 0Wj  long inf
0We -0We  real inf       0w / 0Wf  -0w float inf
0Wp -0Wp  timestamp inf  0Wm month inf  0Wd date inf
0wz       datetime inf (note lower-case w)
0Wn timespan inf  0Wu minute inf  0Wv second inf  0Wt time inf
```
Quirks:
- Float/real use lower-case: `0w`, `0we`, `0n`. Datetime uses `0wz` (lower-case w),
  while most temporal infs use upper-case `0W…`. **Case is significant and inconsistent.**
- `0N` and `0W` with no suffix = long. `0n`/`0w` (lower) with no suffix = float.

---

## Lexer gotchas summary
1. Suffix letters `h i j e f b x` and temporal `m d p z n u v t g` must be matched
   greedily after a numeric/date body, but several are also valid name characters — the
   suffix only applies when immediately abutting a numeric literal.
2. `0N…` / `0W…` / `0w` / `0n` are special atom tokens, not "0" followed by a name.
3. Negative literals: leading `-` is part of the constant only per syntax.md whitespace
   rules (see syntax.md ref file) — purely lexical decisions are insufficient; left
   context (name/const/`)`/`]`) matters.
4. `.` and `:` are reused as date/time separators, decimal point, namespace separator,
   and operators — temporal literal lexing must be a single greedy token.
5. Symbol vectors and timestamp/datetime literals contain characters (backtick, `D`,
   `T`, `.`, `:`) that are operators elsewhere; the scanner must commit to the literal.
