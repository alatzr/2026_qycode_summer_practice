# CF552E · Vanya and Brackets

- 难度：2100
- 标签：brute force、dp、expression parsing、greedy、implementation、strings
- 链接：https://codeforces.com/problemset/problem/552/E
- 时间限制：1 second　内存限制：256 megabytes
- 出现位置：Day02-表达式解析-栈-括号序列/选做；Day30-结营-个人错题重做-公共重测池-尖子拔高

## 中文题意

给定一个形如 $x_1 \circ x_2 \circ \cdots \circ x_n$ 的表达式，其中 $x_1, x_2, \ldots, x_n$ 是 $1$ 到 $9$ 的数字，符号 $\circ$ 表示加号 `+` 或乘号 `*`。你需要在表达式中恰好添加一对括号，使得所得表达式的值最大。

## 输入格式（中文）

第一行为表达式 $s$（$1 \le |s| \le 5001$，且 $|s|$ 为奇数），其奇数位置只包含 $1$ 到 $9$ 的数字，偶数位置只包含符号 `+` 和 `*`。其中 `*` 号的个数不超过 $15$ 个。

## 输出格式（中文）

输出一行一个整数，表示所得表达式的最大可能值。

## 样例

### 样例 1

输入：

```text
3+5*7+8*4
```

输出：

```text
303
```

### 样例 2

输入：

```text
2+3*5
```

输出：

```text
25
```

### 样例 3

输入：

```text
3*4*5
```

输出：

```text
60
```

## 样例解释（英文原文）

Note to the first sample test. 3 + 5 * (7 + 8) * 4 = 303.
Note to the second sample test. (2 + 3) * 5 = 25.
Note to the third sample test. (3 * 4) * 5 = 60 (also many other variants are valid, for instance, (3) * 4 * 5 = 60).

## 英文原题面

### Statement

Vanya is doing his maths homework. He has an expression of form , where x1, x2, ..., xn are digits from 1 to 9, and sign  represents either a plus '+' or the multiplication sign '*'. Vanya needs to add one pair of brackets in this expression so that to maximize the value of the resulting expression.

### Input

The first line contains expression s (1 ≤ |s| ≤ 5001, |s| is odd), its odd positions only contain digits from 1 to 9, and even positions only contain signs  +  and  * . 
The number of signs  *  doesn't exceed 15.

### Output

In the first line print the maximum possible value of an expression.
