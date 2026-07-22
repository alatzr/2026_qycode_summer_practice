# CF2233C · Cost of a Bracket Sequence

- 难度：1400
- 标签：brute force、dp、greedy
- 链接：https://codeforces.com/problemset/problem/2233/C
- 时间限制：2 seconds　内存限制：512 megabytes
- 出现位置：Day07-阶段模拟1-J保温-S入门衔接

## 中文题意

定义一个括号串的**代价**为其最长合法括号子序列的长度。

给定一个由 `(` 和 `)` 组成的长度为 $n$ 的括号串 $s$ 和一个整数 $k$，你最多可以删除 $k$ 个字符，目标是使删除后括号串的代价**最小**。

**输出一个长度为 $n$ 的 01 串**表示删除方案：第 $i$ 位为 `1` 表示删除 $s$ 的第 $i$ 个字符，`0` 表示保留。要求 `1` 的个数不超过 $k$，且删除后代价最小。若有多种方案，输出任意一种。

本题包含 $t$ 组测试数据。

## 输入格式（中文）

第一行一个整数 $t$（$1 \le t \le 10^3$）——测试数据组数。

每组第一行两个整数 $n$、$k$（$1 \le n \le 5000$；$0 \le k \le n$）——串长与最多删除数。

第二行一个长为 $n$、仅含 `(` 和 `)` 的括号串 $s$。

保证所有数据的 $n$ 之和不超过 $5000$。

## 输出格式（中文）

对每组数据输出一个长度为 $n$ 的 01 串：第 $i$ 位为 `1` 表示删除对应字符，`0` 表示保留。`1` 的个数不得超过 $k$，删除后代价须最小。多解输出任意一种（本题用 special judge 校验）。

## 样例

### 样例 1

输入：

```text
10
2 1
)(
2 0
()
4 1
(())
4 1
())(
5 1
((())
6 2
()()()
6 2
(()())
6 2
())(()
7 3
(()((()
10 3
(()())())(
```

输出：

```text
00
00
1000
1000
00010
101000
001001
100001
1100001
0101001000
```

## 样例解释（英文原文）

In the first test case, the cost of the string is already $0$, so it is possible not to delete anything.
In the third test case, it is impossible to obtain a string of cost $0$ after one deletion, but it is possible to obtain a string of cost $2$ by deleting any character.

## 英文原题面

### Statement

Let the cost of an arbitrary bracket string be the length of it's longest subsequence$^{\text{∗}}$ that is a regular bracket sequence$^{\text{†}}$.
You are given a bracket string $s$ and an integer $k$. Your task is to remove at most $k$ characters from the string $s$ so that the cost of the resulting string is minimized.
$^{\text{∗}}$A sequence $a$ is a subsequence of a sequence $b$ if $a$ can be obtained from $b$ by the deletion of several (possibly, zero or all) element from arbitrary positions.
$^{\text{†}}$A bracket sequence is called regular if it is possible to obtain a correct arithmetic expression by inserting the characters $+$ and $1$ into this sequence. For example, the sequences "$\texttt{(())()}$", "$\texttt{()}$", and "$\texttt{(()(()))}$" are regular, while "$\texttt{)(}$", "$\texttt{(()}$", and "$\texttt{(()))(}$" — are not.

### Input

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^3$). The description of the test cases follows.
The first line of each test case contains two integers $n$ and $k$ ($1 \le n \le 5\,000$; $0 \le k \le n$) — the length of the string $s$ and the maximum number of deletions.
The second line of each test case contains a string $s$ of length $n$ consisting of the characters "$\texttt{(}$" and/or "$\texttt{)}$".
Additional input constraints: 
 -  the sum of $n$ over all test cases does not exceed $5\,000$.

### Output

For each test case, output a binary string of length $n$. The $i$-th character should be equal to "1" if the corresponding character of the string $s$ is removed, and "0" otherwise.
The number of ones in the string must not exceed $k$. The cost of the string obtained after removing the marked characters must be as small as possible.
If there are several answers, output any of them.
