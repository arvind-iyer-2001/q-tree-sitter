#include "tree_sitter/parser.h"
enum TokenType { COMMENT, SYSTEM_COMMAND_TOK, NEG_NUMBER, LIST_WS, ADVERB_TOK, EOS, ERROR_SENTINEL };
void *tree_sitter_q_external_scanner_create(void) { return NULL; }
void  tree_sitter_q_external_scanner_destroy(void *p) { (void)p; }
unsigned tree_sitter_q_external_scanner_serialize(void *p, char *b) { (void)p;(void)b; return 0; }
void  tree_sitter_q_external_scanner_deserialize(void *p, const char *b, unsigned n) { (void)p;(void)b;(void)n; }
bool  tree_sitter_q_external_scanner_scan(void *p, TSLexer *l, const bool *valid) {
  (void)p;(void)l;(void)valid; return false;  // Task 2 replaces this
}
