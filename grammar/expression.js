// =============================================================================
// CONFLICTS FOR TASK 10:
// (Reconcile these conflict resolutions when merging all modules. Every GLR
//  conflict surfaced by `tree-sitter generate` for the expression core is
//  recorded here, with how it was resolved. Final state: `tree-sitter generate`
//  is clean — no warnings, no unresolved conflicts.)
//
// CONFLICTS THAT REQUIRE a `conflicts:` entry in grammar.js (true ambiguity,
// GLR keeps both stacks):
//
//   A. [$.symbol_vector, $._primary]
//      A single `symbol` is a `_primary`; a run of symbols is a `symbol_vector`
//      (repeat1 symbol, defined in identifiers/T4). At `symbol • symbol` the
//      parser cannot decide without lookahead. -> conflicts entry.
//
//   B. [$.call, $.index]
//      Both are `primary '[' args ']'` (now `primary arguments`). q resolves
//      index-vs-apply at EVAL time, not parse time, so they are genuinely
//      ambiguous. `call` wins in practice (declared first / GLR), `index` is
//      retained as a named node for other modules / T10. -> conflicts entry.
//
//   C. [$.call, $._application]
//      `primary primary` (juxtaposition) -> is the second primary the argument
//      of a prefix `call`, or a bare `_application` sibling? Genuine ambiguity;
//      GLR keeps both. The juxtaposition `call` branch is left at DEFAULT static
//      precedence (0) on purpose: giving it a higher prec made the parser eat
//      `1` `2` across an intervening operator in `1+2` (it dropped the `binary`
//      reduction and errored on `+`). At default prec the [call,_application]
//      conflict lets `binary` survive because an operator cannot begin an
//      `_application`. -> conflicts entry.
//
//   D. [$.builtin, $.select_statement]
//      `builtin` (identifiers/T4) includes the keyword `select`, which also
//      starts `select_statement` (qsql/T7). `select` as a bare primary vs the
//      start of a select statement. -> conflicts entry.
//
// CONFLICTS that `tree-sitter` reported as "unnecessary" once prec/structure was
// in place — these were tried, then REMOVED from grammar.js (resolved without a
// conflicts entry). Listed so T10 does not re-add them:
//
//   E. binary vs call (juxtaposition)  -> resolved: operator cannot begin an
//      _application, so `binary` reduces deterministically.
//   F. binary vs adverb_apply          -> resolved: the adverb glyph token forces
//      the adverb_apply branch; an adverb token cannot begin a binary.
//   G. parenthesized vs list           -> resolved: `( e )` vs `( e ; ... )`
//      disambiguated by the `;` (list requires repeat1 of `; e`).
//   H. parenthesized vs table_literal  -> resolved: table_literal requires `[`
//      immediately after `(`; parenthesized cannot start with `[`.
//
// RTL is encoded by `binary` = prec.right(PREC.binary, left _application, op,
// optional right _expression). `optional(right)` models operator-left-projection
// (`3+`). prec.right makes `2*3+4` fold right: (2 * (3 + 4)).
//
// NOTE / DEVIATION FOR T10 (scanner dependency):
//   The brief specifies the adverb glyph come from the external `$._adverb_tok`
//   (Task 2 scanner). The Task-2 scanner is currently a stub that emits NOTHING,
//   so `_adverb_tok` never fires and adverb/vector tests could not pass. To make
//   THIS worktree's corpus green, `_adverb` is a choice of the external
//   `$._adverb_tok` AND an in-grammar `_adverb_glyph` token. When the real
//   scanner lands, the external branch takes over for whitespace-sensitive cases;
//   T10 may drop the in-grammar fallback. Likewise the corpus avoids
//   space-separated vector literals (`1 2 3`) and negative literals because those
//   also depend on the (stubbed) external scanner; bracket/`;`-separated forms
//   are used instead.
// =============================================================================

function sep(rule, s) {
  return optional(seq(rule, repeat(seq(s, optional(rule)))));
}

// NOTE: `$` is intentionally NOT in this set — it has its own shared $._dollar
// token (grammar.js) so cond `$[...]` and the binary `$` operator use ONE token
// type. Overload resolution (cast/enum/pad/cond) is q's eval-time concern, not
// the parser's.
const OPERATOR = token(choice(
  '<=', '>=', '<>',
  '+', '-', '*', '%', '&', '|', '^', '=', '<', '>', '~', '!',
  '#', '_', '?', '@', '.', ',',
));

const PREC = {
  binary: 1,
  adverb: 2,
  bracket: 4,
};

module.exports = {
  _expression: $ => choice(
    $.binary,
    $._application,
    // W1-qsql (T7): qsql statements are valid expression values (RHS of
    // assignment, e.g. `q:select ... from t`).
    $.select_statement,
    $.exec_statement,
    $.update_statement,
    $.delete_statement,
    // W1-qsql (T7): assignment as an expression value enables computed columns
    // `col:expr` inside select/by/where phrases (which are _expression lists).
    $.assignment,
    $.cond,
    $.control,
  ),

  // Right-to-left, no precedence: left arg is the single value immediately to
  // the left (an _application); right arg is everything remaining (_expression).
  // Right-recursive => folds RTL. Right is optional to model operator left-
  // projection (`3+`).
  binary: $ => prec.right(PREC.binary, seq(
    field('left', $._application),
    field('operator', choice(alias(OPERATOR, $.operator), alias($._dollar, $.operator))),
    optional(field('right', $._expression)),
  )),

  _application: $ => choice(
    $.call,
    $.index,
    $.adverb_apply,
    $._primary,
  ),

  // Application: bracket form `f[a;b]` / `.[f;args]` / `@[x;i;f]`, and prefix
  // juxtaposition `f x`. Operators (`.`, `@`, ...) may be the bracketed function.
  call: $ => choice(
    prec(PREC.bracket, seq(
      field('function', choice($._primary, alias(OPERATOR, $.operator))),
      field('arguments', $.arguments),
    )),
    // Juxtaposition apply: kept at default (0) static prec so the GLR parser
    // does not statically prefer it over `binary`; the declared
    // [call, _application] conflict lets both survive and `binary` wins when an
    // operator intervenes (an operator cannot begin an `_application`).
    prec.right(seq(
      field('function', $._primary),
      field('arguments', $._application),
    )),
  ),

  // Structurally identical to bracket-call; kept as a named node for other
  // modules / T10. `call` wins the bracket form via equal prec + conflicts.
  index: $ => prec(PREC.bracket, seq(
    field('function', $._primary),
    field('arguments', $.arguments),
  )),

  // Bracketed `;`-separated argument list. One `arguments` node per `[...]`;
  // each slot is an _expression (slots may be elided for projection).
  arguments: $ => seq('[', sep($._expression, ';'), ']'),

  // Postfix iterator yields a (derived) function; here applied via brackets or
  // left as a value. `function` may be an operator glyph (`+/`) or a primary
  // (`f'`).
  adverb_apply: $ => prec.left(PREC.adverb, seq(
    field('function', choice($._primary, alias(OPERATOR, $.operator))),
    field('adverb', $._adverb),
    optional(field('arguments', $.arguments)),
  )),

  // External scanner (Task 2) supplies the whitespace-sensitive token; the
  // in-grammar glyph is the fallback so adverbs parse before the scanner lands.
  // `'` (the single-quote each adverb) comes from the shared $._quote token so
  // it does not collide with signal_stmt's `'`. The 2-char glyphs and `\`,`/`
  // stay here. Longest-match keeps `':`/`/:`/`\:` whole; bare `'` -> $._quote.
  _adverb: $ => choice($._adverb_tok, $._adverb_glyph, $._quote),
  _adverb_glyph: $ => token(choice("':", '\\:', '/:', '\\', '/')),

  _primary: $ => choice(
    $.lambda, $.parenthesized, $.list, $.table_literal,
    $.number, $.boolean, $.byte, $.string, $.char, $.symbol, $.symbol_vector,
    $.vector, $.null, $.infinity,
    $.timestamp, $.datetime, $.date, $.month, $.timespan, $.time, $.second, $.minute,
    $.builtin, $.dotted_name, $.identifier,
  ),

  // `()` is the empty general list; `(e)` is a parenthesized expression. The
  // expression is optional so empty `()` parses (very common as an empty column
  // value, e.g. `([]a:();b:())`).
  parenthesized: $ => seq('(', optional($._expression), ')'),

  // `(e1;e2;...)` — at least one `;`. Slots may be empty (elision => null atom).
  list: $ => seq(
    '(',
    optional($._expression),
    repeat1(seq(';', optional($._expression))),
    ')',
  ),

  // `([keycols] col:vals; ...)` — `[]` may be empty (simple table). Columns are
  // `name:vals` assignments (or bare value expressions). T10: `assignment` is now
  // part of `_expression`, so columns are just `_expression` (no separate
  // _table_column choice — that caused an _expression/_table_column conflict).
  table_literal: $ => seq(
    '(',
    '[', alias(sep($._expression, ';'), $.key_columns), ']',
    sep($._expression, ';'),
    ')',
  ),
};
