function sep1(rule, s) { return seq(rule, repeat(seq(s, rule))); }

// Amend-assign operators: `x+:1`, `x,:y`, `B[s],:v`, `x|:y` ... — a function
// glyph fused with `:`. One token each so the lexer takes them whole (longest
// match) before `+`/`:` can split. `$:` is included; bare `$` still lexes as
// $._dollar and `$[` still starts cond. q resolves which amend op it is at eval
// time — the grammar only needs the uniform shape `lhs <op>: rhs`.
const AMEND = token(choice(
  '+:', '-:', '*:', '%:', '&:', '|:', '^:', '=:', '<:', '>:',
  '~:', '!:', '#:', '_:', '$:', '?:', '@:', '.:', ',:',
));

module.exports = {
  // assignment: right-associative.
  // left can be: identifier, dotted_name, or index (x[i] for amend-assign)
  assignment: $ => prec.right(1, seq(
    field('left', choice($.identifier, $.dotted_name, alias($.call, $.index))),
    field('operator', choice('::', ':', alias(AMEND, $.operator))),
    field('right', choice($.assignment, $._expression)),
  )),

  lambda: $ => seq(
    '{',
    optional(field('parameters', $.parameters)),
    // Body: `;`-separated statements; slots may be empty so a trailing `;`
    // (`{a:1;}`) or an empty statement (`{;}`) is tolerated.
    field('body', optional(seq(
      optional($._statement),
      repeat(seq(';', optional($._statement))),
    ))),
    '}',
  ),

  parameters: $ => seq('[', optional(sep1(field('param', $.param), ';')), ']'),

  param: $ => $.identifier,
};
