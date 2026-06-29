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

  extras: $ => [/[ \t]/, $.comment],   // W1-scanner: removed \n\r from extras; _eos now handles newlines

  // GLR conflicts: UNION of all wave-1 module conflict declarations (T10).
  // T10-converge: tree-sitter flags all 6 as "unnecessary" (they don't change
  // the recognised language), but all 6 are KEPT because removing them causes
  // GLR ambiguity explosion at parse time (confirmed: tree-sitter parse hung
  // at 99% CPU on the mixed-snippet test after removal). The conflicts act as
  // GLR disambiguation hints that bound parse-forest branching.
  conflicts: $ => [
    // W1-expression: single symbol (primary) vs symbol_vector (repeat1 symbol)
    [$.symbol_vector, $._primary],
    // W1-expression: bracket-form call vs index (structurally identical in q;
    // q resolves index-vs-apply at eval time, not parse time)
    [$.call, $.index],
    // W1-expression: `primary primary` -> juxtaposition call vs bare application
    [$.call, $._application],
    // W1-expression: q-SQL keyword `select` is also in `builtin` choice
    // (defined in identifiers/T4); statement form vs builtin-as-primary.
    [$.builtin, $.select_statement],
    // W1-qsql: qsql keyword tokens also match $.builtin (identifiers.js).
    [$.exec_statement, $.builtin],
    [$.update_statement, $.builtin],
    [$.delete_statement, $.builtin],
    // W1-qsql: qsql statements appear in both _statement and _expression
    // (RHS of assignment, e.g. `q:select ... from t`).
    [$._statement, $._expression],
    // W1-control: `identifier :` can begin an assignment OR be a primary
    // followed by a return_stmt. (T6 renamed _literal_ref -> _primary.)
    [$.assignment, $._primary],
  ],

  word: $ => $.identifier,

  rules: Object.assign(
    {
      // T10: tolerate blank lines / leading & trailing _eos (the corpus harness
      // feeds inputs with a leading newline). A bare _eos with no statement is a
      // separator, not an ERROR.
      source_file: $ => repeat(choice($._statement, $._eos)),

      // _statement and _expression are the shared backbone. _expression is
      // OWNED by expression.js (Task 6). namespace_directive is FOLDED into
      // system_command (W1-commands). qsql statements + control/return/signal
      // are statement-level constructs (also reachable via _expression).
      _statement: $ => choice(
        $.assignment,
        $.system_command,
        // W1-control:
        $.control,
        $.return_stmt,
        $.signal_stmt,
        // W1-qsql:
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
