# CF1881E · Block Sequence

- 难度：1500
- 标签：dp
- 链接：https://codeforces.com/problemset/problem/1881/E
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day06-线性DP-游戏DP-数位DP入口

## 中文题意

给定长度为 $n$ 的整数序列 $a$。

一个序列被称为「漂亮的」，若它由若干个块依次拼接而成，每个块以自身长度开头：先是块的长度，然后是块内元素。例如序列 [$\color{red}{3},\ \color{red}{3},\ \color{red}{4},\ \color{red}{5},\ \color{green}{2},\ \color{green}{6},\ \color{green}{1}$] 与 [$\color{red}{1},\ \color{red}{8},\ \color{green}{4},\ \color{green}{5},\ \color{green}{2},\ \color{green}{6},\ \color{green}{1}$] 是漂亮的（不同块用不同颜色标出），而 [$1$]、[$1,\ 4,\ 3$]、[$3,\ 2,\ 1$] 不是。

每次操作可以删除序列中的任意一个元素。求使给定序列变漂亮所需的最少操作次数。

## 输入格式（中文）

本题包含 $t$ 组测试数据。第一行一个整数 $t$（$1 \le t \le 10^4$）——测试数据组数。接下来是各组测试数据的描述。

每组测试数据的第一行一个整数 $n$（$1 \le n \le 2 \cdot 10^5$）——序列 $a$ 的长度。

第二行 $n$ 个整数 $a_1, a_2, \dots, a_n$（$1 \le a_i \le 10^6$）——序列 $a$ 的元素。

保证所有测试数据的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式（中文）

对每组测试数据，输出一个数——使序列 $a$ 变漂亮所需的最少删除次数。

## 样例

### 样例 1

输入：

```text
7
7
3 3 4 5 2 6 1
4
5 6 3 2
6
3 4 1 6 7 7
3
1 4 3
5
1 2 3 4 5
5
1 2 3 1 2
5
4 5 5 1 5
```

输出：

```text
0
4
1
1
2
1
0
```

## 样例解释（英文原文）

In the first test case of the example, the given sequence is already beautiful, as shown in the statement.
In the second test case of the example, the sequence can only be made beautiful by removing all elements from it.
In the fifth test case of the example, the sequence can be made beautiful by removing the first and last elements. Then the sequence will become [$2,\ 3,\ 4$].

## 英文原题面

### Statement

Given a sequence of integers $a$ of length $n$.
A sequence is called beautiful if it has the form of a series of blocks, each starting with its length, i.e., first comes the length of the block, and then its elements. For example, the sequences [$\color{red}{3},\ \color{red}{3},\ \color{red}{4},\ \color{red}{5},\ \color{green}{2},\ \color{green}{6},\ \color{green}{1}$] and [$\color{red}{1},\ \color{red}{8},\ \color{green}{4},\ \color{green}{5},\ \color{green}{2},\ \color{green}{6},\ \color{green}{1}$] are beautiful (different blocks are colored differently), while [$1$], [$1,\ 4,\ 3$], [$3,\ 2,\ 1$] are not.
In one operation, you can remove any element from the sequence. What is the minimum number of operations required to make the given sequence beautiful?

### Input

The first line of the input contains a single integer $t$ ($1 \le t \le 10^4$) — the number of test cases. Then follows the descriptions of the test cases.
The first line of each test case contains a single integer $n$ ($1 \le n \le 2 \cdot 10^5$) — the length of the sequence $a$.
The second line of each test case contains $n$ integers $a_1, a_2, \dots, a_n$ ($1 \le a_i \le 10^6$) — the elements of the sequence $a$.
It is guaranteed that the sum of the values of $n$ over all test cases does not exceed $2 \cdot 10^5$.

### Output

For each test case, output a single number — the minimum number of deletions required to make the sequence $a$ beautiful.
