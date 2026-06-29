function sep1(rule, s) { return seq(rule, repeat(seq(s, rule))); }

module.exports = {
  cond:    $ => seq('$', '[', sep1($._expression, ';'), ']'),
  control: $ => seq(field('keyword', choice('if', 'do', 'while')),
                    '[', sep1($._statement, ';'), ']'),
};
