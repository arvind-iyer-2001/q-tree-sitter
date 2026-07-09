#!/usr/bin/env python3
"""Render HTML viz for an oversized graphify graph.json.

Two views:
  graph-communities.html  one super-node per community, edges = cross-community links
  graph-hubs.html         subgraph of top-N nodes by degree (default 3000)
"""
import json
import sys
from collections import Counter
from pathlib import Path

import networkx as nx
from graphify.build import build_from_json
from graphify.cluster import cluster
from graphify.export import to_html

out = Path(sys.argv[1]) if len(sys.argv) > 1 else Path("graphify-out")
TOP_N = int(sys.argv[2]) if len(sys.argv) > 2 else 3000

raw = json.loads((out / "graph.json").read_text())
G = build_from_json(raw)
communities = cluster(G)
node2cid = {n: cid for cid, members in communities.items() for n in members}
print(f"graph: {G.number_of_nodes()} nodes, {G.number_of_edges()} edges, "
      f"{len(communities)} communities")

# --- view 1: community super-graph ---
CG = nx.Graph()
for cid, members in communities.items():
    # label the community by its highest-degree member
    top = max(members, key=lambda n: G.degree(n))
    label = G.nodes[top].get("label", top)
    CG.add_node(f"c{cid}", label=f"[{len(members)}] {label}")
weights = Counter()
for u, v in G.edges():
    cu, cv = node2cid.get(u), node2cid.get(v)
    if cu is None or cv is None or cu == cv:
        continue
    weights[tuple(sorted((cu, cv)))] += 1
for (cu, cv), w in weights.items():
    CG.add_edge(f"c{cu}", f"c{cv}", weight=w, confidence="high" if w >= 5 else "low")
cg_comms = {cid: [f"c{cid}"] for cid in communities}
member_counts = {cid: len(m) for cid, m in communities.items()}
to_html(CG, cg_comms, str(out / "graph-communities.html"),
        member_counts=member_counts)
print(f"graph-communities.html: {CG.number_of_nodes()} nodes, {CG.number_of_edges()} edges")

# --- view 2: top-degree hub subgraph ---
top_nodes = sorted(G.degree, key=lambda kv: kv[1], reverse=True)[:TOP_N]
H = G.subgraph([n for n, _ in top_nodes]).copy()
H.remove_nodes_from(list(nx.isolates(H)))
h_comms = {}
for n in H.nodes():
    h_comms.setdefault(node2cid.get(n, 0), []).append(n)
to_html(H, h_comms, str(out / "graph-hubs.html"))
print(f"graph-hubs.html: {H.number_of_nodes()} nodes, {H.number_of_edges()} edges")
