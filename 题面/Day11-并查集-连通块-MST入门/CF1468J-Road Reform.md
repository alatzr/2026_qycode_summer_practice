# CF1468J · Road Reform

- 难度：1800
- 标签：dsu、graphs、greedy
- 链接：https://codeforces.com/problemset/problem/1468/J
- 时间限制：2 seconds　内存限制：512 megabytes
- 出现位置：Day11-并查集-连通块-MST入门

## 中文题意

Berland 有 $n$ 座城市和 $m$ 条双向道路，第 $i$ 条道路连接城市 $x_i$ 与 $y_i$，限速为 $s_i$。道路网保证任意两城市互相可达。

交通部计划进行道路改革：

1. 拆除 $m - (n - 1)$ 条道路，使剩下的 $n - 1$ 条道路仍保持任意两城市互相可达，即剩余道路构成一棵无向树；
2. 之后可以逐次修改剩余道路的限速，每次操作将某条道路的限速加 $1$ 或减 $1$。

目标是使保留的 $n - 1$ 条道路中限速的最大值恰好等于 $k$。求达到目标所需的最少限速修改次数。

例如，若初始道路网如原题配图（图略）且 $k = 7$，一种最优方案是拆除道路 $1$–$4$ 与 $3$–$4$，再将道路 $2$–$3$ 的限速减 $1$。

## 输入格式（中文）

本题包含 $t$ 组测试数据。第一行一个整数 $t$（$1 \le t \le 1000$），表示测试数据组数。

每组数据第一行三个整数 $n$、$m$、$k$（$2 \le n \le 2 \cdot 10^5$；$n - 1 \le m \le \min(2 \cdot 10^5, \frac{n(n-1)}{2})$；$1 \le k \le 10^9$），分别表示城市数、道路数和要求的最大限速。

接下来 $m$ 行，第 $i$ 行三个整数 $x_i$、$y_i$、$s_i$（$1 \le x_i, y_i \le n$；$x_i \ne y_i$；$1 \le s_i \le 10^9$），表示第 $i$ 条道路连接的两座城市及其限速。所有道路均为双向。

保证每组数据的道路网连通，且任意两城市之间至多一条道路。

保证所有测试数据的 $n$ 之和不超过 $2 \cdot 10^5$，$m$ 之和不超过 $2 \cdot 10^5$。

## 输出格式（中文）

对每组测试数据，输出一个整数，表示使保留的 $n - 1$ 条道路的最大限速恰好为 $k$ 所需的最少修改次数。

## 样例

### 样例 1

输入：

```text
4
4 5 7
4 1 3
1 2 5
2 3 8
2 4 1
3 4 4
4 6 5
1 2 1
1 3 1
1 4 2
2 4 1
4 3 1
3 2 1
3 2 10
1 2 8
1 3 10
5 5 15
1 2 17
3 1 15
2 3 10
1 4 14
2 5 8
```

输出：

```text
1
3
0
0
```

## 样例解释（英文原文）

The explanation for the example test:
The first test case is described in the problem statement.
In the second test case, the road network initially looks like that:
  
The Ministry can demolish the roads $1$–$2$, $3$–$2$ and $3$–$4$, and then increase the speed limit on the road $1$–$4$ three times.
In the third test case, the road network already meets all the requirements.
In the fourth test case, it is enough to demolish the road $1$–$2$ so the resulting road network meets the requirements.

## 英文原题面

### Statement

There are $n$ cities and $m$ bidirectional roads in Berland. The $i$-th road connects the cities $x_i$ and $y_i$, and has the speed limit $s_i$. The road network allows everyone to get from any city to any other city. 
The Berland Transport Ministry is planning a road reform.
First of all, maintaining all $m$ roads is too costly, so $m - (n - 1)$ roads will be demolished in such a way that the remaining $(n - 1)$ roads still allow to get to any city from any other city. Formally, the remaining roads should represent an undirected tree.
Secondly, the speed limits on the remaining roads might be changed. The changes will be done sequentially, each change is either increasing the speed limit on some road by $1$, or decreasing it by $1$. Since changing the speed limit requires a lot of work, the Ministry wants to minimize the number of changes.
The goal of the Ministry is to have a road network of $(n - 1)$ roads with the maximum speed limit over all roads equal to exactly $k$. They assigned you the task of calculating the minimum number of speed limit changes they have to perform so the road network meets their requirements.
For example, suppose the initial map of Berland looks like that, and $k = 7$:
  
Then one of the optimal courses of action is to demolish the roads $1$–$4$ and $3$–$4$, and then decrease the speed limit on the road $2$–$3$ by $1$, so the resulting road network looks like that:

### Input

The first line contains one integer $t$ ($1 \le t \le 1000$) — the number of test cases.
The first line of each test case contains three integers $n$, $m$ and $k$ ($2 \le n \le 2 \cdot 10^5$; $n - 1 \le m \le \min(2 \cdot 10^5, \frac{n(n-1)}{2})$; $1 \le k \le 10^9$) — the number of cities, the number of roads and the required maximum speed limit, respectively.
Then $m$ lines follow. The $i$-th line contains three integers $x_i$, $y_i$ and $s_i$ ($1 \le x_i, y_i \le n$; $x_i \ne y_i$; $1 \le s_i \le 10^9$) — the cities connected by the $i$-th road and the speed limit on it, respectively. All roads are bidirectional.
The road network in each test case is connected (that is, it is possible to reach any city from any other city by traveling along the road), and each pair of cities is connected by at most one road.
The sum of $n$ over all test cases does not exceed $2 \cdot 10^5$. Similarly, the sum of $m$ over all test cases does not exceed $2 \cdot 10^5$.

### Output

For each test case, print one integer — the minimum number of changes the Ministry has to perform so that the maximum speed limit among the remaining $(n - 1)$ roads is exactly $k$.
