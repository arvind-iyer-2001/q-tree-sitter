function sep1(rule, s) { return seq(rule, repeat(seq(s, rule))); }

module.exports = {
  _expression: $ => choice($.binary_expression, $.call, $.lambda, $.parenthesized, $.list,
                            $.cond, $._literal_ref),
  // W1-literals: expanded to include all literal types from grammar/literals.js
  _literal_ref: $ => choice(
    $.number, $.boolean, $.byte, $.string, $.char, $.symbol,
    $.null, $.infinity,
    $.timestamp, $.datetime, $.date, $.month,
    $.timespan, $.time, $.second, $.minute,
    $.vector,
    $.identifier, $.dotted_name,
  ),
  _noun:        $ => $._literal_ref,
  binary_expression: $ => prec.left(1, seq(
    field('left',     $._expression),
    field('operator', $.operator),
    field('right',    $._expression))),
  operator: $ => /[+\-*%&|^!~<>=,#_$?@]/,
  call: $ => prec.left(2, seq(field('function', choice($.identifier, $.dotted_name)),
                            '[', field('arguments', optional(sep1($._expression, ';'))), ']')),
  parenthesized: $ => seq('(', $._expression, ')'),
  list:          $ => seq('(', $._expression, ';', optional($._expression),
                           repeat(seq(';', optional($._expression))), ')'),
};
