"""Shared helpers for bespoke extractors (q)."""
from pathlib import Path


def _file_stem(p) -> str:
    return Path(p).stem


def _make_id(*parts) -> str:
    return ":".join(str(x) for x in parts)


def _read_text(node, src):
    text = src[node.start_byte:node.end_byte]
    return text.decode("utf-8", errors="replace") if isinstance(text, bytes) else text
