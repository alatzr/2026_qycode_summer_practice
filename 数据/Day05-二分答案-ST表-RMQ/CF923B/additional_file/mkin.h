#!/usr/bin/env python3
# CF923B Producing Snow 数据生成器：写出 inputs/ 全部 .in（含官方样例 + 边界 + 随机 + 满量程）
# Constraints: 1 <= n <= 1e5; 0 <= volume[i], temp[i] <= 1e9.
import os
import random

OUT = os.path.join(os.path.dirname(__file__), "inputs")
os.makedirs(OUT, exist_ok=True)

samples = [
    "3\n10 10 5\n5 7 2\n",
    "5\n30 25 20 15 10\n9 10 12 4 13\n",
]


def case(n, volume, temp):
    return f"{n}\n{' '.join(map(str, volume))}\n{' '.join(map(str, temp))}\n"


def rand_case(rng, n, vmax, tmax):
    volume = [rng.randint(1, vmax) for _ in range(n)]
    temp = [rng.randint(1, tmax) for _ in range(n)]
    return case(n, volume, temp)


def main():
    files = []
    files += samples                                   # 1,2 官方样例
    files.append(case(1, [1], [1]))                    # 最小规模
    files.append(case(1, [0], [0]))                    # 零体积、零温度
    files.append(case(5, [0, 5, 0, 10, 1], [0, 0, 2, 0, 100]))
    files.append(case(1, [10**9], [1]))                # 单堆大体积慢融
    files.append(case(2, [1, 1], [10**9, 10**9]))      # 一天融完
    rng = random.Random(9231)
    files.append(rand_case(rng, 10, 20, 5))            # 小随机(对拍)
    files.append(rand_case(rng, 50, 100, 10))          # 小随机(对拍)
    files.append(rand_case(rng, 200, 1000, 50))        # 小随机(对拍)
    files.append(case(1000, [10**9] * 1000, [1] * 1000))   # 全大体积低温：几乎不融
    files.append(rand_case(rng, 100000, 10**9, 1))     # 满量程：温度极低
    files.append(rand_case(rng, 100000, 10**9, 10**9)) # 满量程：温度极高(当天融完多)
    files.append(rand_case(rng, 100000, 10**9, 10**4)) # 满量程：一般
    files.append(case(100000, [10**9] * 100000, [0] * 100000))
    for idx, content in enumerate(files, 1):
        with open(os.path.join(OUT, f"{idx}.in"), "w", newline="\n") as fh:
            fh.write(content)
    print(f"CF923B 生成 {len(files)} 个输入")


if __name__ == "__main__":
    main()
