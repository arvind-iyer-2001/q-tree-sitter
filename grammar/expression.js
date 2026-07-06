// =============================================================================
// grammar/expression.js — expression core, rebuilt on the k/q grammar model
// (2026-07-05 rewrite; see AUDIT_2026-07-05.md for why the old core was replaced)
//
// q's real grammar is tiny and uniform:
//
//   expr    := noun | noun verb expr | noun expr | verb-as-value
//   verb    := operator | derived
//   derived := (operator | noun | derived) iterator        (iterators stack)
//   noun    := primary | noun[args]                        (left-recursive)
//
// Three structural decisions carry the whole design:
//
// 1. ITERATORS ARE token.immediate. q's lexical rule is that an iterator glyph
//    attaches with NO whitespace (`f'`, `+/`, `vs/:`); with whitespace, `/`
//    starts a comment instead. token.immediate encodes exactly that, which
//    retires the external ADVERB_TOK (whose prev_was_value gate could never
//    work — the scanner never sees internally-lexed tokens).
//
// 2. DERIVED VERBS ARE FIRST-CLASS. `adverb_apply` (name kept for the
//    extractor) may appear as binary's operator (`x f'y`, `a,'b`), as a
//    bracket-call function (`f'[x;y]`), as a juxtaposition function (`(+/)x`),
//    or bare as a trailing value (`{..}\:`). The old grammar only had the
//    postfix form, so every infix use parsed by GLR accident — top-level
//    often "worked", inside `{}` it errored (the audit's headline bug).
//
// 3. JUXTAPOSITION IS RTL AND UNRESTRICTED. `call` (juxt form) is
//    `noun _expression` — any noun applies (bracket-call results:
//    `neg[h](...)`; conds: `count$[c;a;b]`), and the argument is everything
//    to the right (`f x+1` = f(x+1)).
// =============================================================================

function sep(rule, s) {
  return optional(seq(rule, repeat(seq(s, optional(rule)))));
}

// NOTE: `$` is intentionally NOT in this set — it has its own shared $._dollar
// token (grammar.js) so cond `$[...]` and the binary `$` operator use ONE token
// type. Overload resolution (cast/enum/pad/cond) is q's eval-time concern.
//
// NOT token()-fused: each glyph must stay an individual anonymous token so
// `'-'` here and `'-'` inside the negative-number rule are the SAME token —
// a fused "operator" token forces the LEXER to pick operator-vs-number
// (context-free, always wrong somewhere); with one shared token the choice
// becomes a syntactic GLR fork the parser resolves by state.
const OPERATOR_GLYPHS = [
  '<=', '>=', '<>',
  '0:', '1:', '2:',   // file/IPC verbs: `("PSFI";",")0:data`, `h 2:...`
  '+', '-', '*', '%', '&', '|', '^', '=', '<', '>', '~', '!',
  '#', '_', '?', '@', '.', ',',
];

// Iterator glyphs. ONLY the `/` family is token.immediate: `f/` (over) vs
// `f /comment` is q's whitespace rule, and the scanner claims the spaced
// form as a comment. The quote/backslash iterators may be space-separated
// (`f[..] ' [..]` appears in production Bloomberg code); `'` reuses the
// shared $._quote token so it cannot lexically collide with signal `'expr`
// — parse state decides. This lives in _iter (a rule), not a fused token.

// binary > juxt: at `x • +/y` both infix (binary via derived verb) and
// juxtaposition (x applied to the verb-value expression `(+/)y`) are viable;
// q's rule is that a verb after a noun is INFIX, so binary must win.
const PREC = {
  juxt: 1,
  binary: 2,
  adverb: 3,
  bracket: 4,
};

module.exports = {
  // Named rule (not a fused token) — see OPERATOR_GLYPHS note above.
  operator: $ => choice(...OPERATOR_GLYPHS),

  _expression: $ => choice(
    $.binary,
    $._noun,             // includes call/index (bracket + juxt application)
    $.adverb_apply,      // bare derived verb as a trailing value: `{..}\:`
    // qsql statements are valid expression values (RHS of assignment).
    $.select_statement,
    $.exec_statement,
    $.update_statement,
    $.delete_statement,
    // assignment as expression enables computed columns `col:expr` in qsql
    // phrases and mid-expression assignment (`c>x:0 t\x`).
    $.assignment,
    $.control,
  ),

  // Nouns: values that can be applied/indexed/infixed-over. Left-recursion
  // through the bracket forms means `g[a][b]`, `neg[h]`, `(f)[x]` are nouns.
  _noun: $ => choice(
    $._primary,
    $.call,
    $.index,
  ),

  // Infix: RTL, no operator precedence. Left is ONE noun; right is everything
  // else (right recursion => folds right-to-left). `optional(right)` models
  // operator left-projection (`3+`; `"/",`). The operator slot admits derived
  // verbs — `x f'y`, `a,'b`, `0 t\x`, `x vs/:y` — which is the audit's #1 fix.
  // `right` may be a bare verb value (`"e"$%` — cast applied to the divide
  // verb) as well as any expression.
  // prec.dynamic: at `a,'b` / `x f'y` GLR also derives the juxtaposition
  // reading (a applied to the derived-verb expression); q's rule is infix —
  // the binary tree must win the ambiguity merge.
  binary: $ => prec.dynamic(1, prec.right(PREC.binary, seq(
    field('left', $._noun),
    field('operator', choice(
      $.operator,
      alias($._dollar, $.operator),
      alias($._infix_kw, $.builtin),
      $.adverb_apply,
    )),
    optional(field('right', choice($._expression, $._op_value))),
  ))),

  // Application, bracket form: `f[a;b]`, `.[f;args]`, `@[x;i;f]`, `g[a][b]`,
  // `f'[x;y]` (derived-verb function), `(expr)[i]`. Operators may be the
  // bracketed function (`@[x;i;:;y]`).
  call: $ => choice(
    prec(PREC.bracket, seq(
      field('function', choice($._noun, $.adverb_apply, $.operator)),
      field('arguments', $.arguments),
    )),
    // Juxtaposition apply, RTL: `f x`, `count$[c;a;b]`, `neg[h](...)`,
    // `(+/) x`. Argument is the whole right-hand expression (`f x+1` = f(x+1)).
    // Function is an APPLICABLE noun — plain numeric/temporal literals can't
    // apply (else `3-4` lexes `-4` as a neg literal and parses as call(3,-4)).
    // Argument must not START with a negative literal — `x-5`, `y-1`,
    // `count[x]-5` are subtraction in q, never application of a neg number.
    prec.right(PREC.juxt, seq(
      field('function', choice($._applicable, $.adverb_apply)),
      field('arguments', $._expression_nn),
    )),
  ),

  // Structurally identical to bracket-call; kept as a named node for the
  // extractor. `call` wins the bracket form via the [call, index] conflict.
  index: $ => prec(PREC.bracket, seq(
    field('function', $._noun),
    field('arguments', $.arguments),
  )),

  // Bracketed `;`-separated argument list. Every slot (including the first)
  // may be elided (projection: `f[;2]`, `@[;`sym;f]`, `qtln[;;8]`) or hold a
  // bare verb value (`@[x;i;:;y]`).
  arguments: $ => seq(
    '[',
    optional(choice($._expression, $._op_value)),
    repeat(seq(';', optional(choice($._expression, $._op_value)))),
    ']',
  ),

  // Derived verb: iterator(s) fused onto an operator, noun, or another derived
  // verb. repeat1 captures stacks (`@'\:`, `,//`). Name kept from the old
  // grammar for extractor compatibility.
  adverb_apply: $ => prec(PREC.adverb, seq(
    field('function', choice(
      $._noun,
      $.operator,
      alias($._dollar, $.operator),
      alias($._infix_kw, $.builtin),
    )),
    repeat1(field('adverb', $.adverb)),
  )),

  adverb: $ => choice(
    token.immediate(prec(1, '/:')),
    token.immediate(prec(1, '/')),
    "':",
    $._quote,
    '\\:',
    '\\',
  ),

  _primary: $ => choice(
    $.lambda, $.parenthesized, $.list, $.table_literal, $.cond,
    $.number, $.boolean, $.byte, $.string, $.char, $.symbol, $.symbol_vector,
    $.vector, $.null, $.infinity,
    $.timestamp, $.datetime, $.date, $.month, $.timespan, $.time, $.second, $.minute,
    $.builtin, alias($._infix_kw, $.builtin), $.dotted_name, $.identifier,
  ),

  // Nouns that can be juxtaposition-applied: functions, names, indexable
  // containers (`"abc" 1`, `(1;2) 0`, `` `a`b`c 1 ``) and bracket results.
  // Excludes numeric/boolean/temporal atoms — `3 x` is never application in q.
  // $.number is included for the q print idiom `-1"msg"` / `0N!x` (int file
  // handles ARE functions); the _nn argument family keeps `3-4` subtraction.
  _applicable: $ => choice(
    $.lambda, $.parenthesized, $.list, $.table_literal, $.cond,
    $.string, $.symbol, $.symbol_vector, $.number, $.vector,
    $.builtin, alias($._infix_kw, $.builtin), $.dotted_name, $.identifier,
    $.call, $.index,
  ),

  // ---------------------------------------------------------------------
  // "_nn" (no-leading-negative) expression family: identical to the plain
  // rules (and aliased to the same node names) EXCEPT the leftmost noun
  // cannot be a bare number/vector. Used ONLY as the juxtaposition
  // argument: without it, `x-5` lexes `-5` as a negative literal and
  // parses as call(x, -5) — q semantics say subtraction. Negatives stay
  // legal everywhere deeper (`f 5+-3`; binary rhs; slots; parens).
  // ---------------------------------------------------------------------
  _expression_nn: $ => choice(
    alias($.binary_nn, $.binary),
    $._noun_nn,
    $.adverb_apply,
    $.select_statement,
    $.exec_statement,
    $.update_statement,
    $.delete_statement,
    $.assignment,
    $.control,
  ),

  binary_nn: $ => prec.dynamic(1, prec.right(PREC.binary, seq(
    field('left', $._noun_nn),
    field('operator', choice(
      $.operator,
      alias($._dollar, $.operator),
      alias($._infix_kw, $.builtin),
      $.adverb_apply,
    )),
    optional(field('right', choice($._expression, $._op_value))),
  ))),

  _noun_nn: $ => choice(
    $._primary_nn,
    $.call,
    $.index,
  ),

  // Numbers/vectors are allowed as long as they don't LEAD with `-`:
  // `til 10` and `f 1 2 3` are applications; only `x-5` must stay binary.
  _primary_nn: $ => choice(
    $.lambda, $.parenthesized, $.list, $.table_literal, $.cond,
    $.boolean, $.byte, $.string, $.char, $.symbol, $.symbol_vector,
    $.null, $.infinity,
    alias($._number_token, $.number),
    // ws-gated negative literal: `x -5` IS application in q (the scanner
    // saw the space); only the no-space grammar composition stays blocked
    alias($._neg_number, $.number),
    alias($.vector_nn, $.vector),
    $.timestamp, $.datetime, $.date, $.month, $.timespan, $.time, $.second, $.minute,
    $.builtin, alias($._infix_kw, $.builtin), $.dotted_name, $.identifier,
  ),

  // Vector whose first element is positive (later elements may be negative:
  // `f 1 -2 3`). Aliased to $.vector.
  vector_nn: $ => prec.dynamic(2, prec.left(2, seq(
    alias($._number_token, $.number),
    repeat1(seq($._list_ws, $._vector_elem)),
  ))),

  // A bare verb used as a value: operators, the shared `$`/`'` tokens, and the
  // assign verbs `:`/`::`. Scoped to arg/list/paren slots — NOT a general
  // `_primary` — so it cannot collide with infix `binary` (an operator can
  // never *begin* a noun, so a slot starting with one is a verb value).
  _op_value: $ => choice(
    $.operator,
    alias($._dollar, $.operator),
    alias($._quote, $.operator),
    alias($.amend_op, $.operator),   // value verbs: `.:`, `@:`, `+:` ...
    alias(':', $.operator),
    alias('::', $.operator),
  ),

  // `()` empty list; `(e)` parenthesized; `(+)`/`(+/)` verb values.
  parenthesized: $ => seq(
    '(',
    optional(choice($._expression, $._op_value)),
    ')',
  ),

  // `(e1;e2;...)` — at least one `;`. Slots may be empty (elision) or bare
  // verb values (`(+;-;*)`).
  list: $ => seq(
    '(',
    optional(choice($._expression, $._op_value)),
    repeat1(seq(';', optional(choice($._expression, $._op_value)))),
    ')',
  ),

  // `([keycols] col:vals; ...)` — `[]` may be empty (simple table).
  table_literal: $ => seq(
    '(',
    '[', alias(sep($._expression, ';'), $.key_columns), ']',
    sep($._expression, ';'),
    ')',
  ),

  // `[e1;e2;...]` — bracket statement group, q's multi-statement expression
  // (`$[c;[a:1;b:2];0]`, and as a bare grouped statement). Slots are
  // statements; elision tolerated.
  block: $ => seq(
    '[',
    optional($._statement),
    repeat(seq(';', optional($._statement))),
    ']',
  ),
};
