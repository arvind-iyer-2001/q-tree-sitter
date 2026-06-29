#include "tree_sitter/parser.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/* Must match externals order in grammar.js */
enum TokenType {
  COMMENT,
  SYSTEM_COMMAND_TOK,
  NEG_NUMBER,
  LIST_WS,
  ADVERB_TOK,
  EOS,
  ERROR_SENTINEL
};

typedef struct {
  unsigned depth;           /* bracket nesting depth: (, [, { */
  bool prev_was_value;      /* last meaningful token was a value/name/) /] */
} Scanner;

void *tree_sitter_q_external_scanner_create(void) {
  Scanner *s = calloc(1, sizeof(Scanner));
  return s;
}

void tree_sitter_q_external_scanner_destroy(void *p) {
  free(p);
}

unsigned tree_sitter_q_external_scanner_serialize(void *p, char *buf) {
  memcpy(buf, p, sizeof(Scanner));
  return sizeof(Scanner);
}

void tree_sitter_q_external_scanner_deserialize(void *p, const char *buf, unsigned n) {
  if (n >= sizeof(Scanner)) memcpy(p, buf, sizeof(Scanner));
}

static void adv(TSLexer *l)  { l->advance(l, false); }
static void skip(TSLexer *l) { l->advance(l, true); }

/* Skip horizontal whitespace; return true if any was skipped */
static bool skip_horiz(TSLexer *l) {
  bool skipped = false;
  while (l->lookahead == ' ' || l->lookahead == '\t') {
    skip(l);
    skipped = true;
  }
  return skipped;
}

bool tree_sitter_q_external_scanner_scan(void *payload, TSLexer *l, const bool *valid) {
  Scanner *s = (Scanner *)payload;

  /* ---------------------------------------------------------------
   * COMMENT: three forms
   * 1. Line comment: `/` at column 0 — rest of line
   * 2. Trailing comment: `/` at column > 0 (space before was consumed
   *    by extras in the internal lexer before calling us)
   * 3. Block comment: a line with only `/` starts a block; terminated
   *    by a line with only `\` or end of file.
   *
   * Key insight: by the time the external scanner is called, the
   * internal lexer has already consumed whitespace via `extras`.
   * So if we see `/` at col > 0, there was a space before it.
   * At col == 0, the `/` is either a line comment or block comment start.
   * --------------------------------------------------------------- */
  if (valid[COMMENT]) {
    /* The internal lexer may have already consumed spaces (as extras),
     * so we might be positioned directly at `/`. But we also call
     * skip_horiz ourselves to handle any remaining spaces not yet consumed. */
    skip_horiz(l);
    uint32_t col = l->get_column(l);

    if (l->lookahead == '/') {
      if (col == 0) {
        /* Line-start: consume '/' */
        adv(l);
        if (l->lookahead == '\n' || l->lookahead == '\r' || l->lookahead == 0) {
          /* Solitary '/' on a line = block comment start */
          /* consume the newline */
          if (l->lookahead == '\n') adv(l);
          else if (l->lookahead == '\r') {
            adv(l);
            if (l->lookahead == '\n') adv(l);
          }
          /* Block comment: consume until a solitary `\` on its own line or EOF */
          while (l->lookahead != 0) {
            /* Start of a new line — check for solitary `\` */
            if (l->lookahead == '\\') {
              adv(l);
              /* Skip any horizontal whitespace after `\` */
              while (l->lookahead == ' ' || l->lookahead == '\t') adv(l);
              if (l->lookahead == '\n' || l->lookahead == '\r' || l->lookahead == 0) {
                /* Solitary `\` on the line — end of block comment */
                if (l->lookahead == '\n') adv(l);
                else if (l->lookahead == '\r') {
                  adv(l);
                  if (l->lookahead == '\n') adv(l);
                }
                l->result_symbol = COMMENT;
                return true;
              }
              /* `\` followed by other chars — still inside block */
              while (l->lookahead != '\n' && l->lookahead != '\r' && l->lookahead != 0) {
                adv(l);
              }
            } else {
              /* consume rest of line */
              while (l->lookahead != '\n' && l->lookahead != '\r' && l->lookahead != 0) {
                adv(l);
              }
            }
            /* consume newline between block comment lines */
            if (l->lookahead == '\n') adv(l);
            else if (l->lookahead == '\r') {
              adv(l);
              if (l->lookahead == '\n') adv(l);
            }
          }
          /* EOF terminates block comment */
          l->result_symbol = COMMENT;
          return true;
        } else {
          /* Single-line comment at col 0 */
          while (l->lookahead != '\n' && l->lookahead != '\r' && l->lookahead != 0) {
            adv(l);
          }
          /* Consume the terminating newline so it's part of the comment token */
          if (l->lookahead == '\r') adv(l);
          if (l->lookahead == '\n') adv(l);
          l->result_symbol = COMMENT;
          return true;
        }
      } else {
        /* col > 0: trailing comment — there was a space before this `/`
         * (consumed by the internal lexer via extras). */
        adv(l);
        while (l->lookahead != '\n' && l->lookahead != '\r' && l->lookahead != 0) {
          adv(l);
        }
        /* Consume the trailing newline as part of the comment token */
        if (l->lookahead == '\r') adv(l);
        if (l->lookahead == '\n') adv(l);
        l->result_symbol = COMMENT;
        return true;
      }
    }
    /* Not a `/` — not a comment */
    /* Fall through to other tokens if valid */
  }

  /* ---------------------------------------------------------------
   * SYSTEM_COMMAND_TOK: `\` at column 0 followed by command content.
   * The grammar has a special literal rule for `\d` (namespace_directive),
   * so we MUST NOT emit SYSTEM_COMMAND_TOK when we see `\d` — the
   * internal lexer's `\\d` literal will match it instead.
   * We also skip `\\` (script-quit) and solitary `\` (debug toggle) to
   * let the comment handler or internal rules deal with those.
   * --------------------------------------------------------------- */
  if (valid[SYSTEM_COMMAND_TOK]) {
    skip_horiz(l);
    uint32_t col = l->get_column(l);
    if (col == 0 && l->lookahead == '\\') {
      /* Peek at the next character to decide if we should handle this */
      adv(l); /* consume '\' */
      /* Skip `\d` (namespace directive) — let the internal literal match it */
      if (l->lookahead == 'd') {
        /* Don't consume: let namespace_directive rule handle `\d` */
        return false;
      }
      /* Skip solitary `\` or `\\` — not a regular system command */
      if (l->lookahead == '\n' || l->lookahead == '\r' ||
          l->lookahead == 0    || l->lookahead == '\\') {
        return false;
      }
      /* consume rest of line (command letter + args) */
      while (l->lookahead != '\n' && l->lookahead != '\r' && l->lookahead != 0) {
        adv(l);
      }
      l->result_symbol = SYSTEM_COMMAND_TOK;
      return true;
    }
  }

  /* ---------------------------------------------------------------
   * NEG_NUMBER: a `-` immediately followed by a digit, where the
   * left context is NOT a value/name/)/].
   * prev_was_value tracks left context.
   * When called: lookahead is `-` and we haven't skipped whitespace yet
   * (extras already consumed spaces before calling us).
   * --------------------------------------------------------------- */
  if (valid[NEG_NUMBER] && !s->prev_was_value && l->lookahead == '-') {
    adv(l); /* consume `-` */
    if (l->lookahead >= '0' && l->lookahead <= '9') {
      while ((l->lookahead >= '0' && l->lookahead <= '9') || l->lookahead == '.') {
        adv(l);
      }
      /* optional exponent */
      if (l->lookahead == 'e' || l->lookahead == 'E') {
        adv(l);
        if (l->lookahead == '+' || l->lookahead == '-') adv(l);
        while (l->lookahead >= '0' && l->lookahead <= '9') adv(l);
      }
      s->prev_was_value = true;
      l->result_symbol = NEG_NUMBER;
      return true;
    }
    return false;
  }

  /* ---------------------------------------------------------------
   * ADVERB_TOK: postfix iterator glyphs after a value.
   * Iterators: / \ ' /: \: ':
   * Only valid when prev_was_value.
   * --------------------------------------------------------------- */
  if (valid[ADVERB_TOK] && s->prev_was_value) {
    if (l->lookahead == '/' || l->lookahead == '\\' || l->lookahead == '\'') {
      adv(l);
      if (l->lookahead == ':') adv(l); /* /: \: ': */
      l->result_symbol = ADVERB_TOK;
      return true;
    }
  }

  /* ---------------------------------------------------------------
   * EOS: top-level statement terminator (newline at depth == 0).
   * Only emitted when grammar has made EOS valid (i.e., a statement
   * could end here). We skip horizontal whitespace, then check for
   * newline.
   * --------------------------------------------------------------- */
  if (valid[EOS]) {
    skip_horiz(l);
    if ((l->lookahead == '\n' || l->lookahead == '\r') && s->depth == 0) {
      adv(l);
      if (l->lookahead == '\n' && l->lookahead == '\r') adv(l); /* \r\n */
      s->prev_was_value = false;
      l->result_symbol = EOS;
      return true;
    }
    if (l->lookahead == 0 && s->depth == 0) {
      l->result_symbol = EOS;
      return true;
    }
  }

  /* ---------------------------------------------------------------
   * LIST_WS: space(s) between numeric tokens in a vector.
   * The grammar's vector rule marks positions where LIST_WS is valid.
   * We emit it when we see whitespace followed by a digit.
   * NOTE: this must come after COMMENT check since both might be valid.
   * --------------------------------------------------------------- */
  if (valid[LIST_WS]) {
    bool saw = skip_horiz(l);
    if (saw && l->lookahead >= '0' && l->lookahead <= '9') {
      l->result_symbol = LIST_WS;
      return true;
    }
  }

  return false;
}
