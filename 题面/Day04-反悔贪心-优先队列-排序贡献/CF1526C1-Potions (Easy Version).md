# CF1526C1 · Potions (Easy Version)

- 难度：1500
- 标签：brute force、data structures、dp、greedy
- 链接：https://codeforces.com/problemset/problem/1526/C1
- 时间限制：1 second　内存限制：256 megabytes
- 出现位置：Day04-反悔贪心-优先队列-排序贡献

## 中文题意

本题为简单版，与困难版唯一区别是这里 $n \leq 2000$。

有 $n$ 瓶药水排成一行，从左到右编号 $1$ 到 $n$。喝下第 $i$ 瓶药水会使生命值变化 $a_i$（$a_i$ 可为负，表示扣血）。你初始生命值为 $0$，从左到右依次经过每一瓶，对每瓶可以选择喝或跳过。要求全程生命值始终**非负**。问最多能喝多少瓶？

## 输入格式（中文）

第一行一个整数 $n$（$1 \leq n \leq 2000$）——药水数。第二行 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$-10^9 \leq a_i \leq 10^9$）——喝下每瓶药水后的生命值变化。

## 输出格式（中文）

输出一个整数，即在生命值不变负的前提下能喝到的最多药水数。

## 样例

### 样例 1

输入：

```text
6
4 -4 1 -3 1 -3
```

输出：

```text
5
```

## 样例解释（英文原文）

For the sample, you can drink $5$ potions by taking potions $1$, $3$, $4$, $5$ and $6$. It is not possible to drink all $6$ potions because your health will go negative at some point

## 英文原题面

### Statement

This is the easy version of the problem. The only difference is that in this version $n \leq 2000$. You can make hacks only if both versions of the problem are solved.
There are $n$ potions in a line, with potion $1$ on the far left and potion $n$ on the far right. Each potion increases your health by $a_i$ when drunk. $a_i$ can be negative, meaning that the potion decreases your health.
You start with $0$ health, and you will walk from left to right, from the first potion to the last one. At each potion, you may choose to drink it or ignore it. You must ensure that your health is always non-negative.
What is the largest number of potions you can drink?

### Input

The first line contains a single integer $n$ ($1 \leq n \leq 2000$) — the number of potions. 
The next line contains $n$ integers $a_1$, $a_2$, ... ,$a_n$ ($-10^9 \leq a_i \leq 10^9$) which represent the change in health after drinking that potion.

### Output

Output a single integer, the maximum number of potions you can drink without your health becoming negative.
