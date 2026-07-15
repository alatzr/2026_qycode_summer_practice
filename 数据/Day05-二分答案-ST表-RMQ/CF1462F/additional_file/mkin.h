#!/usr/bin/env python3
# CF1462F The Treasure of The Segments 数据生成器（多测）
# 约束：n 总和 <= 2e5；1 <= l_i <= r_i <= 1e9
import os
import random

OUT = os.path.join(os.path.dirname(__file__), "inputs")
os.makedirs(OUT, exist_ok=True)

sample1 = ("4\n3\n1 4\n2 3\n3 6\n4\n1 2\n2 3\n3 5\n4 5\n5\n1 2\n3 8\n4 5\n6 7\n9 10\n"
           "5\n1 5\n2 4\n3 5\n3 8\n4 8\n")


def one(segs):
    return f"{len(segs)}\n" + "".join(f"{l} {r}\n" for l, r in segs)


def pack(cases):
    assert 1 <= len(cases) <= 200000
    assert sum(len(segs) for segs in cases) <= 200000
    for segs in cases:
        assert 1 <= len(segs) <= 200000
        assert all(1 <= left <= right <= 10**9 for left, right in segs)
    return f"{len(cases)}\n" + "".join(one(c) for c in cases)


def rand_segs(rng, n, hi):
    segs = []
    for _ in range(n):
        a = rng.randint(1, hi); b = rng.randint(1, hi)
        if a > b: a, b = b, a
        segs.append((a, b))
    return segs


def main():
    rng = random.Random(14620)
    files = [sample1]                                       # 1 官方样例
    files.append(pack([[(1, 1)]]))                          # n=1，答案0
    files.append(pack([[(1, 1000000000)] * 1 + [(1, 1)]]))  # 大区间覆盖
    files.append(pack([[(1, 2), (3, 4), (5, 6)]]))          # 全不相交
    # 小随机(对拍)
    files.append(pack([rand_segs(rng, rng.randint(1, 8), 20) for _ in range(5)]))
    files.append(pack([rand_segs(rng, rng.randint(1, 30), 50) for _ in range(6)]))
    files.append(pack([rand_segs(rng, rng.randint(1, 80), 200) for _ in range(4)]))
    # 全部共享一个公共点 -> 答案0
    files.append(pack([[(rng.randint(1, 500), rng.randint(500, 1000)) for _ in range(1000)]]))
    # 满量程：单组 n=2e5
    files.append(pack([rand_segs(rng, 200000, 10**9)]))
    # 满量程：两两不相交，答案为 n-1，防止只覆盖小删除量
    files.append(pack([[(3 * i + 1, 3 * i + 2) for i in range(200000)]]))
    # 满量程：多组总和 2e5
    files.append(pack([rand_segs(rng, s, 10**9) for s in [40000, 60000, 100000]]))
    # 满量程：t 顶格
    files.append(pack([rand_segs(rng, 1, 10**9) for _ in range(200000)]))
    for idx, content in enumerate(files, 1):
        with open(os.path.join(OUT, f"{idx}.in"), "w", newline="\n") as fh:
            fh.write(content)
    print(f"CF1462F 生成 {len(files)} 个输入")


if __name__ == "__main__":
    main()
