# Graph Report - .  (2026-07-05)

## Corpus Check
- 71 files · ~226,924 words
- Verdict: corpus is large enough that graph structure adds value.

## Summary
- 433 nodes · 523 edges · 78 communities (59 shown, 19 thin omitted)
- Extraction: 92% EXTRACTED · 8% INFERRED · 0% AMBIGUOUS · INFERRED: 42 edges (avg confidence: 0.84)
- Token cost: 0 input · 0 output

## Community Hubs (Navigation)
- [[_COMMUNITY_Community 0|Community 0]]
- [[_COMMUNITY_Community 1|Community 1]]
- [[_COMMUNITY_Community 2|Community 2]]
- [[_COMMUNITY_Community 3|Community 3]]
- [[_COMMUNITY_Community 4|Community 4]]
- [[_COMMUNITY_Community 5|Community 5]]
- [[_COMMUNITY_Community 6|Community 6]]
- [[_COMMUNITY_Community 7|Community 7]]
- [[_COMMUNITY_Community 8|Community 8]]
- [[_COMMUNITY_Community 9|Community 9]]
- [[_COMMUNITY_Community 10|Community 10]]
- [[_COMMUNITY_Community 11|Community 11]]
- [[_COMMUNITY_Community 12|Community 12]]
- [[_COMMUNITY_Community 13|Community 13]]
- [[_COMMUNITY_Community 15|Community 15]]
- [[_COMMUNITY_Community 16|Community 16]]
- [[_COMMUNITY_Community 17|Community 17]]
- [[_COMMUNITY_Community 18|Community 18]]
- [[_COMMUNITY_Community 19|Community 19]]
- [[_COMMUNITY_Community 20|Community 20]]
- [[_COMMUNITY_Community 21|Community 21]]
- [[_COMMUNITY_Community 22|Community 22]]
- [[_COMMUNITY_Community 23|Community 23]]
- [[_COMMUNITY_Community 24|Community 24]]
- [[_COMMUNITY_Community 25|Community 25]]
- [[_COMMUNITY_Community 26|Community 26]]
- [[_COMMUNITY_Community 27|Community 27]]
- [[_COMMUNITY_Community 28|Community 28]]
- [[_COMMUNITY_Community 29|Community 29]]
- [[_COMMUNITY_Community 30|Community 30]]
- [[_COMMUNITY_Community 32|Community 32]]
- [[_COMMUNITY_Community 33|Community 33]]
- [[_COMMUNITY_Community 34|Community 34]]
- [[_COMMUNITY_Community 35|Community 35]]
- [[_COMMUNITY_Community 36|Community 36]]
- [[_COMMUNITY_Community 37|Community 37]]
- [[_COMMUNITY_Community 38|Community 38]]
- [[_COMMUNITY_Community 39|Community 39]]
- [[_COMMUNITY_Community 40|Community 40]]
- [[_COMMUNITY_Community 41|Community 41]]
- [[_COMMUNITY_Community 42|Community 42]]
- [[_COMMUNITY_Community 43|Community 43]]
- [[_COMMUNITY_Community 44|Community 44]]
- [[_COMMUNITY_Community 45|Community 45]]
- [[_COMMUNITY_Community 46|Community 46]]
- [[_COMMUNITY_Community 47|Community 47]]
- [[_COMMUNITY_Community 48|Community 48]]
- [[_COMMUNITY_Community 49|Community 49]]
- [[_COMMUNITY_Community 50|Community 50]]
- [[_COMMUNITY_Community 51|Community 51]]
- [[_COMMUNITY_Community 52|Community 52]]
- [[_COMMUNITY_Community 53|Community 53]]
- [[_COMMUNITY_Community 55|Community 55]]
- [[_COMMUNITY_Community 57|Community 57]]
- [[_COMMUNITY_Community 58|Community 58]]
- [[_COMMUNITY_Community 62|Community 62]]
- [[_COMMUNITY_Community 63|Community 63]]
- [[_COMMUNITY_Community 64|Community 64]]
- [[_COMMUNITY_Community 65|Community 65]]
- [[_COMMUNITY_Community 66|Community 66]]
- [[_COMMUNITY_Community 67|Community 67]]
- [[_COMMUNITY_Community 68|Community 68]]
- [[_COMMUNITY_Community 69|Community 69]]
- [[_COMMUNITY_Community 70|Community 70]]
- [[_COMMUNITY_Community 74|Community 74]]
- [[_COMMUNITY_Community 75|Community 75]]
- [[_COMMUNITY_Community 76|Community 76]]
- [[_COMMUNITY_Community 77|Community 77]]

## God Nodes (most connected - your core abstractions)
1. `rules` - 57 edges
2. `members` - 21 edges
3. `content` - 15 edges
4. `Task 6: Expression core — RTL, application, adverbs, lists` - 13 edges
5. `Task 10: Convergence — merge, generate, resolve GLR conflicts` - 13 edges
6. `Task 1: Foundation — compiling skeleton + frozen interfaces` - 11 edges
7. `Main grammar module - merges all submodules` - 10 edges
8. `Right-to-left expression core, application, adverbs, lists` - 9 edges
9. `Array` - 7 edges
10. `Task 2: External scanner (src/scanner.c)` - 7 edges

## Surprising Connections (you probably didn't know these)
- `External scanner handles whitespace semantics, comments, negative numbers` --rationale_for--> `Literal lexical forms (numbers, temporal, strings, symbols, etc)`  [INFERRED]
  docs/superpowers/specs/2026-06-28-tree-sitter-q-graphify-design.md → grammar/literals.js
- `Comprehensive literal types: dates, times, numbers, symbols, strings, bool vectors` --implements--> `Literal lexical forms (numbers, temporal, strings, symbols, etc)`  [INFERRED]
  docs/superpowers/specs/2026-06-28-tree-sitter-q-graphify-design.md → grammar/literals.js
- `Namespace system via .ns.name qualification and \d directive` --implements--> `Identifier rules, dotted names, builtins, symbol vectors`  [INFERRED]
  docs/superpowers/specs/2026-06-28-tree-sitter-q-graphify-design.md → grammar/identifiers.js
- `Postfix adverbs (/, \, ', /:, \:, etc) applied to verbs` --implements--> `Right-to-left expression core, application, adverbs, lists`  [INFERRED]
  docs/superpowers/specs/2026-06-28-tree-sitter-q-graphify-design.md → grammar/expression.js
- `Right-to-left expression evaluation with no operator precedence` --implements--> `Right-to-left expression core, application, adverbs, lists`  [INFERRED]
  docs/superpowers/specs/2026-06-28-tree-sitter-q-graphify-design.md → grammar/expression.js

## Import Cycles
- 1-file cycle: `grammar.js -> grammar.js`

## Hyperedges (group relationships)
- **Wave 1: Parallel Grammar Task Cluster** — task_2_scanner, task_3_literals, task_4_identifiers, task_5_functions, task_6_expression, task_7_qsql, task_8_control [EXTRACTED 1.00]
- **** — task_1_foundation, wave_1_parallel, task_10_convergence [EXTRACTED 1.00]
- **Convergence: Wave-1 Merge to Main** — wave_1_parallel, task_10_convergence, wave_2_convergence [EXTRACTED 1.00]
- **Wave 1: Parallel grammar module tasks with modular file structure** — grammar_literals_js, grammar_identifiers_js, grammar_functions_js, grammar_expression_js, grammar_qsql_js, grammar_control_js, grammar_commands_js [EXTRACTED 1.00]
- **Python binding stack: C extension + module wrapper + language() export** — binding_c_python, binding_init_py, package_json_config [EXTRACTED 1.00]
- **Frozen node taxonomy: assignment/lambda/call/qsql/control/system_command** — node_taxonomy_assignment, node_taxonomy_lambda, node_taxonomy_call, node_taxonomy_qsql, node_taxonomy_control, node_taxonomy_system_command [EXTRACTED 1.00]
- **q Language Reference Specification** — references_datatypes_q_datatype, references_keywords_qsql_templates, references_operators_glyphs, references_syntax_evaluation_order [EXTRACTED 1.00]
- **Test Corpus Coverage** — test_corpus_commands, test_corpus_control, test_corpus_functions, test_corpus_literals [EXTRACTED 0.95]
- **Parse Quality Validation** — scripts_parse_rate_tool, scripts_analyze_errors_tool, scripts_diff_oracle_tool [INFERRED 0.85]
- **SQL-like query construct** — test_qsql_select_statement, test_qsql_from_clause, test_qsql_where_clause [EXTRACTED 1.00]
- **Lexical scanner elements** — test_scanner_comment, test_scanner_system_command, test_scanner_assignment [EXTRACTED 1.00]
- **Python tree-sitter integration** — test_python_test_load, test_python_tree_sitter_q, test_python_language_function [EXTRACTED 1.00]

## Communities (78 total, 19 thin omitted)

### Community 0 - "Community 0"
Cohesion: 0.04
Nodes (48): content, type, content, type, value, content, type, value (+40 more)

### Community 1 - "Community 1"
Cohesion: 0.08
Nodes (42): content, content, content, type, content, type, value, content (+34 more)

### Community 2 - "Community 2"
Cohesion: 0.07
Nodes (40): Task 10 Completed: 0cfc478 (convergence commit), Task 11 Completed: 59cea5a (wheel), Task 1 Completed: d3e3fe2, Task 2 Completed: 764089c (w1-scanner), Task 3 Completed: feb6b0b (w1-literals), Task 4 Completed: 5968b35 (w1-identifiers), Task 5 Completed: 0de7651 (w1-functions), Task 6 Completed: 010c3a6 (w1-expression) (+32 more)

### Community 3 - "Community 3"
Cohesion: 0.11
Nodes (26): Postfix adverbs (/, \, ', /:, \:, etc) applied to verbs, Python binding exposing language() function, External scanner handles whitespace semantics, comments, negative numbers, Functions defined as assignments to lambdas, System/backslash commands grammar, Control flow (cond, if/do/while, return, signal), Right-to-left expression core, application, adverbs, lists, Lambda, parameters, assignment rules (+18 more)

### Community 4 - "Community 4"
Cohesion: 0.11
Nodes (17): PyMODINIT_FUNC, PyObject, TSLexer, tree_sitter_q(), ts_lex(), ts_lex_keywords(), adv(), TSLexer (+9 more)

### Community 5 - "Community 5"
Cohesion: 0.15
Nodes (13): type, type, type, type, type, type, rules, boolean (+5 more)

### Community 6 - "Community 6"
Cohesion: 0.40
Nodes (8): Array, _array__assign(), _array__delete(), _array__erase(), _array__grow(), _array__reserve(), _array__splice(), _array__swap()

### Community 7 - "Community 7"
Cohesion: 0.20
Nodes (9): description, devDependencies, tree-sitter-cli, main, name, scripts, generate, test (+1 more)

### Community 8 - "Community 8"
Cohesion: 0.20
Nodes (9): Literal Lexical Forms, q Datatypes, Scalar Types, Temporal Datatypes, Comment Forms, Whitespace Sensitivity, Tree-Sitter Grammar for q, Node Types Schema (+1 more)

### Community 9 - "Community 9"
Cohesion: 0.20
Nodes (9): conflicts, externals, extras, inline, name, precedences, $schema, supertypes (+1 more)

### Community 10 - "Community 10"
Cohesion: 0.22
Nodes (7): commands, control, expression, functions, identifiers, literals, qsql

### Community 11 - "Community 11"
Cohesion: 0.29
Nodes (7): Control Words, Application Forms, Right-to-Left Evaluation, Lambda Notation, Control Flow Test Corpus, Expressions Test Corpus, Functions Test Corpus

### Community 12 - "Community 12"
Cohesion: 0.29
Nodes (7): q-SQL Template Words, q-SQL Evaluation Order, From Phrase, Functional q-SQL Forms, Select Phrase, q-SQL Template Syntax, Where Phrase

### Community 13 - "Community 13"
Cohesion: 0.47
Nodes (5): main(), Return True if tree-sitter parses with NO ERROR/MISSING node., Return {name: ('OK', ast) | ('ERR', msg)} from q's parse., run_q_oracle(), ts_parse()

### Community 15 - "Community 15"
Cohesion: 0.40
Nodes (5): macOS Tree-sitter Dylib Cache Clash, tree-sitter-q + Graphify SDD Project, Wave 1: Parallel Grammar Tasks, Wave 2: Convergence and Merge, Wave 3: Packaging and Integration

### Community 16 - "Community 16"
Cohesion: 0.40
Nodes (5): SQL-like query test suite, exec_statement, from_clause, select_statement, where_clause

### Community 17 - "Community 17"
Cohesion: 0.40
Nodes (4): language(), tree_sitter_q module, q grammar, KDB+/q tree-sitter grammar

### Community 18 - "Community 18"
Cohesion: 0.40
Nodes (4): grammars, metadata, description, version

### Community 19 - "Community 19"
Cohesion: 0.50
Nodes (4): Lexical scanner test suite, assignment, comment, system_command

### Community 21 - "Community 21"
Cohesion: 0.50
Nodes (4): Names and Namespaces, System Commands, Commands Test Corpus, Identifiers Test Corpus

### Community 22 - "Community 22"
Cohesion: 0.50
Nodes (4): content, type, value, adverb_apply

### Community 23 - "Community 23"
Cohesion: 0.50
Nodes (4): content, type, value, by_clause

### Community 24 - "Community 24"
Cohesion: 0.50
Nodes (4): content, type, value, delete_statement

### Community 25 - "Community 25"
Cohesion: 0.50
Nodes (4): content, type, value, return_stmt

### Community 26 - "Community 26"
Cohesion: 0.50
Nodes (4): select_clause, content, type, value

### Community 27 - "Community 27"
Cohesion: 0.50
Nodes (4): update_statement, content, type, value

### Community 28 - "Community 28"
Cohesion: 0.50
Nodes (4): where_clause, content, type, value

### Community 29 - "Community 29"
Cohesion: 0.67
Nodes (3): Comprehensive Tree-sitter grammar for KDB+/q with Graphify integration, Design: Tree-sitter grammar for KDB+/q + Graphify integration, Tree-sitter q + Graphify integration implementation plan

### Community 32 - "Community 32"
Cohesion: 0.67
Nodes (3): Primitive Operator Glyphs, Iterator Glyphs, Multi-Character Tokens

### Community 34 - "Community 34"
Cohesion: 0.67
Nodes (3): members, type, _adverb

### Community 35 - "Community 35"
Cohesion: 0.67
Nodes (3): members, type, _application

### Community 36 - "Community 36"
Cohesion: 0.67
Nodes (3): members, type, arguments

### Community 37 - "Community 37"
Cohesion: 0.67
Nodes (3): members, type, call

### Community 38 - "Community 38"
Cohesion: 0.67
Nodes (3): members, type, control

### Community 39 - "Community 39"
Cohesion: 0.67
Nodes (3): members, type, _expression

### Community 40 - "Community 40"
Cohesion: 0.67
Nodes (3): members, type, from_clause

### Community 41 - "Community 41"
Cohesion: 0.67
Nodes (3): type, value, identifier

### Community 42 - "Community 42"
Cohesion: 0.67
Nodes (3): members, type, lambda

### Community 43 - "Community 43"
Cohesion: 0.67
Nodes (3): members, type, list

### Community 44 - "Community 44"
Cohesion: 0.67
Nodes (3): members, type, number

### Community 45 - "Community 45"
Cohesion: 0.67
Nodes (3): members, type, _op_value

### Community 46 - "Community 46"
Cohesion: 0.67
Nodes (3): name, type, param

### Community 47 - "Community 47"
Cohesion: 0.67
Nodes (3): members, type, parameters

### Community 48 - "Community 48"
Cohesion: 0.67
Nodes (3): members, type, parenthesized

### Community 49 - "Community 49"
Cohesion: 0.67
Nodes (3): members, type, _primary

### Community 50 - "Community 50"
Cohesion: 0.67
Nodes (3): _statement, members, type

### Community 51 - "Community 51"
Cohesion: 0.67
Nodes (3): system_command, name, type

### Community 52 - "Community 52"
Cohesion: 0.67
Nodes (3): table_literal, members, type

### Community 53 - "Community 53"
Cohesion: 0.67
Nodes (3): binary, index, lambda

## Knowledge Gaps
- **175 isolated node(s):** `PyObject`, `PyMODINIT_FUNC`, `literals`, `identifiers`, `functions` (+170 more)
  These have ≤1 connection - possible missing edges or undocumented components.
- **19 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.