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
// _expression is extended here (this module merges after expression.js in grammar.js
// Object.assign, so this definition wins) to include qsql statements as valid
// expression values (e.g. RHS of assignment: q:select ... from t).

function sep1(rule, s) { return seq(rule, repeat(seq(s, rule))); }

module.exports = {
  // Override _expression to include qsql statement variants as values,
  // and to include assignment so that column-naming expressions like
  // `colname:expr` are valid within select/by/where phrases.
  // Must preserve all choices from expression.js (Task 6 owns the logic).
  // W1-qsql: assignment added to _expression so computed columns parse correctly.
  _expression: $ => choice(
    $.select_statement,
    $.exec_statement,
    $.update_statement,
    $.delete_statement,
    $.assignment,
    $.binary_expression,
    $.call,
    $.lambda,
    $.parenthesized,
    $.list,
    $.cond,
    $._literal_ref,
  ),

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
