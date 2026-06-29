#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 110
#define LARGE_STATE_COUNT 13
#define SYMBOL_COUNT 48
#define ALIAS_COUNT 0
#define TOKEN_COUNT 27
#define EXTERNAL_TOKEN_COUNT 7
#define FIELD_COUNT 10
#define MAX_ALIAS_SEQUENCE_LENGTH 6
#define PRODUCTION_ID_COUNT 14

enum ts_symbol_identifiers {
  sym_identifier = 1,
  sym_number = 2,
  sym_string = 3,
  sym_symbol = 4,
  sym_dotted_name = 5,
  sym_builtin = 6,
  sym_symbol_vector = 7,
  anon_sym_COLON_COLON = 8,
  anon_sym_COLON = 9,
  anon_sym_LBRACE = 10,
  anon_sym_RBRACE = 11,
  anon_sym_SEMI = 12,
  anon_sym_LBRACK = 13,
  anon_sym_RBRACK = 14,
  sym_operator = 15,
  anon_sym_LPAREN = 16,
  anon_sym_RPAREN = 17,
  anon_sym_DOLLAR = 18,
  anon_sym_BSLASHd = 19,
  sym_comment = 20,
  sym__system_command_tok = 21,
  sym__neg_number = 22,
  sym__list_ws = 23,
  sym__adverb_tok = 24,
  sym__eos = 25,
  sym__error_sentinel = 26,
  sym_source_file = 27,
  sym__statement = 28,
  sym_assignment = 29,
  sym_lambda = 30,
  sym__lambda_body = 31,
  sym_parameters = 32,
  sym_param = 33,
  sym__expression = 34,
  sym__literal_ref = 35,
  sym_binary_expression = 36,
  sym_call = 37,
  sym_parenthesized = 38,
  sym_list = 39,
  sym_cond = 40,
  sym_system_command = 41,
  sym_namespace_directive = 42,
  aux_sym_source_file_repeat1 = 43,
  aux_sym__lambda_body_repeat1 = 44,
  aux_sym_parameters_repeat1 = 45,
  aux_sym_call_repeat1 = 46,
  aux_sym_list_repeat1 = 47,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_identifier] = "identifier",
  [sym_number] = "number",
  [sym_string] = "string",
  [sym_symbol] = "symbol",
  [sym_dotted_name] = "dotted_name",
  [sym_builtin] = "builtin",
  [sym_symbol_vector] = "symbol_vector",
  [anon_sym_COLON_COLON] = "::",
  [anon_sym_COLON] = ":",
  [anon_sym_LBRACE] = "{",
  [anon_sym_RBRACE] = "}",
  [anon_sym_SEMI] = ";",
  [anon_sym_LBRACK] = "[",
  [anon_sym_RBRACK] = "]",
  [sym_operator] = "operator",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [anon_sym_DOLLAR] = "$",
  [anon_sym_BSLASHd] = "\\d",
  [sym_comment] = "comment",
  [sym__system_command_tok] = "_system_command_tok",
  [sym__neg_number] = "_neg_number",
  [sym__list_ws] = "_list_ws",
  [sym__adverb_tok] = "_adverb_tok",
  [sym__eos] = "_eos",
  [sym__error_sentinel] = "_error_sentinel",
  [sym_source_file] = "source_file",
  [sym__statement] = "_statement",
  [sym_assignment] = "assignment",
  [sym_lambda] = "lambda",
  [sym__lambda_body] = "_lambda_body",
  [sym_parameters] = "parameters",
  [sym_param] = "param",
  [sym__expression] = "_expression",
  [sym__literal_ref] = "_literal_ref",
  [sym_binary_expression] = "binary_expression",
  [sym_call] = "call",
  [sym_parenthesized] = "parenthesized",
  [sym_list] = "list",
  [sym_cond] = "cond",
  [sym_system_command] = "system_command",
  [sym_namespace_directive] = "namespace_directive",
  [aux_sym_source_file_repeat1] = "source_file_repeat1",
  [aux_sym__lambda_body_repeat1] = "_lambda_body_repeat1",
  [aux_sym_parameters_repeat1] = "parameters_repeat1",
  [aux_sym_call_repeat1] = "call_repeat1",
  [aux_sym_list_repeat1] = "list_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_identifier] = sym_identifier,
  [sym_number] = sym_number,
  [sym_string] = sym_string,
  [sym_symbol] = sym_symbol,
  [sym_dotted_name] = sym_dotted_name,
  [sym_builtin] = sym_builtin,
  [sym_symbol_vector] = sym_symbol_vector,
  [anon_sym_COLON_COLON] = anon_sym_COLON_COLON,
  [anon_sym_COLON] = anon_sym_COLON,
  [anon_sym_LBRACE] = anon_sym_LBRACE,
  [anon_sym_RBRACE] = anon_sym_RBRACE,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [anon_sym_LBRACK] = anon_sym_LBRACK,
  [anon_sym_RBRACK] = anon_sym_RBRACK,
  [sym_operator] = sym_operator,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [anon_sym_DOLLAR] = anon_sym_DOLLAR,
  [anon_sym_BSLASHd] = anon_sym_BSLASHd,
  [sym_comment] = sym_comment,
  [sym__system_command_tok] = sym__system_command_tok,
  [sym__neg_number] = sym__neg_number,
  [sym__list_ws] = sym__list_ws,
  [sym__adverb_tok] = sym__adverb_tok,
  [sym__eos] = sym__eos,
  [sym__error_sentinel] = sym__error_sentinel,
  [sym_source_file] = sym_source_file,
  [sym__statement] = sym__statement,
  [sym_assignment] = sym_assignment,
  [sym_lambda] = sym_lambda,
  [sym__lambda_body] = sym__lambda_body,
  [sym_parameters] = sym_parameters,
  [sym_param] = sym_param,
  [sym__expression] = sym__expression,
  [sym__literal_ref] = sym__literal_ref,
  [sym_binary_expression] = sym_binary_expression,
  [sym_call] = sym_call,
  [sym_parenthesized] = sym_parenthesized,
  [sym_list] = sym_list,
  [sym_cond] = sym_cond,
  [sym_system_command] = sym_system_command,
  [sym_namespace_directive] = sym_namespace_directive,
  [aux_sym_source_file_repeat1] = aux_sym_source_file_repeat1,
  [aux_sym__lambda_body_repeat1] = aux_sym__lambda_body_repeat1,
  [aux_sym_parameters_repeat1] = aux_sym_parameters_repeat1,
  [aux_sym_call_repeat1] = aux_sym_call_repeat1,
  [aux_sym_list_repeat1] = aux_sym_list_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [sym_number] = {
    .visible = true,
    .named = true,
  },
  [sym_string] = {
    .visible = true,
    .named = true,
  },
  [sym_symbol] = {
    .visible = true,
    .named = true,
  },
  [sym_dotted_name] = {
    .visible = true,
    .named = true,
  },
  [sym_builtin] = {
    .visible = true,
    .named = true,
  },
  [sym_symbol_vector] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_COLON_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_COLON] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACE] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SEMI] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LBRACK] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RBRACK] = {
    .visible = true,
    .named = false,
  },
  [sym_operator] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DOLLAR] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BSLASHd] = {
    .visible = true,
    .named = false,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym__system_command_tok] = {
    .visible = false,
    .named = true,
  },
  [sym__neg_number] = {
    .visible = false,
    .named = true,
  },
  [sym__list_ws] = {
    .visible = false,
    .named = true,
  },
  [sym__adverb_tok] = {
    .visible = false,
    .named = true,
  },
  [sym__eos] = {
    .visible = false,
    .named = true,
  },
  [sym__error_sentinel] = {
    .visible = false,
    .named = true,
  },
  [sym_source_file] = {
    .visible = true,
    .named = true,
  },
  [sym__statement] = {
    .visible = false,
    .named = true,
  },
  [sym_assignment] = {
    .visible = true,
    .named = true,
  },
  [sym_lambda] = {
    .visible = true,
    .named = true,
  },
  [sym__lambda_body] = {
    .visible = false,
    .named = true,
  },
  [sym_parameters] = {
    .visible = true,
    .named = true,
  },
  [sym_param] = {
    .visible = true,
    .named = true,
  },
  [sym__expression] = {
    .visible = false,
    .named = true,
  },
  [sym__literal_ref] = {
    .visible = false,
    .named = true,
  },
  [sym_binary_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_call] = {
    .visible = true,
    .named = true,
  },
  [sym_parenthesized] = {
    .visible = true,
    .named = true,
  },
  [sym_list] = {
    .visible = true,
    .named = true,
  },
  [sym_cond] = {
    .visible = true,
    .named = true,
  },
  [sym_system_command] = {
    .visible = true,
    .named = true,
  },
  [sym_namespace_directive] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_source_file_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym__lambda_body_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_parameters_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_call_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_list_repeat1] = {
    .visible = false,
    .named = false,
  },
};

enum ts_field_identifiers {
  field_arguments = 1,
  field_body = 2,
  field_command = 3,
  field_function = 4,
  field_left = 5,
  field_namespace = 6,
  field_operator = 7,
  field_param = 8,
  field_parameters = 9,
  field_right = 10,
};

static const char * const ts_field_names[] = {
  [0] = NULL,
  [field_arguments] = "arguments",
  [field_body] = "body",
  [field_command] = "command",
  [field_function] = "function",
  [field_left] = "left",
  [field_namespace] = "namespace",
  [field_operator] = "operator",
  [field_param] = "param",
  [field_parameters] = "parameters",
  [field_right] = "right",
};

static const TSFieldMapSlice ts_field_map_slices[PRODUCTION_ID_COUNT] = {
  [1] = {.index = 0, .length = 1},
  [2] = {.index = 1, .length = 2},
  [3] = {.index = 3, .length = 1},
  [4] = {.index = 4, .length = 3},
  [5] = {.index = 7, .length = 1},
  [6] = {.index = 8, .length = 1},
  [7] = {.index = 9, .length = 1},
  [8] = {.index = 10, .length = 2},
  [9] = {.index = 12, .length = 1},
  [10] = {.index = 13, .length = 2},
  [11] = {.index = 15, .length = 3},
  [12] = {.index = 18, .length = 2},
  [13] = {.index = 20, .length = 2},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_command, 0},
  [1] =
    {field_arguments, 1},
    {field_function, 0},
  [3] =
    {field_namespace, 1},
  [4] =
    {field_left, 0},
    {field_operator, 1},
    {field_right, 2},
  [7] =
    {field_function, 0},
  [8] =
    {field_body, 1},
  [9] =
    {field_parameters, 1},
  [10] =
    {field_arguments, 2},
    {field_function, 0},
  [12] =
    {field_param, 1},
  [13] =
    {field_body, 2},
    {field_parameters, 1},
  [15] =
    {field_arguments, 2},
    {field_arguments, 3},
    {field_function, 0},
  [18] =
    {field_param, 1},
    {field_param, 2, .inherited = true},
  [20] =
    {field_param, 0, .inherited = true},
    {field_param, 1, .inherited = true},
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 2,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 7,
  [9] = 9,
  [10] = 4,
  [11] = 11,
  [12] = 11,
  [13] = 13,
  [14] = 13,
  [15] = 15,
  [16] = 16,
  [17] = 16,
  [18] = 18,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 21,
  [24] = 20,
  [25] = 18,
  [26] = 19,
  [27] = 27,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 35,
  [36] = 36,
  [37] = 37,
  [38] = 38,
  [39] = 39,
  [40] = 40,
  [41] = 41,
  [42] = 42,
  [43] = 43,
  [44] = 44,
  [45] = 45,
  [46] = 46,
  [47] = 47,
  [48] = 48,
  [49] = 49,
  [50] = 50,
  [51] = 51,
  [52] = 31,
  [53] = 28,
  [54] = 30,
  [55] = 32,
  [56] = 41,
  [57] = 33,
  [58] = 27,
  [59] = 34,
  [60] = 37,
  [61] = 40,
  [62] = 38,
  [63] = 42,
  [64] = 43,
  [65] = 39,
  [66] = 29,
  [67] = 67,
  [68] = 68,
  [69] = 69,
  [70] = 68,
  [71] = 69,
  [72] = 67,
  [73] = 73,
  [74] = 36,
  [75] = 75,
  [76] = 76,
  [77] = 35,
  [78] = 78,
  [79] = 79,
  [80] = 80,
  [81] = 81,
  [82] = 82,
  [83] = 83,
  [84] = 84,
  [85] = 85,
  [86] = 86,
  [87] = 84,
  [88] = 88,
  [89] = 89,
  [90] = 90,
  [91] = 47,
  [92] = 81,
  [93] = 82,
  [94] = 88,
  [95] = 95,
  [96] = 90,
  [97] = 97,
  [98] = 98,
  [99] = 46,
  [100] = 100,
  [101] = 101,
  [102] = 45,
  [103] = 103,
  [104] = 104,
  [105] = 104,
  [106] = 106,
  [107] = 107,
  [108] = 106,
  [109] = 103,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(5);
      ADVANCE_MAP(
        '"', 1,
        '$', 22,
        '(', 20,
        ')', 21,
        '.', 4,
        ':', 13,
        ';', 16,
        '[', 17,
        '\\', 3,
        ']', 18,
        '`', 8,
        '{', 14,
        '}', 15,
      );
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(0);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(6);
      if (('!' <= lookahead && lookahead <= '&') ||
          ('*' <= lookahead && lookahead <= '-') ||
          ('<' <= lookahead && lookahead <= '@') ||
          lookahead == '^' ||
          lookahead == '_' ||
          ('|' <= lookahead && lookahead <= '~')) ADVANCE(19);
      if (('A' <= lookahead && lookahead <= 'z')) ADVANCE(9);
      END_STATE();
    case 1:
      if (lookahead == '"') ADVANCE(7);
      if (lookahead != 0) ADVANCE(1);
      END_STATE();
    case 2:
      if (lookahead == ')') ADVANCE(21);
      if (lookahead == ';') ADVANCE(16);
      if (lookahead == ']') ADVANCE(18);
      if (lookahead == '}') ADVANCE(15);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(2);
      if (lookahead == '!' ||
          ('#' <= lookahead && lookahead <= '&') ||
          ('*' <= lookahead && lookahead <= '-') ||
          ('<' <= lookahead && lookahead <= '@') ||
          lookahead == '^' ||
          lookahead == '_' ||
          ('|' <= lookahead && lookahead <= '~')) ADVANCE(19);
      END_STATE();
    case 3:
      if (lookahead == 'd') ADVANCE(23);
      END_STATE();
    case 4:
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(10);
      END_STATE();
    case 5:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 6:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(6);
      END_STATE();
    case 7:
      ACCEPT_TOKEN(sym_string);
      END_STATE();
    case 8:
      ACCEPT_TOKEN(sym_symbol);
      if (lookahead == '`') ADVANCE(11);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= ':') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('_' <= lookahead && lookahead <= 'z')) ADVANCE(8);
      END_STATE();
    case 9:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(9);
      END_STATE();
    case 10:
      ACCEPT_TOKEN(sym_dotted_name);
      if (lookahead == ':') ADVANCE(4);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(10);
      END_STATE();
    case 11:
      ACCEPT_TOKEN(sym_symbol_vector);
      if (lookahead == '`') ADVANCE(11);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= ':') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          ('_' <= lookahead && lookahead <= 'z')) ADVANCE(11);
      END_STATE();
    case 12:
      ACCEPT_TOKEN(anon_sym_COLON_COLON);
      END_STATE();
    case 13:
      ACCEPT_TOKEN(anon_sym_COLON);
      if (lookahead == ':') ADVANCE(12);
      END_STATE();
    case 14:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 15:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 16:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 17:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 18:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 19:
      ACCEPT_TOKEN(sym_operator);
      END_STATE();
    case 20:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 21:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 22:
      ACCEPT_TOKEN(anon_sym_DOLLAR);
      END_STATE();
    case 23:
      ACCEPT_TOKEN(anon_sym_BSLASHd);
      END_STATE();
    default:
      return false;
  }
}

static bool ts_lex_keywords(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      ADVANCE_MAP(
        'a', 1,
        'b', 2,
        'c', 3,
        'd', 4,
        'e', 5,
        'f', 6,
        'g', 7,
        'h', 8,
        'i', 9,
        'k', 10,
        'l', 11,
        'm', 12,
        'n', 13,
        'o', 14,
        'p', 15,
        'r', 16,
        's', 17,
        't', 18,
        'u', 19,
        'v', 20,
        'w', 21,
        'x', 22,
      );
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(0);
      END_STATE();
    case 1:
      ADVANCE_MAP(
        'b', 23,
        'c', 24,
        'j', 25,
        'l', 26,
        'n', 27,
        's', 28,
        't', 29,
        'v', 30,
      );
      END_STATE();
    case 2:
      if (lookahead == 'i') ADVANCE(31);
      if (lookahead == 'y') ADVANCE(32);
      END_STATE();
    case 3:
      if (lookahead == 'e') ADVANCE(33);
      if (lookahead == 'o') ADVANCE(34);
      if (lookahead == 'r') ADVANCE(35);
      if (lookahead == 's') ADVANCE(36);
      if (lookahead == 'u') ADVANCE(37);
      END_STATE();
    case 4:
      if (lookahead == 'e') ADVANCE(38);
      if (lookahead == 'i') ADVANCE(39);
      if (lookahead == 'o') ADVANCE(32);
      if (lookahead == 's') ADVANCE(40);
      END_STATE();
    case 5:
      if (lookahead == 'a') ADVANCE(41);
      if (lookahead == 'j') ADVANCE(32);
      if (lookahead == 'm') ADVANCE(42);
      if (lookahead == 'n') ADVANCE(43);
      if (lookahead == 'v') ADVANCE(44);
      if (lookahead == 'x') ADVANCE(45);
      END_STATE();
    case 6:
      if (lookahead == 'b') ADVANCE(46);
      if (lookahead == 'i') ADVANCE(47);
      if (lookahead == 'k') ADVANCE(48);
      if (lookahead == 'l') ADVANCE(49);
      if (lookahead == 'r') ADVANCE(50);
      END_STATE();
    case 7:
      if (lookahead == 'e') ADVANCE(51);
      if (lookahead == 'r') ADVANCE(52);
      if (lookahead == 't') ADVANCE(53);
      END_STATE();
    case 8:
      if (lookahead == 'c') ADVANCE(54);
      if (lookahead == 'd') ADVANCE(55);
      if (lookahead == 'o') ADVANCE(56);
      if (lookahead == 's') ADVANCE(57);
      END_STATE();
    case 9:
      if (lookahead == 'a') ADVANCE(58);
      if (lookahead == 'd') ADVANCE(59);
      if (lookahead == 'f') ADVANCE(32);
      if (lookahead == 'j') ADVANCE(60);
      if (lookahead == 'n') ADVANCE(61);
      END_STATE();
    case 10:
      if (lookahead == 'e') ADVANCE(62);
      END_STATE();
    case 11:
      if (lookahead == 'a') ADVANCE(63);
      if (lookahead == 'i') ADVANCE(64);
      if (lookahead == 'j') ADVANCE(65);
      if (lookahead == 'o') ADVANCE(66);
      if (lookahead == 's') ADVANCE(67);
      if (lookahead == 't') ADVANCE(68);
      END_STATE();
    case 12:
      ADVANCE_MAP(
        'a', 69,
        'c', 70,
        'd', 71,
        'e', 72,
        'i', 73,
        'm', 74,
        'o', 75,
        's', 76,
      );
      END_STATE();
    case 13:
      if (lookahead == 'e') ADVANCE(77);
      if (lookahead == 'o') ADVANCE(78);
      if (lookahead == 'u') ADVANCE(79);
      END_STATE();
    case 14:
      if (lookahead == 'r') ADVANCE(32);
      if (lookahead == 'v') ADVANCE(80);
      END_STATE();
    case 15:
      if (lookahead == 'a') ADVANCE(81);
      if (lookahead == 'e') ADVANCE(82);
      if (lookahead == 'j') ADVANCE(32);
      if (lookahead == 'r') ADVANCE(83);
      END_STATE();
    case 16:
      if (lookahead == 'a') ADVANCE(84);
      if (lookahead == 'e') ADVANCE(85);
      if (lookahead == 'l') ADVANCE(86);
      if (lookahead == 'o') ADVANCE(87);
      if (lookahead == 's') ADVANCE(88);
      if (lookahead == 't') ADVANCE(89);
      END_STATE();
    case 17:
      ADVANCE_MAP(
        'a', 90,
        'c', 91,
        'd', 92,
        'e', 93,
        'h', 94,
        'i', 95,
        'q', 96,
        's', 97,
        't', 98,
        'u', 99,
        'v', 100,
        'y', 101,
      );
      END_STATE();
    case 18:
      if (lookahead == 'a') ADVANCE(102);
      if (lookahead == 'i') ADVANCE(103);
      if (lookahead == 'r') ADVANCE(104);
      if (lookahead == 'y') ADVANCE(105);
      END_STATE();
    case 19:
      if (lookahead == 'j') ADVANCE(106);
      if (lookahead == 'n') ADVANCE(107);
      if (lookahead == 'p') ADVANCE(108);
      END_STATE();
    case 20:
      if (lookahead == 'a') ADVANCE(109);
      if (lookahead == 'i') ADVANCE(110);
      if (lookahead == 's') ADVANCE(32);
      END_STATE();
    case 21:
      if (lookahead == 'a') ADVANCE(111);
      if (lookahead == 'h') ADVANCE(112);
      if (lookahead == 'i') ADVANCE(113);
      if (lookahead == 'j') ADVANCE(114);
      if (lookahead == 's') ADVANCE(115);
      END_STATE();
    case 22:
      ADVANCE_MAP(
        'a', 116,
        'b', 117,
        'c', 118,
        'd', 119,
        'e', 120,
        'g', 121,
        'k', 122,
        'l', 123,
        'p', 124,
        'r', 125,
      );
      END_STATE();
    case 23:
      if (lookahead == 's') ADVANCE(32);
      END_STATE();
    case 24:
      if (lookahead == 'o') ADVANCE(126);
      END_STATE();
    case 25:
      ACCEPT_TOKEN(sym_builtin);
      if (lookahead == '0') ADVANCE(32);
      if (lookahead == 'f') ADVANCE(127);
      END_STATE();
    case 26:
      if (lookahead == 'l') ADVANCE(32);
      END_STATE();
    case 27:
      if (lookahead == 'd' ||
          lookahead == 'y') ADVANCE(32);
      END_STATE();
    case 28:
      if (lookahead == 'c') ADVANCE(32);
      if (lookahead == 'i') ADVANCE(128);
      if (lookahead == 'o') ADVANCE(129);
      END_STATE();
    case 29:
      if (lookahead == 'a') ADVANCE(130);
      if (lookahead == 't') ADVANCE(131);
      END_STATE();
    case 30:
      if (lookahead == 'g') ADVANCE(132);
      END_STATE();
    case 31:
      if (lookahead == 'n') ADVANCE(133);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(sym_builtin);
      END_STATE();
    case 33:
      if (lookahead == 'i') ADVANCE(134);
      END_STATE();
    case 34:
      if (lookahead == 'l') ADVANCE(135);
      if (lookahead == 'u') ADVANCE(136);
      if (lookahead == 'r' ||
          lookahead == 's' ||
          lookahead == 'v') ADVANCE(32);
      END_STATE();
    case 35:
      if (lookahead == 'o') ADVANCE(137);
      END_STATE();
    case 36:
      if (lookahead == 'v') ADVANCE(32);
      END_STATE();
    case 37:
      if (lookahead == 't') ADVANCE(32);
      END_STATE();
    case 38:
      if (lookahead == 'l') ADVANCE(138);
      if (lookahead == 's') ADVANCE(139);
      if (lookahead == 'v') ADVANCE(32);
      END_STATE();
    case 39:
      if (lookahead == 'f') ADVANCE(140);
      if (lookahead == 's') ADVANCE(141);
      if (lookahead == 'v') ADVANCE(32);
      END_STATE();
    case 40:
      if (lookahead == 'a') ADVANCE(142);
      END_STATE();
    case 41:
      if (lookahead == 'c') ADVANCE(143);
      END_STATE();
    case 42:
      if (lookahead == 'a') ADVANCE(32);
      END_STATE();
    case 43:
      if (lookahead == 'l') ADVANCE(144);
      END_STATE();
    case 44:
      if (lookahead == 'a') ADVANCE(145);
      END_STATE();
    case 45:
      if (lookahead == 'c') ADVANCE(146);
      if (lookahead == 'e') ADVANCE(147);
      if (lookahead == 'i') ADVANCE(148);
      if (lookahead == 'p') ADVANCE(32);
      END_STATE();
    case 46:
      if (lookahead == 'y') ADVANCE(32);
      END_STATE();
    case 47:
      if (lookahead == 'l') ADVANCE(149);
      if (lookahead == 'r') ADVANCE(150);
      END_STATE();
    case 48:
      if (lookahead == 'e') ADVANCE(151);
      END_STATE();
    case 49:
      if (lookahead == 'i') ADVANCE(152);
      if (lookahead == 'o') ADVANCE(153);
      END_STATE();
    case 50:
      if (lookahead == 'o') ADVANCE(154);
      END_STATE();
    case 51:
      if (lookahead == 't') ADVANCE(155);
      END_STATE();
    case 52:
      if (lookahead == 'o') ADVANCE(156);
      END_STATE();
    case 53:
      if (lookahead == 'i') ADVANCE(157);
      END_STATE();
    case 54:
      if (lookahead == 'l') ADVANCE(158);
      if (lookahead == 'o') ADVANCE(159);
      END_STATE();
    case 55:
      if (lookahead == 'e') ADVANCE(160);
      END_STATE();
    case 56:
      if (lookahead == 'p') ADVANCE(161);
      END_STATE();
    case 57:
      if (lookahead == 'y') ADVANCE(162);
      END_STATE();
    case 58:
      if (lookahead == 's') ADVANCE(163);
      END_STATE();
    case 59:
      if (lookahead == 'e') ADVANCE(164);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(sym_builtin);
      if (lookahead == 'f') ADVANCE(32);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(sym_builtin);
      if (lookahead == 's') ADVANCE(165);
      if (lookahead == 't') ADVANCE(166);
      if (lookahead == 'v') ADVANCE(32);
      END_STATE();
    case 62:
      if (lookahead == 'y') ADVANCE(167);
      END_STATE();
    case 63:
      if (lookahead == 's') ADVANCE(168);
      END_STATE();
    case 64:
      if (lookahead == 'k') ADVANCE(169);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(sym_builtin);
      if (lookahead == 'f') ADVANCE(32);
      END_STATE();
    case 66:
      if (lookahead == 'a') ADVANCE(170);
      if (lookahead == 'g') ADVANCE(32);
      if (lookahead == 'w') ADVANCE(171);
      END_STATE();
    case 67:
      if (lookahead == 'q') ADVANCE(32);
      END_STATE();
    case 68:
      if (lookahead == 'i') ADVANCE(172);
      if (lookahead == 'r') ADVANCE(173);
      END_STATE();
    case 69:
      if (lookahead == 'v') ADVANCE(174);
      if (lookahead == 'x') ADVANCE(175);
      END_STATE();
    case 70:
      if (lookahead == 'o') ADVANCE(176);
      END_STATE();
    case 71:
      if (lookahead == '5') ADVANCE(32);
      if (lookahead == 'e') ADVANCE(177);
      END_STATE();
    case 72:
      if (lookahead == 'd') ADVANCE(32);
      if (lookahead == 't') ADVANCE(178);
      END_STATE();
    case 73:
      if (lookahead == 'n') ADVANCE(179);
      END_STATE();
    case 74:
      if (lookahead == 'a') ADVANCE(180);
      if (lookahead == 'i') ADVANCE(181);
      if (lookahead == 'u') ADVANCE(32);
      END_STATE();
    case 75:
      if (lookahead == 'd') ADVANCE(32);
      END_STATE();
    case 76:
      if (lookahead == 'u') ADVANCE(182);
      END_STATE();
    case 77:
      if (lookahead == 'g') ADVANCE(32);
      if (lookahead == 'x') ADVANCE(183);
      END_STATE();
    case 78:
      if (lookahead == 't') ADVANCE(32);
      END_STATE();
    case 79:
      if (lookahead == 'l') ADVANCE(184);
      END_STATE();
    case 80:
      if (lookahead == 'e') ADVANCE(185);
      END_STATE();
    case 81:
      if (lookahead == 'r') ADVANCE(186);
      END_STATE();
    case 82:
      if (lookahead == 'a') ADVANCE(187);
      END_STATE();
    case 83:
      if (lookahead == 'd') ADVANCE(188);
      if (lookahead == 'e') ADVANCE(189);
      if (lookahead == 'i') ADVANCE(190);
      END_STATE();
    case 84:
      if (lookahead == 'n') ADVANCE(191);
      if (lookahead == 't') ADVANCE(192);
      if (lookahead == 'z') ADVANCE(193);
      END_STATE();
    case 85:
      if (lookahead == 'a') ADVANCE(194);
      if (lookahead == 'c') ADVANCE(195);
      if (lookahead == 'v') ADVANCE(196);
      END_STATE();
    case 86:
      if (lookahead == 'o') ADVANCE(197);
      END_STATE();
    case 87:
      if (lookahead == 't') ADVANCE(198);
      END_STATE();
    case 88:
      if (lookahead == 'a') ADVANCE(199);
      END_STATE();
    case 89:
      if (lookahead == 'r') ADVANCE(200);
      END_STATE();
    case 90:
      if (lookahead == 'v') ADVANCE(201);
      END_STATE();
    case 91:
      if (lookahead == 'a') ADVANCE(202);
      if (lookahead == 'o') ADVANCE(203);
      END_STATE();
    case 92:
      if (lookahead == 'e') ADVANCE(204);
      END_STATE();
    case 93:
      if (lookahead == 'l') ADVANCE(205);
      if (lookahead == 't') ADVANCE(206);
      END_STATE();
    case 94:
      if (lookahead == 'o') ADVANCE(207);
      END_STATE();
    case 95:
      if (lookahead == 'g') ADVANCE(208);
      if (lookahead == 'n') ADVANCE(32);
      END_STATE();
    case 96:
      if (lookahead == 'r') ADVANCE(209);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(sym_builtin);
      if (lookahead == 'r') ADVANCE(32);
      END_STATE();
    case 98:
      if (lookahead == 'r') ADVANCE(210);
      END_STATE();
    case 99:
      if (lookahead == 'b') ADVANCE(211);
      if (lookahead == 'm') ADVANCE(212);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(sym_builtin);
      if (lookahead == 'a') ADVANCE(213);
      END_STATE();
    case 101:
      if (lookahead == 's') ADVANCE(214);
      END_STATE();
    case 102:
      if (lookahead == 'b') ADVANCE(215);
      if (lookahead == 'n') ADVANCE(32);
      END_STATE();
    case 103:
      if (lookahead == 'l') ADVANCE(32);
      END_STATE();
    case 104:
      if (lookahead == 'i') ADVANCE(216);
      END_STATE();
    case 105:
      if (lookahead == 'p') ADVANCE(217);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(sym_builtin);
      if (lookahead == 'f') ADVANCE(32);
      END_STATE();
    case 107:
      if (lookahead == 'g') ADVANCE(218);
      if (lookahead == 'i') ADVANCE(219);
      END_STATE();
    case 108:
      if (lookahead == 'd') ADVANCE(220);
      if (lookahead == 'p') ADVANCE(221);
      if (lookahead == 's') ADVANCE(222);
      END_STATE();
    case 109:
      if (lookahead == 'l') ADVANCE(223);
      if (lookahead == 'r') ADVANCE(32);
      END_STATE();
    case 110:
      if (lookahead == 'e') ADVANCE(224);
      END_STATE();
    case 111:
      if (lookahead == 'v') ADVANCE(225);
      END_STATE();
    case 112:
      if (lookahead == 'e') ADVANCE(226);
      if (lookahead == 'i') ADVANCE(227);
      END_STATE();
    case 113:
      if (lookahead == 't') ADVANCE(228);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(sym_builtin);
      if (lookahead == '1') ADVANCE(32);
      END_STATE();
    case 115:
      if (lookahead == 'u') ADVANCE(229);
      END_STATE();
    case 116:
      if (lookahead == 's') ADVANCE(230);
      END_STATE();
    case 117:
      if (lookahead == 'a') ADVANCE(231);
      END_STATE();
    case 118:
      if (lookahead == 'o') ADVANCE(232);
      END_STATE();
    case 119:
      if (lookahead == 'e') ADVANCE(233);
      END_STATE();
    case 120:
      if (lookahead == 'x') ADVANCE(234);
      END_STATE();
    case 121:
      if (lookahead == 'r') ADVANCE(235);
      END_STATE();
    case 122:
      if (lookahead == 'e') ADVANCE(236);
      END_STATE();
    case 123:
      if (lookahead == 'o') ADVANCE(237);
      END_STATE();
    case 124:
      if (lookahead == 'r') ADVANCE(238);
      END_STATE();
    case 125:
      if (lookahead == 'a') ADVANCE(239);
      END_STATE();
    case 126:
      if (lookahead == 's') ADVANCE(32);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(sym_builtin);
      if (lookahead == '0') ADVANCE(32);
      END_STATE();
    case 128:
      if (lookahead == 'n') ADVANCE(32);
      END_STATE();
    case 129:
      if (lookahead == 'f') ADVANCE(32);
      END_STATE();
    case 130:
      if (lookahead == 'n') ADVANCE(32);
      END_STATE();
    case 131:
      if (lookahead == 'r') ADVANCE(32);
      END_STATE();
    case 132:
      ACCEPT_TOKEN(sym_builtin);
      if (lookahead == 's') ADVANCE(32);
      END_STATE();
    case 133:
      ACCEPT_TOKEN(sym_builtin);
      if (lookahead == 'r') ADVANCE(32);
      END_STATE();
    case 134:
      if (lookahead == 'l') ADVANCE(240);
      END_STATE();
    case 135:
      if (lookahead == 's') ADVANCE(32);
      END_STATE();
    case 136:
      if (lookahead == 'n') ADVANCE(241);
      END_STATE();
    case 137:
      if (lookahead == 's') ADVANCE(242);
      END_STATE();
    case 138:
      if (lookahead == 'e') ADVANCE(243);
      if (lookahead == 't') ADVANCE(244);
      END_STATE();
    case 139:
      if (lookahead == 'c') ADVANCE(32);
      END_STATE();
    case 140:
      if (lookahead == 'f') ADVANCE(245);
      END_STATE();
    case 141:
      if (lookahead == 't') ADVANCE(246);
      END_STATE();
    case 142:
      if (lookahead == 'v') ADVANCE(247);
      END_STATE();
    case 143:
      if (lookahead == 'h') ADVANCE(32);
      END_STATE();
    case 144:
      if (lookahead == 'i') ADVANCE(248);
      END_STATE();
    case 145:
      if (lookahead == 'l') ADVANCE(32);
      END_STATE();
    case 146:
      if (lookahead == 'e') ADVANCE(249);
      END_STATE();
    case 147:
      if (lookahead == 'c') ADVANCE(32);
      END_STATE();
    case 148:
      if (lookahead == 't') ADVANCE(32);
      END_STATE();
    case 149:
      if (lookahead == 'l') ADVANCE(250);
      END_STATE();
    case 150:
      if (lookahead == 's') ADVANCE(251);
      END_STATE();
    case 151:
      if (lookahead == 'y') ADVANCE(252);
      END_STATE();
    case 152:
      if (lookahead == 'p') ADVANCE(32);
      END_STATE();
    case 153:
      if (lookahead == 'o') ADVANCE(253);
      END_STATE();
    case 154:
      if (lookahead == 'm') ADVANCE(32);
      END_STATE();
    case 155:
      ACCEPT_TOKEN(sym_builtin);
      if (lookahead == 'e') ADVANCE(254);
      END_STATE();
    case 156:
      if (lookahead == 'u') ADVANCE(255);
      END_STATE();
    case 157:
      if (lookahead == 'm') ADVANCE(256);
      END_STATE();
    case 158:
      if (lookahead == 'o') ADVANCE(257);
      END_STATE();
    case 159:
      if (lookahead == 'u') ADVANCE(258);
      END_STATE();
    case 160:
      if (lookahead == 'l') ADVANCE(32);
      END_STATE();
    case 161:
      if (lookahead == 'e') ADVANCE(259);
      END_STATE();
    case 162:
      if (lookahead == 'm') ADVANCE(32);
      END_STATE();
    case 163:
      if (lookahead == 'c') ADVANCE(32);
      END_STATE();
    case 164:
      if (lookahead == 's') ADVANCE(260);
      END_STATE();
    case 165:
      if (lookahead == 'e') ADVANCE(261);
      END_STATE();
    case 166:
      if (lookahead == 'e') ADVANCE(262);
      END_STATE();
    case 167:
      ACCEPT_TOKEN(sym_builtin);
      if (lookahead == 's') ADVANCE(32);
      END_STATE();
    case 168:
      if (lookahead == 't') ADVANCE(32);
      END_STATE();
    case 169:
      if (lookahead == 'e') ADVANCE(32);
      END_STATE();
    case 170:
      if (lookahead == 'd') ADVANCE(32);
      END_STATE();
    case 171:
      if (lookahead == 'e') ADVANCE(263);
      END_STATE();
    case 172:
      if (lookahead == 'm') ADVANCE(264);
      END_STATE();
    case 173:
      if (lookahead == 'i') ADVANCE(265);
      END_STATE();
    case 174:
      if (lookahead == 'g') ADVANCE(32);
      END_STATE();
    case 175:
      ACCEPT_TOKEN(sym_builtin);
      if (lookahead == 's') ADVANCE(32);
      END_STATE();
    case 176:
      if (lookahead == 'u') ADVANCE(266);
      END_STATE();
    case 177:
      if (lookahead == 'v') ADVANCE(32);
      END_STATE();
    case 178:
      if (lookahead == 'a') ADVANCE(32);
      END_STATE();
    case 179:
      ACCEPT_TOKEN(sym_builtin);
      if (lookahead == 's') ADVANCE(32);
      END_STATE();
    case 180:
      if (lookahead == 'x') ADVANCE(32);
      END_STATE();
    case 181:
      if (lookahead == 'n') ADVANCE(32);
      END_STATE();
    case 182:
      if (lookahead == 'm') ADVANCE(32);
      END_STATE();
    case 183:
      if (lookahead == 't') ADVANCE(32);
      END_STATE();
    case 184:
      if (lookahead == 'l') ADVANCE(32);
      END_STATE();
    case 185:
      if (lookahead == 'r') ADVANCE(32);
      END_STATE();
    case 186:
      if (lookahead == 's') ADVANCE(267);
      END_STATE();
    case 187:
      if (lookahead == 'c') ADVANCE(268);
      END_STATE();
    case 188:
      ACCEPT_TOKEN(sym_builtin);
      if (lookahead == 's') ADVANCE(32);
      END_STATE();
    case 189:
      if (lookahead == 'v') ADVANCE(32);
      END_STATE();
    case 190:
      if (lookahead == 'o') ADVANCE(269);
      END_STATE();
    case 191:
      if (lookahead == 'd' ||
          lookahead == 'k') ADVANCE(32);
      END_STATE();
    case 192:
      if (lookahead == 'i') ADVANCE(270);
      END_STATE();
    case 193:
      if (lookahead == 'e') ADVANCE(32);
      END_STATE();
    case 194:
      if (lookahead == 'd') ADVANCE(271);
      END_STATE();
    case 195:
      if (lookahead == 'i') ADVANCE(272);
      END_STATE();
    case 196:
      if (lookahead == 'a') ADVANCE(273);
      if (lookahead == 'e') ADVANCE(274);
      END_STATE();
    case 197:
      if (lookahead == 'a') ADVANCE(275);
      END_STATE();
    case 198:
      if (lookahead == 'a') ADVANCE(276);
      END_STATE();
    case 199:
      if (lookahead == 'v') ADVANCE(277);
      END_STATE();
    case 200:
      if (lookahead == 'i') ADVANCE(278);
      END_STATE();
    case 201:
      if (lookahead == 'e') ADVANCE(32);
      END_STATE();
    case 202:
      if (lookahead == 'n') ADVANCE(32);
      END_STATE();
    case 203:
      if (lookahead == 'v') ADVANCE(32);
      END_STATE();
    case 204:
      if (lookahead == 'v') ADVANCE(32);
      END_STATE();
    case 205:
      if (lookahead == 'e') ADVANCE(279);
      END_STATE();
    case 206:
      ACCEPT_TOKEN(sym_builtin);
      if (lookahead == 'e') ADVANCE(280);
      END_STATE();
    case 207:
      if (lookahead == 'w') ADVANCE(32);
      END_STATE();
    case 208:
      if (lookahead == 'n') ADVANCE(281);
      END_STATE();
    case 209:
      if (lookahead == 't') ADVANCE(32);
      END_STATE();
    case 210:
      if (lookahead == 'i') ADVANCE(282);
      END_STATE();
    case 211:
      if (lookahead == 'l') ADVANCE(283);
      END_STATE();
    case 212:
      ACCEPT_TOKEN(sym_builtin);
      if (lookahead == 's') ADVANCE(32);
      END_STATE();
    case 213:
      if (lookahead == 'r') ADVANCE(32);
      END_STATE();
    case 214:
      if (lookahead == 't') ADVANCE(284);
      END_STATE();
    case 215:
      if (lookahead == 'l') ADVANCE(285);
      END_STATE();
    case 216:
      if (lookahead == 'm') ADVANCE(32);
      END_STATE();
    case 217:
      if (lookahead == 'e') ADVANCE(32);
      END_STATE();
    case 218:
      if (lookahead == 'r') ADVANCE(286);
      END_STATE();
    case 219:
      if (lookahead == 'o') ADVANCE(287);
      END_STATE();
    case 220:
      if (lookahead == 'a') ADVANCE(288);
      END_STATE();
    case 221:
      if (lookahead == 'e') ADVANCE(289);
      END_STATE();
    case 222:
      if (lookahead == 'e') ADVANCE(290);
      END_STATE();
    case 223:
      if (lookahead == 'u') ADVANCE(291);
      END_STATE();
    case 224:
      if (lookahead == 'w') ADVANCE(292);
      END_STATE();
    case 225:
      if (lookahead == 'g') ADVANCE(32);
      END_STATE();
    case 226:
      if (lookahead == 'r') ADVANCE(293);
      END_STATE();
    case 227:
      if (lookahead == 'l') ADVANCE(294);
      END_STATE();
    case 228:
      if (lookahead == 'h') ADVANCE(295);
      END_STATE();
    case 229:
      if (lookahead == 'm') ADVANCE(32);
      END_STATE();
    case 230:
      if (lookahead == 'c') ADVANCE(32);
      END_STATE();
    case 231:
      if (lookahead == 'r') ADVANCE(32);
      END_STATE();
    case 232:
      if (lookahead == 'l') ADVANCE(296);
      END_STATE();
    case 233:
      if (lookahead == 's') ADVANCE(297);
      END_STATE();
    case 234:
      if (lookahead == 'p') ADVANCE(32);
      END_STATE();
    case 235:
      if (lookahead == 'o') ADVANCE(298);
      END_STATE();
    case 236:
      if (lookahead == 'y') ADVANCE(32);
      END_STATE();
    case 237:
      if (lookahead == 'g') ADVANCE(32);
      END_STATE();
    case 238:
      if (lookahead == 'e') ADVANCE(299);
      END_STATE();
    case 239:
      if (lookahead == 'n') ADVANCE(300);
      END_STATE();
    case 240:
      if (lookahead == 'i') ADVANCE(301);
      END_STATE();
    case 241:
      if (lookahead == 't') ADVANCE(32);
      END_STATE();
    case 242:
      if (lookahead == 's') ADVANCE(32);
      END_STATE();
    case 243:
      if (lookahead == 't') ADVANCE(302);
      END_STATE();
    case 244:
      if (lookahead == 'a') ADVANCE(303);
      END_STATE();
    case 245:
      if (lookahead == 'e') ADVANCE(304);
      END_STATE();
    case 246:
      if (lookahead == 'i') ADVANCE(305);
      END_STATE();
    case 247:
      if (lookahead == 'e') ADVANCE(32);
      END_STATE();
    case 248:
      if (lookahead == 's') ADVANCE(306);
      END_STATE();
    case 249:
      if (lookahead == 'p') ADVANCE(307);
      END_STATE();
    case 250:
      if (lookahead == 's') ADVANCE(32);
      END_STATE();
    case 251:
      if (lookahead == 't') ADVANCE(32);
      END_STATE();
    case 252:
      if (lookahead == 's') ADVANCE(32);
      END_STATE();
    case 253:
      if (lookahead == 'r') ADVANCE(32);
      END_STATE();
    case 254:
      if (lookahead == 'n') ADVANCE(308);
      END_STATE();
    case 255:
      if (lookahead == 'p') ADVANCE(32);
      END_STATE();
    case 256:
      if (lookahead == 'e') ADVANCE(32);
      END_STATE();
    case 257:
      if (lookahead == 's') ADVANCE(309);
      END_STATE();
    case 258:
      if (lookahead == 'n') ADVANCE(310);
      END_STATE();
    case 259:
      if (lookahead == 'n') ADVANCE(32);
      END_STATE();
    case 260:
      if (lookahead == 'c') ADVANCE(32);
      END_STATE();
    case 261:
      if (lookahead == 'r') ADVANCE(311);
      END_STATE();
    case 262:
      if (lookahead == 'r') ADVANCE(32);
      END_STATE();
    case 263:
      if (lookahead == 'r') ADVANCE(32);
      END_STATE();
    case 264:
      if (lookahead == 'e') ADVANCE(32);
      END_STATE();
    case 265:
      if (lookahead == 'm') ADVANCE(32);
      END_STATE();
    case 266:
      if (lookahead == 'n') ADVANCE(312);
      END_STATE();
    case 267:
      if (lookahead == 'e') ADVANCE(32);
      END_STATE();
    case 268:
      if (lookahead == 'h') ADVANCE(32);
      END_STATE();
    case 269:
      if (lookahead == 'r') ADVANCE(32);
      END_STATE();
    case 270:
      if (lookahead == 'o') ADVANCE(313);
      END_STATE();
    case 271:
      if (lookahead == '0' ||
          lookahead == '1') ADVANCE(32);
      END_STATE();
    case 272:
      if (lookahead == 'p') ADVANCE(314);
      END_STATE();
    case 273:
      if (lookahead == 'l') ADVANCE(32);
      END_STATE();
    case 274:
      if (lookahead == 'r') ADVANCE(315);
      END_STATE();
    case 275:
      if (lookahead == 'd') ADVANCE(32);
      END_STATE();
    case 276:
      if (lookahead == 't') ADVANCE(316);
      END_STATE();
    case 277:
      if (lookahead == 'e') ADVANCE(32);
      END_STATE();
    case 278:
      if (lookahead == 'm') ADVANCE(32);
      END_STATE();
    case 279:
      if (lookahead == 'c') ADVANCE(317);
      END_STATE();
    case 280:
      if (lookahead == 'n') ADVANCE(318);
      END_STATE();
    case 281:
      if (lookahead == 'u') ADVANCE(319);
      END_STATE();
    case 282:
      if (lookahead == 'n') ADVANCE(320);
      END_STATE();
    case 283:
      if (lookahead == 'i') ADVANCE(321);
      END_STATE();
    case 284:
      if (lookahead == 'e') ADVANCE(322);
      END_STATE();
    case 285:
      if (lookahead == 'e') ADVANCE(323);
      END_STATE();
    case 286:
      if (lookahead == 'o') ADVANCE(324);
      END_STATE();
    case 287:
      if (lookahead == 'n') ADVANCE(32);
      END_STATE();
    case 288:
      if (lookahead == 't') ADVANCE(325);
      END_STATE();
    case 289:
      if (lookahead == 'r') ADVANCE(32);
      END_STATE();
    case 290:
      if (lookahead == 'r') ADVANCE(326);
      END_STATE();
    case 291:
      if (lookahead == 'e') ADVANCE(32);
      END_STATE();
    case 292:
      ACCEPT_TOKEN(sym_builtin);
      if (lookahead == 's') ADVANCE(32);
      END_STATE();
    case 293:
      if (lookahead == 'e') ADVANCE(32);
      END_STATE();
    case 294:
      if (lookahead == 'e') ADVANCE(32);
      END_STATE();
    case 295:
      if (lookahead == 'i') ADVANCE(327);
      END_STATE();
    case 296:
      ACCEPT_TOKEN(sym_builtin);
      if (lookahead == 's') ADVANCE(32);
      END_STATE();
    case 297:
      if (lookahead == 'c') ADVANCE(32);
      END_STATE();
    case 298:
      if (lookahead == 'u') ADVANCE(328);
      END_STATE();
    case 299:
      if (lookahead == 'v') ADVANCE(32);
      END_STATE();
    case 300:
      if (lookahead == 'k') ADVANCE(32);
      END_STATE();
    case 301:
      if (lookahead == 'n') ADVANCE(329);
      END_STATE();
    case 302:
      if (lookahead == 'e') ADVANCE(32);
      END_STATE();
    case 303:
      if (lookahead == 's') ADVANCE(32);
      END_STATE();
    case 304:
      if (lookahead == 'r') ADVANCE(32);
      END_STATE();
    case 305:
      if (lookahead == 'n') ADVANCE(330);
      END_STATE();
    case 306:
      if (lookahead == 't') ADVANCE(32);
      END_STATE();
    case 307:
      if (lookahead == 't') ADVANCE(32);
      END_STATE();
    case 308:
      if (lookahead == 'v') ADVANCE(32);
      END_STATE();
    case 309:
      if (lookahead == 'e') ADVANCE(32);
      END_STATE();
    case 310:
      if (lookahead == 't') ADVANCE(32);
      END_STATE();
    case 311:
      if (lookahead == 't') ADVANCE(32);
      END_STATE();
    case 312:
      if (lookahead == 't') ADVANCE(32);
      END_STATE();
    case 313:
      if (lookahead == 's') ADVANCE(32);
      END_STATE();
    case 314:
      if (lookahead == 'r') ADVANCE(331);
      END_STATE();
    case 315:
      if (lookahead == 's') ADVANCE(332);
      END_STATE();
    case 316:
      if (lookahead == 'e') ADVANCE(32);
      END_STATE();
    case 317:
      if (lookahead == 't') ADVANCE(32);
      END_STATE();
    case 318:
      if (lookahead == 'v') ADVANCE(32);
      END_STATE();
    case 319:
      if (lookahead == 'm') ADVANCE(32);
      END_STATE();
    case 320:
      if (lookahead == 'g') ADVANCE(32);
      END_STATE();
    case 321:
      if (lookahead == 's') ADVANCE(333);
      END_STATE();
    case 322:
      if (lookahead == 'm') ADVANCE(32);
      END_STATE();
    case 323:
      if (lookahead == 's') ADVANCE(32);
      END_STATE();
    case 324:
      if (lookahead == 'u') ADVANCE(334);
      END_STATE();
    case 325:
      if (lookahead == 'e') ADVANCE(32);
      END_STATE();
    case 326:
      if (lookahead == 't') ADVANCE(32);
      END_STATE();
    case 327:
      if (lookahead == 'n') ADVANCE(32);
      END_STATE();
    case 328:
      if (lookahead == 'p') ADVANCE(32);
      END_STATE();
    case 329:
      if (lookahead == 'g') ADVANCE(32);
      END_STATE();
    case 330:
      if (lookahead == 'c') ADVANCE(335);
      END_STATE();
    case 331:
      if (lookahead == 'o') ADVANCE(336);
      END_STATE();
    case 332:
      if (lookahead == 'e') ADVANCE(32);
      END_STATE();
    case 333:
      if (lookahead == 't') ADVANCE(32);
      END_STATE();
    case 334:
      if (lookahead == 'p') ADVANCE(32);
      END_STATE();
    case 335:
      if (lookahead == 't') ADVANCE(32);
      END_STATE();
    case 336:
      if (lookahead == 'c') ADVANCE(337);
      END_STATE();
    case 337:
      if (lookahead == 'a') ADVANCE(338);
      END_STATE();
    case 338:
      if (lookahead == 'l') ADVANCE(32);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0, .external_lex_state = 1},
  [1] = {.lex_state = 0, .external_lex_state = 2},
  [2] = {.lex_state = 0, .external_lex_state = 2},
  [3] = {.lex_state = 0, .external_lex_state = 2},
  [4] = {.lex_state = 0, .external_lex_state = 3},
  [5] = {.lex_state = 0, .external_lex_state = 2},
  [6] = {.lex_state = 0, .external_lex_state = 2},
  [7] = {.lex_state = 0, .external_lex_state = 2},
  [8] = {.lex_state = 0, .external_lex_state = 2},
  [9] = {.lex_state = 0, .external_lex_state = 2},
  [10] = {.lex_state = 0, .external_lex_state = 4},
  [11] = {.lex_state = 0, .external_lex_state = 4},
  [12] = {.lex_state = 0, .external_lex_state = 3},
  [13] = {.lex_state = 0, .external_lex_state = 4},
  [14] = {.lex_state = 0, .external_lex_state = 4},
  [15] = {.lex_state = 0, .external_lex_state = 4},
  [16] = {.lex_state = 0, .external_lex_state = 4},
  [17] = {.lex_state = 0, .external_lex_state = 4},
  [18] = {.lex_state = 0, .external_lex_state = 4},
  [19] = {.lex_state = 0, .external_lex_state = 4},
  [20] = {.lex_state = 0, .external_lex_state = 4},
  [21] = {.lex_state = 0, .external_lex_state = 4},
  [22] = {.lex_state = 0, .external_lex_state = 4},
  [23] = {.lex_state = 0, .external_lex_state = 4},
  [24] = {.lex_state = 0, .external_lex_state = 4},
  [25] = {.lex_state = 0, .external_lex_state = 4},
  [26] = {.lex_state = 0, .external_lex_state = 4},
  [27] = {.lex_state = 0, .external_lex_state = 3},
  [28] = {.lex_state = 0, .external_lex_state = 3},
  [29] = {.lex_state = 0, .external_lex_state = 3},
  [30] = {.lex_state = 0, .external_lex_state = 3},
  [31] = {.lex_state = 0, .external_lex_state = 3},
  [32] = {.lex_state = 0, .external_lex_state = 3},
  [33] = {.lex_state = 0, .external_lex_state = 3},
  [34] = {.lex_state = 0, .external_lex_state = 3},
  [35] = {.lex_state = 0, .external_lex_state = 3},
  [36] = {.lex_state = 0, .external_lex_state = 3},
  [37] = {.lex_state = 0, .external_lex_state = 3},
  [38] = {.lex_state = 0, .external_lex_state = 3},
  [39] = {.lex_state = 0, .external_lex_state = 3},
  [40] = {.lex_state = 0, .external_lex_state = 3},
  [41] = {.lex_state = 0, .external_lex_state = 3},
  [42] = {.lex_state = 0, .external_lex_state = 3},
  [43] = {.lex_state = 0, .external_lex_state = 3},
  [44] = {.lex_state = 0, .external_lex_state = 3},
  [45] = {.lex_state = 0, .external_lex_state = 3},
  [46] = {.lex_state = 0, .external_lex_state = 3},
  [47] = {.lex_state = 0, .external_lex_state = 3},
  [48] = {.lex_state = 0, .external_lex_state = 2},
  [49] = {.lex_state = 0, .external_lex_state = 2},
  [50] = {.lex_state = 0, .external_lex_state = 2},
  [51] = {.lex_state = 0, .external_lex_state = 2},
  [52] = {.lex_state = 2, .external_lex_state = 4},
  [53] = {.lex_state = 2, .external_lex_state = 4},
  [54] = {.lex_state = 2, .external_lex_state = 4},
  [55] = {.lex_state = 2, .external_lex_state = 4},
  [56] = {.lex_state = 2, .external_lex_state = 4},
  [57] = {.lex_state = 2, .external_lex_state = 4},
  [58] = {.lex_state = 2, .external_lex_state = 4},
  [59] = {.lex_state = 2, .external_lex_state = 4},
  [60] = {.lex_state = 2, .external_lex_state = 4},
  [61] = {.lex_state = 2, .external_lex_state = 4},
  [62] = {.lex_state = 2, .external_lex_state = 4},
  [63] = {.lex_state = 2, .external_lex_state = 4},
  [64] = {.lex_state = 2, .external_lex_state = 4},
  [65] = {.lex_state = 2, .external_lex_state = 4},
  [66] = {.lex_state = 2, .external_lex_state = 4},
  [67] = {.lex_state = 2, .external_lex_state = 4},
  [68] = {.lex_state = 2, .external_lex_state = 4},
  [69] = {.lex_state = 2, .external_lex_state = 4},
  [70] = {.lex_state = 2, .external_lex_state = 4},
  [71] = {.lex_state = 2, .external_lex_state = 4},
  [72] = {.lex_state = 2, .external_lex_state = 4},
  [73] = {.lex_state = 2, .external_lex_state = 4},
  [74] = {.lex_state = 2, .external_lex_state = 4},
  [75] = {.lex_state = 0, .external_lex_state = 4},
  [76] = {.lex_state = 0, .external_lex_state = 4},
  [77] = {.lex_state = 2, .external_lex_state = 4},
  [78] = {.lex_state = 0, .external_lex_state = 4},
  [79] = {.lex_state = 0, .external_lex_state = 4},
  [80] = {.lex_state = 0, .external_lex_state = 4},
  [81] = {.lex_state = 0, .external_lex_state = 4},
  [82] = {.lex_state = 0, .external_lex_state = 4},
  [83] = {.lex_state = 0, .external_lex_state = 4},
  [84] = {.lex_state = 2, .external_lex_state = 4},
  [85] = {.lex_state = 0, .external_lex_state = 4},
  [86] = {.lex_state = 2, .external_lex_state = 4},
  [87] = {.lex_state = 2, .external_lex_state = 4},
  [88] = {.lex_state = 0, .external_lex_state = 4},
  [89] = {.lex_state = 0, .external_lex_state = 4},
  [90] = {.lex_state = 0, .external_lex_state = 4},
  [91] = {.lex_state = 0, .external_lex_state = 4},
  [92] = {.lex_state = 0, .external_lex_state = 4},
  [93] = {.lex_state = 0, .external_lex_state = 4},
  [94] = {.lex_state = 0, .external_lex_state = 4},
  [95] = {.lex_state = 0, .external_lex_state = 4},
  [96] = {.lex_state = 0, .external_lex_state = 4},
  [97] = {.lex_state = 0, .external_lex_state = 4},
  [98] = {.lex_state = 0, .external_lex_state = 4},
  [99] = {.lex_state = 0, .external_lex_state = 4},
  [100] = {.lex_state = 0, .external_lex_state = 4},
  [101] = {.lex_state = 0, .external_lex_state = 4},
  [102] = {.lex_state = 0, .external_lex_state = 4},
  [103] = {.lex_state = 0, .external_lex_state = 4},
  [104] = {.lex_state = 0, .external_lex_state = 4},
  [105] = {.lex_state = 0, .external_lex_state = 4},
  [106] = {.lex_state = 0, .external_lex_state = 4},
  [107] = {.lex_state = 0, .external_lex_state = 4},
  [108] = {.lex_state = 0, .external_lex_state = 4},
  [109] = {.lex_state = 0, .external_lex_state = 4},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [sym_number] = ACTIONS(1),
    [sym_string] = ACTIONS(1),
    [sym_symbol] = ACTIONS(1),
    [sym_dotted_name] = ACTIONS(1),
    [sym_builtin] = ACTIONS(1),
    [sym_symbol_vector] = ACTIONS(1),
    [anon_sym_COLON_COLON] = ACTIONS(1),
    [anon_sym_COLON] = ACTIONS(1),
    [anon_sym_LBRACE] = ACTIONS(1),
    [anon_sym_RBRACE] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_LBRACK] = ACTIONS(1),
    [anon_sym_RBRACK] = ACTIONS(1),
    [sym_operator] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [anon_sym_DOLLAR] = ACTIONS(1),
    [anon_sym_BSLASHd] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
    [sym__system_command_tok] = ACTIONS(1),
    [sym__neg_number] = ACTIONS(1),
    [sym__list_ws] = ACTIONS(1),
    [sym__adverb_tok] = ACTIONS(1),
    [sym__eos] = ACTIONS(1),
    [sym__error_sentinel] = ACTIONS(1),
  },
  [1] = {
    [sym_source_file] = STATE(107),
    [sym__statement] = STATE(44),
    [sym_assignment] = STATE(44),
    [sym_lambda] = STATE(36),
    [sym__expression] = STATE(36),
    [sym__literal_ref] = STATE(36),
    [sym_binary_expression] = STATE(36),
    [sym_call] = STATE(36),
    [sym_parenthesized] = STATE(36),
    [sym_list] = STATE(36),
    [sym_cond] = STATE(36),
    [sym_system_command] = STATE(44),
    [sym_namespace_directive] = STATE(44),
    [aux_sym_source_file_repeat1] = STATE(6),
    [ts_builtin_sym_end] = ACTIONS(5),
    [sym_identifier] = ACTIONS(7),
    [sym_number] = ACTIONS(9),
    [sym_string] = ACTIONS(9),
    [sym_symbol] = ACTIONS(11),
    [sym_dotted_name] = ACTIONS(13),
    [sym_builtin] = ACTIONS(15),
    [sym_symbol_vector] = ACTIONS(9),
    [anon_sym_LBRACE] = ACTIONS(17),
    [anon_sym_LPAREN] = ACTIONS(19),
    [anon_sym_DOLLAR] = ACTIONS(21),
    [anon_sym_BSLASHd] = ACTIONS(23),
    [sym_comment] = ACTIONS(3),
    [sym__system_command_tok] = ACTIONS(25),
  },
  [2] = {
    [sym__statement] = STATE(79),
    [sym_assignment] = STATE(79),
    [sym_lambda] = STATE(74),
    [sym__lambda_body] = STATE(108),
    [sym_parameters] = STATE(7),
    [sym__expression] = STATE(74),
    [sym__literal_ref] = STATE(74),
    [sym_binary_expression] = STATE(74),
    [sym_call] = STATE(74),
    [sym_parenthesized] = STATE(74),
    [sym_list] = STATE(74),
    [sym_cond] = STATE(74),
    [sym_system_command] = STATE(79),
    [sym_namespace_directive] = STATE(79),
    [sym_identifier] = ACTIONS(27),
    [sym_number] = ACTIONS(29),
    [sym_string] = ACTIONS(29),
    [sym_symbol] = ACTIONS(31),
    [sym_dotted_name] = ACTIONS(33),
    [sym_builtin] = ACTIONS(35),
    [sym_symbol_vector] = ACTIONS(29),
    [anon_sym_LBRACE] = ACTIONS(37),
    [anon_sym_RBRACE] = ACTIONS(39),
    [anon_sym_LBRACK] = ACTIONS(41),
    [anon_sym_LPAREN] = ACTIONS(43),
    [anon_sym_DOLLAR] = ACTIONS(45),
    [anon_sym_BSLASHd] = ACTIONS(47),
    [sym_comment] = ACTIONS(3),
    [sym__system_command_tok] = ACTIONS(49),
  },
  [3] = {
    [sym__statement] = STATE(79),
    [sym_assignment] = STATE(79),
    [sym_lambda] = STATE(74),
    [sym__lambda_body] = STATE(106),
    [sym_parameters] = STATE(8),
    [sym__expression] = STATE(74),
    [sym__literal_ref] = STATE(74),
    [sym_binary_expression] = STATE(74),
    [sym_call] = STATE(74),
    [sym_parenthesized] = STATE(74),
    [sym_list] = STATE(74),
    [sym_cond] = STATE(74),
    [sym_system_command] = STATE(79),
    [sym_namespace_directive] = STATE(79),
    [sym_identifier] = ACTIONS(27),
    [sym_number] = ACTIONS(29),
    [sym_string] = ACTIONS(29),
    [sym_symbol] = ACTIONS(31),
    [sym_dotted_name] = ACTIONS(33),
    [sym_builtin] = ACTIONS(35),
    [sym_symbol_vector] = ACTIONS(29),
    [anon_sym_LBRACE] = ACTIONS(37),
    [anon_sym_RBRACE] = ACTIONS(51),
    [anon_sym_LBRACK] = ACTIONS(41),
    [anon_sym_LPAREN] = ACTIONS(43),
    [anon_sym_DOLLAR] = ACTIONS(45),
    [anon_sym_BSLASHd] = ACTIONS(47),
    [sym_comment] = ACTIONS(3),
    [sym__system_command_tok] = ACTIONS(49),
  },
  [4] = {
    [sym_lambda] = STATE(37),
    [sym__expression] = STATE(37),
    [sym__literal_ref] = STATE(37),
    [sym_binary_expression] = STATE(37),
    [sym_call] = STATE(37),
    [sym_parenthesized] = STATE(37),
    [sym_list] = STATE(37),
    [sym_cond] = STATE(37),
    [ts_builtin_sym_end] = ACTIONS(53),
    [sym_identifier] = ACTIONS(55),
    [sym_number] = ACTIONS(57),
    [sym_string] = ACTIONS(57),
    [sym_symbol] = ACTIONS(59),
    [sym_dotted_name] = ACTIONS(15),
    [sym_builtin] = ACTIONS(15),
    [sym_symbol_vector] = ACTIONS(57),
    [anon_sym_COLON_COLON] = ACTIONS(61),
    [anon_sym_COLON] = ACTIONS(63),
    [anon_sym_LBRACE] = ACTIONS(17),
    [anon_sym_LBRACK] = ACTIONS(65),
    [sym_operator] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(19),
    [anon_sym_DOLLAR] = ACTIONS(21),
    [anon_sym_BSLASHd] = ACTIONS(53),
    [sym_comment] = ACTIONS(3),
    [sym__system_command_tok] = ACTIONS(53),
    [sym__eos] = ACTIONS(53),
  },
  [5] = {
    [sym__statement] = STATE(44),
    [sym_assignment] = STATE(44),
    [sym_lambda] = STATE(36),
    [sym__expression] = STATE(36),
    [sym__literal_ref] = STATE(36),
    [sym_binary_expression] = STATE(36),
    [sym_call] = STATE(36),
    [sym_parenthesized] = STATE(36),
    [sym_list] = STATE(36),
    [sym_cond] = STATE(36),
    [sym_system_command] = STATE(44),
    [sym_namespace_directive] = STATE(44),
    [aux_sym_source_file_repeat1] = STATE(5),
    [ts_builtin_sym_end] = ACTIONS(69),
    [sym_identifier] = ACTIONS(71),
    [sym_number] = ACTIONS(74),
    [sym_string] = ACTIONS(74),
    [sym_symbol] = ACTIONS(77),
    [sym_dotted_name] = ACTIONS(80),
    [sym_builtin] = ACTIONS(83),
    [sym_symbol_vector] = ACTIONS(74),
    [anon_sym_LBRACE] = ACTIONS(86),
    [anon_sym_LPAREN] = ACTIONS(89),
    [anon_sym_DOLLAR] = ACTIONS(92),
    [anon_sym_BSLASHd] = ACTIONS(95),
    [sym_comment] = ACTIONS(3),
    [sym__system_command_tok] = ACTIONS(98),
  },
  [6] = {
    [sym__statement] = STATE(44),
    [sym_assignment] = STATE(44),
    [sym_lambda] = STATE(36),
    [sym__expression] = STATE(36),
    [sym__literal_ref] = STATE(36),
    [sym_binary_expression] = STATE(36),
    [sym_call] = STATE(36),
    [sym_parenthesized] = STATE(36),
    [sym_list] = STATE(36),
    [sym_cond] = STATE(36),
    [sym_system_command] = STATE(44),
    [sym_namespace_directive] = STATE(44),
    [aux_sym_source_file_repeat1] = STATE(5),
    [ts_builtin_sym_end] = ACTIONS(101),
    [sym_identifier] = ACTIONS(7),
    [sym_number] = ACTIONS(9),
    [sym_string] = ACTIONS(9),
    [sym_symbol] = ACTIONS(11),
    [sym_dotted_name] = ACTIONS(13),
    [sym_builtin] = ACTIONS(15),
    [sym_symbol_vector] = ACTIONS(9),
    [anon_sym_LBRACE] = ACTIONS(17),
    [anon_sym_LPAREN] = ACTIONS(19),
    [anon_sym_DOLLAR] = ACTIONS(21),
    [anon_sym_BSLASHd] = ACTIONS(23),
    [sym_comment] = ACTIONS(3),
    [sym__system_command_tok] = ACTIONS(25),
  },
  [7] = {
    [sym__statement] = STATE(79),
    [sym_assignment] = STATE(79),
    [sym_lambda] = STATE(74),
    [sym__lambda_body] = STATE(104),
    [sym__expression] = STATE(74),
    [sym__literal_ref] = STATE(74),
    [sym_binary_expression] = STATE(74),
    [sym_call] = STATE(74),
    [sym_parenthesized] = STATE(74),
    [sym_list] = STATE(74),
    [sym_cond] = STATE(74),
    [sym_system_command] = STATE(79),
    [sym_namespace_directive] = STATE(79),
    [sym_identifier] = ACTIONS(27),
    [sym_number] = ACTIONS(29),
    [sym_string] = ACTIONS(29),
    [sym_symbol] = ACTIONS(31),
    [sym_dotted_name] = ACTIONS(33),
    [sym_builtin] = ACTIONS(35),
    [sym_symbol_vector] = ACTIONS(29),
    [anon_sym_LBRACE] = ACTIONS(37),
    [anon_sym_RBRACE] = ACTIONS(103),
    [anon_sym_LPAREN] = ACTIONS(43),
    [anon_sym_DOLLAR] = ACTIONS(45),
    [anon_sym_BSLASHd] = ACTIONS(47),
    [sym_comment] = ACTIONS(3),
    [sym__system_command_tok] = ACTIONS(49),
  },
  [8] = {
    [sym__statement] = STATE(79),
    [sym_assignment] = STATE(79),
    [sym_lambda] = STATE(74),
    [sym__lambda_body] = STATE(105),
    [sym__expression] = STATE(74),
    [sym__literal_ref] = STATE(74),
    [sym_binary_expression] = STATE(74),
    [sym_call] = STATE(74),
    [sym_parenthesized] = STATE(74),
    [sym_list] = STATE(74),
    [sym_cond] = STATE(74),
    [sym_system_command] = STATE(79),
    [sym_namespace_directive] = STATE(79),
    [sym_identifier] = ACTIONS(27),
    [sym_number] = ACTIONS(29),
    [sym_string] = ACTIONS(29),
    [sym_symbol] = ACTIONS(31),
    [sym_dotted_name] = ACTIONS(33),
    [sym_builtin] = ACTIONS(35),
    [sym_symbol_vector] = ACTIONS(29),
    [anon_sym_LBRACE] = ACTIONS(37),
    [anon_sym_RBRACE] = ACTIONS(105),
    [anon_sym_LPAREN] = ACTIONS(43),
    [anon_sym_DOLLAR] = ACTIONS(45),
    [anon_sym_BSLASHd] = ACTIONS(47),
    [sym_comment] = ACTIONS(3),
    [sym__system_command_tok] = ACTIONS(49),
  },
  [9] = {
    [sym__statement] = STATE(100),
    [sym_assignment] = STATE(100),
    [sym_lambda] = STATE(74),
    [sym__expression] = STATE(74),
    [sym__literal_ref] = STATE(74),
    [sym_binary_expression] = STATE(74),
    [sym_call] = STATE(74),
    [sym_parenthesized] = STATE(74),
    [sym_list] = STATE(74),
    [sym_cond] = STATE(74),
    [sym_system_command] = STATE(100),
    [sym_namespace_directive] = STATE(100),
    [sym_identifier] = ACTIONS(27),
    [sym_number] = ACTIONS(29),
    [sym_string] = ACTIONS(29),
    [sym_symbol] = ACTIONS(31),
    [sym_dotted_name] = ACTIONS(33),
    [sym_builtin] = ACTIONS(35),
    [sym_symbol_vector] = ACTIONS(29),
    [anon_sym_LBRACE] = ACTIONS(37),
    [anon_sym_LPAREN] = ACTIONS(43),
    [anon_sym_DOLLAR] = ACTIONS(45),
    [anon_sym_BSLASHd] = ACTIONS(47),
    [sym_comment] = ACTIONS(3),
    [sym__system_command_tok] = ACTIONS(49),
  },
  [10] = {
    [sym_lambda] = STATE(60),
    [sym__expression] = STATE(60),
    [sym__literal_ref] = STATE(60),
    [sym_binary_expression] = STATE(60),
    [sym_call] = STATE(60),
    [sym_parenthesized] = STATE(60),
    [sym_list] = STATE(60),
    [sym_cond] = STATE(60),
    [sym_identifier] = ACTIONS(107),
    [sym_number] = ACTIONS(109),
    [sym_string] = ACTIONS(109),
    [sym_symbol] = ACTIONS(111),
    [sym_dotted_name] = ACTIONS(35),
    [sym_builtin] = ACTIONS(35),
    [sym_symbol_vector] = ACTIONS(109),
    [anon_sym_COLON_COLON] = ACTIONS(113),
    [anon_sym_COLON] = ACTIONS(115),
    [anon_sym_LBRACE] = ACTIONS(37),
    [anon_sym_RBRACE] = ACTIONS(53),
    [anon_sym_SEMI] = ACTIONS(53),
    [anon_sym_LBRACK] = ACTIONS(117),
    [sym_operator] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(43),
    [anon_sym_DOLLAR] = ACTIONS(45),
    [sym_comment] = ACTIONS(3),
  },
  [11] = {
    [sym_lambda] = STATE(60),
    [sym__expression] = STATE(60),
    [sym__literal_ref] = STATE(60),
    [sym_binary_expression] = STATE(60),
    [sym_call] = STATE(60),
    [sym_parenthesized] = STATE(60),
    [sym_list] = STATE(60),
    [sym_cond] = STATE(60),
    [sym_identifier] = ACTIONS(107),
    [sym_number] = ACTIONS(109),
    [sym_string] = ACTIONS(109),
    [sym_symbol] = ACTIONS(111),
    [sym_dotted_name] = ACTIONS(35),
    [sym_builtin] = ACTIONS(35),
    [sym_symbol_vector] = ACTIONS(109),
    [anon_sym_LBRACE] = ACTIONS(37),
    [anon_sym_RBRACE] = ACTIONS(53),
    [anon_sym_SEMI] = ACTIONS(53),
    [anon_sym_LBRACK] = ACTIONS(117),
    [anon_sym_RBRACK] = ACTIONS(53),
    [sym_operator] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(43),
    [anon_sym_RPAREN] = ACTIONS(53),
    [anon_sym_DOLLAR] = ACTIONS(45),
    [sym_comment] = ACTIONS(3),
  },
  [12] = {
    [sym_lambda] = STATE(37),
    [sym__expression] = STATE(37),
    [sym__literal_ref] = STATE(37),
    [sym_binary_expression] = STATE(37),
    [sym_call] = STATE(37),
    [sym_parenthesized] = STATE(37),
    [sym_list] = STATE(37),
    [sym_cond] = STATE(37),
    [ts_builtin_sym_end] = ACTIONS(53),
    [sym_identifier] = ACTIONS(55),
    [sym_number] = ACTIONS(57),
    [sym_string] = ACTIONS(57),
    [sym_symbol] = ACTIONS(59),
    [sym_dotted_name] = ACTIONS(15),
    [sym_builtin] = ACTIONS(15),
    [sym_symbol_vector] = ACTIONS(57),
    [anon_sym_LBRACE] = ACTIONS(17),
    [anon_sym_LBRACK] = ACTIONS(65),
    [sym_operator] = ACTIONS(67),
    [anon_sym_LPAREN] = ACTIONS(19),
    [anon_sym_DOLLAR] = ACTIONS(21),
    [anon_sym_BSLASHd] = ACTIONS(53),
    [sym_comment] = ACTIONS(3),
    [sym__system_command_tok] = ACTIONS(53),
    [sym__eos] = ACTIONS(53),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(37), 1,
      anon_sym_LBRACE,
    ACTIONS(43), 1,
      anon_sym_LPAREN,
    ACTIONS(45), 1,
      anon_sym_DOLLAR,
    ACTIONS(107), 1,
      sym_identifier,
    ACTIONS(121), 1,
      sym_symbol,
    ACTIONS(123), 1,
      anon_sym_SEMI,
    ACTIONS(125), 1,
      anon_sym_RPAREN,
    STATE(81), 1,
      aux_sym_list_repeat1,
    ACTIONS(35), 2,
      sym_dotted_name,
      sym_builtin,
    ACTIONS(119), 3,
      sym_number,
      sym_string,
      sym_symbol_vector,
    STATE(69), 8,
      sym_lambda,
      sym__expression,
      sym__literal_ref,
      sym_binary_expression,
      sym_call,
      sym_parenthesized,
      sym_list,
      sym_cond,
  [47] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(37), 1,
      anon_sym_LBRACE,
    ACTIONS(43), 1,
      anon_sym_LPAREN,
    ACTIONS(45), 1,
      anon_sym_DOLLAR,
    ACTIONS(107), 1,
      sym_identifier,
    ACTIONS(123), 1,
      anon_sym_SEMI,
    ACTIONS(129), 1,
      sym_symbol,
    ACTIONS(131), 1,
      anon_sym_RPAREN,
    STATE(92), 1,
      aux_sym_list_repeat1,
    ACTIONS(35), 2,
      sym_dotted_name,
      sym_builtin,
    ACTIONS(127), 3,
      sym_number,
      sym_string,
      sym_symbol_vector,
    STATE(71), 8,
      sym_lambda,
      sym__expression,
      sym__literal_ref,
      sym_binary_expression,
      sym_call,
      sym_parenthesized,
      sym_list,
      sym_cond,
  [94] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(37), 1,
      anon_sym_LBRACE,
    ACTIONS(43), 1,
      anon_sym_LPAREN,
    ACTIONS(45), 1,
      anon_sym_DOLLAR,
    ACTIONS(107), 1,
      sym_identifier,
    ACTIONS(135), 1,
      sym_symbol,
    ACTIONS(35), 2,
      sym_dotted_name,
      sym_builtin,
    ACTIONS(137), 2,
      anon_sym_SEMI,
      anon_sym_RPAREN,
    ACTIONS(133), 3,
      sym_number,
      sym_string,
      sym_symbol_vector,
    STATE(86), 8,
      sym_lambda,
      sym__expression,
      sym__literal_ref,
      sym_binary_expression,
      sym_call,
      sym_parenthesized,
      sym_list,
      sym_cond,
  [136] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(37), 1,
      anon_sym_LBRACE,
    ACTIONS(43), 1,
      anon_sym_LPAREN,
    ACTIONS(45), 1,
      anon_sym_DOLLAR,
    ACTIONS(107), 1,
      sym_identifier,
    ACTIONS(141), 1,
      sym_symbol,
    ACTIONS(143), 1,
      anon_sym_RBRACK,
    ACTIONS(35), 2,
      sym_dotted_name,
      sym_builtin,
    ACTIONS(139), 3,
      sym_number,
      sym_string,
      sym_symbol_vector,
    STATE(72), 8,
      sym_lambda,
      sym__expression,
      sym__literal_ref,
      sym_binary_expression,
      sym_call,
      sym_parenthesized,
      sym_list,
      sym_cond,
  [177] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(37), 1,
      anon_sym_LBRACE,
    ACTIONS(43), 1,
      anon_sym_LPAREN,
    ACTIONS(45), 1,
      anon_sym_DOLLAR,
    ACTIONS(107), 1,
      sym_identifier,
    ACTIONS(147), 1,
      sym_symbol,
    ACTIONS(149), 1,
      anon_sym_RBRACK,
    ACTIONS(35), 2,
      sym_dotted_name,
      sym_builtin,
    ACTIONS(145), 3,
      sym_number,
      sym_string,
      sym_symbol_vector,
    STATE(67), 8,
      sym_lambda,
      sym__expression,
      sym__literal_ref,
      sym_binary_expression,
      sym_call,
      sym_parenthesized,
      sym_list,
      sym_cond,
  [218] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(37), 1,
      anon_sym_LBRACE,
    ACTIONS(43), 1,
      anon_sym_LPAREN,
    ACTIONS(45), 1,
      anon_sym_DOLLAR,
    ACTIONS(107), 1,
      sym_identifier,
    ACTIONS(153), 1,
      sym_symbol,
    ACTIONS(35), 2,
      sym_dotted_name,
      sym_builtin,
    ACTIONS(151), 3,
      sym_number,
      sym_string,
      sym_symbol_vector,
    STATE(84), 8,
      sym_lambda,
      sym__expression,
      sym__literal_ref,
      sym_binary_expression,
      sym_call,
      sym_parenthesized,
      sym_list,
      sym_cond,
  [256] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(37), 1,
      anon_sym_LBRACE,
    ACTIONS(43), 1,
      anon_sym_LPAREN,
    ACTIONS(45), 1,
      anon_sym_DOLLAR,
    ACTIONS(107), 1,
      sym_identifier,
    ACTIONS(157), 1,
      sym_symbol,
    ACTIONS(35), 2,
      sym_dotted_name,
      sym_builtin,
    ACTIONS(155), 3,
      sym_number,
      sym_string,
      sym_symbol_vector,
    STATE(68), 8,
      sym_lambda,
      sym__expression,
      sym__literal_ref,
      sym_binary_expression,
      sym_call,
      sym_parenthesized,
      sym_list,
      sym_cond,
  [294] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(19), 1,
      anon_sym_LPAREN,
    ACTIONS(21), 1,
      anon_sym_DOLLAR,
    ACTIONS(55), 1,
      sym_identifier,
    ACTIONS(161), 1,
      sym_symbol,
    ACTIONS(15), 2,
      sym_dotted_name,
      sym_builtin,
    ACTIONS(159), 3,
      sym_number,
      sym_string,
      sym_symbol_vector,
    STATE(39), 8,
      sym_lambda,
      sym__expression,
      sym__literal_ref,
      sym_binary_expression,
      sym_call,
      sym_parenthesized,
      sym_list,
      sym_cond,
  [332] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(17), 1,
      anon_sym_LBRACE,
    ACTIONS(19), 1,
      anon_sym_LPAREN,
    ACTIONS(21), 1,
      anon_sym_DOLLAR,
    ACTIONS(55), 1,
      sym_identifier,
    ACTIONS(165), 1,
      sym_symbol,
    ACTIONS(15), 2,
      sym_dotted_name,
      sym_builtin,
    ACTIONS(163), 3,
      sym_number,
      sym_string,
      sym_symbol_vector,
    STATE(35), 8,
      sym_lambda,
      sym__expression,
      sym__literal_ref,
      sym_binary_expression,
      sym_call,
      sym_parenthesized,
      sym_list,
      sym_cond,
  [370] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(37), 1,
      anon_sym_LBRACE,
    ACTIONS(43), 1,
      anon_sym_LPAREN,
    ACTIONS(45), 1,
      anon_sym_DOLLAR,
    ACTIONS(107), 1,
      sym_identifier,
    ACTIONS(169), 1,
      sym_symbol,
    ACTIONS(35), 2,
      sym_dotted_name,
      sym_builtin,
    ACTIONS(167), 3,
      sym_number,
      sym_string,
      sym_symbol_vector,
    STATE(73), 8,
      sym_lambda,
      sym__expression,
      sym__literal_ref,
      sym_binary_expression,
      sym_call,
      sym_parenthesized,
      sym_list,
      sym_cond,
  [408] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(37), 1,
      anon_sym_LBRACE,
    ACTIONS(43), 1,
      anon_sym_LPAREN,
    ACTIONS(45), 1,
      anon_sym_DOLLAR,
    ACTIONS(107), 1,
      sym_identifier,
    ACTIONS(173), 1,
      sym_symbol,
    ACTIONS(35), 2,
      sym_dotted_name,
      sym_builtin,
    ACTIONS(171), 3,
      sym_number,
      sym_string,
      sym_symbol_vector,
    STATE(77), 8,
      sym_lambda,
      sym__expression,
      sym__literal_ref,
      sym_binary_expression,
      sym_call,
      sym_parenthesized,
      sym_list,
      sym_cond,
  [446] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(37), 1,
      anon_sym_LBRACE,
    ACTIONS(43), 1,
      anon_sym_LPAREN,
    ACTIONS(45), 1,
      anon_sym_DOLLAR,
    ACTIONS(107), 1,
      sym_identifier,
    ACTIONS(177), 1,
      sym_symbol,
    ACTIONS(35), 2,
      sym_dotted_name,
      sym_builtin,
    ACTIONS(175), 3,
      sym_number,
      sym_string,
      sym_symbol_vector,
    STATE(65), 8,
      sym_lambda,
      sym__expression,
      sym__literal_ref,
      sym_binary_expression,
      sym_call,
      sym_parenthesized,
      sym_list,
      sym_cond,
  [484] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(37), 1,
      anon_sym_LBRACE,
    ACTIONS(43), 1,
      anon_sym_LPAREN,
    ACTIONS(45), 1,
      anon_sym_DOLLAR,
    ACTIONS(107), 1,
      sym_identifier,
    ACTIONS(181), 1,
      sym_symbol,
    ACTIONS(35), 2,
      sym_dotted_name,
      sym_builtin,
    ACTIONS(179), 3,
      sym_number,
      sym_string,
      sym_symbol_vector,
    STATE(87), 8,
      sym_lambda,
      sym__expression,
      sym__literal_ref,
      sym_binary_expression,
      sym_call,
      sym_parenthesized,
      sym_list,
      sym_cond,
  [522] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(37), 1,
      anon_sym_LBRACE,
    ACTIONS(43), 1,
      anon_sym_LPAREN,
    ACTIONS(45), 1,
      anon_sym_DOLLAR,
    ACTIONS(107), 1,
      sym_identifier,
    ACTIONS(185), 1,
      sym_symbol,
    ACTIONS(35), 2,
      sym_dotted_name,
      sym_builtin,
    ACTIONS(183), 3,
      sym_number,
      sym_string,
      sym_symbol_vector,
    STATE(70), 8,
      sym_lambda,
      sym__expression,
      sym__literal_ref,
      sym_binary_expression,
      sym_call,
      sym_parenthesized,
      sym_list,
      sym_cond,
  [560] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(189), 3,
      sym_symbol,
      sym_identifier,
      sym_operator,
    ACTIONS(187), 12,
      sym__system_command_tok,
      sym__eos,
      ts_builtin_sym_end,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [583] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(193), 3,
      sym_symbol,
      sym_identifier,
      sym_operator,
    ACTIONS(191), 12,
      sym__system_command_tok,
      sym__eos,
      ts_builtin_sym_end,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [606] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(197), 3,
      sym_symbol,
      sym_identifier,
      sym_operator,
    ACTIONS(195), 12,
      sym__system_command_tok,
      sym__eos,
      ts_builtin_sym_end,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [629] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(201), 3,
      sym_symbol,
      sym_identifier,
      sym_operator,
    ACTIONS(199), 12,
      sym__system_command_tok,
      sym__eos,
      ts_builtin_sym_end,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [652] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(205), 3,
      sym_symbol,
      sym_identifier,
      sym_operator,
    ACTIONS(203), 12,
      sym__system_command_tok,
      sym__eos,
      ts_builtin_sym_end,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [675] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(209), 3,
      sym_symbol,
      sym_identifier,
      sym_operator,
    ACTIONS(207), 12,
      sym__system_command_tok,
      sym__eos,
      ts_builtin_sym_end,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [698] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(213), 3,
      sym_symbol,
      sym_identifier,
      sym_operator,
    ACTIONS(211), 12,
      sym__system_command_tok,
      sym__eos,
      ts_builtin_sym_end,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [721] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(217), 3,
      sym_symbol,
      sym_identifier,
      sym_operator,
    ACTIONS(215), 12,
      sym__system_command_tok,
      sym__eos,
      ts_builtin_sym_end,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [744] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(223), 1,
      sym_operator,
    ACTIONS(221), 2,
      sym_symbol,
      sym_identifier,
    ACTIONS(219), 12,
      sym__system_command_tok,
      sym__eos,
      ts_builtin_sym_end,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [769] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(223), 1,
      sym_operator,
    ACTIONS(227), 2,
      sym_symbol,
      sym_identifier,
    ACTIONS(225), 12,
      sym__system_command_tok,
      sym__eos,
      ts_builtin_sym_end,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [794] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(231), 3,
      sym_symbol,
      sym_identifier,
      sym_operator,
    ACTIONS(229), 12,
      sym__system_command_tok,
      sym__eos,
      ts_builtin_sym_end,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [817] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(235), 3,
      sym_symbol,
      sym_identifier,
      sym_operator,
    ACTIONS(233), 12,
      sym__system_command_tok,
      sym__eos,
      ts_builtin_sym_end,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [840] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(239), 3,
      sym_symbol,
      sym_identifier,
      sym_operator,
    ACTIONS(237), 12,
      sym__system_command_tok,
      sym__eos,
      ts_builtin_sym_end,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [863] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(243), 3,
      sym_symbol,
      sym_identifier,
      sym_operator,
    ACTIONS(241), 12,
      sym__system_command_tok,
      sym__eos,
      ts_builtin_sym_end,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [886] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(247), 3,
      sym_symbol,
      sym_identifier,
      sym_operator,
    ACTIONS(245), 12,
      sym__system_command_tok,
      sym__eos,
      ts_builtin_sym_end,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [909] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(251), 3,
      sym_symbol,
      sym_identifier,
      sym_operator,
    ACTIONS(249), 12,
      sym__system_command_tok,
      sym__eos,
      ts_builtin_sym_end,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [932] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(255), 3,
      sym_symbol,
      sym_identifier,
      sym_operator,
    ACTIONS(253), 12,
      sym__system_command_tok,
      sym__eos,
      ts_builtin_sym_end,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [955] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(261), 1,
      sym__eos,
    ACTIONS(259), 2,
      sym_symbol,
      sym_identifier,
    ACTIONS(257), 11,
      sym__system_command_tok,
      ts_builtin_sym_end,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [979] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(265), 2,
      sym_symbol,
      sym_identifier,
    ACTIONS(263), 12,
      sym__system_command_tok,
      sym__eos,
      ts_builtin_sym_end,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [1001] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(269), 2,
      sym_symbol,
      sym_identifier,
    ACTIONS(267), 12,
      sym__system_command_tok,
      sym__eos,
      ts_builtin_sym_end,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [1023] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(275), 1,
      sym_dotted_name,
    ACTIONS(273), 2,
      sym_symbol,
      sym_identifier,
    ACTIONS(271), 11,
      sym__system_command_tok,
      sym__eos,
      ts_builtin_sym_end,
      sym_number,
      sym_string,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [1047] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(277), 2,
      sym_symbol,
      sym_identifier,
    ACTIONS(279), 11,
      sym__system_command_tok,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [1068] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(281), 2,
      sym_symbol,
      sym_identifier,
    ACTIONS(283), 11,
      sym__system_command_tok,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [1089] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(285), 2,
      sym_symbol,
      sym_identifier,
    ACTIONS(287), 11,
      sym__system_command_tok,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [1110] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(289), 2,
      sym_symbol,
      sym_identifier,
    ACTIONS(69), 11,
      sym__system_command_tok,
      ts_builtin_sym_end,
      sym_number,
      sym_string,
      sym_dotted_name,
      sym_builtin,
      sym_symbol_vector,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [1131] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(203), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1142] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(191), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1153] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(199), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1164] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(207), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1175] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(245), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1186] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(211), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1197] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(187), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1208] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(215), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1219] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(229), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1230] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(241), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1241] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(233), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1252] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(249), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1263] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(253), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1274] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(237), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1285] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(195), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1296] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(291), 1,
      anon_sym_SEMI,
    ACTIONS(293), 1,
      anon_sym_RBRACK,
    ACTIONS(295), 1,
      sym_operator,
    STATE(90), 1,
      aux_sym_call_repeat1,
  [1312] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(291), 1,
      anon_sym_SEMI,
    ACTIONS(295), 1,
      sym_operator,
    ACTIONS(297), 1,
      anon_sym_RBRACK,
    STATE(82), 1,
      aux_sym_call_repeat1,
  [1328] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(123), 1,
      anon_sym_SEMI,
    ACTIONS(295), 1,
      sym_operator,
    ACTIONS(299), 1,
      anon_sym_RPAREN,
    STATE(88), 1,
      aux_sym_list_repeat1,
  [1344] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(291), 1,
      anon_sym_SEMI,
    ACTIONS(295), 1,
      sym_operator,
    ACTIONS(301), 1,
      anon_sym_RBRACK,
    STATE(93), 1,
      aux_sym_call_repeat1,
  [1360] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(123), 1,
      anon_sym_SEMI,
    ACTIONS(295), 1,
      sym_operator,
    ACTIONS(303), 1,
      anon_sym_RPAREN,
    STATE(94), 1,
      aux_sym_list_repeat1,
  [1376] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(291), 1,
      anon_sym_SEMI,
    ACTIONS(295), 1,
      sym_operator,
    ACTIONS(305), 1,
      anon_sym_RBRACK,
    STATE(96), 1,
      aux_sym_call_repeat1,
  [1392] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(295), 1,
      sym_operator,
    ACTIONS(307), 2,
      anon_sym_SEMI,
      anon_sym_RBRACK,
  [1403] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(295), 1,
      sym_operator,
    ACTIONS(225), 2,
      anon_sym_RBRACE,
      anon_sym_SEMI,
  [1414] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(309), 1,
      anon_sym_SEMI,
    ACTIONS(311), 1,
      anon_sym_RBRACK,
    STATE(76), 1,
      aux_sym_parameters_repeat1,
  [1427] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(309), 1,
      anon_sym_SEMI,
    ACTIONS(313), 1,
      anon_sym_RBRACK,
    STATE(85), 1,
      aux_sym_parameters_repeat1,
  [1440] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(295), 1,
      sym_operator,
    ACTIONS(219), 2,
      anon_sym_RBRACE,
      anon_sym_SEMI,
  [1451] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(315), 1,
      anon_sym_RBRACE,
    ACTIONS(317), 1,
      anon_sym_SEMI,
    STATE(78), 1,
      aux_sym__lambda_body_repeat1,
  [1464] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(320), 1,
      anon_sym_RBRACE,
    ACTIONS(322), 1,
      anon_sym_SEMI,
    STATE(80), 1,
      aux_sym__lambda_body_repeat1,
  [1477] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(322), 1,
      anon_sym_SEMI,
    ACTIONS(324), 1,
      anon_sym_RBRACE,
    STATE(78), 1,
      aux_sym__lambda_body_repeat1,
  [1490] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(123), 1,
      anon_sym_SEMI,
    ACTIONS(299), 1,
      anon_sym_RPAREN,
    STATE(95), 1,
      aux_sym_list_repeat1,
  [1503] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(291), 1,
      anon_sym_SEMI,
    ACTIONS(326), 1,
      anon_sym_RBRACK,
    STATE(83), 1,
      aux_sym_call_repeat1,
  [1516] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(307), 1,
      anon_sym_RBRACK,
    ACTIONS(328), 1,
      anon_sym_SEMI,
    STATE(83), 1,
      aux_sym_call_repeat1,
  [1529] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(295), 1,
      sym_operator,
    ACTIONS(331), 1,
      anon_sym_SEMI,
    ACTIONS(333), 1,
      anon_sym_RPAREN,
  [1542] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(335), 1,
      anon_sym_SEMI,
    ACTIONS(338), 1,
      anon_sym_RBRACK,
    STATE(85), 1,
      aux_sym_parameters_repeat1,
  [1555] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(295), 1,
      sym_operator,
    ACTIONS(340), 2,
      anon_sym_SEMI,
      anon_sym_RPAREN,
  [1566] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(295), 1,
      sym_operator,
    ACTIONS(342), 1,
      anon_sym_SEMI,
    ACTIONS(344), 1,
      anon_sym_RPAREN,
  [1579] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(123), 1,
      anon_sym_SEMI,
    ACTIONS(346), 1,
      anon_sym_RPAREN,
    STATE(95), 1,
      aux_sym_list_repeat1,
  [1592] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(348), 1,
      sym_identifier,
    ACTIONS(350), 1,
      anon_sym_RBRACK,
    STATE(75), 1,
      sym_param,
  [1605] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(291), 1,
      anon_sym_SEMI,
    ACTIONS(352), 1,
      anon_sym_RBRACK,
    STATE(83), 1,
      aux_sym_call_repeat1,
  [1618] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(354), 1,
      sym_dotted_name,
    ACTIONS(271), 2,
      anon_sym_RBRACE,
      anon_sym_SEMI,
  [1629] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(123), 1,
      anon_sym_SEMI,
    ACTIONS(303), 1,
      anon_sym_RPAREN,
    STATE(95), 1,
      aux_sym_list_repeat1,
  [1642] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(291), 1,
      anon_sym_SEMI,
    ACTIONS(356), 1,
      anon_sym_RBRACK,
    STATE(83), 1,
      aux_sym_call_repeat1,
  [1655] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(123), 1,
      anon_sym_SEMI,
    ACTIONS(358), 1,
      anon_sym_RPAREN,
    STATE(95), 1,
      aux_sym_list_repeat1,
  [1668] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(340), 1,
      anon_sym_RPAREN,
    ACTIONS(360), 1,
      anon_sym_SEMI,
    STATE(95), 1,
      aux_sym_list_repeat1,
  [1681] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(291), 1,
      anon_sym_SEMI,
    ACTIONS(363), 1,
      anon_sym_RBRACK,
    STATE(83), 1,
      aux_sym_call_repeat1,
  [1694] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(348), 1,
      sym_identifier,
    STATE(98), 1,
      sym_param,
  [1704] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(365), 2,
      anon_sym_SEMI,
      anon_sym_RBRACK,
  [1712] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(267), 2,
      anon_sym_RBRACE,
      anon_sym_SEMI,
  [1720] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(315), 2,
      anon_sym_RBRACE,
      anon_sym_SEMI,
  [1728] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(367), 2,
      anon_sym_SEMI,
      anon_sym_RBRACK,
  [1736] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(263), 2,
      anon_sym_RBRACE,
      anon_sym_SEMI,
  [1744] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(369), 1,
      anon_sym_LBRACK,
  [1751] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(371), 1,
      anon_sym_RBRACE,
  [1758] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(373), 1,
      anon_sym_RBRACE,
  [1765] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(375), 1,
      anon_sym_RBRACE,
  [1772] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(377), 1,
      ts_builtin_sym_end,
  [1779] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(379), 1,
      anon_sym_RBRACE,
  [1786] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(381), 1,
      anon_sym_LBRACK,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(13)] = 0,
  [SMALL_STATE(14)] = 47,
  [SMALL_STATE(15)] = 94,
  [SMALL_STATE(16)] = 136,
  [SMALL_STATE(17)] = 177,
  [SMALL_STATE(18)] = 218,
  [SMALL_STATE(19)] = 256,
  [SMALL_STATE(20)] = 294,
  [SMALL_STATE(21)] = 332,
  [SMALL_STATE(22)] = 370,
  [SMALL_STATE(23)] = 408,
  [SMALL_STATE(24)] = 446,
  [SMALL_STATE(25)] = 484,
  [SMALL_STATE(26)] = 522,
  [SMALL_STATE(27)] = 560,
  [SMALL_STATE(28)] = 583,
  [SMALL_STATE(29)] = 606,
  [SMALL_STATE(30)] = 629,
  [SMALL_STATE(31)] = 652,
  [SMALL_STATE(32)] = 675,
  [SMALL_STATE(33)] = 698,
  [SMALL_STATE(34)] = 721,
  [SMALL_STATE(35)] = 744,
  [SMALL_STATE(36)] = 769,
  [SMALL_STATE(37)] = 794,
  [SMALL_STATE(38)] = 817,
  [SMALL_STATE(39)] = 840,
  [SMALL_STATE(40)] = 863,
  [SMALL_STATE(41)] = 886,
  [SMALL_STATE(42)] = 909,
  [SMALL_STATE(43)] = 932,
  [SMALL_STATE(44)] = 955,
  [SMALL_STATE(45)] = 979,
  [SMALL_STATE(46)] = 1001,
  [SMALL_STATE(47)] = 1023,
  [SMALL_STATE(48)] = 1047,
  [SMALL_STATE(49)] = 1068,
  [SMALL_STATE(50)] = 1089,
  [SMALL_STATE(51)] = 1110,
  [SMALL_STATE(52)] = 1131,
  [SMALL_STATE(53)] = 1142,
  [SMALL_STATE(54)] = 1153,
  [SMALL_STATE(55)] = 1164,
  [SMALL_STATE(56)] = 1175,
  [SMALL_STATE(57)] = 1186,
  [SMALL_STATE(58)] = 1197,
  [SMALL_STATE(59)] = 1208,
  [SMALL_STATE(60)] = 1219,
  [SMALL_STATE(61)] = 1230,
  [SMALL_STATE(62)] = 1241,
  [SMALL_STATE(63)] = 1252,
  [SMALL_STATE(64)] = 1263,
  [SMALL_STATE(65)] = 1274,
  [SMALL_STATE(66)] = 1285,
  [SMALL_STATE(67)] = 1296,
  [SMALL_STATE(68)] = 1312,
  [SMALL_STATE(69)] = 1328,
  [SMALL_STATE(70)] = 1344,
  [SMALL_STATE(71)] = 1360,
  [SMALL_STATE(72)] = 1376,
  [SMALL_STATE(73)] = 1392,
  [SMALL_STATE(74)] = 1403,
  [SMALL_STATE(75)] = 1414,
  [SMALL_STATE(76)] = 1427,
  [SMALL_STATE(77)] = 1440,
  [SMALL_STATE(78)] = 1451,
  [SMALL_STATE(79)] = 1464,
  [SMALL_STATE(80)] = 1477,
  [SMALL_STATE(81)] = 1490,
  [SMALL_STATE(82)] = 1503,
  [SMALL_STATE(83)] = 1516,
  [SMALL_STATE(84)] = 1529,
  [SMALL_STATE(85)] = 1542,
  [SMALL_STATE(86)] = 1555,
  [SMALL_STATE(87)] = 1566,
  [SMALL_STATE(88)] = 1579,
  [SMALL_STATE(89)] = 1592,
  [SMALL_STATE(90)] = 1605,
  [SMALL_STATE(91)] = 1618,
  [SMALL_STATE(92)] = 1629,
  [SMALL_STATE(93)] = 1642,
  [SMALL_STATE(94)] = 1655,
  [SMALL_STATE(95)] = 1668,
  [SMALL_STATE(96)] = 1681,
  [SMALL_STATE(97)] = 1694,
  [SMALL_STATE(98)] = 1704,
  [SMALL_STATE(99)] = 1712,
  [SMALL_STATE(100)] = 1720,
  [SMALL_STATE(101)] = 1728,
  [SMALL_STATE(102)] = 1736,
  [SMALL_STATE(103)] = 1744,
  [SMALL_STATE(104)] = 1751,
  [SMALL_STATE(105)] = 1758,
  [SMALL_STATE(106)] = 1765,
  [SMALL_STATE(107)] = 1772,
  [SMALL_STATE(108)] = 1779,
  [SMALL_STATE(109)] = 1786,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0, 0, 0),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(4),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [11] = {.entry = {.count = 1, .reusable = false}}, SHIFT(36),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(103),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [27] = {.entry = {.count = 1, .reusable = false}}, SHIFT(10),
  [29] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [31] = {.entry = {.count = 1, .reusable = false}}, SHIFT(74),
  [33] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [35] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [37] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [39] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [41] = {.entry = {.count = 1, .reusable = true}}, SHIFT(89),
  [43] = {.entry = {.count = 1, .reusable = true}}, SHIFT(25),
  [45] = {.entry = {.count = 1, .reusable = true}}, SHIFT(109),
  [47] = {.entry = {.count = 1, .reusable = true}}, SHIFT(91),
  [49] = {.entry = {.count = 1, .reusable = true}}, SHIFT(99),
  [51] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [53] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__literal_ref, 1, 0, 0),
  [55] = {.entry = {.count = 1, .reusable = false}}, SHIFT(12),
  [57] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [59] = {.entry = {.count = 1, .reusable = false}}, SHIFT(37),
  [61] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [63] = {.entry = {.count = 1, .reusable = false}}, SHIFT(21),
  [65] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [67] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__literal_ref, 1, 0, 0),
  [69] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0),
  [71] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(4),
  [74] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(36),
  [77] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(36),
  [80] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(4),
  [83] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(12),
  [86] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(2),
  [89] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(18),
  [92] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(103),
  [95] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(47),
  [98] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(46),
  [101] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
  [103] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [105] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [107] = {.entry = {.count = 1, .reusable = false}}, SHIFT(11),
  [109] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [111] = {.entry = {.count = 1, .reusable = false}}, SHIFT(60),
  [113] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [115] = {.entry = {.count = 1, .reusable = false}}, SHIFT(23),
  [117] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [119] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [121] = {.entry = {.count = 1, .reusable = false}}, SHIFT(69),
  [123] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [125] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [127] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [129] = {.entry = {.count = 1, .reusable = false}}, SHIFT(71),
  [131] = {.entry = {.count = 1, .reusable = true}}, SHIFT(54),
  [133] = {.entry = {.count = 1, .reusable = true}}, SHIFT(86),
  [135] = {.entry = {.count = 1, .reusable = false}}, SHIFT(86),
  [137] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_list_repeat1, 1, 0, 0),
  [139] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [141] = {.entry = {.count = 1, .reusable = false}}, SHIFT(72),
  [143] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [145] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [147] = {.entry = {.count = 1, .reusable = false}}, SHIFT(67),
  [149] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [151] = {.entry = {.count = 1, .reusable = true}}, SHIFT(84),
  [153] = {.entry = {.count = 1, .reusable = false}}, SHIFT(84),
  [155] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [157] = {.entry = {.count = 1, .reusable = false}}, SHIFT(68),
  [159] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [161] = {.entry = {.count = 1, .reusable = false}}, SHIFT(39),
  [163] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [165] = {.entry = {.count = 1, .reusable = false}}, SHIFT(35),
  [167] = {.entry = {.count = 1, .reusable = true}}, SHIFT(73),
  [169] = {.entry = {.count = 1, .reusable = false}}, SHIFT(73),
  [171] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [173] = {.entry = {.count = 1, .reusable = false}}, SHIFT(77),
  [175] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [177] = {.entry = {.count = 1, .reusable = false}}, SHIFT(65),
  [179] = {.entry = {.count = 1, .reusable = true}}, SHIFT(87),
  [181] = {.entry = {.count = 1, .reusable = false}}, SHIFT(87),
  [183] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [185] = {.entry = {.count = 1, .reusable = false}}, SHIFT(70),
  [187] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cond, 5, 0, 0),
  [189] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cond, 5, 0, 0),
  [191] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_lambda, 4, 0, 10),
  [193] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_lambda, 4, 0, 10),
  [195] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call, 4, 0, 8),
  [197] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_call, 4, 0, 8),
  [199] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list, 4, 0, 0),
  [201] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_list, 4, 0, 0),
  [203] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call, 5, 0, 11),
  [205] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_call, 5, 0, 11),
  [207] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cond, 4, 0, 0),
  [209] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cond, 4, 0, 0),
  [211] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list, 5, 0, 0),
  [213] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_list, 5, 0, 0),
  [215] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list, 6, 0, 0),
  [217] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_list, 6, 0, 0),
  [219] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_assignment, 3, 0, 4),
  [221] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_assignment, 3, 0, 4),
  [223] = {.entry = {.count = 1, .reusable = false}}, SHIFT(20),
  [225] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__statement, 1, 0, 0),
  [227] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__statement, 1, 0, 0),
  [229] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call, 2, 0, 2),
  [231] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_call, 2, 0, 2),
  [233] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_lambda, 3, 0, 6),
  [235] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_lambda, 3, 0, 6),
  [237] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binary_expression, 3, 0, 4),
  [239] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_binary_expression, 3, 0, 4),
  [241] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call, 3, 0, 5),
  [243] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_call, 3, 0, 5),
  [245] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_lambda, 2, 0, 0),
  [247] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_lambda, 2, 0, 0),
  [249] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_lambda, 3, 0, 7),
  [251] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_lambda, 3, 0, 7),
  [253] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parenthesized, 3, 0, 0),
  [255] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_parenthesized, 3, 0, 0),
  [257] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 1, 0, 0),
  [259] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 1, 0, 0),
  [261] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [263] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_namespace_directive, 2, 0, 3),
  [265] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_namespace_directive, 2, 0, 3),
  [267] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_system_command, 1, 0, 1),
  [269] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_system_command, 1, 0, 1),
  [271] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_namespace_directive, 1, 0, 0),
  [273] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_namespace_directive, 1, 0, 0),
  [275] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [277] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_parameters, 3, 0, 9),
  [279] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameters, 3, 0, 9),
  [281] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_parameters, 4, 0, 12),
  [283] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameters, 4, 0, 12),
  [285] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_parameters, 2, 0, 0),
  [287] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameters, 2, 0, 0),
  [289] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0),
  [291] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [293] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [295] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [297] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [299] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [301] = {.entry = {.count = 1, .reusable = true}}, SHIFT(55),
  [303] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [305] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [307] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_call_repeat1, 2, 0, 0),
  [309] = {.entry = {.count = 1, .reusable = true}}, SHIFT(97),
  [311] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [313] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [315] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__lambda_body_repeat1, 2, 0, 0),
  [317] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__lambda_body_repeat1, 2, 0, 0), SHIFT_REPEAT(9),
  [320] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__lambda_body, 1, 0, 0),
  [322] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [324] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__lambda_body, 2, 0, 0),
  [326] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [328] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_call_repeat1, 2, 0, 0), SHIFT_REPEAT(22),
  [331] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [333] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [335] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_parameters_repeat1, 2, 0, 13), SHIFT_REPEAT(97),
  [338] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_parameters_repeat1, 2, 0, 13),
  [340] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_list_repeat1, 2, 0, 0),
  [342] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [344] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [346] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [348] = {.entry = {.count = 1, .reusable = true}}, SHIFT(101),
  [350] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [352] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [354] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [356] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [358] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [360] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_list_repeat1, 2, 0, 0), SHIFT_REPEAT(15),
  [363] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [365] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_parameters_repeat1, 2, 0, 9),
  [367] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_param, 1, 0, 0),
  [369] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [371] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [373] = {.entry = {.count = 1, .reusable = true}}, SHIFT(53),
  [375] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [377] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [379] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [381] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
};

enum ts_external_scanner_symbol_identifiers {
  ts_external_token_comment = 0,
  ts_external_token__system_command_tok = 1,
  ts_external_token__neg_number = 2,
  ts_external_token__list_ws = 3,
  ts_external_token__adverb_tok = 4,
  ts_external_token__eos = 5,
  ts_external_token__error_sentinel = 6,
};

static const TSSymbol ts_external_scanner_symbol_map[EXTERNAL_TOKEN_COUNT] = {
  [ts_external_token_comment] = sym_comment,
  [ts_external_token__system_command_tok] = sym__system_command_tok,
  [ts_external_token__neg_number] = sym__neg_number,
  [ts_external_token__list_ws] = sym__list_ws,
  [ts_external_token__adverb_tok] = sym__adverb_tok,
  [ts_external_token__eos] = sym__eos,
  [ts_external_token__error_sentinel] = sym__error_sentinel,
};

static const bool ts_external_scanner_states[5][EXTERNAL_TOKEN_COUNT] = {
  [1] = {
    [ts_external_token_comment] = true,
    [ts_external_token__system_command_tok] = true,
    [ts_external_token__neg_number] = true,
    [ts_external_token__list_ws] = true,
    [ts_external_token__adverb_tok] = true,
    [ts_external_token__eos] = true,
    [ts_external_token__error_sentinel] = true,
  },
  [2] = {
    [ts_external_token_comment] = true,
    [ts_external_token__system_command_tok] = true,
  },
  [3] = {
    [ts_external_token_comment] = true,
    [ts_external_token__system_command_tok] = true,
    [ts_external_token__eos] = true,
  },
  [4] = {
    [ts_external_token_comment] = true,
  },
};

#ifdef __cplusplus
extern "C" {
#endif
void *tree_sitter_q_external_scanner_create(void);
void tree_sitter_q_external_scanner_destroy(void *);
bool tree_sitter_q_external_scanner_scan(void *, TSLexer *, const bool *);
unsigned tree_sitter_q_external_scanner_serialize(void *, char *);
void tree_sitter_q_external_scanner_deserialize(void *, const char *, unsigned);

#ifdef TREE_SITTER_HIDE_SYMBOLS
#define TS_PUBLIC
#elif defined(_WIN32)
#define TS_PUBLIC __declspec(dllexport)
#else
#define TS_PUBLIC __attribute__((visibility("default")))
#endif

TS_PUBLIC const TSLanguage *tree_sitter_q(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .field_names = ts_field_names,
    .field_map_slices = ts_field_map_slices,
    .field_map_entries = ts_field_map_entries,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .keyword_lex_fn = ts_lex_keywords,
    .keyword_capture_token = sym_identifier,
    .external_scanner = {
      &ts_external_scanner_states[0][0],
      ts_external_scanner_symbol_map,
      tree_sitter_q_external_scanner_create,
      tree_sitter_q_external_scanner_destroy,
      tree_sitter_q_external_scanner_scan,
      tree_sitter_q_external_scanner_serialize,
      tree_sitter_q_external_scanner_deserialize,
    },
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
