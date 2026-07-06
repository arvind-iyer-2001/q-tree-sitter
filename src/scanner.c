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

  /* Skip horizontal whitespace ONCE, up front, and share the result. Every
   * ws-sensitive branch (trailing comment, LIST_WS) reads this flag — when
   * each branch called skip_horiz itself, the first branch consumed the
   * whitespace and every later branch saw saw_ws=false (that bug silently
   * turned `1 2 3` vectors into juxtaposition chains). */
  bool saw_ws = skip_horiz(l);

  /* ---------------------------------------------------------------
   * EOS FIRST: statement terminator (newline at top level). Must run
   * before the comment branch, which may skip newlines while hunting
   * for `/` — a statement has to end at its newline before any comment
   * on the next line is considered.
   * --------------------------------------------------------------- */
  if (valid[EOS] && (l->lookahead == '\n' || l->lookahead == '\r') && s->depth == 0) {
    bool was_cr = (l->lookahead == '\r');
    adv(l);
    if (was_cr && l->lookahead == '\n') adv(l); /* \r\n */
    /* q continuation rule: a line that BEGINS with whitespace continues
     * the previous statement — the newline is NOT a terminator. Do NOT
     * return here: fall through so the COMMENT branch still gets its look
     * (returning false ends the whole scan call, and tree-sitter will not
     * consult the scanner again until after the internal lexer has eaten
     * the whitespace — which orphaned comment lines after blank lines). */
    if (l->lookahead != ' ' && l->lookahead != '\t') {
      s->prev_was_value = false;
      l->result_symbol = EOS;
      return true;
    }
  }

  /* ---------------------------------------------------------------
   * COMMENT: three forms
   * 1. Line comment: `/` at column 0 — rest of line
   * 2. Trailing comment: `/` at column > 0 with whitespace before it
   * 3. Block comment: a line with only `/` starts a block; terminated
   *    by a line with only `\` or end of file.
   *
   * The branch may skip whitespace INCLUDING NEWLINES itself: extras are
   * consumed by the internal lexer between scanner calls, so by the time
   * the scanner would sit directly on a mid-line `/` the "was there
   * whitespace before it" signal is gone. Peeking across newlines here is
   * safe — if no `/` follows, we return false and the position resets.
   * --------------------------------------------------------------- */
  if (valid[COMMENT]) {
    bool saw_any = saw_ws;
    while (l->lookahead == '\n' || l->lookahead == '\r' ||
           l->lookahead == ' '  || l->lookahead == '\t') {
      skip(l);
      saw_any = true;
    }
    uint32_t col = l->get_column(l);
    saw_ws = saw_any;

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
          /* Single-line comment at col 0. Leave the newline for the EOS
           * scanner — statements now REQUIRE separators, so a comment that
           * swallows its newline erases the statement boundary. */
          while (l->lookahead != '\n' && l->lookahead != '\r' && l->lookahead != 0) {
            adv(l);
          }
          l->result_symbol = COMMENT;
          return true;
        }
      } else if (saw_ws) {
        /* col > 0 trailing comment. A `/` here is a comment ONLY if whitespace
         * precedes it (`x:1 /note`) — q's lexical rule. With NO preceding
         * space (`+/`, `f/`) the `/` is the over-iterator, which the grammar
         * now lexes itself via token.immediate, so fall through. */
        adv(l);
        while (l->lookahead != '\n' && l->lookahead != '\r' && l->lookahead != 0) {
          adv(l);
        }
        /* Do NOT consume the newline — EOS must still fire on it, or the
         * following line fuses into this statement (`a:1 /c` + `b:2`). */
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
    uint32_t col = l->get_column(l);
    if (col == 0 && l->lookahead == '\\') {
      adv(l); /* consume '\' */
      /* Solitary `\` on its own line = end-of-script marker: q ignores
       * EVERYTHING after it (free-form trailing prose). Consume to EOF. */
      if (l->lookahead == '\n' || l->lookahead == '\r' || l->lookahead == 0) {
        while (l->lookahead != 0) adv(l);
        l->result_symbol = SYSTEM_COMMAND_TOK;
        return true;
      }
      /* consume rest of the line (command letter(s) + args); q's continuation
       * rule applies here too — an indented following line extends the
       * command (`\t select ...` wrapping). Peek past each newline with
       * mark_end so a NON-indented next line stays unconsumed. */
      for (;;) {
        while (l->lookahead != '\n' && l->lookahead != '\r' && l->lookahead != 0) {
          adv(l);
        }
        l->mark_end(l);
        if (l->lookahead == 0) break;
        if (l->lookahead == '\r') { adv(l); if (l->lookahead == '\n') adv(l); }
        else adv(l); /* \n */
        if (l->lookahead != ' ' && l->lookahead != '\t') break;
        /* indented continuation: absorb it, then extend the token end */
        while (l->lookahead != '\n' && l->lookahead != '\r' && l->lookahead != 0) {
          adv(l);
        }
        l->mark_end(l);
      }
      l->result_symbol = SYSTEM_COMMAND_TOK;
      return true;
    }
  }

  /* ---------------------------------------------------------------
   * NEG_NUMBER: RETIRED (2026-07-05 rewrite). Whether `-5` is a negative
   * literal or subtraction depends on the parse state, which the scanner
   * cannot know (its prev_was_value gate was unknowable for internally
   * lexed tokens — see AUDIT_2026-07-05.md). Negative literals are now the
   * grammar composition `'-' _number_token`; the enum slot stays so the
   * externals order keeps matching grammar.js.
   * --------------------------------------------------------------- */

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
    /* Newline EOS is handled FIRST, above the comment branch. */
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
    if (saw_ws && l->lookahead >= '0' && l->lookahead <= '9') {
      l->result_symbol = LIST_WS;
      return true;
    }
    /* `-5 -4 -3`: separator before a NEGATIVE element. Peek past the `-`
     * for a digit/dot; mark_end first so the `-` itself stays unconsumed
     * (the grammar's number rule owns it). */
    if (saw_ws && l->lookahead == '-') {
      l->mark_end(l);
      adv(l);
      if ((l->lookahead >= '0' && l->lookahead <= '9') || l->lookahead == '.') {
        l->result_symbol = LIST_WS;
        return true;
      }
      return false;
    }
  }

  /* ---------------------------------------------------------------
   * NEG_NUMBER (whitespace-gated): `x -5` is APPLICATION of x to the
   * literal -5 in q (space before `-`, digit right after), while `x-5`
   * and `x - 5` are subtraction. Whitespace IS observable by the scanner,
   * so unlike the retired prev_was_value gate this rule is sound. Runs AFTER
   * LIST_WS: in vector context (`2 -3`) the separator wins and the grammar
   * composes the negative element itself.
   * --------------------------------------------------------------- */
  if (valid[NEG_NUMBER] && saw_ws && l->lookahead == '-') {
    adv(l); /* consume `-` */
    bool lead_digit = (l->lookahead >= '0' && l->lookahead <= '9');
    if (lead_digit || l->lookahead == '.') {
      while ((l->lookahead >= '0' && l->lookahead <= '9') || l->lookahead == '.') {
        adv(l);
      }
      if (l->lookahead == 'e' || l->lookahead == 'E') {
        adv(l);
        if (l->lookahead == '+' || l->lookahead == '-') adv(l);
        while (l->lookahead >= '0' && l->lookahead <= '9') adv(l);
      }
      /* type suffix (-42j, -0.5f, ...) */
      if (l->lookahead == 'j' || l->lookahead == 'i' || l->lookahead == 'h' ||
          l->lookahead == 'f') {
        adv(l);
      }
      l->result_symbol = NEG_NUMBER;
      return true;
    }
    return false;
  }

  return false;
}
