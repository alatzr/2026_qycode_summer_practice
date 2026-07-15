# CF923B · Producing Snow

- 难度：1600
- 标签：binary search、data structures
- 链接：https://codeforces.com/problemset/problem/923/B
- 时间限制：1 second　内存限制：256 megabytes
- 出现位置：Day05-二分答案-ST表-RMQ

## 中文题意

Bob 送给 Alice 一台造雪机。第 $i$ 天他会造出一堆体积为 $V_i$ 的雪堆放进花园。

每天所有雪堆都会因融化而缩小：当天温度为 $T_i$ 时，每堆雪的体积各减少 $T_i$。若某次减少使一堆雪的体积降到 $0$ 或以下，它就永久消失。各雪堆相互独立。

注意：第 $i$ 天造出的雪堆当天也会融化一次。极端情况下，某天结束时可能一堆雪都不剩。

给定每天造的雪堆初始体积和每天的温度，求每一天融化掉的雪的总体积。

## 输入格式（中文）

第一行一个整数 $N$（$1 \le N \le 10^5$）——天数。

第二行 $N$ 个整数 $V_1, V_2, \dots, V_N$（$0 \le V_i \le 10^9$），$V_i$ 是第 $i$ 天造的雪堆初始体积。

第三行 $N$ 个整数 $T_1, T_2, \dots, T_N$（$0 \le T_i \le 10^9$），$T_i$ 是第 $i$ 天的温度。

## 输出格式（中文）

一行 $N$ 个整数，第 $i$ 个表示第 $i$ 天融化掉的雪的总体积。

## 样例

### 样例 1

输入：

```text
3
10 10 5
5 7 2
```

输出：

```text
5 12 4
```

### 样例 2

输入：

```text
5
30 25 20 15 10
9 10 12 4 13
```

输出：

```text
9 20 35 11 25
```

## 样例解释（英文原文）

In the first sample, Bob first makes a snow pile of volume 10, which melts to the size of 5 on the same day. On the second day, he makes another pile of size 10. Since it is a bit warmer than the day before, the first pile disappears completely while the second pile shrinks to 3. At the end of the second day, he has only a single pile of size 3. On the third day he makes a smaller pile than usual, but as the temperature dropped too, both piles survive till the end of the day.

## 英文原题面

### Statement

Alice likes snow a lot! Unfortunately, this year's winter is already over, and she can't expect to have any more of it. Bob has thus bought her a gift — a large snow maker. He plans to make some amount of snow every day. On day i he will make a pile of snow of volume Vi and put it in her garden.
Each day, every pile will shrink a little due to melting. More precisely, when the temperature on a given day is Ti, each pile will reduce its volume by Ti. If this would reduce the volume of a pile to or below zero, it disappears forever. All snow piles are independent of each other. 
Note that the pile made on day i already loses part of its volume on the same day. In an extreme case, this may mean that there are no piles left at the end of a particular day.
You are given the initial pile sizes and the temperature on each day. Determine the total volume of snow melted on each day.

### Input

The first line contains a single integer N (1 ≤ N ≤ 105) — the number of days. 
The second line contains N integers V1, V2, ..., VN (0 ≤ Vi ≤ 109), where Vi is the initial size of a snow pile made on the day i.
The third line contains N integers T1, T2, ..., TN (0 ≤ Ti ≤ 109), where Ti is the temperature on the day i.

### Output

Output a single line with N integers, where the i-th integer represents the total volume of snow melted on day i.
