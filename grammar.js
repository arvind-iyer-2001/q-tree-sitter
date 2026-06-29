const literals    = require('./grammar/literals.js');
const identifiers = require('./grammar/identifiers.js');
const functions   = require('./grammar/functions.js');
const expression  = require('./grammar/expression.js');
const qsql        = require('./grammar/qsql.js');
const control     = require('./grammar/control.js');
const commands    = require('./grammar/commands.js');

function sep1(rule, s) { return seq(rule, repeat(seq(s, rule))); }

module.exports = grammar({
  name: 'q',

  // External scanner tokens (implemented in src/scanner.c — see Task 2)
  externals: $ => [
    $.comment,
    $._system_command_tok,   // line-start backslash command line
    $._neg_number,           // negative numeric literal (whitespace-sensitive)
    $._list_ws,              // significant separator inside a vector
    $._adverb_tok,           // postfix iterator glyph
    $._eos,                  // top-level statement terminator (newline, not continuation)
    $._error_sentinel,       // never emitted; forces external-scanner fallback
  ],

  extras: $ => [/[ \t\n\r]/, $.comment],   // spaces/newlines ignored in skeleton; Task 2 makes _eos significant

  // GLR conflicts are added here by Task 10 as real ambiguities surface.
  // W1-qsql: qsql keywords ('select','exec','update','delete','from','where','by')
  // appear both as statement-opening literals and as $.builtin identifiers.
  // Conflicts registered for T10:
  //   [$.select_statement, $.builtin]
  //   [$.exec_statement,   $.builtin]
  //   [$.update_statement, $.builtin]
  //   [$.delete_statement, $.builtin]
  conflicts: $ => [
    // W1-qsql: qsql keyword tokens ('select','exec','update','delete','from','where','by')
    // overlap with $.builtin (identifiers.js) which also matches those literals.
    // Registered for T10 to audit and potentially resolve with precedence:
    [$.select_statement, $.builtin],
    [$.exec_statement,   $.builtin],
    [$.update_statement, $.builtin],
    [$.delete_statement, $.builtin],
    // W1-qsql: qsql statements appear in both _statement and _expression (as RHS values).
    // Required for 'q:select ... from t' (assignment with select_statement as value).
    [$._statement, $._expression],
  ],

  word: $ => $.identifier,

  rules: Object.assign(
    {
      source_file: $ => repeat(seq($._statement, optional($._eos))),

      // _statement and _expression are the shared backbone. _expression is
      // OWNED by expression.js (Task 6); qsql statements are added here so
      // they can appear as values (e.g. right-hand side of assignment).
      // W1-qsql: qsql variants added to _expression choice.
      _statement: $ => choice(
        $.assignment,
        $.system_command,
        $.namespace_directive,
        $.select_statement,
        $.exec_statement,
        $.update_statement,
        $.delete_statement,
        $._expression,
      ),
    },
    literals,
    identifiers,
    functions,
    expression,
    qsql,
    control,
    commands,
  ),
});
