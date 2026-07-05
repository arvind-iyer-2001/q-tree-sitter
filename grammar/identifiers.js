// KEYWORDS: the complete keyword-function set enumerated verbatim from
// references/keywords.md (§ alphabetical flattened list, all categories).
// Total: 170+ entries covering control, env, interpret, io, iterate, join,
// list, logic, math, meta, query, sort, table, and text categories.
// Keywords q uses INFIX (`"?" vs x`, `d within r`, `s like p`, `t lj kt`).
// Lexed as their own token so binary's operator slot accepts exactly these;
// aliased back to $.builtin in noun positions so the tree shape is unchanged.
const INFIX_KEYWORDS = [
  'vs', 'sv', 'like', 'in', 'within', 'bin', 'binr', 'ss', 'xbar', 'xexp',
  'xlog', 'xprev', 'xrank', 'xgroup', 'xasc', 'xdesc', 'xcol', 'xcols',
  'xkey', 'mod', 'div', 'cross', 'union', 'inter', 'except', 'each', 'over',
  'scan', 'prior', 'peach', 'cut', 'rotate', 'sublist', 'fby', 'mavg',
  'msum', 'mmax', 'mmin', 'mcount', 'mdev', 'ema', 'wavg', 'wsum', 'cor',
  'cov', 'scov', 'lsq', 'mmu', 'lj', 'ljf', 'ij', 'ijf', 'uj', 'ujf', 'pj',
  'ej', 'aj', 'aj0', 'ajf', 'ajf0', 'asof', 'wj', 'wj1', 'upsert', 'insert',
  'set', 'setenv', 'and', 'or',
];

const KEYWORDS = [
  'do', 'exit', 'if', 'while', 'getenv', 'gtime', 'ltime', 'eval', 'parse',
  'reval', 'show', 'system', 'value', 'dsave', 'get', 'hclose', 'hcount',
  'hdel', 'hopen', 'hsym', 'load', 'read0', 'read1', 'rload', 'rsave',
  'save', 'count', 'enlist', 'fills', 'first', 'flip', 'group', 'last',
  'next', 'prev', 'raze', 'reverse', 'til', 'where', 'all', 'any', 'not',
  'abs', 'acos', 'asin', 'atan', 'avg', 'avgs', 'ceiling', 'cos', 'deltas',
  'dev', 'exp', 'floor', 'inv', 'log', 'max', 'maxs', 'med', 'min', 'mins',
  'neg', 'prd', 'prds', 'rand', 'ratios', 'reciprocal', 'sdev', 'signum',
  'sin', 'sqrt', 'sum', 'sums', 'svar', 'tan', 'var', 'attr', 'null',
  'tables', 'type', 'view', 'views', 'delete', 'exec', 'select', 'update',
  'asc', 'desc', 'differ', 'distinct', 'iasc', 'idesc', 'rank', 'cols',
  'csv', 'fkeys', 'key', 'keys', 'meta', 'ungroup', 'lower', 'ltrim', 'md5',
  'rtrim', 'ssr', 'string', 'trim', 'upper', 'by', 'from',
];

module.exports = {
  // identifier: plain name, must not match a standalone builtin keyword.
  // Tree-sitter keyword extraction: the `word` rule is $.identifier, so
  // tree-sitter will automatically use the longest-match rule — the builtin
  // token wins for exact keyword strings via token(prec(1,…)), while any
  // longer string (e.g. "counter") falls through to identifier.
  identifier: $ => /[A-Za-z][A-Za-z0-9_]*/,

  // dotted_name: namespace-qualified name. Supports the full forms including
  // colon used in qualified/handle names per the BINDING HANDOFF FIX requirement.
  // Regex: starts with '.', then a letter, then any combo of letters, digits,
  // underscores, dots, or colons. Covers .Q.dd, .z.ts, .q.foo:bar, handle forms.
  dotted_name: $ => token(/\.[A-Za-z][A-Za-z0-9_.]*(?::[A-Za-z][A-Za-z0-9_.]*)*/),

  // builtin: wins over identifier for exact keyword strings via prec(1, …).
  // token(prec(1, …)) ensures the lexer resolves keyword vs identifier at the
  // character level — "count" → builtin, "counter" → identifier.
  builtin: $ => token(prec(1, choice(...KEYWORDS))),

  // Infix-capable keyword token; referenced by binary's operator slot and
  // aliased to $.builtin everywhere a keyword is used as a plain noun.
  _infix_kw: $ => token(prec(1, choice(...INFIX_KEYWORDS))),

  // symbol_vector: two or more juxtaposed backtick-symbols with no spaces.
  // Implemented as a single lexer token so the scanner greedily matches all
  // adjacent backtick-names before the parser can reduce any single symbol.
  // Two or more backtick-name sequences: `a`b or `a`b`c etc.
  // Must win over a single $.symbol — token(prec(1,...)) ensures lexer priority.
  symbol_vector: $ => token(prec(1, /`[A-Za-z0-9._:]*(`[A-Za-z0-9._:]*)+/)),
};
