# CF103B · Cthulhu

- 难度：1500
- 标签：dfs and similar、dsu、graphs
- 链接：https://codeforces.com/problemset/problem/103/B
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day11-并查集-连通块-MST入门

## 中文题意

给定一张 $n$ 个点 $m$ 条边的无向图。若这张图可以表示为三棵或更多有根树、且这些树的根恰好被一个简单环连接起来，则称它是 Cthulhu。判断给定的图是否是 Cthulhu。

保证图中无重边、无自环。

## 输入格式（中文）

第一行两个整数 $n$ 和 $m$，表示图的点数和边数（$1 \le n \le 100$，$0 \le m \le$ ）。（注：英文原文此处 $m$ 的上界公式缺失。）

接下来 $m$ 行，每行两个整数 $x$ 和 $y$，表示点 $x$ 与点 $y$ 之间存在一条边（$1 \le x, y \le n$，$x \ne y$）。任意一对点之间至多一条边，没有边连接点自身。

## 输出格式（中文）

若图不是 Cthulhu，输出 `NO`；若是，输出 `FHTAGN!`。（原文未说明大小写不敏感，按原样输出。）

## 样例

### 样例 1

输入：

```text
6 6
6 3
6 4
5 1
2 5
1 4
5 4
```

输出：

```text
FHTAGN!
```

### 样例 2

输入：

```text
6 5
5 6
4 6
3 1
5 1
1 2
```

输出：

```text
NO
```

## 样例解释（英文原文）

Let us denote as a simple cycle a set of v vertices that can be numbered so that the edges will only exist between vertices number 1 and 2, 2 and 3, ..., v - 1 and v, v and 1.
A tree is a connected undirected graph consisting of n vertices and n - 1 edges (n > 0).
A rooted tree is a tree where one vertex is selected to be the root.

## 英文原题面

### Statement

...Once upon a time a man came to the sea. The sea was stormy and dark. The man started to call for the little mermaid to appear but alas, he only woke up Cthulhu...
Whereas on the other end of the world Pentagon is actively collecting information trying to predict the monster's behavior and preparing the secret super weapon. Due to high seismic activity and poor weather conditions the satellites haven't yet been able to make clear shots of the monster. The analysis of the first shot resulted in an undirected graph with n vertices and m edges. Now the world's best minds are about to determine whether this graph can be regarded as Cthulhu or not.
To add simplicity, let's suppose that Cthulhu looks from the space like some spherical body with tentacles attached to it. Formally, we shall regard as Cthulhu such an undirected graph that can be represented as a set of three or more rooted trees, whose roots are connected by a simple cycle.
It is guaranteed that the graph contains no multiple edges and self-loops.

### Input

The first line contains two integers — the number of vertices n and the number of edges m of the graph (1 ≤ n ≤ 100, 0 ≤ m ≤ ).
Each of the following m lines contains a pair of integers x and y, that show that an edge exists between vertices x and y (1 ≤ x, y ≤ n, x ≠ y). For each pair of vertices there will be at most one edge between them, no edge connects a vertex to itself.

### Output

Print "NO", if the graph is not Cthulhu and "FHTAGN!" if it is.
