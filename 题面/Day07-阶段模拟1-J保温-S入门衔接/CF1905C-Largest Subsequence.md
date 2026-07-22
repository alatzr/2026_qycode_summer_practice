# CF1905C · Largest Subsequence

- 难度：1400
- 标签：greedy、strings
- 链接：https://codeforces.com/problemset/problem/1905/C
- 时间限制：1 second　内存限制：256 megabytes
- 出现位置：Day07-阶段模拟1-J保温-S入门衔接

## 中文题意

给定长度为 $n$ 的字符串 $s$。一次操作定义为：取出 $s$ 的**字典序最大**的子序列，将这个子序列整体循环右移一位后放回原来的位置。

求把 $s$ 变成非降序（有序）所需的最少操作次数；若无法做到，输出 $-1$。

本题包含 $t$ 组测试数据。

## 输入格式（中文）

第一行一个整数 $t$（$1 \le t \le 10^4$）——测试数据组数。

每组第一行一个整数 $n$（$1 \le n \le 2\cdot10^5$）——字符串长度。

第二行一个长为 $n$ 的字符串 $s$，仅含小写英文字母。

保证所有数据的 $n$ 之和不超过 $2\cdot10^5$。

## 输出格式（中文）

对每组数据输出一行一个整数：使 $s$ 有序的最少操作次数；无法做到则输出 $-1$。

## 样例

### 样例 1

输入：

```text
6
5
aaabc
3
acb
3
bac
4
zbca
15
czddeneeeemigec
13
cdefmopqsvxzz
```

输出：

```text
0
1
-1
2
6
0
```

## 样例解释（英文原文）

In the first test case, the string $s$ is already sorted, so we need no operations.
In the second test case, doing one operation, we will select cb and cyclic shift it. The string $s$ is now abc which is sorted.
In the third test case, $s$ cannot be sorted.
In the fourth test case we will perform the following operations:
-  The lexicographically largest subsequence is zca. Then $s$ becomes abzc.
-  The lexicographically largest subsequence is zc. Then $s$ becomes abcz. The string becomes sorted.

Thus, we need $2$ operations.

## 英文原题面

### Statement

Given is a string $s$ of length $n$. In one operation you can select the lexicographically largest$^\dagger$ subsequence of string $s$ and cyclic shift it to the right$^\ddagger$. 
Your task is to calculate the minimum number of operations it would take for $s$ to become sorted, or report that it never reaches a sorted state.
$^\dagger$A string $a$ is lexicographically smaller than a string $b$ if and only if one of the following holds:
-  $a$ is a prefix of $b$, but $a \ne b$;
-  In the first position where $a$ and $b$ differ, the string $a$ has a letter that appears earlier in the alphabet than the corresponding letter in $b$.

$^\ddagger$By cyclic shifting the string $t_1t_2\ldots t_m$ to the right, we get the string $t_mt_1\ldots t_{m-1}$.

### Input

Each test consists of multiple test cases. The first line contains a single integer $t$ ($1 \le t \le 10^4$) — the number of test cases. The description of the test cases follows.
The first line of each test case contains a single integer $n$ ($1 \le n \le 2 \cdot 10^5$) — the length of the string $s$.
The second line of each test case contains a single string $s$ of length $n$, consisting of lowercase English letters.
It is guaranteed that sum of $n$ over all test cases does not exceed $2 \cdot 10^5$.

### Output

For each test case, output a single integer — the minimum number of operations required to make $s$ sorted, or $-1$ if it's impossible.
