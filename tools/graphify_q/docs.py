"""Local (no-LLM) document extractor: PDF/markdown/text → section nodes.

Produces doc-file and doc-section nodes plus a `mentions` list linking
sections to code symbols they reference (dotted q namespaces and well-known
process acronyms). The caller resolves mention tokens against the code
graph's definitions — this module never sends content anywhere.
"""
from __future__ import annotations

import re
from pathlib import Path

# Process/acronym → the q namespace that implements it. Acronyms with no
# namespace in the codebase (RDB, HDB, GW …) still get concept nodes so
# runbook sections about them cluster together.
PROC_NS = {
    "EMS": ".ems", "SDL": ".sdl", "MDL": ".mdl", "DBW": ".dbw", "RP": ".rp",
    "MQ": ".mq", "RT": ".rt", "RTO": ".rto", "MON": ".mon", "DISC": ".disc",
    "SM": ".sm", "GW": ".gw", "SGW": ".sgw", "CDL": ".cdl", "VEE": ".vee",
    "AGG": ".agg", "RDB": ".rdb", "IDB": ".idb", "HDB": ".hdb",
    "SAPI": ".sapi", "SP": ".sp", "QETCD": ".qetcd",
}

_DOTTED = re.compile(r"\.[a-z][a-zA-Z0-9]*(?:\.[a-zA-Z0-9]+)+")
_ACRONYM = re.compile(r"\b(" + "|".join(sorted(PROC_NS, key=len, reverse=True)) + r")\b")
_MD_HEADING = re.compile(r"^#{1,4}\s+(.+)$", re.M)


def _pdf_sections(path: Path) -> list[tuple[str, int, str]]:
    """One section per page: (title, page_no, text)."""
    from pypdf import PdfReader
    out = []
    reader = PdfReader(str(path))
    for i, page in enumerate(reader.pages):
        text = page.extract_text() or ""
        if text.strip():
            out.append((f"p{i + 1}", i + 1, text))
    return out


def _md_sections(path: Path) -> list[tuple[str, int, str]]:
    """One section per heading; preamble before the first heading is 'intro'."""
    text = path.read_text(errors="replace")
    heads = list(_MD_HEADING.finditer(text))
    if not heads:
        return [("intro", 1, text)] if text.strip() else []
    out = []
    if text[: heads[0].start()].strip():
        out.append(("intro", 1, text[: heads[0].start()]))
    for i, h in enumerate(heads):
        end = heads[i + 1].start() if i + 1 < len(heads) else len(text)
        line = text[: h.start()].count("\n") + 1
        out.append((h.group(1).strip(), line, text[h.start():end]))
    return out


def extract_docs(paths: list[Path]) -> dict:
    """Extract nodes/edges/mentions from document files.

    Returns {"nodes": [...], "edges": [...], "mentions": [(section_id, token)]}
    where token is a dotted namespace ('.ems') or PROC_NS acronym ('RDB').
    """
    nodes: list[dict] = []
    edges: list[dict] = []
    mentions: list[tuple[str, str]] = []

    for path in paths:
        suffix = path.suffix.lower()
        try:
            if suffix == ".pdf":
                sections = _pdf_sections(path)
            elif suffix in (".md", ".markdown", ".txt", ".rst"):
                sections = _md_sections(path)
            else:
                continue
        except Exception:
            continue
        if not sections:
            continue

        str_path = str(path)
        file_id = f"doc:{path}"
        nodes.append({
            "id": file_id,
            "label": path.name,
            "file_type": "document",
            "source_file": str_path,
            "source_location": "L1",
            "kind": "document",
        })
        for title, line, text in sections:
            sec_id = f"{file_id}#{title}"
            nodes.append({
                "id": sec_id,
                "label": f"{path.stem} § {title}",
                "file_type": "document",
                "source_file": str_path,
                "source_location": f"L{line}",
                "kind": "doc-section",
                "description": " ".join(text.split())[:800],
            })
            edges.append({
                "source": file_id, "target": sec_id, "relation": "contains",
                "confidence": "EXTRACTED", "source_file": str_path,
                "source_location": f"L{line}",
            })
            seen: set[str] = set()
            for m in _DOTTED.finditer(text):
                tok = m.group(0)
                if tok not in seen:
                    seen.add(tok)
                    mentions.append((sec_id, tok))
            for m in _ACRONYM.finditer(text):
                ns = PROC_NS[m.group(1)]
                if ns not in seen:
                    seen.add(ns)
                    mentions.append((sec_id, ns))

    return {"nodes": nodes, "edges": edges, "mentions": mentions}
