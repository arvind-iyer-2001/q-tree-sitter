function sep1(rule, s) { return seq(rule, repeat(seq(s, rule))); }

module.exports = {
  // assignment: right-associative.
  // left can be: identifier, dotted_name, or index (x[i] for amend-assign)
  assignment: $ => prec.right(1, seq(
    field('left', choice($.identifier, $.dotted_name, alias($.call, $.index))),
    field('operator', choice('::', ':')),
    field('right', choice($.assignment, $._expression)),
  )),

  lambda: $ => seq(
    '{',
    optional(field('parameters', $.parameters)),
    field('body', optional(sep1($._statement, ';'))),
    '}',
  ),

  parameters: $ => seq('[', optional(sep1(field('param', $.param), ';')), ']'),

  param: $ => $.identifier,
};
