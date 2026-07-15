# CF489C · Given Length and Sum of Digits...

- 难度：1400
- 标签：dp、greedy、implementation
- 链接：https://codeforces.com/problemset/problem/489/C
- 时间限制：1 second　内存限制：256 megabytes
- 出现位置：Day06-线性DP-游戏DP-数位DP入口

## 中文题意

给定正整数 $m$ 和非负整数 $s$。求所有位数为 $m$、数位和为 $s$ 的数中的最小值与最大值。所求的数必须是十进制下无前导零的非负整数。

## 输入格式（中文）

一行两个整数 $m, s$（$1 \le m \le 100$，$0 \le s \le 900$）——所求数的位数与数位和。

## 输出格式（中文）

输出满足条件的两个非负整数——先输出最小值，再输出最大值。若不存在满足条件的数，输出 `-1 -1`（不含引号）。

## 样例

### 样例 1

输入：

```text
2 15
```

输出：

```text
69 96
```

### 样例 2

输入：

```text
3 0
```

输出：

```text
-1 -1
```

## 英文原题面

### Statement

You have a positive integer m and a non-negative integer s. Your task is to find the smallest and the largest of the numbers that have length m and sum of digits s. The required numbers should be non-negative integers written in the decimal base without leading zeroes.

### Input

The single line of the input contains a pair of integers m, s (1 ≤ m ≤ 100, 0 ≤ s ≤ 900) — the length and the sum of the digits of the required numbers.

### Output

In the output print the pair of the required non-negative integer numbers — first the minimum possible number, then — the maximum possible number. If no numbers satisfying conditions required exist, print the pair of numbers "-1 -1" (without the quotes).
