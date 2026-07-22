# CF1056D · Decorate Apple Tree

- 难度：1600
- 标签：constructive algorithms、dfs and similar、dp、graphs、greedy、sortings、trees
- 链接：https://codeforces.com/problemset/problem/1056/D
- 时间限制：1 second　内存限制：256 megabytes
- 出现位置：Day09-树上DFS-DFS序-树形递归

## 中文题意

以下为官方英文题意（课堂讲解时请要求学生能用自己的话复述条件与目标）。

There is one apple tree in Arkady's garden. It can be represented as a set of junctions connected with branches so that there is only one way to reach any junctions from any other one using branches. The junctions are enumerated from $1$ to $n$, the junction $1$ is called the root.
A subtree of a junction $v$ is a set of junctions $u$ such that the path from $u$ to the root must pass through $v$. Note that $v$ itself is included in a subtree of $v$.
A leaf is such a junction that its subtree contains exactly one junction.
The New Year is coming, so Arkady wants to decorate the tree. He will put a light bulb of some color on each leaf junction and then count the number happy junctions. A happy junction is such a junction $t$ that all light bulbs in the subtree of $t$ have different colors.
Arkady is interested in the following question: for each $k$ from $1$ to $n$, what is the minimum number of different colors needed to make the number of happy junctions be greater than or equal to $k$?

**Note（官方）**：
In the first example for $k = 1$ and $k = 2$ we can use only one color: the junctions $2$ and $3$ will be happy. For $k = 3$ you have to put the bulbs of different colors to make all the junctions happy.
In the second example for $k = 4$ you can, for example, put the bulbs of color $1$ in junctions $2$ and $4$, and a bulb of color $2$ into junction $5$. The happy junctions are the ones with indices $2$, $3$, $4$ and $5$ then.


## 输入格式（中文）

The first line contains a single integer $n$ ($1 \le n \le 10^5$) — the number of junctions in the tree.
The second line contains $n - 1$ integers $p_2$, $p_3$, ..., $p_n$ ($1 \le p_i  \lt  i$), where $p_i$ means there is a branch between junctions $i$ and $p_i$. It is guaranteed that this set of branches forms a tree.


## 输出格式（中文）

Output $n$ integers. The $i$-th of them should be the minimum number of colors needed to make the number of happy junctions be at least $i$.


## 样例

### 样例 1

输入：

```text
3
1 1
```

输出：

```text
1 1 2 
```

### 样例 2

输入：

```text
5
1 1 3 3
```

输出：

```text
1 1 1 2 3 
```

## 样例解释（英文原文）

In the first example for $k = 1$ and $k = 2$ we can use only one color: the junctions $2$ and $3$ will be happy. For $k = 3$ you have to put the bulbs of different colors to make all the junctions happy.
In the second example for $k = 4$ you can, for example, put the bulbs of color $1$ in junctions $2$ and $4$, and a bulb of color $2$ into junction $5$. The happy junctions are the ones with indices $2$, $3$, $4$ and $5$ then.

## 英文原题面

### Statement

There is one apple tree in Arkady's garden. It can be represented as a set of junctions connected with branches so that there is only one way to reach any junctions from any other one using branches. The junctions are enumerated from $1$ to $n$, the junction $1$ is called the root.
A subtree of a junction $v$ is a set of junctions $u$ such that the path from $u$ to the root must pass through $v$. Note that $v$ itself is included in a subtree of $v$.
A leaf is such a junction that its subtree contains exactly one junction.
The New Year is coming, so Arkady wants to decorate the tree. He will put a light bulb of some color on each leaf junction and then count the number happy junctions. A happy junction is such a junction $t$ that all light bulbs in the subtree of $t$ have different colors.
Arkady is interested in the following question: for each $k$ from $1$ to $n$, what is the minimum number of different colors needed to make the number of happy junctions be greater than or equal to $k$?

### Input

The first line contains a single integer $n$ ($1 \le n \le 10^5$) — the number of junctions in the tree.
The second line contains $n - 1$ integers $p_2$, $p_3$, ..., $p_n$ ($1 \le p_i  \lt  i$), where $p_i$ means there is a branch between junctions $i$ and $p_i$. It is guaranteed that this set of branches forms a tree.

### Output

Output $n$ integers. The $i$-th of them should be the minimum number of colors needed to make the number of happy junctions be at least $i$.
