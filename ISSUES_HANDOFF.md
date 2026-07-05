# q-tree-sitter: Issue Analysis Handoff
**Generated:** 2026-07-05  
**Method:** Graphify knowledge graph (433 nodes, 523 edges, 78 communities) + codebase scan  
**Prior Claude chats:** 0 found

---

## Executive Summary

Parse success rate on real-world q files: **33.33%** (30/90 clean, 60/90 ERROR nodes).  
Target: **<2%** error rate. **Gap: 65 percentage points.**

No timeouts or crashes. Issue is grammar coverage, not stability.

---

## Critical Issue: Parse Failure Rate

**What:** 60 of 90 real q files in `test/real/` produce ERROR nodes during parsing.

**Where:** Tracked in `scripts/PARSE_FAILURES.md`  

**Files affected:** Bloomberg, KDB+, reQ codebases (complete list in PARSE_FAILURES.md)

**Impact:** Graphify extraction skips files with ERROR nodes → incomplete corpus analysis.

**Root cause analysis:**

| Category | Examples | Status |
|----------|----------|--------|
| **Projection syntax** | `f[;2]` leading-elision | OPEN |
| **Operator ambiguity** | `?[x;1;2]` (vector vs control) | OPEN |
| **Numeric literals** | `-1.5e-3` negative floats | FIXED (c96a79a) |
| **Operator-as-value** | `+` as data, not operator | FIXED (c96a79a) |
| **Stacked adverbs** | `/\` double postfix | FIXED (59cfc83) |
| **Default/optional args** | Function signatures with defaults | UNKNOWN |
| **Contextual keywords** | Keywords vs identifiers in context | UNKNOWN |

---

## Known Parse Edge Cases (from task reports)

### Task 6: Expression Core
- Binary expression handling had reduction issues (`1+2` dropping `binary` → ERROR on `+`)
- Leading-elision projection (`f[;2]`) → ERROR node on `;`
- Middle elision works; trailing elision works
- **Status:** Partially addressed; leading case remains

### Task 8: Control Flow  
- Vector conditional `?[x;1;2]` parses as ERROR instead of control construct
- Reason: `?` overloaded (ternary operator in q)
- **Status:** Documented; likely needs GLR resolution or scanner lookahead

### Recent Fixes (commits 59cfc83, c96a79a)
- Negative float parsing (`-1.5e-3`) ✓
- Operators-as-values (allowing `+` bare) ✓
- Stacked adverbs (`f//\[x]`) ✓
- Leading-elided args (partial) ✓

---

## Architecture Observations

### Graph Metrics
- **Nodes:** 433 (292 code AST, 141 semantic doc/rationale)
- **Edges:** 523 (482 AST, 41 semantic)
- **Communities:** 78 (high fragmentation; ideal ~5-10)
- **God nodes (highest degree):**
  - `rules` (57 edges) — bottleneck
  - `members` (21)
  - `content` (15)
  - Task 6: Expression core (13)
  - Task 10: Convergence (13)

### Design Constraints (not issues)
1. **Right-to-left evaluation:** q-specific, no operator precedence
2. **Namespace system:** `.ns.name` + `\d` directive required
3. **External scanner:** Handles whitespace semantics, comment disambiguation, negative number prefix
4. **Adverbs:** Postfix operators (/, \, ', /:, \:, etc) applied to verbs
5. **Function-as-lambda:** `f:{x+y}` pattern; assignment-to-lambda syntax

### Import Cycle (Low Priority)
- `grammar.js` → `grammar.js` (self-reference)
- Common in modular grammars; not a functional issue
- Could refactor into submodule exports if needed

---

## Resolved Issues

### 1. Scanner EOF-EOS Infinite Loop ✓
- **Commit:** ce12ee5
- **What:** Empty or unterminated input triggered unbounded `EOS` token emission
- **Symptom:** OOM (>1.5GB in <1s), 99% CPU hang, parser tree explosion
- **Fix:** `eof_eos_emitted` flag; fire once per parse
- **Status:** Verified in current `src/scanner.c`

### 2. Tree-sitter Process Orphans ✓
- **What:** `tree-sitter parse &` then `kill -9 $PID` leaves detached node process
- **Symptom:** Process reparents to init (ppid=1), keeps running at 99% CPU, survives ~3min, eats 17GB swap
- **Workaround:** Use `pkill -9 -f 'tree-sitter parse'` instead of `kill`
- **Status:** Documented in memory; no fix needed (CLI behavior)

### 3. Corpus Test Stability ✓
- Skeleton corpus (task 1): zero ERROR nodes
- Handwritten corpus (tasks 2-8): all topics covered
- Full convergence (task 10): parser generates, tests pass

---

## Test Coverage

### What's Green
- ✓ Skeleton syntax (`f:{x+y}`)
- ✓ Literals (numbers, temporal, symbols, strings, bool vectors)
- ✓ Identifiers (dotted names, keywords, builtins)
- ✓ Functions (lambda syntax, assignment-to-lambda)
- ✓ Expressions (right-to-left, application, adverbs)
- ✓ q-SQL (select/exec/update/delete + clauses)
- ✓ Control flow (cond, if/do/while, return, signal)
- ✓ System commands (backslash directives)
- ✓ Scanner lexical elements (comments, whitespace, assignments)

### What's Not
- ✗ 60/90 real-world files (edge cases, syntactic sugar)
- ? Default/optional function arguments
- ? Some operator overloading contexts
- ? Rare control-flow patterns

---

## Next Steps (Roadmap Inference)

### Phase 3 (Current): Real-world Parse Rate
1. **Profile the 60 failing files** — group by error type
2. **Fix top 3-5 patterns** — likely projection syntax, operator ambiguity
3. **Target:** Get to <10% error rate (9/90) as intermediate milestone
4. **Timeline:** Unknown (memory doesn't specify)

### Phase 4 (Next): Graphify Integration
1. Python wheel distribution complete (task 11, 59cea5a)
2. Extractor contract wired (extractor must handle ERROR nodes gracefully)
3. Graphify cli.q support packaged (deliverable in b13e25f)

---

## Commands for Debugging

### Real-world parse rate
```bash
python3 scripts/parse_rate.py test/real/
```

### Analyze specific failures
```bash
python3 scripts/analyze_errors.py test/real/cookbook/bloomberg/bpipe.q
```

### Diff against oracle (q VM output)
```bash
python3 scripts/diff_oracle.py test/real/kdb/bell.q
```

### Watch for memory runaway
```bash
pkill -9 -f 'tree-sitter parse'  # Always use pkill, not kill
memguard.sh <limit>              # If present
```

---

## File Locations

- **Parse failures list:** `scripts/PARSE_FAILURES.md` (maintained, up-to-date)
- **Analysis tools:** `scripts/parse_rate.py`, `analyze_errors.py`, `diff_oracle.py`
- **Grammar source:** `grammar.js` + `grammar/*.js` modules
- **Scanner:** `src/scanner.c`
- **Parser:** `src/parser.c` (generated)
- **Test corpus:** `test/corpus/*.txt` (handwritten), `test/real/` (real-world)
- **Task history:** `.superpowers/sdd/task-*-{brief,report}.md`

---

## Caveats

- **No prior Claude chats:** This is the first analysis pass; no conversation history exists
- **Graph extraction warnings:** 54 edges missing `source_file` field (minor data quality issue, doesn't affect findings)
- **Community labels:** Auto-generated ("Community 0"–"Community 77"); not semantically meaningful yet
- **Memory age:** Prior observations (orphans, EOF-EOS) from 2026-06-29; verified current as of 2026-07-05

---

**Next review target:** After top-3 parse-failure patterns fixed, re-run graphify to measure community cohesion improvement.
