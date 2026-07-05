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

  // Horizontal whitespace + comments are always ignorable. Newlines are ALSO
  // ignorable as extras, BUT the external scanner is consulted first: at depth 0
  // it emits $._eos (statement terminator) before the newline can be eaten as an
  // extra. Inside (), [], {} the grammar makes $._eos invalid, so in-bracket
  // newlines fall through to extras and are ignored — enabling multi-line lists,
  // tables and lambdas.
  extras: $ => [/[ \t\r\n]/, $.comment],

  // GLR conflicts (2026-07-05 rewrite): genuine q ambiguities the parser must
  // keep both stacks for. Kept deliberately minimal — every entry is either a
  // real eval-time ambiguity in q (call vs index) or a 1-token-lookahead limit
  // (noun then iterator vs noun then juxtaposition).
  conflicts: $ => [
    // single symbol (primary) vs symbol_vector (repeat1 symbol)
    [$.symbol_vector, $._primary],
    // bracket-form call vs index: structurally identical; q resolves
    // index-vs-apply at eval time
    [$.call, $.index],
    // `noun • noun` — second noun may be a juxt argument (call), the start of
    // an infix operator position (binary via adverb_apply on a noun: `0 t\x`),
    // or a sibling; iterator immediacy decides one token later
    [$.call, $.binary],
    [$.call, $.adverb_apply],
    [$.binary, $.adverb_apply],
    [$._noun, $.adverb_apply],
    [$.call, $.binary, $.adverb_apply],
    // q-SQL keyword `select` is also in `builtin`; statement vs builtin-primary
    [$.builtin, $.select_statement],
    [$.exec_statement, $.builtin],
    [$.update_statement, $.builtin],
    [$.delete_statement, $.builtin],
    // qsql statements appear in both _statement and _expression
    [$._statement, $._expression],
    // `identifier :` can begin an assignment OR be a primary before return_stmt
    [$.assignment, $._primary],
    // `{[a` — identifier may be a lambda param or the first expr of a bracket
    // block; parameters carry prec.dynamic(1) and win at the `]`
    [$.param, $._primary],
    [$.parameters, $.block],
    // juxt-function (_applicable) vs plain value (_primary/_noun) — resolved
    // one token later (does an expression follow?)
    [$._primary, $._applicable],
    [$._noun, $._applicable],
    // no-leading-negative juxt-argument family overlaps the plain family on
    // every member except number/vector
    [$._primary, $._primary_nn],
    [$._noun, $._noun_nn],
    [$._primary, $._primary_nn, $._applicable],
    [$._primary_nn, $._applicable],
    [$._noun_nn, $._applicable],
    [$._noun, $._noun_nn, $._applicable],
    [$._expression, $._expression_nn],
    // `-` then digits: negative literal vs minus-then-number; a syntactic
    // GLR fork (shared anonymous '-' token), resolved by which stack survives
    [$.number, $.operator],
    [$.number, $._primary_nn],
    [$.vector, $.vector_nn],
    // `x$'y` vs `x$(';...)`-ish: quote after an operator — iterator on the
    // verb vs bare verb value in a slot; one token of lookahead decides
    [$.adverb, $._op_value],
  ],

  word: $ => $.identifier,

  rules: Object.assign(
    {
      // Top level: statements REQUIRE a separator (_eos newline or `;`) between
      // them. The old `repeat(choice(statement, sep))` let statements abut,
      // which let `g'x` parse as statement `g` + signal-statement `'x`,
      // stealing the iterator glyph. Leading/trailing/blank separators are
      // tolerated (corpus harness feeds a leading newline).
      // prec.dynamic on each separated statement: a juxtaposition can span a
      // newline on the GLR stack where EOS was invalid (`f "s"` + next line as
      // its argument); at the merge, the parse with MORE separated statements
      // must win — one point per separator-statement pair breaks the tie.
      source_file: $ => seq(
        repeat(choice($._eos, ';')),
        optional(seq(
          $._statement,
          repeat(prec.dynamic(1, seq(repeat1(choice($._eos, ';')), $._statement))),
          repeat(choice($._eos, ';')),
        )),
      ),

      // Shared `$` token. q overloads `$` heavily (cast, cond `$[...]`, enum,
      // pad, vector-conditional) but resolves the overload at EVAL time by
      // argument type/valence — never at parse time. So the grammar uses ONE
      // `$` token for every role; cond and the binary operator both reference
      // it, which avoids a two-token lexer collision (`a$b` previously failed).
      _dollar: $ => token('$'),

      // `k)` lines embed raw k; parsing k is out of scope — one opaque token.
      k_expression: $ => token(seq('k)', /[^\r\n]*/)),

      // Shared `'` token. `'` is the signal/throw prefix (`'err`) AND the
      // each/quote adverb glyph (`f'`). Like `$`, one token type lets the parser
      // disambiguate structurally (prefix-of-statement vs postfix-on-value)
      // instead of two competing `'` tokens that collide in the lexer.
      _quote: $ => token("'"),

      // _statement and _expression are the shared backbone. _expression is
      // OWNED by expression.js (Task 6). namespace_directive is FOLDED into
      // system_command (W1-commands). qsql statements + control/return/signal
      // are statement-level constructs (also reachable via _expression).
      _statement: $ => choice(
        $.assignment,
        $.system_command,
        // control:
        $.control,
        $.return_stmt,
        $.signal_stmt,
        // qsql:
        $.select_statement,
        $.exec_statement,
        $.update_statement,
        $.delete_statement,
        // bracket statement group `[a:1;b:2]` — legal as a statement and in
        // cond/control slots (which are _statement lists)
        $.block,
        // `k)...` — embedded k expression, treated as an opaque line
        $.k_expression,
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
