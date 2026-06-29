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
  // W1-control: assignment vs _literal_ref+return_stmt when `identifier :` is seen
  conflicts: $ => [
    [$.assignment, $._literal_ref],
  ],

  word: $ => $.identifier,

  rules: Object.assign(
    {
      source_file: $ => repeat(seq($._statement, optional($._eos))),

      // _statement and _expression are the shared backbone. _expression is
      // OWNED by expression.js (Task 6); declared here only as the entry alias.
      _statement: $ => choice(
        $.assignment,
        $.system_command,
        $.namespace_directive,
        // W1-control: control words, return, signal are statement-level constructs
        $.control,
        $.return_stmt,
        $.signal_stmt,
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
