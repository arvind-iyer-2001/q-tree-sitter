"""Graphify extractor for KDB+/q (bespoke: functions are assignments to lambdas)."""
from __future__ import annotations

import importlib
import re
from pathlib import Path
from typing import Any

from graphify.extractors.base import _file_stem, _make_id, _read_text

# A reference worth a node/edge is an identifier, optionally dotted:
# `f`, `.rt.pub`, `.mdl.api.addSensor`. Anything else found in callee/name
# position (whole conditionals, operators, string literals, projections) is
# call-site noise and must not become a graph node.
_IDENT_RE = re.compile(r"^\.?[A-Za-z][A-Za-z0-9_]*(?:\.[A-Za-z][A-Za-z0-9_]*)*$")

# q keywords and built-in functions. Edges to these carry no structure —
# they glue every function into one mega-community — so they are never
# callee targets. (Definitions shadowing a builtin name still get nodes.)
_Q_BUILTINS = frozenset("""
abs acos aj aj0 ajf ajf0 all and any asc asin asof atan attr avg avgs bin binr
ceiling cols cor cos count cov cross csv cut delete deltas desc dev differ
distinct div do dsave each ej ema enlist eval except exec exit exp fby fills
first fkeys flip floor get getenv group gtime hclose hcount hdel hopen hsym
iasc idesc if ij ijf in insert inter inv key keys last like lj ljf load log
lower lsq ltime ltrim mavg max maxs mcount md5 mdev med meta min mins mmax
mmin mmu mod msum neg next not null or over parse peach pj prd prds prev prior
rand rank ratios raze read0 read1 reciprocal reval reverse rload rotate rsave
rtrim save scan scov sdev select set setenv show signum sin sqrt ss ssr string
sublist sum sums sv svar system tables tan til trim type uj ujf ungroup union
update upper upsert value var view views vs wavg where while within wj wj2
wsum xasc xbar xcol xcols xdesc xexp xgroup xkey xlog xprev xrank
""".split())

# Namespaces provided by the q binary itself. Calls INTO these are runtime
# plumbing, not codebase structure. Assignments to them (e.g. `.z.ts:{...}`)
# are still extracted — event-handler definitions matter.
_SYSTEM_NS_RE = re.compile(r"^\.(z|Q|q|h|j|o|m)(\.|$)")


def _parser():
    mod = importlib.import_module("tree_sitter_q")
    from tree_sitter import Language, Parser
    return Parser(Language(mod.language()))


def _is_real_callee(name: str) -> bool:
    """True if a callee reference should become a node/edge."""
    if not _IDENT_RE.match(name):
        return False
    if name in _Q_BUILTINS:
        return False
    if _SYSTEM_NS_RE.match(name):
        return False
    return True


def extract_q(path: Path) -> dict:
    """Extract functions, variables, calls, imports, and table uses from a .q file.

    Returns a dict matching the Graphify extraction schema:
        {"nodes": [...], "edges": [...]}

    Node fields: id, label, file_type, source_file, source_location, kind
    Edge fields: source, target, relation, confidence, source_file
    """
    try:
        parser = _parser()
    except ImportError:
        return {"nodes": [], "edges": [], "error": "tree_sitter_q not installed"}

    try:
        src = Path(path).read_bytes()
        tree = parser.parse(src)
        root = tree.root_node
    except Exception as e:
        return {"nodes": [], "edges": [], "error": str(e)}

    str_path = str(path)
    stem = _file_stem(Path(path))

    nodes: list[dict] = []
    edges: list[dict] = []
    seen_ids: set[str] = set()
    ns_stack: list[str] = [""]  # namespace stack from \d directives
    # Maps qualified label -> node id for fast callee resolution
    label_to_nid: dict[str, str] = {}

    def add_node(nid: str, label: str, line: int, kind: str = "function") -> None:
        if nid not in seen_ids:
            seen_ids.add(nid)
            label_to_nid[label] = nid
            nodes.append({
                "id": nid,
                "label": label,
                "file_type": "code",
                "source_file": str_path,
                "source_location": f"L{line}",
                "kind": kind,
            })

    def add_edge(src_id: str, tgt_id: str, relation: str, line: int,
                 confidence: str = "EXTRACTED") -> None:
        edges.append({
            "source": src_id,
            "target": tgt_id,
            "relation": relation,
            "confidence": confidence,
            "source_file": str_path,
            "source_location": f"L{line}",
        })

    def ensure_external_node(label: str, line: int, kind: str = "external") -> str:
        """Return (possibly creating) a stub node for a cross-file symbol."""
        if label in label_to_nid:
            return label_to_nid[label]
        nid = _make_id(label)
        if nid not in seen_ids:
            seen_ids.add(nid)
            label_to_nid[label] = nid
            nodes.append({
                "id": nid,
                "label": label,
                "file_type": "code",
                "source_file": str_path,
                "source_location": f"L{line}",
                "kind": kind,
            })
        return nid

    # File-level node
    file_nid = _make_id(str(path))
    add_node(file_nid, Path(path).name, 1, kind="file")

    def current_ns() -> str:
        return ns_stack[-1]

    def qualify(name: str) -> str:
        """Resolve a bare name against the current namespace, or pass through dotted names."""
        if name.startswith("."):
            return name
        ns = current_ns()
        return f"{ns}.{name}" if ns else name

    def walk_calls(node: Any, caller_nid: str) -> None:
        """Recursively find call/index nodes within a subtree and emit calls edges."""
        if node.type in ("call", "index"):
            fn = node.child_by_field_name("function")
            if fn is not None:
                callee_text = _read_text(fn, src).strip()
                if _is_real_callee(callee_text):
                    callee_qualified = qualify(callee_text)
                    line = node.start_point[0] + 1
                    # Resolve to a real node id (stub created for cross-file callees)
                    callee_nid = ensure_external_node(callee_qualified, line)
                    add_edge(caller_nid, callee_nid, "calls", line, "INFERRED")
        for child in node.children:
            walk_calls(child, caller_nid)

    def scan_qsql(node: Any, owner_nid: str) -> None:
        """Find q-SQL statements and emit uses edges for referenced tables."""
        if node.type in ("select_statement", "exec_statement",
                         "update_statement", "delete_statement"):
            frm = node.child_by_field_name("from")
            if frm is not None:
                table_text = _read_text(frm, src).split()[-1]
                if _IDENT_RE.match(table_text):
                    table_qualified = qualify(table_text)
                    line = node.start_point[0] + 1
                    table_nid = ensure_external_node(table_qualified, line,
                                                     kind="table")
                    add_edge(owner_nid, table_nid, "uses", line, "INFERRED")
        for child in node.children:
            scan_qsql(child, owner_nid)

    def handle_assignment(node: Any) -> None:
        left = node.child_by_field_name("left")
        right = node.child_by_field_name("right")
        if left is None or right is None:
            return
        raw_name = _read_text(left, src).strip()
        # Compound left sides (indexed assignment `t[i]:v`, dictionary keys,
        # amend forms) are statements, not definitions — scan the right side
        # for calls/tables against the file, but create no definition node.
        if not _IDENT_RE.match(raw_name):
            walk_calls(right, file_nid)
            scan_qsql(right, file_nid)
            return
        name = qualify(raw_name)
        line = node.start_point[0] + 1

        # Compound assignment (`,:` `+:` `-:` …) mutates an existing global —
        # a registration/append, not a definition. `::` (global assign) and
        # plain `:` are definitions. Without this, plugin files that append to
        # core globals (`.schema.tbls,:…`) steal the definition site.
        op = node.child_by_field_name("operator")
        if op is not None and _read_text(op, src).strip() not in (":", "::"):
            tgt_nid = ensure_external_node(name, line)
            add_edge(file_nid, tgt_nid, "modifies", line)
            walk_calls(right, file_nid)
            scan_qsql(right, file_nid)
            return

        nid = _make_id(str(path), name)

        if right.type == "lambda":
            add_node(nid, name, line, kind="function")
            add_edge(file_nid, nid, "contains", line)
            # Walk the whole lambda, not child_by_field_name("body"): a multi-
            # statement body (`{a:1; select from t}`) tags every statement with
            # the `body` field, and child_by_field_name returns only the first,
            # which would miss calls/qsql in later statements.
            walk_calls(right, nid)
            scan_qsql(right, nid)
        else:
            add_node(nid, name, line, kind="variable")
            add_edge(file_nid, nid, "contains", line)
            walk_calls(right, nid)
            scan_qsql(right, nid)

    def handle_system_command(node: Any) -> None:
        """Handle \\d (namespace) and \\l (load) system commands."""
        text = _read_text(node, src).strip()
        line = node.start_point[0] + 1

        if text.startswith("\\d"):
            parts = text.split()
            new_ns = parts[1] if len(parts) > 1 else "."
            ns_stack[-1] = "" if new_ns == "." else new_ns
        elif text.startswith("\\l"):
            rest = text[2:].strip()
            if rest:
                tgt_stem = Path(rest).stem
                tgt_nid = _make_id(tgt_stem)
                add_node(tgt_nid, tgt_stem, line, kind="file")
                add_edge(file_nid, tgt_nid, "imports", line)

    def handle_system_call(node: Any) -> None:
        """Handle system"l file.q" calls (load via system function call)."""
        t = _read_text(node, src)
        m = re.search(r'system\s*"l\s+([^"]+)"', t)
        if m:
            tgt_stem = Path(m.group(1).strip()).stem
            tgt_nid = _make_id(tgt_stem)
            add_node(tgt_nid, tgt_stem, node.start_point[0] + 1, kind="file")
            add_edge(file_nid, tgt_nid, "imports", node.start_point[0] + 1)

    def walk(node: Any) -> None:
        if node.type == "assignment":
            # An assignment whose own subtree parsed clean is reliable even
            # inside a file with ERROR regions elsewhere — skipping those
            # drops real definitions and call-site stubs steal attribution.
            if not node.has_error:
                handle_assignment(node)
                # Don't recurse — handle_assignment already walks the lambda
                # body via walk_calls/scan_qsql.
                return
            # Malformed assignment: salvage any clean nested assignments.
        elif node.type in ("system_command", "namespace_directive"):
            handle_system_command(node)
        elif node.type in ("call", "index") and not node.has_error:
            # Top-level (script-scope) call: attribute it to the file so load-
            # time wiring (subscriptions, registrations) shows up as data flow.
            handle_system_call(node)
            walk_calls(node, file_nid)
            scan_qsql(node, file_nid)
            return
        for child in node.children:
            walk(child)

    walk(root)

    # All edge endpoints are known node ids (stub nodes created for cross-file
    # callees and table references), so a simple both-endpoints check suffices.
    clean_edges = [
        e for e in edges
        if e["source"] in seen_ids and e["target"] in seen_ids
    ]

    return {"nodes": nodes, "edges": clean_edges}
