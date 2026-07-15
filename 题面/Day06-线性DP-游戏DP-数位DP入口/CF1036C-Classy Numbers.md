# CF1036C · Classy Numbers

- 难度：1900
- 标签：combinatorics、dp
- 链接：https://codeforces.com/problemset/problem/1036/C
- 时间限制：3 seconds　内存限制：256 megabytes
- 出现位置：Day06-线性DP-游戏DP-数位DP入口

## 中文题意

称一个正整数是「优雅的」（classy），若其十进制表示中非零数位不超过 $3$ 个。例如 $4$、$200000$、$10203$ 是优雅的，而 $4231$、$102306$、$7277420000$ 不是。

给定区间 $[L; R]$，统计满足 $L \le x \le R$ 的优雅整数 $x$ 的个数。

本题一次输入包含多个区间，需要对每个区间分别求解。

## 输入格式（中文）

第一行一个整数 $T$（$1 \le T \le 10^4$）——区间个数。

接下来 $T$ 行，每行两个整数 $L_i$ 和 $R_i$（$1 \le L_i \le R_i \le 10^{18}$）。

## 输出格式（中文）

输出 $T$ 行，第 $i$ 行为区间 $[L_i; R_i]$ 内优雅整数的个数。

## 样例

### 样例 1

输入：

```text
4
1 1000
1024 1024
65536 65536
999999 1000001
```

输出：

```text
1000
1
0
2
```

## 英文原题面

### Statement

Let's call some positive integer classy if its decimal representation contains no more than $3$ non-zero digits. For example, numbers $4$, $200000$, $10203$ are classy and numbers $4231$, $102306$, $7277420000$ are not.
You are given a segment $[L; R]$. Count the number of classy integers $x$ such that $L \le x \le R$.
Each testcase contains several segments, for each of them you are required to solve the problem separately.

### Input

The first line contains a single integer $T$ ($1 \le T \le 10^4$) — the number of segments in a testcase.
Each of the next $T$ lines contains two integers $L_i$ and $R_i$ ($1 \le L_i \le R_i \le 10^{18}$).

### Output

Print $T$ lines — the $i$-th line should contain the number of classy integers on a segment $[L_i; R_i]$.
