// grammar/control.js — cond, if/do/while, return/signal

module.exports = {
  // $[c;t;f] — Cond. Uses the shared $._dollar token (grammar.js) so plain
  // `a$b` (binary `$`) and `$[...]` share one token type. Slots are statements
  // (signal `'err`, return `:x`, blocks and assignments all legal in branches)
  // and every slot may be elided — `$[c;v;]` is a real projection idiom
  // (`$[-11=type x;value;] x`). prec(2) keeps cond preferred when `$` is
  // immediately followed by `[`.
  cond: $ => prec(2, seq(
    $._dollar,
    '[',
    optional(choice($._statement, $._op_value)),
    repeat(seq(';', optional(choice($._statement, $._op_value)))),
    ']',
  )),

  // if/do/while control words — NOT functions; `word` in grammar.js ensures
  // these keyword strings take priority over the identifier rule. Slots may
  // be elided (trailing `;` inside the brackets is common).
  control: $ => seq(
    field('keyword', choice('if', 'do', 'while')),
    '[',
    optional($._statement),
    repeat(seq(';', optional($._statement))),
    ']',
  ),

  // `:expr` — explicit return inside a lambda (statement-initial colon).
  return_stmt: $ => prec.left(seq(':', $._expression)),

  // `'expr` — signal / throw. Uses the shared $._quote token (grammar.js) so it
  // shares one token type with the each/quote iterator glyph `f'`.
  signal_stmt: $ => prec.left(seq($._quote, $._expression)),
};
