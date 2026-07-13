# CF845C · Two TVs

- 难度：1500
- 标签：data structures、greedy、sortings
- 链接：https://codeforces.com/problemset/problem/845/C
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day04-反悔贪心-优先队列-排序贡献

## 中文题意

Polycarp 记下了今天想看的所有电视节目，共 $n$ 个，第 $i$ 个节目在时刻 $l_i$ 开始、$r_i$ 结束。他有两台电视，可以同时用两台电视看两个不同节目，但一台电视在同一时刻只能看一个节目。若一个节目结束的时刻恰好是另一个节目开始的时刻，则这两个节目**不能**在同一台电视上连着看（端点相同也算冲突）。请判断两台电视是否足以看完全部 $n$ 个节目。

## 输入格式（中文）

第一行一个整数 $n$（$1 \le n \le 2 \cdot 10^5$）——节目数。接下来 $n$ 行，每行两个整数 $l_i$、$r_i$（$0 \le l_i < r_i \le 10^9$）——第 $i$ 个节目的开始与结束时刻。

## 输出格式（中文）

若两台电视足以看完所有节目，输出 `YES`（不含引号），否则输出 `NO`（不含引号）。

## 样例

### 样例 1

输入：

```text
3
1 2
2 3
4 5
```

输出：

```text
YES
```

### 样例 2

输入：

```text
4
1 2
2 3
2 3
1 2
```

输出：

```text
NO
```

## 英文原题面

### Statement

Polycarp is a great fan of television.
He wrote down all the TV programs he is interested in for today. His list contains n shows, i-th of them starts at moment li and ends at moment ri.
Polycarp owns two TVs. He can watch two different shows simultaneously with two TVs but he can only watch one show at any given moment on a single TV. If one show ends at the same moment some other show starts then you can't watch them on a single TV.
Polycarp wants to check out all n shows. Are two TVs enough to do so?

### Input

The first line contains one integer n (1 ≤ n ≤ 2·105) — the number of shows.
Each of the next n lines contains two integers li and ri (0 ≤ li < ri ≤ 109) — starting and ending time of i-th show.

### Output

If Polycarp is able to check out all the shows using only two TVs then print "YES" (without quotes). Otherwise, print "NO" (without quotes).
