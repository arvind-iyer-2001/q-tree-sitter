// grammar/literals.js — comprehensive q literal lexical forms
// Source of truth: references/datatypes.md
// Precedence strategy: longest-match temporal first (timestamp > date, timespan > time > second > minute)
// Negative literals: $._neg_number is provided by external scanner (scanner.c, Task 2).

module.exports = {
  // -------------------------------------------------------------------------
  // number: integer (j/i/h suffixes), float (f), real (e), exponential
  // Includes $._neg_number alias for negative literals from the external scanner.
  // -------------------------------------------------------------------------
  // Negative literals are a GRAMMAR composition (`'-' _number_token`), not a
  // fused lexer token: whether `-5` is a literal or subtraction depends on the
  // parse state (`x-5` subtracts; `n?-5`, `f[-5]`, `x:-5` negate), which only
  // the parser knows. The external NEG_NUMBER token is retired (audit: its
  // prev_was_value gate was unknowable). The juxt-argument _nn family blocks
  // the one bad reading (`call(x, -5)`).
  number: $ => choice(
    seq('-', $._number_token),
    $._number_token,
  ),

  _number_token: $ => token(choice(
      // Null/infinity are handled by their own rules with higher precedence.
      // Float with optional exponent — must come BEFORE bare integer to avoid ambiguity
      // e.g. "3.14", "0.0", "3.14f", "3.14e", "1.2e20", "1.234568e+08", "0f", "42f"
      /[0-9]+\.[0-9]*([eE][+-]?[0-9]+)?[fe]?/,
      // ".digits" float: ".5", ".5e2"
      /\.[0-9]+([eE][+-]?[0-9]+)?[fe]?/,
      // Integer with suffix: "42j", "42i", "42h", or bare "42"
      // "0e" and "0f" (no decimal) — integer + e/f suffix
      /[0-9]+[jihfe]?/,
  )),

  // -------------------------------------------------------------------------
  // boolean: 0b, 1b, and boolean vectors like 0101b, 01110001b
  // A run of '0'/'1' digits followed immediately by 'b'.
  // -------------------------------------------------------------------------
  boolean: $ => token(/[01]+b/),

  // -------------------------------------------------------------------------
  // byte: 0x followed by an even number of hex digits (at least 2)
  // Atom: 0x00 … 0xff. Vector: 0x010203 etc.
  // -------------------------------------------------------------------------
  byte: $ => token(/0x[0-9a-fA-F]{2}([0-9a-fA-F]{2})*/),

  // -------------------------------------------------------------------------
  // char: a single character (or escape sequence) in double quotes
  // Note: tree-sitter cannot distinguish char from 1-char string at the regex level;
  // char is defined as single char to allow the grammar to expose node type.
  // In practice q itself has no char vs string distinction in syntax — both are "…".
  // We expose 'string' only (covers all double-quoted literals).
  // -------------------------------------------------------------------------
  char: $ => token(seq('"', choice(/[^"\\]/, /\\(?:[\\nrt"]|[0-7]{3})/), '"')),

  // -------------------------------------------------------------------------
  // string: zero or more characters in double quotes (char vector)
  // Escapes: \" \\ \n \r \t \NNN (3 octal digits)
  // -------------------------------------------------------------------------
  string: $ => token(seq('"', repeat(choice(/[^"\\]/, /\\(?:[\\nrt"]|[0-7]{3})/)), '"')),

  // -------------------------------------------------------------------------
  // symbol: backtick + optional name; or file/handle path after `:
  //   `ibm  `a.b_2  `  (empty symbol)
  //   `:path/to/file  `:/abs  `:host:port  (file/handle hsym)
  // -------------------------------------------------------------------------
  symbol: $ => token(choice(
    // file/handle symbols: backtick + colon + path chars (may include / : . _)
    /`:[A-Za-z0-9._/:\-]*/,
    // regular symbols: backtick + optional name chars
    /`[A-Za-z0-9._]*/,
  )),

  // -------------------------------------------------------------------------
  // null literals — 0N family plus 0n (float null) and 0Nf
  // Order: longest tokens first; all are complete tokens (no following name char)
  // -------------------------------------------------------------------------
  null: $ => token(prec(10, choice(
    // typed nulls — two chars after 0N
    '0Nh', '0Ni', '0Nj', '0Ne', '0Ng',
    '0Np', '0Nm', '0Nd', '0Nz',
    '0Nn', '0Nu', '0Nv', '0Nt',
    '0Nf',
    // untyped long null (must come after typed forms)
    '0N',
    // float null (lower-case n)
    '0n',
  ))),

  // -------------------------------------------------------------------------
  // infinity literals — 0W family plus 0w/-0w (float) and 0wz (datetime)
  // Positive and negative variants.
  // -------------------------------------------------------------------------
  infinity: $ => token(prec(10, choice(
    // negative typed infinities
    '-0Wh', '-0Wi', '-0We',
    '-0Wp', '-0Wm', '-0Wd',
    '-0Wn', '-0Wu', '-0Wv', '-0Wt',
    '-0W',
    '-0w',
    // positive typed infinities
    '0Wh', '0Wi', '0Wj',
    '0We', '0Wf',
    '0Wp', '0Wm', '0Wd',
    '0wz',   // datetime inf — lower-case w, note the quirk
    '0Wn', '0Wu', '0Wv', '0Wt',
    // untyped long inf
    '0W',
    // float inf (lower-case)
    '0w',
  ))),

  // -------------------------------------------------------------------------
  // TEMPORAL LITERALS — longest-first precedence is critical:
  //   timestamp (YYYY.MM.DDDhh:mm:ss.f{9}) must beat date (YYYY.MM.DD)
  //   datetime  (YYYY.MM.DDThh:mm:ss.fff)  must beat date
  //   timespan  ([d]Dhh:mm:ss.f{9})        must beat time/second/minute
  //   time      (hh:mm:ss.fff)             must beat second
  //   second    (hh:mm:ss)                 must beat minute
  // -------------------------------------------------------------------------

  // timestamp (12): YYYY.MM.DDDhh:mm:ss[.f{1-9}]
  timestamp: $ => token(prec(5,
    /[0-9]{4}\.[0-9]{2}\.[0-9]{2}D[0-9]{2}:[0-9]{2}:[0-9]{2}(\.[0-9]{1,9})?/
  )),

  // datetime (15, deprecated): YYYY.MM.DDThh:mm:ss[.fff]
  datetime: $ => token(prec(5,
    /[0-9]{4}\.[0-9]{2}\.[0-9]{2}T[0-9]{2}:[0-9]{2}:[0-9]{2}(\.[0-9]{1,3})?/
  )),

  // date (14): YYYY.MM.DD — must be lower precedence than timestamp/datetime
  date: $ => token(prec(4,
    /[0-9]{4}\.[0-9]{2}\.[0-9]{2}/
  )),

  // month (13): YYYY.MMm
  month: $ => token(prec(4,
    /[0-9]{4}\.[0-9]{2}m/
  )),

  // timespan (16): [d+D]hh:mm:ss.f{1-9}
  // Must be disambiguated from time (hh:mm:ss.fff = 3 digits):
  //   - with day prefix: "0D12:00:00.000000000"
  //   - without day prefix but with 4-9 fractional digits (time only has 3)
  timespan: $ => token(prec(3, choice(
    // day-prefixed form: "0D12:00:00.000000000", "106751D23:47:16.854775806"
    /[0-9]+D[0-9]{2}:[0-9]{2}:[0-9]{2}\.[0-9]{1,9}/,
    // no day prefix but fractional part is 4-9 digits (distinguishes from time's 3)
    /[0-9]{2}:[0-9]{2}:[0-9]{2}\.[0-9]{4,9}/,
  ))),

  // time (19): hh:mm:ss.fff  (exactly 3 fractional digits is canonical; allow 1-3)
  time: $ => token(prec(2,
    /[0-9]{2}:[0-9]{2}:[0-9]{2}\.[0-9]{1,3}/
  )),

  // second (18): hh:mm:ss
  second: $ => token(prec(1,
    /[0-9]{2}:[0-9]{2}:[0-9]{2}/
  )),

  // minute (17): hh:mm
  minute: $ => token(prec(0,
    /[0-9]{2}:[0-9]{2}/
  )),

  // -------------------------------------------------------------------------
  // vector: space-separated numbers. T10: wired to the external scanner's
  // $._list_ws token (w1-scanner) — significant whitespace separating numbers
  // in vector context — so `1 2 3` is one vector, not juxtaposed atoms.
  // -------------------------------------------------------------------------
  // prec.dynamic: with numbers in _applicable (for the `-1"msg"` print idiom)
  // a GLR fork could read `1 2 3` as juxtaposition chains; the vector must win.
  vector: $ => prec.dynamic(2, prec.left(2, seq($.number, repeat1(seq($._list_ws, $.number))))),
};
