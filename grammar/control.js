// grammar/control.js — Task 8: cond, if/do/while, return/signal
// Owned by w1-control branch.

function sep1(rule, s) { return seq(rule, repeat(seq(s, rule))); }

module.exports = {
  // $[c;t;f] — Cond.  prec(2) ensures this wins over `$` operator + `[` bracket.
  cond: $ => prec(2, seq('$', '[', sep1($._expression, ';'), ']')),

  // if/do/while control words — NOT functions; `word` in grammar.js ensures
  // these keyword strings take priority over the identifier rule.
  control: $ => seq(
    field('keyword', choice('if', 'do', 'while')),
    '[', sep1($._statement, ';'), ']'),

  // `:expr` — explicit return inside a lambda (statement-initial colon).
  return_stmt: $ => prec.left(seq(':', $._expression)),

  // `'expr` — signal / throw.
  signal_stmt: $ => prec.left(seq("'", $._expression)),
};
