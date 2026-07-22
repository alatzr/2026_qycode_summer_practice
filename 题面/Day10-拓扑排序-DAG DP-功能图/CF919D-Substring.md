# CF919D · Substring

- 难度：1700
- 标签：dfs and similar、dp、graphs
- 链接：https://codeforces.com/problemset/problem/919/D
- 时间限制：3 seconds　内存限制：256 megabytes
- 出现位置：Day10-拓扑排序-DAG DP-功能图

## 中文题意

以下为官方英文题意（课堂讲解时请要求学生能用自己的话复述条件与目标）。

You are given a graph with $n$ nodes and $m$ directed edges. One lowercase letter is assigned to each node. We define a path's value as the number of the most frequently occurring letter. For example, if letters on a path are "abaca", then the value of that path is $3$. Your task is find a path whose value is the largest.

**Note（官方）**：
In the first sample, the path with largest value is $1 \to 3 \to 4 \to 5$. The value is $3$ because the letter 'a' appears $3$ times.


## 输入格式（中文）

The first line contains two positive integers $n, m$ ($1 \leq n, m \leq 300\,000$), denoting that the graph has $n$ nodes and $m$ directed edges.
The second line contains a string $s$ with only lowercase English letters. The $i$-th character is the letter assigned to the $i$-th node.
Then $m$ lines follow. Each line contains two integers $x, y$ ($1 \leq x, y \leq n$), describing a directed edge from $x$ to $y$. Note that $x$ can be equal to $y$ and there can be multiple edges between $x$ and $y$. Also the graph can be not connected.


## 输出格式（中文）

Output a single line with a single integer denoting the largest value. If the value can be arbitrarily large, output -1 instead.


## 样例

### 样例 1

输入：

```text
5 4
abaca
1 2
1 3
3 4
4 5
```

输出：

```text
3
```

### 样例 2

输入：

```text
6 6
xzyabc
1 2
3 1
2 3
5 4
4 3
6 4
```

输出：

```text
-1
```

### 样例 3

输入：

```text
10 14
xzyzyzyzqx
1 2
2 4
3 5
4 5
2 6
6 8
6 5
2 10
3 9
10 9
4 6
1 10
2 8
3 7
```

输出：

```text
4
```

## 样例解释（英文原文）

In the first sample, the path with largest value is $1 \to 3 \to 4 \to 5$. The value is $3$ because the letter 'a' appears $3$ times.

## 英文原题面

### Statement

You are given a graph with $n$ nodes and $m$ directed edges. One lowercase letter is assigned to each node. We define a path's value as the number of the most frequently occurring letter. For example, if letters on a path are "abaca", then the value of that path is $3$. Your task is find a path whose value is the largest.

### Input

The first line contains two positive integers $n, m$ ($1 \leq n, m \leq 300\,000$), denoting that the graph has $n$ nodes and $m$ directed edges.
The second line contains a string $s$ with only lowercase English letters. The $i$-th character is the letter assigned to the $i$-th node.
Then $m$ lines follow. Each line contains two integers $x, y$ ($1 \leq x, y \leq n$), describing a directed edge from $x$ to $y$. Note that $x$ can be equal to $y$ and there can be multiple edges between $x$ and $y$. Also the graph can be not connected.

### Output

Output a single line with a single integer denoting the largest value. If the value can be arbitrarily large, output -1 instead.
