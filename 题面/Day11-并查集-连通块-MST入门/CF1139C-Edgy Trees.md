# CF1139C · Edgy Trees

- 难度：1500
- 标签：dfs and similar、dsu、graphs、math、trees
- 链接：https://codeforces.com/problemset/problem/1139/C
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day11-并查集-连通块-MST入门

## 中文题意

给定一棵 $n$ 个点的树（无环连通无向图），$n - 1$ 条边中每条被染成黑色或红色。另给定整数 $k$。

考虑长度为 $k$ 的点序列 $[a_1, a_2, \ldots, a_k]$：从 $a_1$ 出发，沿最短路径走到 $a_2$，再沿最短路径走到 $a_3$，依此类推，直到沿最短路径从 $a_{k-1}$ 走到 $a_k$（过程中可以重复经过同一条边或同一个点）。若整个过程中至少经过一条黑边，则称该序列是好的。

长度为 $k$ 的点序列共有 $n^k$ 个，统计其中好序列的数量。答案可能很大，对 $10^9+7$ 取模后输出。

## 输入格式（中文）

第一行两个整数 $n$ 和 $k$（$2 \le n \le 10^5$，$2 \le k \le 100$），分别表示树的大小与点序列的长度。

接下来 $n - 1$ 行，每行三个整数 $u_i$、$v_i$、$x_i$（$1 \le u_i, v_i \le n$，$x_i \in \{0, 1\}$），其中 $u_i$、$v_i$ 为一条边的两个端点，$x_i$ 为这条边的颜色（$0$ 表示红边，$1$ 表示黑边）。

## 输出格式（中文）

输出好序列的数量对 $10^9 + 7$ 取模的结果。

## 样例

### 样例 1

输入：

```text
4 4
1 2 1
2 3 1
3 4 1
```

输出：

```text
252
```

### 样例 2

输入：

```text
4 6
1 2 0
1 3 0
1 4 0
```

输出：

```text
0
```

### 样例 3

输入：

```text
3 5
1 2 1
2 3 0
```

输出：

```text
210
```

## 样例解释（英文原文）

In the first example, all sequences ($4^4$) of length $4$ except the following are good: 
 -  $[1, 1, 1, 1]$
-  $[2, 2, 2, 2]$
-  $[3, 3, 3, 3]$
-  $[4, 4, 4, 4]$ 

In the second example, all edges are red, hence there aren't any good sequences.

## 英文原题面

### Statement

You are given a tree (a connected undirected graph without cycles) of $n$ vertices. Each of the $n - 1$ edges of the tree is colored in either black or red.
You are also given an integer $k$. Consider sequences of $k$ vertices. Let's call a sequence $[a_1, a_2, \ldots, a_k]$ good if it satisfies the following criterion:
 -  We will walk a path (possibly visiting same edge/vertex multiple times) on the tree, starting from $a_1$ and ending at $a_k$. 
-  Start at $a_1$, then go to $a_2$ using the shortest path between $a_1$ and $a_2$, then go to $a_3$ in a similar way, and so on, until you travel the shortest path between $a_{k-1}$ and $a_k$.
-  If you walked over at least one black edge during this process, then the sequence is good. 

  
Consider the tree on the picture. If $k=3$ then the following sequences are good: $[1, 4, 7]$, $[5, 5, 3]$ and $[2, 3, 7]$. The following sequences are not good: $[1, 4, 6]$, $[5, 5, 5]$, $[3, 7, 3]$.
There are $n^k$ sequences of vertices, count how many of them are good. Since this number can be quite large, print it modulo $10^9+7$.

### Input

The first line contains two integers $n$ and $k$ ($2 \le n \le 10^5$, $2 \le k \le 100$), the size of the tree and the length of the vertex sequence.
Each of the next $n - 1$ lines contains three integers $u_i$, $v_i$ and $x_i$ ($1 \le u_i, v_i \le n$, $x_i \in \{0, 1\}$), where $u_i$ and $v_i$ denote the endpoints of the corresponding edge and $x_i$ is the color of this edge ($0$ denotes red edge and $1$ denotes black edge).

### Output

Print the number of good sequences modulo $10^9 + 7$.
