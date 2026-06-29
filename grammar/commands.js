module.exports = {
  system_command:     $ => seq(field('command', $._system_command_tok)),
  namespace_directive: $ => prec.right(seq('\\d', optional(field('namespace', $.dotted_name)))),
};
