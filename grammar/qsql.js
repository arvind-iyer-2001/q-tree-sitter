// q-SQL grammar: select, exec, update, delete with clauses
// Reference: references/qsql.md
// Token order: [limit] [select-phrase] [by by-phrase] from table-expr [where where-phrase]
//
// Conflict note (W1-qsql): The string literals 'select', 'from', 'where', 'by', 'exec',
// 'update', 'delete' used here overlap with $.builtin (identifiers.js) and $.identifier.
// Conflicts for T10:
//   [$.select_statement, $.builtin]
//   [$.exec_statement,   $.builtin]
//   [$.update_statement, $.builtin]
//   [$.delete_statement, $.builtin]
//
// T10 NOTE: _expression is OWNED by grammar/expression.js (T6). The qsql
// statement variants and `assignment` (for computed columns `col:expr` in
// phrases) were folded INTO expression.js's _expression during convergence, so
// this module no longer overrides _expression.

function sep1(rule, s) { return seq(rule, repeat(seq(s, rule))); }

module.exports = {
  select_statement: $ => prec.right(10, seq(
    'select',
    optional(field('select', $.select_clause)),
    optional(field('by', $.by_clause)),
    field('from', $.from_clause),
    optional(field('where', $.where_clause))
  )),

  exec_statement: $ => prec.right(10, seq(
    'exec',
    optional(field('select', $.select_clause)),
    optional(field('by', $.by_clause)),
    field('from', $.from_clause),
    optional(field('where', $.where_clause))
  )),

  update_statement: $ => prec.right(10, seq(
    'update',
    optional(field('select', $.select_clause)),
    optional(field('by', $.by_clause)),
    field('from', $.from_clause),
    optional(field('where', $.where_clause))
  )),

  // delete has two forms:
  //   delete from t [where pw]   -> delete rows
  //   delete ps from t           -> delete columns
  delete_statement: $ => prec.right(10, seq(
    'delete',
    optional(field('select', $.select_clause)),
    field('from', $.from_clause),
    optional(field('where', $.where_clause))
  )),

  // Clause nodes (named so the downstream extractor can walk them by type)

  // select_clause: comma-separated column expressions
  select_clause: $ => prec.right(sep1($._expression, ',')),

  // by_clause: 'by' + comma-separated grouping expressions
  by_clause: $ => prec.right(seq('by', sep1($._expression, ','))),

  // from_clause: 'from' + table expression (child accessible to extractor)
  from_clause: $ => seq('from', $._expression),

  // where_clause: 'where' + comma-separated filter expressions
  where_clause: $ => prec.right(seq('where', sep1($._expression, ','))),
};
