#!/usr/bin/env python3
"""Deterministic test generator for CF1106D Lunar New Year and a Wander."""

import random
from collections import deque
from pathlib import Path


LIMIT = 100_000
ROOT = Path(__file__).resolve().parent
OUT = ROOT / "inputs"

SAMPLES = [
    [(3, [(1, 2), (1, 3)])],
    [(5, [(1, 4), (3, 4), (5, 4), (3, 2), (1, 5)])],
    [
        (
            10,
            [
                (1, 4), (6, 8), (2, 5), (3, 7), (9, 4),
                (5, 6), (3, 4), (8, 10), (8, 9), (1, 10),
            ],
        )
    ],
]


def is_connected(n, edges):
    graph = [[] for _ in range(n + 1)]
    for u, v in edges:
        graph[u].append(v)
        graph[v].append(u)
    seen = [False] * (n + 1)
    q = deque([1])
    seen[1] = True
    while q:
        u = q.popleft()
        for v in graph[u]:
            if not seen[v]:
                seen[v] = True
                q.append(v)
    return all(seen[1:])


def add_case(cases, n, edges):
    assert 1 <= n <= LIMIT
    assert 1 <= len(edges) <= LIMIT
    assert all(1 <= u <= n and 1 <= v <= n for u, v in edges)
    assert is_connected(n, edges)
    cases.append((n, edges))


def random_connected(rng, n, m, allow_loops=True):
    assert n - 1 <= m <= LIMIT
    edges = [(rng.randint(1, v - 1), v) for v in range(2, n + 1)]
    while len(edges) < m:
        u = rng.randint(1, n)
        v = rng.randint(1, n) if allow_loops else rng.randint(1, n - 1)
        if not allow_loops and v >= u:
            v += 1
        edges.append((u, v))
    rng.shuffle(edges)
    return edges


def star_case(rng, n):
    edges = [(1, v) for v in range(2, n + 1)]
    edges.append((1, 1))
    rng.shuffle(edges)
    return edges


def chain_frontier_trap(rng, n):
    # 1 simultaneously exposes 2 and n. A sorted-adjacency ordinary BFS visits n too early.
    edges = [(1, n)]
    edges.extend((u, u + 1) for u in range(1, n - 1))
    edges.append((n // 2, n // 2))
    assert len(edges) == n
    rng.shuffle(edges)
    return edges


def comb_frontier_trap(rng):
    # The 1..50000 backbone keeps revealing smaller vertices while 50001..100000 wait in the heap.
    edges = [(u, u + 1) for u in range(1, 50_000)]
    edges.extend((leaf - 50_000, leaf) for leaf in range(50_001, 100_001))
    edges.append((77_777, 77_777))
    assert len(edges) == LIMIT
    rng.shuffle(edges)
    return edges


def write_case(index, n, edges):
    lines = [f"{n} {len(edges)}"]
    lines.extend(f"{u} {v}" for u, v in edges)
    (OUT / f"{index}.in").write_text("\n".join(lines) + "\n", encoding="ascii")


def main():
    rng = random.Random(11062026)
    cases = []

    # G1: official samples, then minimal/self-loop/parallel-edge cases.
    for sample in SAMPLES:
        n, edges = sample[0]
        add_case(cases, n, edges)
    add_case(cases, 1, [(1, 1)])
    add_case(cases, 2, [(1, 2), (2, 2), (1, 2), (1, 1)])

    # G2: small adversarial graphs, all small enough for the independent exhaustive oracle.
    add_case(cases, 6, [(1, 4), (1, 2), (2, 3), (3, 5), (4, 6), (1, 4), (2, 2), (5, 5)])
    add_case(cases, 10, [(1, v) for v in range(10, 1, -1)] + [(1, 1)] * 9)
    add_case(cases, 10, random_connected(rng, 10, 30))
    add_case(cases, 12, random_connected(rng, 12, 50))

    # G3: medium transition cases. A queue with locally sorted adjacency fails test 10.
    add_case(cases, 2_000, chain_frontier_trap(rng, 2_000))
    add_case(cases, 10_000, random_connected(rng, 10_000, 20_000))

    # G4: full constraints, each with a different frontier shape or edge multiplicity pattern.
    add_case(cases, LIMIT, star_case(rng, LIMIT))
    add_case(cases, LIMIT, chain_frontier_trap(rng, LIMIT))
    add_case(cases, LIMIT, comb_frontier_trap(rng))
    add_case(cases, LIMIT, random_connected(rng, LIMIT, LIMIT))
    add_case(cases, 2, [(1, 2)] + [(1, 1) if i % 2 == 0 else (1, 2) for i in range(LIMIT - 1)])

    assert len(cases) == 16
    OUT.mkdir(parents=True, exist_ok=True)
    for old in OUT.glob("*.in"):
        old.unlink()
    for index, (n, edges) in enumerate(cases, start=1):
        write_case(index, n, edges)
    print(f"CF1106D generated {len(cases)} inputs")


if __name__ == "__main__":
    main()
