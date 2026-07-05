function sep1(rule, s) { return seq(rule, repeat(seq(s, rule))); }

// Amend-assign operators: `x+:1`, `x,:y`, `B[s],:v`, `x|:y` ... — a function
// glyph fused with `:`. One token each so the lexer takes them whole (longest
// match) before `+`/`:` can split. `$:` is included; bare `$` still lexes as
// $._dollar and `$[` still starts cond. q resolves which amend op it is at eval
// time — the grammar only needs the uniform shape `lhs <op>: rhs`.
const AMEND = token(choice(
  // global amend `x+::v` first (longest match), then local `x+:v`
  '+::', '-::', '*::', '%::', '&::', '|::', '^::', '=::', '<::', '>::',
  '~::', '!::', '#::', '_::', '$::', '?::', '@::', '.::', ',::',
  '+:', '-:', '*:', '%:', '&:', '|:', '^:', '=:', '<:', '>:',
  '~:', '!:', '#:', '_:', '$:', '?:', '@:', '.:', ',:',
));

module.exports = {
  // assignment: right-associative.
  // left can be: identifier, dotted_name, or index (x[i] for amend-assign)
  // left can be: identifier, dotted_name, builtin (q lets keyword-named
  // globals be assigned — `view::select ...` defines a view named `view`),
  // index (x[i] for amend-assign), or a parenthesized apply-target
  // (`(qp n):v` assigns through the application `qp n`)
  assignment: $ => prec.right(1, seq(
    field('left', choice($.identifier, $.dotted_name, $.builtin,
                         alias($._infix_kw, $.builtin),
                         $.parenthesized, alias($.call, $.index))),
    field('operator', choice('::', ':', alias($.amend_op, $.operator))),
    field('right', choice($.assignment, $._expression)),
  )),

  lambda: $ => seq(
    '{',
    optional(field('parameters', $.parameters)),
    // Body: `;`-separated statements; slots may be empty so a trailing `;`
    // (`{a:1;}`) or an empty statement (`{;}`) is tolerated.
    field('body', optional(seq(
      optional($._statement),
      repeat(seq(';', optional($._statement))),
    ))),
    '}',
  ),

  // prec.dynamic: `{[a;b] ...}` — a `[` opening a lambda is ALWAYS the
  // parameter list in q, never a bracket statement-block; the dynamic prec
  // beats $.block when GLR holds both parses to the closing `]`.
  parameters: $ => prec.dynamic(1, seq('[', optional(sep1(field('param', $.param), ';')), ']')),

  param: $ => $.identifier,

  // Named so _op_value (expression.js) can reuse the same token (`@[.:;x;::]`
  // passes the value verb `.:` as an argument).
  amend_op: $ => AMEND,
};
