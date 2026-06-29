// KEYWORDS: the complete keyword-function set enumerated verbatim from
// references/keywords.md (§ alphabetical flattened list, all categories).
// Total: 170+ entries covering control, env, interpret, io, iterate, join,
// list, logic, math, meta, query, sort, table, and text categories.
const KEYWORDS = [
  // control
  'do', 'exit', 'if', 'while',
  // env
  'getenv', 'gtime', 'ltime', 'setenv',
  // interpret
  'eval', 'parse', 'reval', 'show', 'system', 'value',
  // io
  'dsave', 'get', 'hclose', 'hcount', 'hdel', 'hopen', 'hsym', 'load',
  'read0', 'read1', 'rload', 'rsave', 'save', 'set',
  // iterate
  'each', 'over', 'peach', 'prior', 'scan',
  // join
  'aj', 'aj0', 'ajf', 'ajf0', 'asof', 'ej', 'ij', 'ijf', 'lj', 'ljf',
  'pj', 'uj', 'ujf', 'wj', 'wj1',
  // list
  'count', 'cross', 'cut', 'enlist', 'except', 'fills', 'first', 'flip',
  'group', 'in', 'inter', 'last', 'mcount', 'next', 'prev', 'raze',
  'reverse', 'rotate', 'sublist', 'sv', 'til', 'union', 'vs', 'where',
  'xprev',
  // logic
  'all', 'and', 'any', 'not', 'or',
  // math
  'abs', 'acos', 'asin', 'atan', 'avg', 'avgs', 'ceiling', 'cor', 'cos',
  'cov', 'deltas', 'dev', 'div', 'ema', 'exp', 'floor', 'inv', 'log',
  'lsq', 'mavg', 'max', 'maxs', 'mdev', 'med', 'min', 'mins', 'mmax',
  'mmin', 'mmu', 'mod', 'msum', 'neg', 'prd', 'prds', 'rand', 'ratios',
  'reciprocal', 'scov', 'sdev', 'signum', 'sin', 'sqrt', 'sum', 'sums',
  'svar', 'tan', 'var', 'wavg', 'within', 'wsum', 'xexp', 'xlog',
  // meta
  'attr', 'null', 'tables', 'type', 'view', 'views',
  // query (q-SQL keyword functions)
  'delete', 'exec', 'fby', 'select', 'update',
  // sort
  'asc', 'bin', 'binr', 'desc', 'differ', 'distinct', 'iasc', 'idesc',
  'rank', 'xbar', 'xrank',
  // table
  'cols', 'csv', 'fkeys', 'insert', 'key', 'keys', 'meta', 'ungroup',
  'upsert', 'xasc', 'xcol', 'xcols', 'xdesc', 'xgroup', 'xkey',
  // text
  'like', 'lower', 'ltrim', 'md5', 'rtrim', 'ss', 'ssr', 'string', 'trim',
  'upper',
  // q-SQL structural words (also reserved)
  'by', 'from',
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

  // symbol_vector: two or more juxtaposed backtick-symbols with no spaces.
  // Implemented as a single lexer token so the scanner greedily matches all
  // adjacent backtick-names before the parser can reduce any single symbol.
  // Two or more backtick-name sequences: `a`b or `a`b`c etc.
  // Must win over a single $.symbol — token(prec(1,...)) ensures lexer priority.
  symbol_vector: $ => token(prec(1, /`[A-Za-z0-9._:]*(`[A-Za-z0-9._:]*)+/)),
};
