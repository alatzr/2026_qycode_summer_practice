# CF601A · The Two Routes

- 难度：1600
- 标签：graphs、shortest paths
- 链接：https://codeforces.com/problemset/problem/601/A
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day08-BFS-最短路-Dijkstra入门-状态图

## 中文题意

以下为官方英文题意（课堂讲解时请要求学生能用自己的话复述条件与目标）。

In Absurdistan, there are n towns (numbered 1 through n) and m bidirectional railways. There is also an absurdly simple road network — for each pair of different towns x and y, there is a bidirectional road between towns x and y if and only if there is no railway between them. Travelling to a different town using one railway or one road always takes exactly one hour.
A train and a bus leave town 1 at the same time. They both have the same destination, town n, and don't make any stops on the way (but they can wait in town n). The train can move only along railways and the bus can move only along roads.
You've been asked to plan out routes for the vehicles; each route can use any road/railway multiple times. One of the most important aspects to consider is safety — in order to avoid accidents at railway crossings, the train and the bus must not arrive at the same town (except town n) simultaneously.
Under these constraints, what is the minimum number of hours needed for both vehicles to reach town n (the maximum of arrival times of the bus and the train)? Note, that bus and train are not required to arrive to the town n at the same moment of time, but are allowed to do so.

**Note（官方）**：
In the first sample, the train can take the route  and the bus can take the route . Note that they can arrive at town 4 at the same time.
In the second sample, Absurdistan is ruled by railwaymen. There are no roads, so there's no way for the bus to reach town 4.


## 输入格式（中文）

The first line of the input contains two integers n and m (2 ≤ n ≤ 400, 0 ≤ m ≤ n(n - 1) / 2) — the number of towns and the number of railways respectively.
Each of the next m lines contains two integers u and v, denoting a railway between towns u and v (1 ≤ u, v ≤ n, u ≠ v).
You may assume that there is at most one railway connecting any two towns.


## 输出格式（中文）

Output one integer — the smallest possible time of the later vehicle's arrival in town n. If it's impossible for at least one of the vehicles to reach town n, output  - 1.


## 样例

### 样例 1

输入：

```text
4 2
1 3
3 4
```

输出：

```text
2
```

### 样例 2

输入：

```text
4 6
1 2
1 3
1 4
2 3
2 4
3 4
```

输出：

```text
-1
```

### 样例 3

输入：

```text
5 5
4 2
3 5
4 5
5 1
1 2
```

输出：

```text
3
```

## 样例解释（英文原文）

In the first sample, the train can take the route  and the bus can take the route . Note that they can arrive at town 4 at the same time.
In the second sample, Absurdistan is ruled by railwaymen. There are no roads, so there's no way for the bus to reach town 4.

## 英文原题面

### Statement

In Absurdistan, there are n towns (numbered 1 through n) and m bidirectional railways. There is also an absurdly simple road network — for each pair of different towns x and y, there is a bidirectional road between towns x and y if and only if there is no railway between them. Travelling to a different town using one railway or one road always takes exactly one hour.
A train and a bus leave town 1 at the same time. They both have the same destination, town n, and don't make any stops on the way (but they can wait in town n). The train can move only along railways and the bus can move only along roads.
You've been asked to plan out routes for the vehicles; each route can use any road/railway multiple times. One of the most important aspects to consider is safety — in order to avoid accidents at railway crossings, the train and the bus must not arrive at the same town (except town n) simultaneously.
Under these constraints, what is the minimum number of hours needed for both vehicles to reach town n (the maximum of arrival times of the bus and the train)? Note, that bus and train are not required to arrive to the town n at the same moment of time, but are allowed to do so.

### Input

The first line of the input contains two integers n and m (2 ≤ n ≤ 400, 0 ≤ m ≤ n(n - 1) / 2) — the number of towns and the number of railways respectively.
Each of the next m lines contains two integers u and v, denoting a railway between towns u and v (1 ≤ u, v ≤ n, u ≠ v).
You may assume that there is at most one railway connecting any two towns.

### Output

Output one integer — the smallest possible time of the later vehicle's arrival in town n. If it's impossible for at least one of the vehicles to reach town n, output  - 1.
