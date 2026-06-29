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
  bool eof_eos_emitted;     /* zero-width EOF terminator already emitted once */
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
    bool saw_ws = skip_horiz(l);
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
      } else if (saw_ws || !valid[ADVERB_TOK]) {
        /* col > 0 trailing comment. A `/` here is a comment ONLY if a space
         * preceded it (saw_ws) — `x:1 /note` — or if no adverb is grammatically
         * expected. With NO preceding space in adverb position (`+/`, `f/`) the
         * `/` is the over-iterator, not a comment, so fall through. */
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
      /* else: `/` is an adverb glyph in adverb position — fall through. */
    }
    /* Not a `/` — not a comment */
    /* Fall through to other tokens if valid */
  }

  /* ---------------------------------------------------------------
   * SYSTEM_COMMAND_TOK: `\` at column 0 followed by command content.
   * T10: namespace_directive was FOLDED into system_command, so ALL
   * backslash commands at col 0 — including `\d .ns`, `\\` (quit) and a
   * solitary `\` (debug/namespace toggle) — are emitted as one opaque
   * SYSTEM_COMMAND_TOK. The downstream extractor (T12) inspects the text.
   * --------------------------------------------------------------- */
  if (valid[SYSTEM_COMMAND_TOK]) {
    skip_horiz(l);
    uint32_t col = l->get_column(l);
    if (col == 0 && l->lookahead == '\\') {
      adv(l); /* consume '\' */
      /* consume rest of the line (command letter(s) + args), if any.
       * A solitary `\` or `\\` ends here with nothing further. */
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
    /* EOF terminator: emit a single zero-width EOS to close a trailing
     * unterminated statement. It must NOT advance (nothing to consume at
     * EOF), so guard with a serialized flag — otherwise repeat(choice(...))
     * re-requests it forever, producing infinite zero-width nodes and an
     * unbounded parse tree (OOM). */
    if (l->lookahead == 0 && s->depth == 0 && !s->eof_eos_emitted) {
      s->eof_eos_emitted = true;
      l->result_symbol = EOS;
      return true;
    }
  }

  /* ---------------------------------------------------------------
   * LIST_WS: space(s) between numeric tokens in a vector.
   * The grammar's vector rule marks positions where LIST_WS is valid.
   * We emit it when we see whitespace followed by the start of the next
   * element: a digit, or a `-` that begins a negative number (`-5 -4 -3`).
   * In the `-` case we clear prev_was_value so the following NEG_NUMBER can
   * fire (NEG_NUMBER is gated on !prev_was_value, which the previous element
   * left set to true). NOTE: must come after COMMENT since both may be valid.
   * --------------------------------------------------------------- */
  if (valid[LIST_WS]) {
    bool saw = skip_horiz(l);
    if (saw && l->lookahead >= '0' && l->lookahead <= '9') {
      l->result_symbol = LIST_WS;
      return true;
    }
    if (saw && l->lookahead == '-' && valid[NEG_NUMBER]) {
      s->prev_was_value = false;
      l->result_symbol = LIST_WS;
      return true;
    }
  }

  return false;
}
