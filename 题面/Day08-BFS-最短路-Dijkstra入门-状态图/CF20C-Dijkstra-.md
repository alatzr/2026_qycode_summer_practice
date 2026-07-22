# CF20C · Dijkstra?

- 难度：1900
- 标签：graphs、shortest paths
- 链接：https://codeforces.com/problemset/problem/20/C
- 时间限制：1 second　内存限制：64 megabytes
- 出现位置：Day08-BFS-最短路-Dijkstra入门-状态图/选做

## 中文题意

以下为官方英文题意（课堂讲解时请要求学生能用自己的话复述条件与目标）。

You are given a weighted undirected graph. The vertices are enumerated from 1 to n. Your task is to find the shortest path between the vertex 1 and the vertex n.


## 输入格式（中文）

The first line contains two integers n and m (2 ≤ n ≤ 105, 0 ≤ m ≤ 105), where n is the number of vertices and m is the number of edges. Following m lines contain one edge each in form ai, bi and wi (1 ≤ ai, bi ≤ n, 1 ≤ wi ≤ 106), where ai, bi are edge endpoints and wi is the length of the edge.
It is possible that the graph has loops and multiple edges between pair of vertices.


## 输出格式（中文）

Write the only integer -1 in case of no path. Write the shortest path in opposite case. If there are many solutions, print any of them.


## 样例

### 样例 1

输入：

```text
5 6
1 2 2
2 5 5
2 3 4
1 4 1
4 3 3
3 5 1
```

输出：

```text
1 4 3 5 
```

### 样例 2

输入：

```text
5 6
1 2 2
2 5 5
2 3 4
1 4 1
4 3 3
3 5 1
```

输出：

```text
1 4 3 5 
```

## 英文原题面

### Statement

You are given a weighted undirected graph. The vertices are enumerated from 1 to n. Your task is to find the shortest path between the vertex 1 and the vertex n.

### Input

The first line contains two integers n and m (2 ≤ n ≤ 105, 0 ≤ m ≤ 105), where n is the number of vertices and m is the number of edges. Following m lines contain one edge each in form ai, bi and wi (1 ≤ ai, bi ≤ n, 1 ≤ wi ≤ 106), where ai, bi are edge endpoints and wi is the length of the edge.
It is possible that the graph has loops and multiple edges between pair of vertices.

### Output

Write the only integer -1 in case of no path. Write the shortest path in opposite case. If there are many solutions, print any of them.
