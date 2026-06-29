function sep1(rule, s) { return seq(rule, repeat(seq(s, rule))); }

module.exports = {
  assignment: $ => prec.right(seq(
    field('left', choice($.identifier, $.dotted_name)),
    field('operator', choice('::', ':')),
    field('right', $._expression))),
  lambda: $ => seq('{', optional(field('parameters', $.parameters)),
                   field('body', optional($._lambda_body)), '}'),
  _lambda_body: $ => sep1($._statement, ';'),
  parameters: $ => seq('[', optional(sep1(field('param', $.param), ';')), ']'),
  param: $ => $.identifier,
};
