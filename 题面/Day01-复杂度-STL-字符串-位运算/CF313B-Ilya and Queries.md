# CF313B · Ilya and Queries

- 难度：1100
- 标签：dp、implementation
- 链接：https://codeforces.com/problemset/problem/313/B
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day01-复杂度-STL-字符串-位运算

## 中文题意

狮子 Ilya 想帮助所有朋友通过考试，他们需要解决下面这道 IT 考试题。

给定字符串 s = s1s2... sn（n 为串长），仅由字符 "." 和 "#" 组成，另给出 m 个询问。每个询问由一对整数 li, ri（1 ≤ li < ri ≤ n）描述，其答案为满足 li ≤ i < ri 且 si = si + 1 的整数 i 的个数。

Ilya 想帮朋友，可谁来帮他呢？请你替 Ilya 解决这个问题。

## 输入格式（中文）

第一行包含长度为 n 的字符串 s（2 ≤ n ≤ 105），保证仅由字符 "." 和 "#" 组成。

下一行包含整数 m（1 ≤ m ≤ 105）——询问个数。接下来 m 行依次描述各询问，第 i 行包含两个整数 li, ri（1 ≤ li < ri ≤ n）。

## 输出格式（中文）

输出 m 个整数——按输入顺序给出每个询问的答案。

## 样例

### 样例 1

输入：

```text
......
4
3 4
2 3
1 6
2 6
```

输出：

```text
1
1
5
4
```

### 样例 2

输入：

```text
#..###
5
1 3
5 6
1 5
3 6
3 4
```

输出：

```text
1
1
2
2
0
```

## 英文原题面

### Statement

Ilya the Lion wants to help all his friends with passing exams. They need to solve the following problem to pass the IT exam.
You've got string s = s1s2... sn (n is the length of the string), consisting only of characters "." and "#" and m queries. Each query is described by a pair of integers li, ri (1 ≤ li < ri ≤ n). The answer to the query li, ri is the number of such integers i (li ≤ i < ri), that si = si + 1.
Ilya the Lion wants to help his friends but is there anyone to help him? Help Ilya, solve the problem.

### Input

The first line contains string s of length n (2 ≤ n ≤ 105). It is guaranteed that the given string only consists of characters "." and "#".
The next line contains integer m (1 ≤ m ≤ 105) — the number of queries. Each of the next m lines contains the description of the corresponding query. The i-th line contains integers li, ri (1 ≤ li < ri ≤ n).

### Output

Print m integers — the answers to the queries in the order in which they are given in the input.
