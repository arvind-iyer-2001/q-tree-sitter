module.exports = {
  select_statement: $ => seq('select', field('from', seq('from', $._expression))),
  exec_statement:   $ => seq('exec',   field('from', seq('from', $._expression))),
  update_statement: $ => seq('update', field('from', seq('from', $._expression))),
  delete_statement: $ => seq('delete', field('from', seq('from', $._expression))),
};
