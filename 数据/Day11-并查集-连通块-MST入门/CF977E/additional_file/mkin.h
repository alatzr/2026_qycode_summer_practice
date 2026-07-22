#!/usr/bin/env python3
"""CF977E Cyclic Components deterministic data generator."""

import random
from pathlib import Path


LIMIT = 200_000
ROOT = Path(__file__).resolve().parent
OUT = ROOT / "inputs"


def cycle(vertices):
    vertices = list(vertices)
    assert len(vertices) >= 3
    return [
        (vertices[i], vertices[(i + 1) % len(vertices)])
        for i in range(len(vertices))
    ]


def path(vertices):
    vertices = list(vertices)
    return [(vertices[i], vertices[i + 1]) for i in range(len(vertices) - 1)]


def random_connected_simple(rng, vertices, m):
    """Generate a connected simple graph on the given vertices."""
    vertices = list(vertices)
    n = len(vertices)
    assert n - 1 <= m <= n * (n - 1) // 2

    order = vertices[:]
    rng.shuffle(order)
    edges = set()
    for i in range(1, n):
        u, v = order[i], order[rng.randrange(i)]
        edges.add((min(u, v), max(u, v)))

    while len(edges) < m:
        u, v = rng.sample(vertices, 2)
        edges.add((min(u, v), max(u, v)))

    result = sorted(edges)
    rng.shuffle(result)
    return result


def add_case(cases, n, edges, expected):
    assert 1 <= n <= LIMIT
    assert 0 <= len(edges) <= LIMIT

    seen = set()
    for u, v in edges:
        assert 1 <= u <= n and 1 <= v <= n
        assert u != v
        key = (min(u, v), max(u, v))
        assert key not in seen
        seen.add(key)

    cases.append((n, edges, expected))


def write_case(index, n, edges):
    lines = [f"{n} {len(edges)}"]
    lines.extend(f"{u} {v}" for u, v in edges)
    (OUT / f"{index}.in").write_text("\n".join(lines) + "\n", encoding="ascii")


def main():
    rng = random.Random(977_2026)
    cases = []

    # G1: official samples and minimum boundaries.
    add_case(cases, 5, [(1, 2), (3, 4), (5, 4), (3, 5)], 1)
    add_case(
        cases,
        17,
        [
            (1, 8), (1, 12), (5, 11), (11, 9), (9, 15),
            (15, 5), (4, 13), (3, 13), (4, 3), (10, 16),
            (7, 10), (16, 7), (14, 3), (14, 4), (17, 6),
        ],
        2,
    )
    add_case(cases, 1, [], 0)
    add_case(cases, 2, [(1, 2)], 0)
    add_case(cases, 3, cycle([1, 2, 3]), 1)

    edges = []
    edges += cycle([1, 2, 3])
    edges += cycle([4, 5, 6, 7])
    edges += [(9, 10)]
    edges += path([11, 12, 13])
    edges += [(14, 15), (14, 16), (14, 17)]
    rng.shuffle(edges)
    add_case(cases, 20, edges, 2)

    # G2: small anti-wrong-solution cases, suitable for exhaustive checking.
    add_case(cases, 4, cycle([1, 2, 3]) + [(3, 4)], 0)  # E=V, but not a cycle component
    add_case(cases, 4, cycle([1, 2, 3, 4]) + [(1, 3)], 0)  # cycle with a chord
    add_case(cases, 6, cycle([1, 2, 3]) + cycle([4, 5, 6]) + [(3, 4)], 0)
    add_case(cases, 5, cycle([1, 2, 3]) + cycle([1, 4, 5]), 0)  # figure eight

    edges = []
    edges += cycle([30, 2, 17])
    edges += cycle([28, 7, 19, 25])
    edges += cycle([1, 3, 5]) + [(5, 9)]
    edges += cycle([10, 11, 12]) + cycle([13, 14, 15]) + [(12, 13)]
    rng.shuffle(edges)
    add_case(cases, 30, edges, 2)

    edges = []
    edges += cycle([1, 2, 3])
    edges += cycle([4, 5, 6, 7])
    edges += cycle([8, 9, 10, 11, 12])
    edges += cycle([13, 14, 15, 16, 17, 18])
    rng.shuffle(edges)
    add_case(cases, 20, edges, 4)

    # G3: medium transition cases.
    edges = []
    cur = 1
    for _ in range(100):
        edges += cycle([cur, cur + 1, cur + 2])
        cur += 3
    for _ in range(100):
        edges += cycle([cur, cur + 1, cur + 2])
        edges.append((cur + 2, cur + 3))
        cur += 4
    edges += path(range(cur, 2001))
    rng.shuffle(edges)
    add_case(cases, 2_000, edges, 100)

    edges = []
    for start in range(1, 151, 3):
        edges += cycle([start, start + 1, start + 2])
    edges += random_connected_simple(rng, range(151, 5001), 9_850)
    rng.shuffle(edges)
    add_case(cases, 5_000, edges, 50)

    add_case(cases, 50_000, path(range(1, 50_001)), 0)

    # G4: full-boundary and adversarial cases.
    add_case(cases, LIMIT, [], 0)

    edges = []
    for start in range(1, 199_999, 3):
        edges += cycle([start, start + 1, start + 2])
    rng.shuffle(edges)
    add_case(cases, LIMIT, edges, 66_666)

    edges = cycle(range(1, LIMIT + 1))
    rng.shuffle(edges)
    add_case(cases, LIMIT, edges, 1)

    edges = cycle([1, 2, 3]) + path(range(3, LIMIT + 1))
    rng.shuffle(edges)
    add_case(cases, LIMIT, edges, 0)  # connected and E=V, but has a long tail

    edges = []
    for start in range(1, 150_001, 3):
        edges += cycle([start, start + 1, start + 2])
    edges += cycle([150_001, 150_002, 150_003])
    edges += path(range(150_003, LIMIT + 1))
    rng.shuffle(edges)
    add_case(cases, LIMIT, edges, 50_000)

    edges = {(1, 2), (1, 3), (1, 4)}
    for v in range(5, LIMIT + 1):
        u = rng.randint(1, v - 1)
        edges.add((u, v))
    while len(edges) < LIMIT:
        u, v = rng.sample(range(1, LIMIT + 1), 2)
        edges.add((min(u, v), max(u, v)))
    edges = sorted(edges)
    rng.shuffle(edges)
    add_case(cases, LIMIT, edges, 0)

    assert len(cases) == 21
    OUT.mkdir(parents=True, exist_ok=True)
    for old in OUT.glob("*.in"):
        old.unlink()
    for index, (n, edges, _) in enumerate(cases, start=1):
        write_case(index, n, edges)

    print(f"CF977E generated {len(cases)} inputs")
    print("expected:", " ".join(str(expected) for _, _, expected in cases))


if __name__ == "__main__":
    main()
