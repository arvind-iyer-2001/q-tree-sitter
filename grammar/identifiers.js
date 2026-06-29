module.exports = {
  identifier:    $ => /[A-Za-z][A-Za-z0-9_]*/,
  dotted_name:   $ => /\.[A-Za-z][A-Za-z0-9_.]*/,
  builtin:       $ => choice('select', 'from', 'where', 'by'),
  symbol_vector: $ => prec.left(repeat1($.symbol)),
};
