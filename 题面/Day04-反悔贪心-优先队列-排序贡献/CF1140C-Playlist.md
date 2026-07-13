# CF1140C · Playlist

- 难度：1600
- 标签：brute force、data structures、sortings
- 链接：https://codeforces.com/problemset/problem/1140/C
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day04-反悔贪心-优先队列-排序贡献

## 中文题意

以下为官方英文题意（课堂讲解时请要求学生能用自己的话复述条件与目标）。

You have a playlist consisting of $n$ songs. The $i$-th song is characterized by two numbers $t_i$ and $b_i$ — its length and beauty respectively. The pleasure of listening to set of songs is equal to the total length of the songs in the set multiplied by the minimum beauty among them. For example, the pleasure of listening to a set of $3$ songs having lengths $[5, 7, 4]$ and beauty values $[11, 14, 6]$ is equal to $(5 + 7 + 4) \cdot 6 = 96$.
You need to choose at most $k$ songs from your playlist, so the pleasure of listening to the set of these songs them is maximum possible.

**Note（官方）**：
In the first test case we can choose songs ${1, 3, 4}$, so the total pleasure is $(4 + 3 + 6) \cdot 6 = 78$.
In the second test case we can choose song $3$. The total pleasure will be equal to $100 \cdot 100 = 10000$.


## 输入格式（中文）

The first line contains two integers $n$ and $k$ ($1 \le k \le n \le 3 \cdot 10^5$) – the number of songs in the playlist and the maximum number of songs you can choose, respectively.
Each of the next $n$ lines contains two integers $t_i$ and $b_i$ ($1 \le t_i, b_i \le 10^6$) — the length and beauty of $i$-th song.


## 输出格式（中文）

Print one integer — the maximum pleasure you can get.


## 样例

### 样例 1

输入：

```text
4 3
4 7
15 1
3 6
6 8
```

输出：

```text
78
```

### 样例 2

输入：

```text
5 3
12 31
112 4
100 100
13 55
55 50
```

输出：

```text
10000
```

## 样例解释（英文原文）

In the first test case we can choose songs ${1, 3, 4}$, so the total pleasure is $(4 + 3 + 6) \cdot 6 = 78$.
In the second test case we can choose song $3$. The total pleasure will be equal to $100 \cdot 100 = 10000$.

## 英文原题面

### Statement

You have a playlist consisting of $n$ songs. The $i$-th song is characterized by two numbers $t_i$ and $b_i$ — its length and beauty respectively. The pleasure of listening to set of songs is equal to the total length of the songs in the set multiplied by the minimum beauty among them. For example, the pleasure of listening to a set of $3$ songs having lengths $[5, 7, 4]$ and beauty values $[11, 14, 6]$ is equal to $(5 + 7 + 4) \cdot 6 = 96$.
You need to choose at most $k$ songs from your playlist, so the pleasure of listening to the set of these songs them is maximum possible.

### Input

The first line contains two integers $n$ and $k$ ($1 \le k \le n \le 3 \cdot 10^5$) – the number of songs in the playlist and the maximum number of songs you can choose, respectively.
Each of the next $n$ lines contains two integers $t_i$ and $b_i$ ($1 \le t_i, b_i \le 10^6$) — the length and beauty of $i$-th song.

### Output

Print one integer — the maximum pleasure you can get.
