#include "tree_sitter/parser.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 116
#define LARGE_STATE_COUNT 23
#define SYMBOL_COUNT 62
#define ALIAS_COUNT 0
#define TOKEN_COUNT 38
#define EXTERNAL_TOKEN_COUNT 7
#define FIELD_COUNT 10
#define MAX_ALIAS_SEQUENCE_LENGTH 6
#define PRODUCTION_ID_COUNT 13

enum ts_symbol_identifiers {
  sym_identifier = 1,
  aux_sym_number_token1 = 2,
  sym_boolean = 3,
  sym_byte = 4,
  sym_char = 5,
  sym_string = 6,
  sym_symbol = 7,
  sym_null = 8,
  sym_infinity = 9,
  sym_timestamp = 10,
  sym_datetime = 11,
  sym_date = 12,
  sym_month = 13,
  sym_timespan = 14,
  sym_time = 15,
  sym_second = 16,
  sym_minute = 17,
  sym_dotted_name = 18,
  anon_sym_COLON_COLON = 19,
  anon_sym_COLON = 20,
  anon_sym_LBRACE = 21,
  anon_sym_RBRACE = 22,
  anon_sym_SEMI = 23,
  anon_sym_LBRACK = 24,
  anon_sym_RBRACK = 25,
  sym_operator = 26,
  anon_sym_LPAREN = 27,
  anon_sym_RPAREN = 28,
  anon_sym_DOLLAR = 29,
  anon_sym_BSLASHd = 30,
  sym_comment = 31,
  sym__system_command_tok = 32,
  sym__neg_number = 33,
  sym__list_ws = 34,
  sym__adverb_tok = 35,
  sym__eos = 36,
  sym__error_sentinel = 37,
  sym_source_file = 38,
  sym__statement = 39,
  sym_number = 40,
  sym_vector = 41,
  sym_assignment = 42,
  sym_lambda = 43,
  sym__lambda_body = 44,
  sym_parameters = 45,
  sym_param = 46,
  sym__expression = 47,
  sym__literal_ref = 48,
  sym_binary_expression = 49,
  sym_call = 50,
  sym_parenthesized = 51,
  sym_list = 52,
  sym_cond = 53,
  sym_system_command = 54,
  sym_namespace_directive = 55,
  aux_sym_source_file_repeat1 = 56,
  aux_sym_vector_repeat1 = 57,
  aux_sym__lambda_body_repeat1 = 58,
  aux_sym_parameters_repeat1 = 59,
  aux_sym_call_repeat1 = 60,
  aux_sym_list_repeat1 = 61,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [sym_identifier] = "identifier",
  [aux_sym_number_token1] = "number_token1",
  [sym_boolean] = "boolean",
  [sym_byte] = "byte",
  [sym_char] = "char",
  [sym_string] = "string",
  [sym_symbol] = "symbol",
  [sym_null] = "null",
  [sym_infinity] = "infinity",
  [sym_timestamp] = "timestamp",
  [sym_datetime] = "datetime",
  [sym_date] = "date",
  [sym_month] = "month",
  [sym_timespan] = "timespan",
  [sym_time] = "time",
  [sym_second] = "second",
  [sym_minute] = "minute",
  [sym_dotted_name] = "dotted_name",
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
  [sym_number] = "number",
  [sym_vector] = "vector",
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
  [aux_sym_vector_repeat1] = "vector_repeat1",
  [aux_sym__lambda_body_repeat1] = "_lambda_body_repeat1",
  [aux_sym_parameters_repeat1] = "parameters_repeat1",
  [aux_sym_call_repeat1] = "call_repeat1",
  [aux_sym_list_repeat1] = "list_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [sym_identifier] = sym_identifier,
  [aux_sym_number_token1] = aux_sym_number_token1,
  [sym_boolean] = sym_boolean,
  [sym_byte] = sym_byte,
  [sym_char] = sym_char,
  [sym_string] = sym_string,
  [sym_symbol] = sym_symbol,
  [sym_null] = sym_null,
  [sym_infinity] = sym_infinity,
  [sym_timestamp] = sym_timestamp,
  [sym_datetime] = sym_datetime,
  [sym_date] = sym_date,
  [sym_month] = sym_month,
  [sym_timespan] = sym_timespan,
  [sym_time] = sym_time,
  [sym_second] = sym_second,
  [sym_minute] = sym_minute,
  [sym_dotted_name] = sym_dotted_name,
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
  [sym_number] = sym_number,
  [sym_vector] = sym_vector,
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
  [aux_sym_vector_repeat1] = aux_sym_vector_repeat1,
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
  [aux_sym_number_token1] = {
    .visible = false,
    .named = false,
  },
  [sym_boolean] = {
    .visible = true,
    .named = true,
  },
  [sym_byte] = {
    .visible = true,
    .named = true,
  },
  [sym_char] = {
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
  [sym_null] = {
    .visible = true,
    .named = true,
  },
  [sym_infinity] = {
    .visible = true,
    .named = true,
  },
  [sym_timestamp] = {
    .visible = true,
    .named = true,
  },
  [sym_datetime] = {
    .visible = true,
    .named = true,
  },
  [sym_date] = {
    .visible = true,
    .named = true,
  },
  [sym_month] = {
    .visible = true,
    .named = true,
  },
  [sym_timespan] = {
    .visible = true,
    .named = true,
  },
  [sym_time] = {
    .visible = true,
    .named = true,
  },
  [sym_second] = {
    .visible = true,
    .named = true,
  },
  [sym_minute] = {
    .visible = true,
    .named = true,
  },
  [sym_dotted_name] = {
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
  [sym_number] = {
    .visible = true,
    .named = true,
  },
  [sym_vector] = {
    .visible = true,
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
  [aux_sym_vector_repeat1] = {
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
  [2] = {.index = 1, .length = 1},
  [3] = {.index = 2, .length = 3},
  [4] = {.index = 5, .length = 1},
  [5] = {.index = 6, .length = 1},
  [6] = {.index = 7, .length = 1},
  [7] = {.index = 8, .length = 2},
  [8] = {.index = 10, .length = 1},
  [9] = {.index = 11, .length = 2},
  [10] = {.index = 13, .length = 3},
  [11] = {.index = 16, .length = 2},
  [12] = {.index = 18, .length = 2},
};

static const TSFieldMapEntry ts_field_map_entries[] = {
  [0] =
    {field_command, 0},
  [1] =
    {field_namespace, 1},
  [2] =
    {field_left, 0},
    {field_operator, 1},
    {field_right, 2},
  [5] =
    {field_function, 0},
  [6] =
    {field_body, 1},
  [7] =
    {field_parameters, 1},
  [8] =
    {field_arguments, 2},
    {field_function, 0},
  [10] =
    {field_param, 1},
  [11] =
    {field_body, 2},
    {field_parameters, 1},
  [13] =
    {field_arguments, 2},
    {field_arguments, 3},
    {field_function, 0},
  [16] =
    {field_param, 1},
    {field_param, 2, .inherited = true},
  [18] =
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
  [7] = 4,
  [8] = 8,
  [9] = 9,
  [10] = 9,
  [11] = 11,
  [12] = 12,
  [13] = 12,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 16,
  [19] = 17,
  [20] = 14,
  [21] = 21,
  [22] = 15,
  [23] = 23,
  [24] = 24,
  [25] = 25,
  [26] = 26,
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
  [52] = 52,
  [53] = 26,
  [54] = 24,
  [55] = 25,
  [56] = 30,
  [57] = 27,
  [58] = 23,
  [59] = 36,
  [60] = 35,
  [61] = 37,
  [62] = 38,
  [63] = 40,
  [64] = 41,
  [65] = 42,
  [66] = 44,
  [67] = 28,
  [68] = 29,
  [69] = 31,
  [70] = 32,
  [71] = 33,
  [72] = 34,
  [73] = 73,
  [74] = 74,
  [75] = 74,
  [76] = 76,
  [77] = 73,
  [78] = 76,
  [79] = 79,
  [80] = 80,
  [81] = 81,
  [82] = 39,
  [83] = 83,
  [84] = 84,
  [85] = 85,
  [86] = 86,
  [87] = 87,
  [88] = 88,
  [89] = 89,
  [90] = 43,
  [91] = 91,
  [92] = 92,
  [93] = 93,
  [94] = 93,
  [95] = 95,
  [96] = 96,
  [97] = 87,
  [98] = 98,
  [99] = 96,
  [100] = 80,
  [101] = 88,
  [102] = 46,
  [103] = 47,
  [104] = 104,
  [105] = 105,
  [106] = 106,
  [107] = 45,
  [108] = 108,
  [109] = 109,
  [110] = 110,
  [111] = 110,
  [112] = 112,
  [113] = 112,
  [114] = 114,
  [115] = 109,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(54);
      ADVANCE_MAP(
        '"', 1,
        '$', 130,
        '(', 128,
        ')', 129,
        '-', 127,
        '.', 22,
        '0', 58,
        '1', 59,
        ':', 120,
        ';', 123,
        '[', 124,
        '\\', 13,
        ']', 125,
        '`', 78,
        '{', 121,
        '}', 122,
      );
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(0);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(62);
      if (('!' <= lookahead && lookahead <= '&') ||
          ('*' <= lookahead && lookahead <= ',') ||
          ('<' <= lookahead && lookahead <= '@') ||
          lookahead == '^' ||
          lookahead == '_' ||
          ('|' <= lookahead && lookahead <= '~')) ADVANCE(126);
      if (('A' <= lookahead && lookahead <= 'z')) ADVANCE(117);
      END_STATE();
    case 1:
      if (lookahead == '"') ADVANCE(77);
      if (lookahead == '\\') ADVANCE(15);
      if (lookahead != 0) ADVANCE(3);
      END_STATE();
    case 2:
      if (lookahead == '"') ADVANCE(77);
      if (lookahead == '\\') ADVANCE(16);
      if (lookahead != 0) ADVANCE(2);
      END_STATE();
    case 3:
      if (lookahead == '"') ADVANCE(76);
      if (lookahead == '\\') ADVANCE(16);
      if (lookahead != 0) ADVANCE(2);
      END_STATE();
    case 4:
      if (lookahead == ')') ADVANCE(129);
      if (lookahead == '.') ADVANCE(21);
      if (lookahead == ':') ADVANCE(120);
      if (lookahead == ';') ADVANCE(123);
      if (lookahead == '[') ADVANCE(124);
      if (lookahead == ']') ADVANCE(125);
      if (lookahead == '}') ADVANCE(122);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(4);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(65);
      if (lookahead == '!' ||
          ('#' <= lookahead && lookahead <= '&') ||
          ('*' <= lookahead && lookahead <= '-') ||
          ('<' <= lookahead && lookahead <= '@') ||
          lookahead == '^' ||
          lookahead == '_' ||
          ('|' <= lookahead && lookahead <= '~')) ADVANCE(126);
      END_STATE();
    case 5:
      if (lookahead == '.') ADVANCE(30);
      END_STATE();
    case 6:
      if (lookahead == ':') ADVANCE(38);
      END_STATE();
    case 7:
      if (lookahead == ':') ADVANCE(40);
      END_STATE();
    case 8:
      if (lookahead == ':') ADVANCE(41);
      END_STATE();
    case 9:
      if (lookahead == ':') ADVANCE(43);
      END_STATE();
    case 10:
      if (lookahead == ':') ADVANCE(45);
      END_STATE();
    case 11:
      if (lookahead == ':') ADVANCE(47);
      END_STATE();
    case 12:
      if (lookahead == 'W') ADVANCE(85);
      if (lookahead == 'w') ADVANCE(83);
      END_STATE();
    case 13:
      if (lookahead == 'd') ADVANCE(131);
      END_STATE();
    case 14:
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(23);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(73);
      END_STATE();
    case 15:
      if (lookahead == '"' ||
          lookahead == '\\' ||
          lookahead == 'n' ||
          lookahead == 'r' ||
          lookahead == 't') ADVANCE(3);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(18);
      END_STATE();
    case 16:
      if (lookahead == '"' ||
          lookahead == '\\' ||
          lookahead == 'n' ||
          lookahead == 'r' ||
          lookahead == 't') ADVANCE(2);
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(19);
      END_STATE();
    case 17:
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(3);
      END_STATE();
    case 18:
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(17);
      END_STATE();
    case 19:
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(20);
      END_STATE();
    case 20:
      if (('0' <= lookahead && lookahead <= '7')) ADVANCE(2);
      END_STATE();
    case 21:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(69);
      END_STATE();
    case 22:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(69);
      if (('A' <= lookahead && lookahead <= 'Z') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(118);
      END_STATE();
    case 23:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(73);
      END_STATE();
    case 24:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(9);
      END_STATE();
    case 25:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(116);
      END_STATE();
    case 26:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(115);
      END_STATE();
    case 27:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(5);
      END_STATE();
    case 28:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(113);
      END_STATE();
    case 29:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(101);
      END_STATE();
    case 30:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(111);
      END_STATE();
    case 31:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(88);
      END_STATE();
    case 32:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(98);
      END_STATE();
    case 33:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(96);
      END_STATE();
    case 34:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(100);
      END_STATE();
    case 35:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(24);
      END_STATE();
    case 36:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(25);
      END_STATE();
    case 37:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(26);
      END_STATE();
    case 38:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(27);
      END_STATE();
    case 39:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(29);
      END_STATE();
    case 40:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(31);
      END_STATE();
    case 41:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(32);
      END_STATE();
    case 42:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(6);
      END_STATE();
    case 43:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(42);
      END_STATE();
    case 44:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(7);
      END_STATE();
    case 45:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(44);
      END_STATE();
    case 46:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(8);
      END_STATE();
    case 47:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(46);
      END_STATE();
    case 48:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(10);
      END_STATE();
    case 49:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(48);
      END_STATE();
    case 50:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(11);
      END_STATE();
    case 51:
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(50);
      END_STATE();
    case 52:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(75);
      END_STATE();
    case 53:
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(52);
      END_STATE();
    case 54:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 55:
      ACCEPT_TOKEN(aux_sym_number_token1);
      END_STATE();
    case 56:
      ACCEPT_TOKEN(aux_sym_number_token1);
      if (lookahead == '.') ADVANCE(69);
      if (lookahead == ':') ADVANCE(36);
      if (lookahead == 'D') ADVANCE(35);
      if (lookahead == 'b') ADVANCE(74);
      if (lookahead == '0' ||
          lookahead == '1') ADVANCE(60);
      if (lookahead == 'e' ||
          lookahead == 'f' ||
          ('h' <= lookahead && lookahead <= 'j')) ADVANCE(55);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(63);
      END_STATE();
    case 57:
      ACCEPT_TOKEN(aux_sym_number_token1);
      if (lookahead == '.') ADVANCE(69);
      if (lookahead == ':') ADVANCE(36);
      if (lookahead == 'D') ADVANCE(35);
      if (lookahead == 'e' ||
          lookahead == 'f' ||
          ('h' <= lookahead && lookahead <= 'j')) ADVANCE(55);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(63);
      END_STATE();
    case 58:
      ACCEPT_TOKEN(aux_sym_number_token1);
      ADVANCE_MAP(
        '.', 69,
        'D', 35,
        'N', 82,
        'W', 86,
        'b', 74,
        'n', 81,
        'w', 84,
        'x', 53,
        '0', 56,
        '1', 56,
      );
      if (lookahead == 'e' ||
          lookahead == 'f' ||
          ('h' <= lookahead && lookahead <= 'j')) ADVANCE(55);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(57);
      END_STATE();
    case 59:
      ACCEPT_TOKEN(aux_sym_number_token1);
      if (lookahead == '.') ADVANCE(69);
      if (lookahead == 'D') ADVANCE(35);
      if (lookahead == 'b') ADVANCE(74);
      if (lookahead == '0' ||
          lookahead == '1') ADVANCE(56);
      if (lookahead == 'e' ||
          lookahead == 'f' ||
          ('h' <= lookahead && lookahead <= 'j')) ADVANCE(55);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(57);
      END_STATE();
    case 60:
      ACCEPT_TOKEN(aux_sym_number_token1);
      if (lookahead == '.') ADVANCE(69);
      if (lookahead == 'D') ADVANCE(35);
      if (lookahead == 'b') ADVANCE(74);
      if (lookahead == '0' ||
          lookahead == '1') ADVANCE(66);
      if (lookahead == 'e' ||
          lookahead == 'f' ||
          ('h' <= lookahead && lookahead <= 'j')) ADVANCE(55);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(67);
      END_STATE();
    case 61:
      ACCEPT_TOKEN(aux_sym_number_token1);
      if (lookahead == '.') ADVANCE(69);
      if (lookahead == 'D') ADVANCE(35);
      if (lookahead == 'b') ADVANCE(74);
      if (lookahead == '0' ||
          lookahead == '1') ADVANCE(61);
      if (lookahead == 'e' ||
          lookahead == 'f' ||
          ('h' <= lookahead && lookahead <= 'j')) ADVANCE(55);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(64);
      END_STATE();
    case 62:
      ACCEPT_TOKEN(aux_sym_number_token1);
      if (lookahead == '.') ADVANCE(69);
      if (lookahead == 'D') ADVANCE(35);
      if (lookahead == 'e' ||
          lookahead == 'f' ||
          ('h' <= lookahead && lookahead <= 'j')) ADVANCE(55);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(57);
      END_STATE();
    case 63:
      ACCEPT_TOKEN(aux_sym_number_token1);
      if (lookahead == '.') ADVANCE(69);
      if (lookahead == 'D') ADVANCE(35);
      if (lookahead == 'e' ||
          lookahead == 'f' ||
          ('h' <= lookahead && lookahead <= 'j')) ADVANCE(55);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(67);
      END_STATE();
    case 64:
      ACCEPT_TOKEN(aux_sym_number_token1);
      if (lookahead == '.') ADVANCE(69);
      if (lookahead == 'D') ADVANCE(35);
      if (lookahead == 'e' ||
          lookahead == 'f' ||
          ('h' <= lookahead && lookahead <= 'j')) ADVANCE(55);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(64);
      END_STATE();
    case 65:
      ACCEPT_TOKEN(aux_sym_number_token1);
      if (lookahead == '.') ADVANCE(69);
      if (lookahead == 'e' ||
          lookahead == 'f' ||
          ('h' <= lookahead && lookahead <= 'j')) ADVANCE(55);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(65);
      END_STATE();
    case 66:
      ACCEPT_TOKEN(aux_sym_number_token1);
      if (lookahead == '.') ADVANCE(71);
      if (lookahead == 'D') ADVANCE(35);
      if (lookahead == 'b') ADVANCE(74);
      if (lookahead == '0' ||
          lookahead == '1') ADVANCE(61);
      if (lookahead == 'e' ||
          lookahead == 'f' ||
          ('h' <= lookahead && lookahead <= 'j')) ADVANCE(55);
      if (('2' <= lookahead && lookahead <= '9')) ADVANCE(64);
      END_STATE();
    case 67:
      ACCEPT_TOKEN(aux_sym_number_token1);
      if (lookahead == '.') ADVANCE(71);
      if (lookahead == 'D') ADVANCE(35);
      if (lookahead == 'e' ||
          lookahead == 'f' ||
          ('h' <= lookahead && lookahead <= 'j')) ADVANCE(55);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(64);
      END_STATE();
    case 68:
      ACCEPT_TOKEN(aux_sym_number_token1);
      if (lookahead == '.') ADVANCE(39);
      if (lookahead == 'E') ADVANCE(14);
      if (lookahead == 'e') ADVANCE(72);
      if (lookahead == 'f') ADVANCE(55);
      if (lookahead == 'm') ADVANCE(102);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(69);
      END_STATE();
    case 69:
      ACCEPT_TOKEN(aux_sym_number_token1);
      if (lookahead == 'E') ADVANCE(14);
      if (lookahead == 'e') ADVANCE(72);
      if (lookahead == 'f') ADVANCE(55);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(69);
      END_STATE();
    case 70:
      ACCEPT_TOKEN(aux_sym_number_token1);
      if (lookahead == 'E') ADVANCE(14);
      if (lookahead == 'e') ADVANCE(72);
      if (lookahead == 'f') ADVANCE(55);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(68);
      END_STATE();
    case 71:
      ACCEPT_TOKEN(aux_sym_number_token1);
      if (lookahead == 'E') ADVANCE(14);
      if (lookahead == 'e') ADVANCE(72);
      if (lookahead == 'f') ADVANCE(55);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(70);
      END_STATE();
    case 72:
      ACCEPT_TOKEN(aux_sym_number_token1);
      if (lookahead == '+' ||
          lookahead == '-') ADVANCE(23);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(73);
      END_STATE();
    case 73:
      ACCEPT_TOKEN(aux_sym_number_token1);
      if (lookahead == 'e' ||
          lookahead == 'f') ADVANCE(55);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(73);
      END_STATE();
    case 74:
      ACCEPT_TOKEN(sym_boolean);
      END_STATE();
    case 75:
      ACCEPT_TOKEN(sym_byte);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'F') ||
          ('a' <= lookahead && lookahead <= 'f')) ADVANCE(52);
      END_STATE();
    case 76:
      ACCEPT_TOKEN(sym_char);
      END_STATE();
    case 77:
      ACCEPT_TOKEN(sym_string);
      END_STATE();
    case 78:
      ACCEPT_TOKEN(sym_symbol);
      if (lookahead == ':') ADVANCE(80);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(79);
      END_STATE();
    case 79:
      ACCEPT_TOKEN(sym_symbol);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(79);
      END_STATE();
    case 80:
      ACCEPT_TOKEN(sym_symbol);
      if (('-' <= lookahead && lookahead <= ':') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(80);
      END_STATE();
    case 81:
      ACCEPT_TOKEN(sym_null);
      END_STATE();
    case 82:
      ACCEPT_TOKEN(sym_null);
      if (('d' <= lookahead && lookahead <= 'j') ||
          lookahead == 'm' ||
          lookahead == 'n' ||
          lookahead == 'p' ||
          ('t' <= lookahead && lookahead <= 'v') ||
          lookahead == 'z') ADVANCE(81);
      END_STATE();
    case 83:
      ACCEPT_TOKEN(sym_infinity);
      END_STATE();
    case 84:
      ACCEPT_TOKEN(sym_infinity);
      if (lookahead == 'z') ADVANCE(83);
      END_STATE();
    case 85:
      ACCEPT_TOKEN(sym_infinity);
      if (lookahead == 'd' ||
          lookahead == 'e' ||
          lookahead == 'h' ||
          lookahead == 'i' ||
          lookahead == 'm' ||
          lookahead == 'n' ||
          lookahead == 'p' ||
          ('t' <= lookahead && lookahead <= 'v')) ADVANCE(83);
      END_STATE();
    case 86:
      ACCEPT_TOKEN(sym_infinity);
      if (('d' <= lookahead && lookahead <= 'f') ||
          ('h' <= lookahead && lookahead <= 'j') ||
          lookahead == 'm' ||
          lookahead == 'n' ||
          lookahead == 'p' ||
          ('t' <= lookahead && lookahead <= 'v')) ADVANCE(83);
      END_STATE();
    case 87:
      ACCEPT_TOKEN(sym_timestamp);
      END_STATE();
    case 88:
      ACCEPT_TOKEN(sym_timestamp);
      if (lookahead == '.') ADVANCE(33);
      END_STATE();
    case 89:
      ACCEPT_TOKEN(sym_timestamp);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(87);
      END_STATE();
    case 90:
      ACCEPT_TOKEN(sym_timestamp);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(89);
      END_STATE();
    case 91:
      ACCEPT_TOKEN(sym_timestamp);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(90);
      END_STATE();
    case 92:
      ACCEPT_TOKEN(sym_timestamp);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(91);
      END_STATE();
    case 93:
      ACCEPT_TOKEN(sym_timestamp);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(92);
      END_STATE();
    case 94:
      ACCEPT_TOKEN(sym_timestamp);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(93);
      END_STATE();
    case 95:
      ACCEPT_TOKEN(sym_timestamp);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(94);
      END_STATE();
    case 96:
      ACCEPT_TOKEN(sym_timestamp);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(95);
      END_STATE();
    case 97:
      ACCEPT_TOKEN(sym_datetime);
      END_STATE();
    case 98:
      ACCEPT_TOKEN(sym_datetime);
      if (lookahead == '.') ADVANCE(34);
      END_STATE();
    case 99:
      ACCEPT_TOKEN(sym_datetime);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(97);
      END_STATE();
    case 100:
      ACCEPT_TOKEN(sym_datetime);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(99);
      END_STATE();
    case 101:
      ACCEPT_TOKEN(sym_date);
      if (lookahead == 'D') ADVANCE(49);
      if (lookahead == 'T') ADVANCE(51);
      END_STATE();
    case 102:
      ACCEPT_TOKEN(sym_month);
      END_STATE();
    case 103:
      ACCEPT_TOKEN(sym_timespan);
      END_STATE();
    case 104:
      ACCEPT_TOKEN(sym_timespan);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(103);
      END_STATE();
    case 105:
      ACCEPT_TOKEN(sym_timespan);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(104);
      END_STATE();
    case 106:
      ACCEPT_TOKEN(sym_timespan);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(105);
      END_STATE();
    case 107:
      ACCEPT_TOKEN(sym_timespan);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(106);
      END_STATE();
    case 108:
      ACCEPT_TOKEN(sym_timespan);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(107);
      END_STATE();
    case 109:
      ACCEPT_TOKEN(sym_timespan);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(108);
      END_STATE();
    case 110:
      ACCEPT_TOKEN(sym_timespan);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(109);
      END_STATE();
    case 111:
      ACCEPT_TOKEN(sym_timespan);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(110);
      END_STATE();
    case 112:
      ACCEPT_TOKEN(sym_time);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(114);
      END_STATE();
    case 113:
      ACCEPT_TOKEN(sym_time);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(112);
      END_STATE();
    case 114:
      ACCEPT_TOKEN(sym_time);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(108);
      END_STATE();
    case 115:
      ACCEPT_TOKEN(sym_second);
      if (lookahead == '.') ADVANCE(28);
      END_STATE();
    case 116:
      ACCEPT_TOKEN(sym_minute);
      if (lookahead == ':') ADVANCE(37);
      END_STATE();
    case 117:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(117);
      END_STATE();
    case 118:
      ACCEPT_TOKEN(sym_dotted_name);
      if (lookahead == '.' ||
          ('0' <= lookahead && lookahead <= '9') ||
          ('A' <= lookahead && lookahead <= 'Z') ||
          lookahead == '_' ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(118);
      END_STATE();
    case 119:
      ACCEPT_TOKEN(anon_sym_COLON_COLON);
      END_STATE();
    case 120:
      ACCEPT_TOKEN(anon_sym_COLON);
      if (lookahead == ':') ADVANCE(119);
      END_STATE();
    case 121:
      ACCEPT_TOKEN(anon_sym_LBRACE);
      END_STATE();
    case 122:
      ACCEPT_TOKEN(anon_sym_RBRACE);
      END_STATE();
    case 123:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 124:
      ACCEPT_TOKEN(anon_sym_LBRACK);
      END_STATE();
    case 125:
      ACCEPT_TOKEN(anon_sym_RBRACK);
      END_STATE();
    case 126:
      ACCEPT_TOKEN(sym_operator);
      END_STATE();
    case 127:
      ACCEPT_TOKEN(sym_operator);
      if (lookahead == '0') ADVANCE(12);
      END_STATE();
    case 128:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 129:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 130:
      ACCEPT_TOKEN(anon_sym_DOLLAR);
      END_STATE();
    case 131:
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
      ACCEPT_TOKEN(ts_builtin_sym_end);
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
  [4] = {.lex_state = 0, .external_lex_state = 2},
  [5] = {.lex_state = 0, .external_lex_state = 2},
  [6] = {.lex_state = 0, .external_lex_state = 2},
  [7] = {.lex_state = 0, .external_lex_state = 2},
  [8] = {.lex_state = 0, .external_lex_state = 2},
  [9] = {.lex_state = 0, .external_lex_state = 3},
  [10] = {.lex_state = 0, .external_lex_state = 3},
  [11] = {.lex_state = 0, .external_lex_state = 3},
  [12] = {.lex_state = 0, .external_lex_state = 3},
  [13] = {.lex_state = 0, .external_lex_state = 3},
  [14] = {.lex_state = 0, .external_lex_state = 3},
  [15] = {.lex_state = 0, .external_lex_state = 3},
  [16] = {.lex_state = 0, .external_lex_state = 3},
  [17] = {.lex_state = 0, .external_lex_state = 3},
  [18] = {.lex_state = 0, .external_lex_state = 3},
  [19] = {.lex_state = 0, .external_lex_state = 3},
  [20] = {.lex_state = 0, .external_lex_state = 3},
  [21] = {.lex_state = 0, .external_lex_state = 3},
  [22] = {.lex_state = 0, .external_lex_state = 3},
  [23] = {.lex_state = 0, .external_lex_state = 4},
  [24] = {.lex_state = 0, .external_lex_state = 4},
  [25] = {.lex_state = 0, .external_lex_state = 4},
  [26] = {.lex_state = 0, .external_lex_state = 4},
  [27] = {.lex_state = 0, .external_lex_state = 4},
  [28] = {.lex_state = 0, .external_lex_state = 4},
  [29] = {.lex_state = 0, .external_lex_state = 4},
  [30] = {.lex_state = 0, .external_lex_state = 4},
  [31] = {.lex_state = 0, .external_lex_state = 4},
  [32] = {.lex_state = 0, .external_lex_state = 4},
  [33] = {.lex_state = 0, .external_lex_state = 4},
  [34] = {.lex_state = 0, .external_lex_state = 4},
  [35] = {.lex_state = 0, .external_lex_state = 4},
  [36] = {.lex_state = 0, .external_lex_state = 4},
  [37] = {.lex_state = 0, .external_lex_state = 4},
  [38] = {.lex_state = 0, .external_lex_state = 4},
  [39] = {.lex_state = 0, .external_lex_state = 4},
  [40] = {.lex_state = 0, .external_lex_state = 4},
  [41] = {.lex_state = 0, .external_lex_state = 4},
  [42] = {.lex_state = 0, .external_lex_state = 4},
  [43] = {.lex_state = 0, .external_lex_state = 4},
  [44] = {.lex_state = 0, .external_lex_state = 4},
  [45] = {.lex_state = 0, .external_lex_state = 4},
  [46] = {.lex_state = 0, .external_lex_state = 4},
  [47] = {.lex_state = 0, .external_lex_state = 4},
  [48] = {.lex_state = 0, .external_lex_state = 4},
  [49] = {.lex_state = 0, .external_lex_state = 2},
  [50] = {.lex_state = 0, .external_lex_state = 2},
  [51] = {.lex_state = 0, .external_lex_state = 2},
  [52] = {.lex_state = 0, .external_lex_state = 2},
  [53] = {.lex_state = 4, .external_lex_state = 3},
  [54] = {.lex_state = 4, .external_lex_state = 3},
  [55] = {.lex_state = 4, .external_lex_state = 3},
  [56] = {.lex_state = 4, .external_lex_state = 3},
  [57] = {.lex_state = 4, .external_lex_state = 5},
  [58] = {.lex_state = 4, .external_lex_state = 5},
  [59] = {.lex_state = 4, .external_lex_state = 5},
  [60] = {.lex_state = 4, .external_lex_state = 5},
  [61] = {.lex_state = 4, .external_lex_state = 5},
  [62] = {.lex_state = 4, .external_lex_state = 5},
  [63] = {.lex_state = 4, .external_lex_state = 5},
  [64] = {.lex_state = 4, .external_lex_state = 5},
  [65] = {.lex_state = 4, .external_lex_state = 5},
  [66] = {.lex_state = 4, .external_lex_state = 5},
  [67] = {.lex_state = 4, .external_lex_state = 5},
  [68] = {.lex_state = 4, .external_lex_state = 5},
  [69] = {.lex_state = 4, .external_lex_state = 5},
  [70] = {.lex_state = 4, .external_lex_state = 5},
  [71] = {.lex_state = 4, .external_lex_state = 5},
  [72] = {.lex_state = 4, .external_lex_state = 5},
  [73] = {.lex_state = 4, .external_lex_state = 5},
  [74] = {.lex_state = 4, .external_lex_state = 5},
  [75] = {.lex_state = 4, .external_lex_state = 5},
  [76] = {.lex_state = 4, .external_lex_state = 5},
  [77] = {.lex_state = 4, .external_lex_state = 5},
  [78] = {.lex_state = 4, .external_lex_state = 5},
  [79] = {.lex_state = 0, .external_lex_state = 5},
  [80] = {.lex_state = 0, .external_lex_state = 5},
  [81] = {.lex_state = 0, .external_lex_state = 5},
  [82] = {.lex_state = 4, .external_lex_state = 5},
  [83] = {.lex_state = 0, .external_lex_state = 5},
  [84] = {.lex_state = 0, .external_lex_state = 5},
  [85] = {.lex_state = 4, .external_lex_state = 5},
  [86] = {.lex_state = 0, .external_lex_state = 5},
  [87] = {.lex_state = 0, .external_lex_state = 5},
  [88] = {.lex_state = 0, .external_lex_state = 5},
  [89] = {.lex_state = 0, .external_lex_state = 5},
  [90] = {.lex_state = 4, .external_lex_state = 5},
  [91] = {.lex_state = 0, .external_lex_state = 5},
  [92] = {.lex_state = 0, .external_lex_state = 5},
  [93] = {.lex_state = 4, .external_lex_state = 5},
  [94] = {.lex_state = 4, .external_lex_state = 5},
  [95] = {.lex_state = 0, .external_lex_state = 5},
  [96] = {.lex_state = 0, .external_lex_state = 5},
  [97] = {.lex_state = 0, .external_lex_state = 5},
  [98] = {.lex_state = 4, .external_lex_state = 5},
  [99] = {.lex_state = 0, .external_lex_state = 5},
  [100] = {.lex_state = 0, .external_lex_state = 5},
  [101] = {.lex_state = 0, .external_lex_state = 5},
  [102] = {.lex_state = 0, .external_lex_state = 5},
  [103] = {.lex_state = 0, .external_lex_state = 5},
  [104] = {.lex_state = 0, .external_lex_state = 5},
  [105] = {.lex_state = 0, .external_lex_state = 5},
  [106] = {.lex_state = 0, .external_lex_state = 5},
  [107] = {.lex_state = 0, .external_lex_state = 5},
  [108] = {.lex_state = 0, .external_lex_state = 5},
  [109] = {.lex_state = 0, .external_lex_state = 5},
  [110] = {.lex_state = 0, .external_lex_state = 5},
  [111] = {.lex_state = 0, .external_lex_state = 5},
  [112] = {.lex_state = 0, .external_lex_state = 5},
  [113] = {.lex_state = 0, .external_lex_state = 5},
  [114] = {.lex_state = 0, .external_lex_state = 5},
  [115] = {.lex_state = 0, .external_lex_state = 5},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [aux_sym_number_token1] = ACTIONS(1),
    [sym_boolean] = ACTIONS(1),
    [sym_byte] = ACTIONS(1),
    [sym_char] = ACTIONS(1),
    [sym_string] = ACTIONS(1),
    [sym_symbol] = ACTIONS(1),
    [sym_null] = ACTIONS(1),
    [sym_infinity] = ACTIONS(1),
    [sym_timestamp] = ACTIONS(1),
    [sym_datetime] = ACTIONS(1),
    [sym_date] = ACTIONS(1),
    [sym_month] = ACTIONS(1),
    [sym_timespan] = ACTIONS(1),
    [sym_time] = ACTIONS(1),
    [sym_second] = ACTIONS(1),
    [sym_minute] = ACTIONS(1),
    [sym_dotted_name] = ACTIONS(1),
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
    [sym_source_file] = STATE(114),
    [sym__statement] = STATE(48),
    [sym_number] = STATE(24),
    [sym_vector] = STATE(43),
    [sym_assignment] = STATE(48),
    [sym_lambda] = STATE(43),
    [sym__expression] = STATE(43),
    [sym__literal_ref] = STATE(43),
    [sym_binary_expression] = STATE(43),
    [sym_call] = STATE(43),
    [sym_parenthesized] = STATE(43),
    [sym_list] = STATE(43),
    [sym_cond] = STATE(43),
    [sym_system_command] = STATE(48),
    [sym_namespace_directive] = STATE(48),
    [aux_sym_source_file_repeat1] = STATE(5),
    [ts_builtin_sym_end] = ACTIONS(5),
    [sym_identifier] = ACTIONS(7),
    [aux_sym_number_token1] = ACTIONS(9),
    [sym_boolean] = ACTIONS(11),
    [sym_byte] = ACTIONS(11),
    [sym_char] = ACTIONS(11),
    [sym_string] = ACTIONS(13),
    [sym_symbol] = ACTIONS(11),
    [sym_null] = ACTIONS(11),
    [sym_infinity] = ACTIONS(11),
    [sym_timestamp] = ACTIONS(11),
    [sym_datetime] = ACTIONS(11),
    [sym_date] = ACTIONS(13),
    [sym_month] = ACTIONS(11),
    [sym_timespan] = ACTIONS(11),
    [sym_time] = ACTIONS(13),
    [sym_second] = ACTIONS(13),
    [sym_minute] = ACTIONS(13),
    [sym_dotted_name] = ACTIONS(7),
    [anon_sym_LBRACE] = ACTIONS(15),
    [anon_sym_LPAREN] = ACTIONS(17),
    [anon_sym_DOLLAR] = ACTIONS(19),
    [anon_sym_BSLASHd] = ACTIONS(21),
    [sym_comment] = ACTIONS(3),
    [sym__system_command_tok] = ACTIONS(23),
    [sym__neg_number] = ACTIONS(25),
  },
  [2] = {
    [sym__statement] = STATE(83),
    [sym_number] = STATE(54),
    [sym_vector] = STATE(90),
    [sym_assignment] = STATE(83),
    [sym_lambda] = STATE(90),
    [sym__lambda_body] = STATE(110),
    [sym_parameters] = STATE(4),
    [sym__expression] = STATE(90),
    [sym__literal_ref] = STATE(90),
    [sym_binary_expression] = STATE(90),
    [sym_call] = STATE(90),
    [sym_parenthesized] = STATE(90),
    [sym_list] = STATE(90),
    [sym_cond] = STATE(90),
    [sym_system_command] = STATE(83),
    [sym_namespace_directive] = STATE(83),
    [sym_identifier] = ACTIONS(27),
    [aux_sym_number_token1] = ACTIONS(29),
    [sym_boolean] = ACTIONS(31),
    [sym_byte] = ACTIONS(31),
    [sym_char] = ACTIONS(31),
    [sym_string] = ACTIONS(33),
    [sym_symbol] = ACTIONS(31),
    [sym_null] = ACTIONS(31),
    [sym_infinity] = ACTIONS(31),
    [sym_timestamp] = ACTIONS(31),
    [sym_datetime] = ACTIONS(31),
    [sym_date] = ACTIONS(33),
    [sym_month] = ACTIONS(31),
    [sym_timespan] = ACTIONS(31),
    [sym_time] = ACTIONS(33),
    [sym_second] = ACTIONS(33),
    [sym_minute] = ACTIONS(33),
    [sym_dotted_name] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(35),
    [anon_sym_RBRACE] = ACTIONS(37),
    [anon_sym_LBRACK] = ACTIONS(39),
    [anon_sym_LPAREN] = ACTIONS(41),
    [anon_sym_DOLLAR] = ACTIONS(43),
    [anon_sym_BSLASHd] = ACTIONS(45),
    [sym_comment] = ACTIONS(3),
    [sym__system_command_tok] = ACTIONS(47),
    [sym__neg_number] = ACTIONS(49),
  },
  [3] = {
    [sym__statement] = STATE(83),
    [sym_number] = STATE(54),
    [sym_vector] = STATE(90),
    [sym_assignment] = STATE(83),
    [sym_lambda] = STATE(90),
    [sym__lambda_body] = STATE(111),
    [sym_parameters] = STATE(7),
    [sym__expression] = STATE(90),
    [sym__literal_ref] = STATE(90),
    [sym_binary_expression] = STATE(90),
    [sym_call] = STATE(90),
    [sym_parenthesized] = STATE(90),
    [sym_list] = STATE(90),
    [sym_cond] = STATE(90),
    [sym_system_command] = STATE(83),
    [sym_namespace_directive] = STATE(83),
    [sym_identifier] = ACTIONS(27),
    [aux_sym_number_token1] = ACTIONS(29),
    [sym_boolean] = ACTIONS(31),
    [sym_byte] = ACTIONS(31),
    [sym_char] = ACTIONS(31),
    [sym_string] = ACTIONS(33),
    [sym_symbol] = ACTIONS(31),
    [sym_null] = ACTIONS(31),
    [sym_infinity] = ACTIONS(31),
    [sym_timestamp] = ACTIONS(31),
    [sym_datetime] = ACTIONS(31),
    [sym_date] = ACTIONS(33),
    [sym_month] = ACTIONS(31),
    [sym_timespan] = ACTIONS(31),
    [sym_time] = ACTIONS(33),
    [sym_second] = ACTIONS(33),
    [sym_minute] = ACTIONS(33),
    [sym_dotted_name] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(35),
    [anon_sym_RBRACE] = ACTIONS(51),
    [anon_sym_LBRACK] = ACTIONS(39),
    [anon_sym_LPAREN] = ACTIONS(41),
    [anon_sym_DOLLAR] = ACTIONS(43),
    [anon_sym_BSLASHd] = ACTIONS(45),
    [sym_comment] = ACTIONS(3),
    [sym__system_command_tok] = ACTIONS(47),
    [sym__neg_number] = ACTIONS(49),
  },
  [4] = {
    [sym__statement] = STATE(83),
    [sym_number] = STATE(54),
    [sym_vector] = STATE(90),
    [sym_assignment] = STATE(83),
    [sym_lambda] = STATE(90),
    [sym__lambda_body] = STATE(113),
    [sym__expression] = STATE(90),
    [sym__literal_ref] = STATE(90),
    [sym_binary_expression] = STATE(90),
    [sym_call] = STATE(90),
    [sym_parenthesized] = STATE(90),
    [sym_list] = STATE(90),
    [sym_cond] = STATE(90),
    [sym_system_command] = STATE(83),
    [sym_namespace_directive] = STATE(83),
    [sym_identifier] = ACTIONS(27),
    [aux_sym_number_token1] = ACTIONS(29),
    [sym_boolean] = ACTIONS(31),
    [sym_byte] = ACTIONS(31),
    [sym_char] = ACTIONS(31),
    [sym_string] = ACTIONS(33),
    [sym_symbol] = ACTIONS(31),
    [sym_null] = ACTIONS(31),
    [sym_infinity] = ACTIONS(31),
    [sym_timestamp] = ACTIONS(31),
    [sym_datetime] = ACTIONS(31),
    [sym_date] = ACTIONS(33),
    [sym_month] = ACTIONS(31),
    [sym_timespan] = ACTIONS(31),
    [sym_time] = ACTIONS(33),
    [sym_second] = ACTIONS(33),
    [sym_minute] = ACTIONS(33),
    [sym_dotted_name] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(35),
    [anon_sym_RBRACE] = ACTIONS(53),
    [anon_sym_LPAREN] = ACTIONS(41),
    [anon_sym_DOLLAR] = ACTIONS(43),
    [anon_sym_BSLASHd] = ACTIONS(45),
    [sym_comment] = ACTIONS(3),
    [sym__system_command_tok] = ACTIONS(47),
    [sym__neg_number] = ACTIONS(49),
  },
  [5] = {
    [sym__statement] = STATE(48),
    [sym_number] = STATE(24),
    [sym_vector] = STATE(43),
    [sym_assignment] = STATE(48),
    [sym_lambda] = STATE(43),
    [sym__expression] = STATE(43),
    [sym__literal_ref] = STATE(43),
    [sym_binary_expression] = STATE(43),
    [sym_call] = STATE(43),
    [sym_parenthesized] = STATE(43),
    [sym_list] = STATE(43),
    [sym_cond] = STATE(43),
    [sym_system_command] = STATE(48),
    [sym_namespace_directive] = STATE(48),
    [aux_sym_source_file_repeat1] = STATE(6),
    [ts_builtin_sym_end] = ACTIONS(55),
    [sym_identifier] = ACTIONS(7),
    [aux_sym_number_token1] = ACTIONS(9),
    [sym_boolean] = ACTIONS(11),
    [sym_byte] = ACTIONS(11),
    [sym_char] = ACTIONS(11),
    [sym_string] = ACTIONS(13),
    [sym_symbol] = ACTIONS(11),
    [sym_null] = ACTIONS(11),
    [sym_infinity] = ACTIONS(11),
    [sym_timestamp] = ACTIONS(11),
    [sym_datetime] = ACTIONS(11),
    [sym_date] = ACTIONS(13),
    [sym_month] = ACTIONS(11),
    [sym_timespan] = ACTIONS(11),
    [sym_time] = ACTIONS(13),
    [sym_second] = ACTIONS(13),
    [sym_minute] = ACTIONS(13),
    [sym_dotted_name] = ACTIONS(7),
    [anon_sym_LBRACE] = ACTIONS(15),
    [anon_sym_LPAREN] = ACTIONS(17),
    [anon_sym_DOLLAR] = ACTIONS(19),
    [anon_sym_BSLASHd] = ACTIONS(21),
    [sym_comment] = ACTIONS(3),
    [sym__system_command_tok] = ACTIONS(23),
    [sym__neg_number] = ACTIONS(25),
  },
  [6] = {
    [sym__statement] = STATE(48),
    [sym_number] = STATE(24),
    [sym_vector] = STATE(43),
    [sym_assignment] = STATE(48),
    [sym_lambda] = STATE(43),
    [sym__expression] = STATE(43),
    [sym__literal_ref] = STATE(43),
    [sym_binary_expression] = STATE(43),
    [sym_call] = STATE(43),
    [sym_parenthesized] = STATE(43),
    [sym_list] = STATE(43),
    [sym_cond] = STATE(43),
    [sym_system_command] = STATE(48),
    [sym_namespace_directive] = STATE(48),
    [aux_sym_source_file_repeat1] = STATE(6),
    [ts_builtin_sym_end] = ACTIONS(57),
    [sym_identifier] = ACTIONS(59),
    [aux_sym_number_token1] = ACTIONS(62),
    [sym_boolean] = ACTIONS(65),
    [sym_byte] = ACTIONS(65),
    [sym_char] = ACTIONS(65),
    [sym_string] = ACTIONS(68),
    [sym_symbol] = ACTIONS(65),
    [sym_null] = ACTIONS(65),
    [sym_infinity] = ACTIONS(65),
    [sym_timestamp] = ACTIONS(65),
    [sym_datetime] = ACTIONS(65),
    [sym_date] = ACTIONS(68),
    [sym_month] = ACTIONS(65),
    [sym_timespan] = ACTIONS(65),
    [sym_time] = ACTIONS(68),
    [sym_second] = ACTIONS(68),
    [sym_minute] = ACTIONS(68),
    [sym_dotted_name] = ACTIONS(59),
    [anon_sym_LBRACE] = ACTIONS(71),
    [anon_sym_LPAREN] = ACTIONS(74),
    [anon_sym_DOLLAR] = ACTIONS(77),
    [anon_sym_BSLASHd] = ACTIONS(80),
    [sym_comment] = ACTIONS(3),
    [sym__system_command_tok] = ACTIONS(83),
    [sym__neg_number] = ACTIONS(86),
  },
  [7] = {
    [sym__statement] = STATE(83),
    [sym_number] = STATE(54),
    [sym_vector] = STATE(90),
    [sym_assignment] = STATE(83),
    [sym_lambda] = STATE(90),
    [sym__lambda_body] = STATE(112),
    [sym__expression] = STATE(90),
    [sym__literal_ref] = STATE(90),
    [sym_binary_expression] = STATE(90),
    [sym_call] = STATE(90),
    [sym_parenthesized] = STATE(90),
    [sym_list] = STATE(90),
    [sym_cond] = STATE(90),
    [sym_system_command] = STATE(83),
    [sym_namespace_directive] = STATE(83),
    [sym_identifier] = ACTIONS(27),
    [aux_sym_number_token1] = ACTIONS(29),
    [sym_boolean] = ACTIONS(31),
    [sym_byte] = ACTIONS(31),
    [sym_char] = ACTIONS(31),
    [sym_string] = ACTIONS(33),
    [sym_symbol] = ACTIONS(31),
    [sym_null] = ACTIONS(31),
    [sym_infinity] = ACTIONS(31),
    [sym_timestamp] = ACTIONS(31),
    [sym_datetime] = ACTIONS(31),
    [sym_date] = ACTIONS(33),
    [sym_month] = ACTIONS(31),
    [sym_timespan] = ACTIONS(31),
    [sym_time] = ACTIONS(33),
    [sym_second] = ACTIONS(33),
    [sym_minute] = ACTIONS(33),
    [sym_dotted_name] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(35),
    [anon_sym_RBRACE] = ACTIONS(89),
    [anon_sym_LPAREN] = ACTIONS(41),
    [anon_sym_DOLLAR] = ACTIONS(43),
    [anon_sym_BSLASHd] = ACTIONS(45),
    [sym_comment] = ACTIONS(3),
    [sym__system_command_tok] = ACTIONS(47),
    [sym__neg_number] = ACTIONS(49),
  },
  [8] = {
    [sym__statement] = STATE(106),
    [sym_number] = STATE(54),
    [sym_vector] = STATE(90),
    [sym_assignment] = STATE(106),
    [sym_lambda] = STATE(90),
    [sym__expression] = STATE(90),
    [sym__literal_ref] = STATE(90),
    [sym_binary_expression] = STATE(90),
    [sym_call] = STATE(90),
    [sym_parenthesized] = STATE(90),
    [sym_list] = STATE(90),
    [sym_cond] = STATE(90),
    [sym_system_command] = STATE(106),
    [sym_namespace_directive] = STATE(106),
    [sym_identifier] = ACTIONS(27),
    [aux_sym_number_token1] = ACTIONS(29),
    [sym_boolean] = ACTIONS(31),
    [sym_byte] = ACTIONS(31),
    [sym_char] = ACTIONS(31),
    [sym_string] = ACTIONS(33),
    [sym_symbol] = ACTIONS(31),
    [sym_null] = ACTIONS(31),
    [sym_infinity] = ACTIONS(31),
    [sym_timestamp] = ACTIONS(31),
    [sym_datetime] = ACTIONS(31),
    [sym_date] = ACTIONS(33),
    [sym_month] = ACTIONS(31),
    [sym_timespan] = ACTIONS(31),
    [sym_time] = ACTIONS(33),
    [sym_second] = ACTIONS(33),
    [sym_minute] = ACTIONS(33),
    [sym_dotted_name] = ACTIONS(27),
    [anon_sym_LBRACE] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(41),
    [anon_sym_DOLLAR] = ACTIONS(43),
    [anon_sym_BSLASHd] = ACTIONS(45),
    [sym_comment] = ACTIONS(3),
    [sym__system_command_tok] = ACTIONS(47),
    [sym__neg_number] = ACTIONS(49),
  },
  [9] = {
    [sym_number] = STATE(54),
    [sym_vector] = STATE(77),
    [sym_lambda] = STATE(77),
    [sym__expression] = STATE(77),
    [sym__literal_ref] = STATE(77),
    [sym_binary_expression] = STATE(77),
    [sym_call] = STATE(77),
    [sym_parenthesized] = STATE(77),
    [sym_list] = STATE(77),
    [sym_cond] = STATE(77),
    [aux_sym_list_repeat1] = STATE(96),
    [sym_identifier] = ACTIONS(91),
    [aux_sym_number_token1] = ACTIONS(29),
    [sym_boolean] = ACTIONS(93),
    [sym_byte] = ACTIONS(93),
    [sym_char] = ACTIONS(93),
    [sym_string] = ACTIONS(95),
    [sym_symbol] = ACTIONS(93),
    [sym_null] = ACTIONS(93),
    [sym_infinity] = ACTIONS(93),
    [sym_timestamp] = ACTIONS(93),
    [sym_datetime] = ACTIONS(93),
    [sym_date] = ACTIONS(95),
    [sym_month] = ACTIONS(93),
    [sym_timespan] = ACTIONS(93),
    [sym_time] = ACTIONS(95),
    [sym_second] = ACTIONS(95),
    [sym_minute] = ACTIONS(95),
    [sym_dotted_name] = ACTIONS(91),
    [anon_sym_LBRACE] = ACTIONS(35),
    [anon_sym_SEMI] = ACTIONS(97),
    [anon_sym_LPAREN] = ACTIONS(41),
    [anon_sym_RPAREN] = ACTIONS(99),
    [anon_sym_DOLLAR] = ACTIONS(43),
    [sym_comment] = ACTIONS(3),
    [sym__neg_number] = ACTIONS(49),
  },
  [10] = {
    [sym_number] = STATE(54),
    [sym_vector] = STATE(73),
    [sym_lambda] = STATE(73),
    [sym__expression] = STATE(73),
    [sym__literal_ref] = STATE(73),
    [sym_binary_expression] = STATE(73),
    [sym_call] = STATE(73),
    [sym_parenthesized] = STATE(73),
    [sym_list] = STATE(73),
    [sym_cond] = STATE(73),
    [aux_sym_list_repeat1] = STATE(99),
    [sym_identifier] = ACTIONS(91),
    [aux_sym_number_token1] = ACTIONS(29),
    [sym_boolean] = ACTIONS(101),
    [sym_byte] = ACTIONS(101),
    [sym_char] = ACTIONS(101),
    [sym_string] = ACTIONS(103),
    [sym_symbol] = ACTIONS(101),
    [sym_null] = ACTIONS(101),
    [sym_infinity] = ACTIONS(101),
    [sym_timestamp] = ACTIONS(101),
    [sym_datetime] = ACTIONS(101),
    [sym_date] = ACTIONS(103),
    [sym_month] = ACTIONS(101),
    [sym_timespan] = ACTIONS(101),
    [sym_time] = ACTIONS(103),
    [sym_second] = ACTIONS(103),
    [sym_minute] = ACTIONS(103),
    [sym_dotted_name] = ACTIONS(91),
    [anon_sym_LBRACE] = ACTIONS(35),
    [anon_sym_SEMI] = ACTIONS(97),
    [anon_sym_LPAREN] = ACTIONS(41),
    [anon_sym_RPAREN] = ACTIONS(105),
    [anon_sym_DOLLAR] = ACTIONS(43),
    [sym_comment] = ACTIONS(3),
    [sym__neg_number] = ACTIONS(49),
  },
  [11] = {
    [sym_number] = STATE(54),
    [sym_vector] = STATE(85),
    [sym_lambda] = STATE(85),
    [sym__expression] = STATE(85),
    [sym__literal_ref] = STATE(85),
    [sym_binary_expression] = STATE(85),
    [sym_call] = STATE(85),
    [sym_parenthesized] = STATE(85),
    [sym_list] = STATE(85),
    [sym_cond] = STATE(85),
    [sym_identifier] = ACTIONS(91),
    [aux_sym_number_token1] = ACTIONS(29),
    [sym_boolean] = ACTIONS(107),
    [sym_byte] = ACTIONS(107),
    [sym_char] = ACTIONS(107),
    [sym_string] = ACTIONS(109),
    [sym_symbol] = ACTIONS(107),
    [sym_null] = ACTIONS(107),
    [sym_infinity] = ACTIONS(107),
    [sym_timestamp] = ACTIONS(107),
    [sym_datetime] = ACTIONS(107),
    [sym_date] = ACTIONS(109),
    [sym_month] = ACTIONS(107),
    [sym_timespan] = ACTIONS(107),
    [sym_time] = ACTIONS(109),
    [sym_second] = ACTIONS(109),
    [sym_minute] = ACTIONS(109),
    [sym_dotted_name] = ACTIONS(91),
    [anon_sym_LBRACE] = ACTIONS(35),
    [anon_sym_SEMI] = ACTIONS(111),
    [anon_sym_LPAREN] = ACTIONS(41),
    [anon_sym_RPAREN] = ACTIONS(111),
    [anon_sym_DOLLAR] = ACTIONS(43),
    [sym_comment] = ACTIONS(3),
    [sym__neg_number] = ACTIONS(49),
  },
  [12] = {
    [sym_number] = STATE(54),
    [sym_vector] = STATE(78),
    [sym_lambda] = STATE(78),
    [sym__expression] = STATE(78),
    [sym__literal_ref] = STATE(78),
    [sym_binary_expression] = STATE(78),
    [sym_call] = STATE(78),
    [sym_parenthesized] = STATE(78),
    [sym_list] = STATE(78),
    [sym_cond] = STATE(78),
    [sym_identifier] = ACTIONS(91),
    [aux_sym_number_token1] = ACTIONS(29),
    [sym_boolean] = ACTIONS(113),
    [sym_byte] = ACTIONS(113),
    [sym_char] = ACTIONS(113),
    [sym_string] = ACTIONS(115),
    [sym_symbol] = ACTIONS(113),
    [sym_null] = ACTIONS(113),
    [sym_infinity] = ACTIONS(113),
    [sym_timestamp] = ACTIONS(113),
    [sym_datetime] = ACTIONS(113),
    [sym_date] = ACTIONS(115),
    [sym_month] = ACTIONS(113),
    [sym_timespan] = ACTIONS(113),
    [sym_time] = ACTIONS(115),
    [sym_second] = ACTIONS(115),
    [sym_minute] = ACTIONS(115),
    [sym_dotted_name] = ACTIONS(91),
    [anon_sym_LBRACE] = ACTIONS(35),
    [anon_sym_RBRACK] = ACTIONS(117),
    [anon_sym_LPAREN] = ACTIONS(41),
    [anon_sym_DOLLAR] = ACTIONS(43),
    [sym_comment] = ACTIONS(3),
    [sym__neg_number] = ACTIONS(49),
  },
  [13] = {
    [sym_number] = STATE(54),
    [sym_vector] = STATE(76),
    [sym_lambda] = STATE(76),
    [sym__expression] = STATE(76),
    [sym__literal_ref] = STATE(76),
    [sym_binary_expression] = STATE(76),
    [sym_call] = STATE(76),
    [sym_parenthesized] = STATE(76),
    [sym_list] = STATE(76),
    [sym_cond] = STATE(76),
    [sym_identifier] = ACTIONS(91),
    [aux_sym_number_token1] = ACTIONS(29),
    [sym_boolean] = ACTIONS(119),
    [sym_byte] = ACTIONS(119),
    [sym_char] = ACTIONS(119),
    [sym_string] = ACTIONS(121),
    [sym_symbol] = ACTIONS(119),
    [sym_null] = ACTIONS(119),
    [sym_infinity] = ACTIONS(119),
    [sym_timestamp] = ACTIONS(119),
    [sym_datetime] = ACTIONS(119),
    [sym_date] = ACTIONS(121),
    [sym_month] = ACTIONS(119),
    [sym_timespan] = ACTIONS(119),
    [sym_time] = ACTIONS(121),
    [sym_second] = ACTIONS(121),
    [sym_minute] = ACTIONS(121),
    [sym_dotted_name] = ACTIONS(91),
    [anon_sym_LBRACE] = ACTIONS(35),
    [anon_sym_RBRACK] = ACTIONS(123),
    [anon_sym_LPAREN] = ACTIONS(41),
    [anon_sym_DOLLAR] = ACTIONS(43),
    [sym_comment] = ACTIONS(3),
    [sym__neg_number] = ACTIONS(49),
  },
  [14] = {
    [sym_number] = STATE(54),
    [sym_vector] = STATE(93),
    [sym_lambda] = STATE(93),
    [sym__expression] = STATE(93),
    [sym__literal_ref] = STATE(93),
    [sym_binary_expression] = STATE(93),
    [sym_call] = STATE(93),
    [sym_parenthesized] = STATE(93),
    [sym_list] = STATE(93),
    [sym_cond] = STATE(93),
    [sym_identifier] = ACTIONS(91),
    [aux_sym_number_token1] = ACTIONS(29),
    [sym_boolean] = ACTIONS(125),
    [sym_byte] = ACTIONS(125),
    [sym_char] = ACTIONS(125),
    [sym_string] = ACTIONS(127),
    [sym_symbol] = ACTIONS(125),
    [sym_null] = ACTIONS(125),
    [sym_infinity] = ACTIONS(125),
    [sym_timestamp] = ACTIONS(125),
    [sym_datetime] = ACTIONS(125),
    [sym_date] = ACTIONS(127),
    [sym_month] = ACTIONS(125),
    [sym_timespan] = ACTIONS(125),
    [sym_time] = ACTIONS(127),
    [sym_second] = ACTIONS(127),
    [sym_minute] = ACTIONS(127),
    [sym_dotted_name] = ACTIONS(91),
    [anon_sym_LBRACE] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(41),
    [anon_sym_DOLLAR] = ACTIONS(43),
    [sym_comment] = ACTIONS(3),
    [sym__neg_number] = ACTIONS(49),
  },
  [15] = {
    [sym_number] = STATE(54),
    [sym_vector] = STATE(75),
    [sym_lambda] = STATE(75),
    [sym__expression] = STATE(75),
    [sym__literal_ref] = STATE(75),
    [sym_binary_expression] = STATE(75),
    [sym_call] = STATE(75),
    [sym_parenthesized] = STATE(75),
    [sym_list] = STATE(75),
    [sym_cond] = STATE(75),
    [sym_identifier] = ACTIONS(91),
    [aux_sym_number_token1] = ACTIONS(29),
    [sym_boolean] = ACTIONS(129),
    [sym_byte] = ACTIONS(129),
    [sym_char] = ACTIONS(129),
    [sym_string] = ACTIONS(131),
    [sym_symbol] = ACTIONS(129),
    [sym_null] = ACTIONS(129),
    [sym_infinity] = ACTIONS(129),
    [sym_timestamp] = ACTIONS(129),
    [sym_datetime] = ACTIONS(129),
    [sym_date] = ACTIONS(131),
    [sym_month] = ACTIONS(129),
    [sym_timespan] = ACTIONS(129),
    [sym_time] = ACTIONS(131),
    [sym_second] = ACTIONS(131),
    [sym_minute] = ACTIONS(131),
    [sym_dotted_name] = ACTIONS(91),
    [anon_sym_LBRACE] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(41),
    [anon_sym_DOLLAR] = ACTIONS(43),
    [sym_comment] = ACTIONS(3),
    [sym__neg_number] = ACTIONS(49),
  },
  [16] = {
    [sym_number] = STATE(54),
    [sym_vector] = STATE(82),
    [sym_lambda] = STATE(82),
    [sym__expression] = STATE(82),
    [sym__literal_ref] = STATE(82),
    [sym_binary_expression] = STATE(82),
    [sym_call] = STATE(82),
    [sym_parenthesized] = STATE(82),
    [sym_list] = STATE(82),
    [sym_cond] = STATE(82),
    [sym_identifier] = ACTIONS(91),
    [aux_sym_number_token1] = ACTIONS(29),
    [sym_boolean] = ACTIONS(133),
    [sym_byte] = ACTIONS(133),
    [sym_char] = ACTIONS(133),
    [sym_string] = ACTIONS(135),
    [sym_symbol] = ACTIONS(133),
    [sym_null] = ACTIONS(133),
    [sym_infinity] = ACTIONS(133),
    [sym_timestamp] = ACTIONS(133),
    [sym_datetime] = ACTIONS(133),
    [sym_date] = ACTIONS(135),
    [sym_month] = ACTIONS(133),
    [sym_timespan] = ACTIONS(133),
    [sym_time] = ACTIONS(135),
    [sym_second] = ACTIONS(135),
    [sym_minute] = ACTIONS(135),
    [sym_dotted_name] = ACTIONS(91),
    [anon_sym_LBRACE] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(41),
    [anon_sym_DOLLAR] = ACTIONS(43),
    [sym_comment] = ACTIONS(3),
    [sym__neg_number] = ACTIONS(49),
  },
  [17] = {
    [sym_number] = STATE(54),
    [sym_vector] = STATE(66),
    [sym_lambda] = STATE(66),
    [sym__expression] = STATE(66),
    [sym__literal_ref] = STATE(66),
    [sym_binary_expression] = STATE(66),
    [sym_call] = STATE(66),
    [sym_parenthesized] = STATE(66),
    [sym_list] = STATE(66),
    [sym_cond] = STATE(66),
    [sym_identifier] = ACTIONS(91),
    [aux_sym_number_token1] = ACTIONS(29),
    [sym_boolean] = ACTIONS(137),
    [sym_byte] = ACTIONS(137),
    [sym_char] = ACTIONS(137),
    [sym_string] = ACTIONS(139),
    [sym_symbol] = ACTIONS(137),
    [sym_null] = ACTIONS(137),
    [sym_infinity] = ACTIONS(137),
    [sym_timestamp] = ACTIONS(137),
    [sym_datetime] = ACTIONS(137),
    [sym_date] = ACTIONS(139),
    [sym_month] = ACTIONS(137),
    [sym_timespan] = ACTIONS(137),
    [sym_time] = ACTIONS(139),
    [sym_second] = ACTIONS(139),
    [sym_minute] = ACTIONS(139),
    [sym_dotted_name] = ACTIONS(91),
    [anon_sym_LBRACE] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(41),
    [anon_sym_DOLLAR] = ACTIONS(43),
    [sym_comment] = ACTIONS(3),
    [sym__neg_number] = ACTIONS(49),
  },
  [18] = {
    [sym_number] = STATE(24),
    [sym_vector] = STATE(39),
    [sym_lambda] = STATE(39),
    [sym__expression] = STATE(39),
    [sym__literal_ref] = STATE(39),
    [sym_binary_expression] = STATE(39),
    [sym_call] = STATE(39),
    [sym_parenthesized] = STATE(39),
    [sym_list] = STATE(39),
    [sym_cond] = STATE(39),
    [sym_identifier] = ACTIONS(141),
    [aux_sym_number_token1] = ACTIONS(9),
    [sym_boolean] = ACTIONS(143),
    [sym_byte] = ACTIONS(143),
    [sym_char] = ACTIONS(143),
    [sym_string] = ACTIONS(145),
    [sym_symbol] = ACTIONS(143),
    [sym_null] = ACTIONS(143),
    [sym_infinity] = ACTIONS(143),
    [sym_timestamp] = ACTIONS(143),
    [sym_datetime] = ACTIONS(143),
    [sym_date] = ACTIONS(145),
    [sym_month] = ACTIONS(143),
    [sym_timespan] = ACTIONS(143),
    [sym_time] = ACTIONS(145),
    [sym_second] = ACTIONS(145),
    [sym_minute] = ACTIONS(145),
    [sym_dotted_name] = ACTIONS(141),
    [anon_sym_LBRACE] = ACTIONS(15),
    [anon_sym_LPAREN] = ACTIONS(17),
    [anon_sym_DOLLAR] = ACTIONS(19),
    [sym_comment] = ACTIONS(3),
    [sym__neg_number] = ACTIONS(25),
  },
  [19] = {
    [sym_number] = STATE(24),
    [sym_vector] = STATE(44),
    [sym_lambda] = STATE(44),
    [sym__expression] = STATE(44),
    [sym__literal_ref] = STATE(44),
    [sym_binary_expression] = STATE(44),
    [sym_call] = STATE(44),
    [sym_parenthesized] = STATE(44),
    [sym_list] = STATE(44),
    [sym_cond] = STATE(44),
    [sym_identifier] = ACTIONS(141),
    [aux_sym_number_token1] = ACTIONS(9),
    [sym_boolean] = ACTIONS(147),
    [sym_byte] = ACTIONS(147),
    [sym_char] = ACTIONS(147),
    [sym_string] = ACTIONS(149),
    [sym_symbol] = ACTIONS(147),
    [sym_null] = ACTIONS(147),
    [sym_infinity] = ACTIONS(147),
    [sym_timestamp] = ACTIONS(147),
    [sym_datetime] = ACTIONS(147),
    [sym_date] = ACTIONS(149),
    [sym_month] = ACTIONS(147),
    [sym_timespan] = ACTIONS(147),
    [sym_time] = ACTIONS(149),
    [sym_second] = ACTIONS(149),
    [sym_minute] = ACTIONS(149),
    [sym_dotted_name] = ACTIONS(141),
    [anon_sym_LBRACE] = ACTIONS(15),
    [anon_sym_LPAREN] = ACTIONS(17),
    [anon_sym_DOLLAR] = ACTIONS(19),
    [sym_comment] = ACTIONS(3),
    [sym__neg_number] = ACTIONS(25),
  },
  [20] = {
    [sym_number] = STATE(54),
    [sym_vector] = STATE(94),
    [sym_lambda] = STATE(94),
    [sym__expression] = STATE(94),
    [sym__literal_ref] = STATE(94),
    [sym_binary_expression] = STATE(94),
    [sym_call] = STATE(94),
    [sym_parenthesized] = STATE(94),
    [sym_list] = STATE(94),
    [sym_cond] = STATE(94),
    [sym_identifier] = ACTIONS(91),
    [aux_sym_number_token1] = ACTIONS(29),
    [sym_boolean] = ACTIONS(151),
    [sym_byte] = ACTIONS(151),
    [sym_char] = ACTIONS(151),
    [sym_string] = ACTIONS(153),
    [sym_symbol] = ACTIONS(151),
    [sym_null] = ACTIONS(151),
    [sym_infinity] = ACTIONS(151),
    [sym_timestamp] = ACTIONS(151),
    [sym_datetime] = ACTIONS(151),
    [sym_date] = ACTIONS(153),
    [sym_month] = ACTIONS(151),
    [sym_timespan] = ACTIONS(151),
    [sym_time] = ACTIONS(153),
    [sym_second] = ACTIONS(153),
    [sym_minute] = ACTIONS(153),
    [sym_dotted_name] = ACTIONS(91),
    [anon_sym_LBRACE] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(41),
    [anon_sym_DOLLAR] = ACTIONS(43),
    [sym_comment] = ACTIONS(3),
    [sym__neg_number] = ACTIONS(49),
  },
  [21] = {
    [sym_number] = STATE(54),
    [sym_vector] = STATE(98),
    [sym_lambda] = STATE(98),
    [sym__expression] = STATE(98),
    [sym__literal_ref] = STATE(98),
    [sym_binary_expression] = STATE(98),
    [sym_call] = STATE(98),
    [sym_parenthesized] = STATE(98),
    [sym_list] = STATE(98),
    [sym_cond] = STATE(98),
    [sym_identifier] = ACTIONS(91),
    [aux_sym_number_token1] = ACTIONS(29),
    [sym_boolean] = ACTIONS(155),
    [sym_byte] = ACTIONS(155),
    [sym_char] = ACTIONS(155),
    [sym_string] = ACTIONS(157),
    [sym_symbol] = ACTIONS(155),
    [sym_null] = ACTIONS(155),
    [sym_infinity] = ACTIONS(155),
    [sym_timestamp] = ACTIONS(155),
    [sym_datetime] = ACTIONS(155),
    [sym_date] = ACTIONS(157),
    [sym_month] = ACTIONS(155),
    [sym_timespan] = ACTIONS(155),
    [sym_time] = ACTIONS(157),
    [sym_second] = ACTIONS(157),
    [sym_minute] = ACTIONS(157),
    [sym_dotted_name] = ACTIONS(91),
    [anon_sym_LBRACE] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(41),
    [anon_sym_DOLLAR] = ACTIONS(43),
    [sym_comment] = ACTIONS(3),
    [sym__neg_number] = ACTIONS(49),
  },
  [22] = {
    [sym_number] = STATE(54),
    [sym_vector] = STATE(74),
    [sym_lambda] = STATE(74),
    [sym__expression] = STATE(74),
    [sym__literal_ref] = STATE(74),
    [sym_binary_expression] = STATE(74),
    [sym_call] = STATE(74),
    [sym_parenthesized] = STATE(74),
    [sym_list] = STATE(74),
    [sym_cond] = STATE(74),
    [sym_identifier] = ACTIONS(91),
    [aux_sym_number_token1] = ACTIONS(29),
    [sym_boolean] = ACTIONS(159),
    [sym_byte] = ACTIONS(159),
    [sym_char] = ACTIONS(159),
    [sym_string] = ACTIONS(161),
    [sym_symbol] = ACTIONS(159),
    [sym_null] = ACTIONS(159),
    [sym_infinity] = ACTIONS(159),
    [sym_timestamp] = ACTIONS(159),
    [sym_datetime] = ACTIONS(159),
    [sym_date] = ACTIONS(161),
    [sym_month] = ACTIONS(159),
    [sym_timespan] = ACTIONS(159),
    [sym_time] = ACTIONS(161),
    [sym_second] = ACTIONS(161),
    [sym_minute] = ACTIONS(161),
    [sym_dotted_name] = ACTIONS(91),
    [anon_sym_LBRACE] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(41),
    [anon_sym_DOLLAR] = ACTIONS(43),
    [sym_comment] = ACTIONS(3),
    [sym__neg_number] = ACTIONS(49),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(167), 1,
      anon_sym_COLON_COLON,
    ACTIONS(169), 1,
      anon_sym_COLON,
    ACTIONS(171), 1,
      anon_sym_LBRACK,
    ACTIONS(165), 7,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
      sym_operator,
    ACTIONS(163), 20,
      sym__system_command_tok,
      sym__neg_number,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [44] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(9), 1,
      aux_sym_number_token1,
    ACTIONS(25), 1,
      sym__neg_number,
    STATE(25), 2,
      sym_number,
      aux_sym_vector_repeat1,
    ACTIONS(165), 6,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
      sym_operator,
    ACTIONS(163), 19,
      sym__system_command_tok,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [87] = 4,
    ACTIONS(3), 1,
      sym_comment,
    STATE(26), 2,
      sym_number,
      aux_sym_vector_repeat1,
    ACTIONS(175), 7,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
      sym_operator,
    ACTIONS(173), 20,
      sym__system_command_tok,
      sym__neg_number,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [126] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(179), 1,
      aux_sym_number_token1,
    ACTIONS(184), 1,
      sym__neg_number,
    STATE(26), 2,
      sym_number,
      aux_sym_vector_repeat1,
    ACTIONS(182), 6,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
      sym_operator,
    ACTIONS(177), 19,
      sym__system_command_tok,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [169] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(171), 1,
      anon_sym_LBRACK,
    ACTIONS(165), 7,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
      sym_operator,
    ACTIONS(163), 20,
      sym__system_command_tok,
      sym__neg_number,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [207] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(189), 7,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
      sym_operator,
    ACTIONS(187), 20,
      sym__system_command_tok,
      sym__neg_number,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [242] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(193), 7,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
      sym_operator,
    ACTIONS(191), 20,
      sym__system_command_tok,
      sym__neg_number,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [277] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(197), 7,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
      sym_operator,
    ACTIONS(195), 20,
      sym__system_command_tok,
      sym__neg_number,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [312] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(201), 7,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
      sym_operator,
    ACTIONS(199), 20,
      sym__system_command_tok,
      sym__neg_number,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [347] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(205), 7,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
      sym_operator,
    ACTIONS(203), 20,
      sym__system_command_tok,
      sym__neg_number,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [382] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(209), 7,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
      sym_operator,
    ACTIONS(207), 20,
      sym__system_command_tok,
      sym__neg_number,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [417] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(213), 7,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
      sym_operator,
    ACTIONS(211), 20,
      sym__system_command_tok,
      sym__neg_number,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [452] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(217), 7,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
      sym_operator,
    ACTIONS(215), 20,
      sym__system_command_tok,
      sym__neg_number,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [487] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(221), 7,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
      sym_operator,
    ACTIONS(219), 20,
      sym__system_command_tok,
      sym__neg_number,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [522] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(225), 7,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
      sym_operator,
    ACTIONS(223), 20,
      sym__system_command_tok,
      sym__neg_number,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [557] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(229), 7,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
      sym_operator,
    ACTIONS(227), 20,
      sym__system_command_tok,
      sym__neg_number,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [592] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(235), 1,
      sym_operator,
    ACTIONS(233), 6,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
    ACTIONS(231), 20,
      sym__system_command_tok,
      sym__neg_number,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [629] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(239), 7,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
      sym_operator,
    ACTIONS(237), 20,
      sym__system_command_tok,
      sym__neg_number,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [664] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(243), 7,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
      sym_operator,
    ACTIONS(241), 20,
      sym__system_command_tok,
      sym__neg_number,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [699] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(247), 7,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
      sym_operator,
    ACTIONS(245), 20,
      sym__system_command_tok,
      sym__neg_number,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [734] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(235), 1,
      sym_operator,
    ACTIONS(251), 6,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
    ACTIONS(249), 20,
      sym__system_command_tok,
      sym__neg_number,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [771] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(255), 7,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
      sym_operator,
    ACTIONS(253), 20,
      sym__system_command_tok,
      sym__neg_number,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [806] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(259), 6,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
    ACTIONS(257), 20,
      sym__system_command_tok,
      sym__neg_number,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [840] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(265), 1,
      sym_dotted_name,
    ACTIONS(263), 6,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
    ACTIONS(261), 19,
      sym__system_command_tok,
      sym__neg_number,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [876] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(269), 6,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
    ACTIONS(267), 20,
      sym__system_command_tok,
      sym__neg_number,
      sym__eos,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [910] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(275), 1,
      sym__eos,
    ACTIONS(273), 6,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
    ACTIONS(271), 19,
      sym__system_command_tok,
      sym__neg_number,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [946] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(279), 6,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
    ACTIONS(277), 19,
      sym__system_command_tok,
      sym__neg_number,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [979] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(283), 6,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
    ACTIONS(281), 19,
      sym__system_command_tok,
      sym__neg_number,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [1012] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(285), 6,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
    ACTIONS(57), 19,
      sym__system_command_tok,
      sym__neg_number,
      ts_builtin_sym_end,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [1045] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(289), 6,
      aux_sym_number_token1,
      sym_string,
      sym_date,
      sym_time,
      sym_second,
      sym_minute,
    ACTIONS(287), 19,
      sym__system_command_tok,
      sym__neg_number,
      sym_boolean,
      sym_byte,
      sym_char,
      sym_symbol,
      sym_null,
      sym_infinity,
      sym_timestamp,
      sym_datetime,
      sym_month,
      sym_timespan,
      sym_identifier,
      sym_dotted_name,
      anon_sym_LBRACE,
      anon_sym_RBRACE,
      anon_sym_LPAREN,
      anon_sym_DOLLAR,
      anon_sym_BSLASHd,
  [1078] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(291), 2,
      sym__neg_number,
      aux_sym_number_token1,
    STATE(53), 2,
      sym_number,
      aux_sym_vector_repeat1,
    ACTIONS(177), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1097] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(49), 2,
      sym__neg_number,
      aux_sym_number_token1,
    STATE(55), 2,
      sym_number,
      aux_sym_vector_repeat1,
    ACTIONS(163), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1116] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(49), 2,
      sym__neg_number,
      aux_sym_number_token1,
    STATE(53), 2,
      sym_number,
      aux_sym_vector_repeat1,
    ACTIONS(173), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1135] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(195), 7,
      sym__neg_number,
      aux_sym_number_token1,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1148] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(294), 1,
      anon_sym_LBRACK,
    ACTIONS(163), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1162] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(294), 1,
      anon_sym_LBRACK,
    ACTIONS(296), 1,
      anon_sym_COLON_COLON,
    ACTIONS(298), 1,
      anon_sym_COLON,
    ACTIONS(163), 3,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      sym_operator,
  [1180] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(219), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1191] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(215), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1202] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(223), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1213] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(227), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1224] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(237), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1235] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(241), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1246] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(245), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1257] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(253), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1268] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(187), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1279] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(191), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1290] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(199), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1301] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(203), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1312] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(207), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1323] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(211), 5,
      anon_sym_RBRACE,
      anon_sym_SEMI,
      anon_sym_RBRACK,
      sym_operator,
      anon_sym_RPAREN,
  [1334] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(97), 1,
      anon_sym_SEMI,
    ACTIONS(300), 1,
      sym_operator,
    ACTIONS(302), 1,
      anon_sym_RPAREN,
    STATE(101), 1,
      aux_sym_list_repeat1,
  [1350] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(300), 1,
      sym_operator,
    ACTIONS(304), 1,
      anon_sym_SEMI,
    ACTIONS(306), 1,
      anon_sym_RBRACK,
    STATE(100), 1,
      aux_sym_call_repeat1,
  [1366] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(300), 1,
      sym_operator,
    ACTIONS(304), 1,
      anon_sym_SEMI,
    ACTIONS(308), 1,
      anon_sym_RBRACK,
    STATE(80), 1,
      aux_sym_call_repeat1,
  [1382] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(300), 1,
      sym_operator,
    ACTIONS(304), 1,
      anon_sym_SEMI,
    ACTIONS(310), 1,
      anon_sym_RBRACK,
    STATE(87), 1,
      aux_sym_call_repeat1,
  [1398] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(97), 1,
      anon_sym_SEMI,
    ACTIONS(300), 1,
      sym_operator,
    ACTIONS(312), 1,
      anon_sym_RPAREN,
    STATE(88), 1,
      aux_sym_list_repeat1,
  [1414] = 5,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(300), 1,
      sym_operator,
    ACTIONS(304), 1,
      anon_sym_SEMI,
    ACTIONS(314), 1,
      anon_sym_RBRACK,
    STATE(97), 1,
      aux_sym_call_repeat1,
  [1430] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(316), 1,
      sym_identifier,
    ACTIONS(318), 1,
      anon_sym_RBRACK,
    STATE(91), 1,
      sym_param,
  [1443] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(304), 1,
      anon_sym_SEMI,
    ACTIONS(320), 1,
      anon_sym_RBRACK,
    STATE(95), 1,
      aux_sym_call_repeat1,
  [1456] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(322), 1,
      anon_sym_SEMI,
    ACTIONS(324), 1,
      anon_sym_RBRACK,
    STATE(84), 1,
      aux_sym_parameters_repeat1,
  [1469] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(300), 1,
      sym_operator,
    ACTIONS(231), 2,
      anon_sym_RBRACE,
      anon_sym_SEMI,
  [1480] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(326), 1,
      anon_sym_RBRACE,
    ACTIONS(328), 1,
      anon_sym_SEMI,
    STATE(92), 1,
      aux_sym__lambda_body_repeat1,
  [1493] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(330), 1,
      anon_sym_SEMI,
    ACTIONS(333), 1,
      anon_sym_RBRACK,
    STATE(84), 1,
      aux_sym_parameters_repeat1,
  [1506] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(300), 1,
      sym_operator,
    ACTIONS(335), 2,
      anon_sym_SEMI,
      anon_sym_RPAREN,
  [1517] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(337), 1,
      anon_sym_RBRACE,
    ACTIONS(339), 1,
      anon_sym_SEMI,
    STATE(86), 1,
      aux_sym__lambda_body_repeat1,
  [1530] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(304), 1,
      anon_sym_SEMI,
    ACTIONS(342), 1,
      anon_sym_RBRACK,
    STATE(95), 1,
      aux_sym_call_repeat1,
  [1543] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(97), 1,
      anon_sym_SEMI,
    ACTIONS(344), 1,
      anon_sym_RPAREN,
    STATE(89), 1,
      aux_sym_list_repeat1,
  [1556] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(335), 1,
      anon_sym_RPAREN,
    ACTIONS(346), 1,
      anon_sym_SEMI,
    STATE(89), 1,
      aux_sym_list_repeat1,
  [1569] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(300), 1,
      sym_operator,
    ACTIONS(249), 2,
      anon_sym_RBRACE,
      anon_sym_SEMI,
  [1580] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(322), 1,
      anon_sym_SEMI,
    ACTIONS(349), 1,
      anon_sym_RBRACK,
    STATE(81), 1,
      aux_sym_parameters_repeat1,
  [1593] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(328), 1,
      anon_sym_SEMI,
    ACTIONS(351), 1,
      anon_sym_RBRACE,
    STATE(86), 1,
      aux_sym__lambda_body_repeat1,
  [1606] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(300), 1,
      sym_operator,
    ACTIONS(353), 1,
      anon_sym_SEMI,
    ACTIONS(355), 1,
      anon_sym_RPAREN,
  [1619] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(300), 1,
      sym_operator,
    ACTIONS(357), 1,
      anon_sym_SEMI,
    ACTIONS(359), 1,
      anon_sym_RPAREN,
  [1632] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(361), 1,
      anon_sym_SEMI,
    ACTIONS(364), 1,
      anon_sym_RBRACK,
    STATE(95), 1,
      aux_sym_call_repeat1,
  [1645] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(97), 1,
      anon_sym_SEMI,
    ACTIONS(312), 1,
      anon_sym_RPAREN,
    STATE(89), 1,
      aux_sym_list_repeat1,
  [1658] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(304), 1,
      anon_sym_SEMI,
    ACTIONS(366), 1,
      anon_sym_RBRACK,
    STATE(95), 1,
      aux_sym_call_repeat1,
  [1671] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(300), 1,
      sym_operator,
    ACTIONS(364), 2,
      anon_sym_SEMI,
      anon_sym_RBRACK,
  [1682] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(97), 1,
      anon_sym_SEMI,
    ACTIONS(302), 1,
      anon_sym_RPAREN,
    STATE(89), 1,
      aux_sym_list_repeat1,
  [1695] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(304), 1,
      anon_sym_SEMI,
    ACTIONS(368), 1,
      anon_sym_RBRACK,
    STATE(95), 1,
      aux_sym_call_repeat1,
  [1708] = 4,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(97), 1,
      anon_sym_SEMI,
    ACTIONS(370), 1,
      anon_sym_RPAREN,
    STATE(89), 1,
      aux_sym_list_repeat1,
  [1721] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(372), 1,
      sym_dotted_name,
    ACTIONS(261), 2,
      anon_sym_RBRACE,
      anon_sym_SEMI,
  [1732] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(267), 2,
      anon_sym_RBRACE,
      anon_sym_SEMI,
  [1740] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(316), 1,
      sym_identifier,
    STATE(105), 1,
      sym_param,
  [1750] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(374), 2,
      anon_sym_SEMI,
      anon_sym_RBRACK,
  [1758] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(337), 2,
      anon_sym_RBRACE,
      anon_sym_SEMI,
  [1766] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(257), 2,
      anon_sym_RBRACE,
      anon_sym_SEMI,
  [1774] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(376), 2,
      anon_sym_SEMI,
      anon_sym_RBRACK,
  [1782] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(378), 1,
      anon_sym_LBRACK,
  [1789] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(380), 1,
      anon_sym_RBRACE,
  [1796] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(382), 1,
      anon_sym_RBRACE,
  [1803] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(384), 1,
      anon_sym_RBRACE,
  [1810] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(386), 1,
      anon_sym_RBRACE,
  [1817] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(388), 1,
      ts_builtin_sym_end,
  [1824] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(390), 1,
      anon_sym_LBRACK,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(23)] = 0,
  [SMALL_STATE(24)] = 44,
  [SMALL_STATE(25)] = 87,
  [SMALL_STATE(26)] = 126,
  [SMALL_STATE(27)] = 169,
  [SMALL_STATE(28)] = 207,
  [SMALL_STATE(29)] = 242,
  [SMALL_STATE(30)] = 277,
  [SMALL_STATE(31)] = 312,
  [SMALL_STATE(32)] = 347,
  [SMALL_STATE(33)] = 382,
  [SMALL_STATE(34)] = 417,
  [SMALL_STATE(35)] = 452,
  [SMALL_STATE(36)] = 487,
  [SMALL_STATE(37)] = 522,
  [SMALL_STATE(38)] = 557,
  [SMALL_STATE(39)] = 592,
  [SMALL_STATE(40)] = 629,
  [SMALL_STATE(41)] = 664,
  [SMALL_STATE(42)] = 699,
  [SMALL_STATE(43)] = 734,
  [SMALL_STATE(44)] = 771,
  [SMALL_STATE(45)] = 806,
  [SMALL_STATE(46)] = 840,
  [SMALL_STATE(47)] = 876,
  [SMALL_STATE(48)] = 910,
  [SMALL_STATE(49)] = 946,
  [SMALL_STATE(50)] = 979,
  [SMALL_STATE(51)] = 1012,
  [SMALL_STATE(52)] = 1045,
  [SMALL_STATE(53)] = 1078,
  [SMALL_STATE(54)] = 1097,
  [SMALL_STATE(55)] = 1116,
  [SMALL_STATE(56)] = 1135,
  [SMALL_STATE(57)] = 1148,
  [SMALL_STATE(58)] = 1162,
  [SMALL_STATE(59)] = 1180,
  [SMALL_STATE(60)] = 1191,
  [SMALL_STATE(61)] = 1202,
  [SMALL_STATE(62)] = 1213,
  [SMALL_STATE(63)] = 1224,
  [SMALL_STATE(64)] = 1235,
  [SMALL_STATE(65)] = 1246,
  [SMALL_STATE(66)] = 1257,
  [SMALL_STATE(67)] = 1268,
  [SMALL_STATE(68)] = 1279,
  [SMALL_STATE(69)] = 1290,
  [SMALL_STATE(70)] = 1301,
  [SMALL_STATE(71)] = 1312,
  [SMALL_STATE(72)] = 1323,
  [SMALL_STATE(73)] = 1334,
  [SMALL_STATE(74)] = 1350,
  [SMALL_STATE(75)] = 1366,
  [SMALL_STATE(76)] = 1382,
  [SMALL_STATE(77)] = 1398,
  [SMALL_STATE(78)] = 1414,
  [SMALL_STATE(79)] = 1430,
  [SMALL_STATE(80)] = 1443,
  [SMALL_STATE(81)] = 1456,
  [SMALL_STATE(82)] = 1469,
  [SMALL_STATE(83)] = 1480,
  [SMALL_STATE(84)] = 1493,
  [SMALL_STATE(85)] = 1506,
  [SMALL_STATE(86)] = 1517,
  [SMALL_STATE(87)] = 1530,
  [SMALL_STATE(88)] = 1543,
  [SMALL_STATE(89)] = 1556,
  [SMALL_STATE(90)] = 1569,
  [SMALL_STATE(91)] = 1580,
  [SMALL_STATE(92)] = 1593,
  [SMALL_STATE(93)] = 1606,
  [SMALL_STATE(94)] = 1619,
  [SMALL_STATE(95)] = 1632,
  [SMALL_STATE(96)] = 1645,
  [SMALL_STATE(97)] = 1658,
  [SMALL_STATE(98)] = 1671,
  [SMALL_STATE(99)] = 1682,
  [SMALL_STATE(100)] = 1695,
  [SMALL_STATE(101)] = 1708,
  [SMALL_STATE(102)] = 1721,
  [SMALL_STATE(103)] = 1732,
  [SMALL_STATE(104)] = 1740,
  [SMALL_STATE(105)] = 1750,
  [SMALL_STATE(106)] = 1758,
  [SMALL_STATE(107)] = 1766,
  [SMALL_STATE(108)] = 1774,
  [SMALL_STATE(109)] = 1782,
  [SMALL_STATE(110)] = 1789,
  [SMALL_STATE(111)] = 1796,
  [SMALL_STATE(112)] = 1803,
  [SMALL_STATE(113)] = 1810,
  [SMALL_STATE(114)] = 1817,
  [SMALL_STATE(115)] = 1824,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 0, 0, 0),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [9] = {.entry = {.count = 1, .reusable = false}}, SHIFT(30),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(43),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(43),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(2),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(14),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(109),
  [21] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [23] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
  [25] = {.entry = {.count = 1, .reusable = true}}, SHIFT(30),
  [27] = {.entry = {.count = 1, .reusable = true}}, SHIFT(58),
  [29] = {.entry = {.count = 1, .reusable = false}}, SHIFT(56),
  [31] = {.entry = {.count = 1, .reusable = true}}, SHIFT(90),
  [33] = {.entry = {.count = 1, .reusable = false}}, SHIFT(90),
  [35] = {.entry = {.count = 1, .reusable = true}}, SHIFT(3),
  [37] = {.entry = {.count = 1, .reusable = true}}, SHIFT(37),
  [39] = {.entry = {.count = 1, .reusable = true}}, SHIFT(79),
  [41] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [43] = {.entry = {.count = 1, .reusable = true}}, SHIFT(115),
  [45] = {.entry = {.count = 1, .reusable = true}}, SHIFT(102),
  [47] = {.entry = {.count = 1, .reusable = true}}, SHIFT(107),
  [49] = {.entry = {.count = 1, .reusable = true}}, SHIFT(56),
  [51] = {.entry = {.count = 1, .reusable = true}}, SHIFT(61),
  [53] = {.entry = {.count = 1, .reusable = true}}, SHIFT(41),
  [55] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_source_file, 1, 0, 0),
  [57] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0),
  [59] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(23),
  [62] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(30),
  [65] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(43),
  [68] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(43),
  [71] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(2),
  [74] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(14),
  [77] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(109),
  [80] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(46),
  [83] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(45),
  [86] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0), SHIFT_REPEAT(30),
  [89] = {.entry = {.count = 1, .reusable = true}}, SHIFT(64),
  [91] = {.entry = {.count = 1, .reusable = true}}, SHIFT(57),
  [93] = {.entry = {.count = 1, .reusable = true}}, SHIFT(77),
  [95] = {.entry = {.count = 1, .reusable = false}}, SHIFT(77),
  [97] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [99] = {.entry = {.count = 1, .reusable = true}}, SHIFT(31),
  [101] = {.entry = {.count = 1, .reusable = true}}, SHIFT(73),
  [103] = {.entry = {.count = 1, .reusable = false}}, SHIFT(73),
  [105] = {.entry = {.count = 1, .reusable = true}}, SHIFT(69),
  [107] = {.entry = {.count = 1, .reusable = true}}, SHIFT(85),
  [109] = {.entry = {.count = 1, .reusable = false}}, SHIFT(85),
  [111] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_list_repeat1, 1, 0, 0),
  [113] = {.entry = {.count = 1, .reusable = true}}, SHIFT(78),
  [115] = {.entry = {.count = 1, .reusable = false}}, SHIFT(78),
  [117] = {.entry = {.count = 1, .reusable = true}}, SHIFT(62),
  [119] = {.entry = {.count = 1, .reusable = true}}, SHIFT(76),
  [121] = {.entry = {.count = 1, .reusable = false}}, SHIFT(76),
  [123] = {.entry = {.count = 1, .reusable = true}}, SHIFT(38),
  [125] = {.entry = {.count = 1, .reusable = true}}, SHIFT(93),
  [127] = {.entry = {.count = 1, .reusable = false}}, SHIFT(93),
  [129] = {.entry = {.count = 1, .reusable = true}}, SHIFT(75),
  [131] = {.entry = {.count = 1, .reusable = false}}, SHIFT(75),
  [133] = {.entry = {.count = 1, .reusable = true}}, SHIFT(82),
  [135] = {.entry = {.count = 1, .reusable = false}}, SHIFT(82),
  [137] = {.entry = {.count = 1, .reusable = true}}, SHIFT(66),
  [139] = {.entry = {.count = 1, .reusable = false}}, SHIFT(66),
  [141] = {.entry = {.count = 1, .reusable = true}}, SHIFT(27),
  [143] = {.entry = {.count = 1, .reusable = true}}, SHIFT(39),
  [145] = {.entry = {.count = 1, .reusable = false}}, SHIFT(39),
  [147] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [149] = {.entry = {.count = 1, .reusable = false}}, SHIFT(44),
  [151] = {.entry = {.count = 1, .reusable = true}}, SHIFT(94),
  [153] = {.entry = {.count = 1, .reusable = false}}, SHIFT(94),
  [155] = {.entry = {.count = 1, .reusable = true}}, SHIFT(98),
  [157] = {.entry = {.count = 1, .reusable = false}}, SHIFT(98),
  [159] = {.entry = {.count = 1, .reusable = true}}, SHIFT(74),
  [161] = {.entry = {.count = 1, .reusable = false}}, SHIFT(74),
  [163] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__literal_ref, 1, 0, 0),
  [165] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__literal_ref, 1, 0, 0),
  [167] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [169] = {.entry = {.count = 1, .reusable = false}}, SHIFT(18),
  [171] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [173] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_vector, 2, 0, 0),
  [175] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_vector, 2, 0, 0),
  [177] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_vector_repeat1, 2, 0, 0),
  [179] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_vector_repeat1, 2, 0, 0), SHIFT_REPEAT(30),
  [182] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_vector_repeat1, 2, 0, 0),
  [184] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_vector_repeat1, 2, 0, 0), SHIFT_REPEAT(30),
  [187] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call, 4, 0, 7),
  [189] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_call, 4, 0, 7),
  [191] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_lambda, 4, 0, 9),
  [193] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_lambda, 4, 0, 9),
  [195] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_number, 1, 0, 0),
  [197] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_number, 1, 0, 0),
  [199] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list, 4, 0, 0),
  [201] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_list, 4, 0, 0),
  [203] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cond, 4, 0, 0),
  [205] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cond, 4, 0, 0),
  [207] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call, 5, 0, 10),
  [209] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_call, 5, 0, 10),
  [211] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list, 5, 0, 0),
  [213] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_list, 5, 0, 0),
  [215] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_cond, 5, 0, 0),
  [217] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_cond, 5, 0, 0),
  [219] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_list, 6, 0, 0),
  [221] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_list, 6, 0, 0),
  [223] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_lambda, 2, 0, 0),
  [225] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_lambda, 2, 0, 0),
  [227] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_call, 3, 0, 4),
  [229] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_call, 3, 0, 4),
  [231] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_assignment, 3, 0, 3),
  [233] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_assignment, 3, 0, 3),
  [235] = {.entry = {.count = 1, .reusable = false}}, SHIFT(19),
  [237] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_lambda, 3, 0, 5),
  [239] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_lambda, 3, 0, 5),
  [241] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_lambda, 3, 0, 6),
  [243] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_lambda, 3, 0, 6),
  [245] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parenthesized, 3, 0, 0),
  [247] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_parenthesized, 3, 0, 0),
  [249] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__statement, 1, 0, 0),
  [251] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__statement, 1, 0, 0),
  [253] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_binary_expression, 3, 0, 3),
  [255] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_binary_expression, 3, 0, 3),
  [257] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_system_command, 1, 0, 1),
  [259] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_system_command, 1, 0, 1),
  [261] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_namespace_directive, 1, 0, 0),
  [263] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_namespace_directive, 1, 0, 0),
  [265] = {.entry = {.count = 1, .reusable = true}}, SHIFT(47),
  [267] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_namespace_directive, 2, 0, 2),
  [269] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_namespace_directive, 2, 0, 2),
  [271] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_source_file_repeat1, 1, 0, 0),
  [273] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 1, 0, 0),
  [275] = {.entry = {.count = 1, .reusable = true}}, SHIFT(51),
  [277] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameters, 4, 0, 11),
  [279] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_parameters, 4, 0, 11),
  [281] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameters, 2, 0, 0),
  [283] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_parameters, 2, 0, 0),
  [285] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_source_file_repeat1, 2, 0, 0),
  [287] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_parameters, 3, 0, 8),
  [289] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_parameters, 3, 0, 8),
  [291] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_vector_repeat1, 2, 0, 0), SHIFT_REPEAT(56),
  [294] = {.entry = {.count = 1, .reusable = true}}, SHIFT(12),
  [296] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [298] = {.entry = {.count = 1, .reusable = false}}, SHIFT(16),
  [300] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [302] = {.entry = {.count = 1, .reusable = true}}, SHIFT(72),
  [304] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [306] = {.entry = {.count = 1, .reusable = true}}, SHIFT(70),
  [308] = {.entry = {.count = 1, .reusable = true}}, SHIFT(32),
  [310] = {.entry = {.count = 1, .reusable = true}}, SHIFT(28),
  [312] = {.entry = {.count = 1, .reusable = true}}, SHIFT(34),
  [314] = {.entry = {.count = 1, .reusable = true}}, SHIFT(67),
  [316] = {.entry = {.count = 1, .reusable = true}}, SHIFT(108),
  [318] = {.entry = {.count = 1, .reusable = true}}, SHIFT(50),
  [320] = {.entry = {.count = 1, .reusable = true}}, SHIFT(35),
  [322] = {.entry = {.count = 1, .reusable = true}}, SHIFT(104),
  [324] = {.entry = {.count = 1, .reusable = true}}, SHIFT(49),
  [326] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__lambda_body, 1, 0, 0),
  [328] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [330] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_parameters_repeat1, 2, 0, 12), SHIFT_REPEAT(104),
  [333] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_parameters_repeat1, 2, 0, 12),
  [335] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_list_repeat1, 2, 0, 0),
  [337] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym__lambda_body_repeat1, 2, 0, 0),
  [339] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym__lambda_body_repeat1, 2, 0, 0), SHIFT_REPEAT(8),
  [342] = {.entry = {.count = 1, .reusable = true}}, SHIFT(33),
  [344] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [346] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_list_repeat1, 2, 0, 0), SHIFT_REPEAT(11),
  [349] = {.entry = {.count = 1, .reusable = true}}, SHIFT(52),
  [351] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__lambda_body, 2, 0, 0),
  [353] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [355] = {.entry = {.count = 1, .reusable = true}}, SHIFT(42),
  [357] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [359] = {.entry = {.count = 1, .reusable = true}}, SHIFT(65),
  [361] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_call_repeat1, 2, 0, 0), SHIFT_REPEAT(21),
  [364] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_call_repeat1, 2, 0, 0),
  [366] = {.entry = {.count = 1, .reusable = true}}, SHIFT(71),
  [368] = {.entry = {.count = 1, .reusable = true}}, SHIFT(60),
  [370] = {.entry = {.count = 1, .reusable = true}}, SHIFT(59),
  [372] = {.entry = {.count = 1, .reusable = true}}, SHIFT(103),
  [374] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_parameters_repeat1, 2, 0, 8),
  [376] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_param, 1, 0, 0),
  [378] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [380] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [382] = {.entry = {.count = 1, .reusable = true}}, SHIFT(63),
  [384] = {.entry = {.count = 1, .reusable = true}}, SHIFT(68),
  [386] = {.entry = {.count = 1, .reusable = true}}, SHIFT(29),
  [388] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [390] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
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

static const bool ts_external_scanner_states[6][EXTERNAL_TOKEN_COUNT] = {
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
    [ts_external_token__neg_number] = true,
  },
  [3] = {
    [ts_external_token_comment] = true,
    [ts_external_token__neg_number] = true,
  },
  [4] = {
    [ts_external_token_comment] = true,
    [ts_external_token__system_command_tok] = true,
    [ts_external_token__neg_number] = true,
    [ts_external_token__eos] = true,
  },
  [5] = {
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
