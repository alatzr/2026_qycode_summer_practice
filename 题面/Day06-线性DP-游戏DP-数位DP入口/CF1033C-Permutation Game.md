# CF1033C · Permutation Game

- 难度：1600
- 标签：brute force、dp、games
- 链接：https://codeforces.com/problemset/problem/1033/C
- 时间限制：1 second　内存限制：256 megabytes
- 出现位置：Day06-线性DP-游戏DP-数位DP入口

## 中文题意

Alice 和 Bob 玩一个小游戏。棋盘由排成一行的 $n$ 个格子组成，编号 $1$ 到 $n$，每个格子上写有一个 $1$ 到 $n$ 之间的数 $a_i$，且任意两个格子上的数互不相同。

一枚棋子被放在某个格子上。两人轮流移动棋子，Alice 先手。当前玩家可以把棋子从格子 $i$ 移到格子 $j$，当且仅当同时满足以下两个条件：

- 新格子 $j$ 上的数严格大于旧格子 $i$ 上的数（即 $a_j \gt a_i$）；
- 本次移动的距离是旧格子上的数的倍数（即 $|i-j| \bmod a_i = 0$）。

无法移动的一方输。对每个可能的起始位置，求双方都采取最优策略时谁获胜。可以证明游戏总是有限的，即必有一方存在必胜策略。

## 输入格式（中文）

第一行一个整数 $n$（$1 \le n \le 10^5$）——数的个数。

第二行 $n$ 个整数 $a_1, a_2, \ldots, a_n$（$1 \le a_i \le n$）。保证不存在下标对 $i \neq j$ 使得 $a_i = a_j$。

## 输出格式（中文）

输出一个长度为 $n$ 的字符串 $s$，其中第 $i$ 个字符表示棋子初始放在格子 $i$ 时的胜负：若 Alice 获胜，则 $s_i$ 为 `A`；否则 $s_i$ 为 `B`（大写，区分大小写）。

## 样例

### 样例 1

输入：

```text
8
3 6 5 4 2 7 1 8
```

输出：

```text
BAAAABAB
```

### 样例 2

输入：

```text
15
3 11 2 5 10 9 7 13 15 8 4 12 6 1 14
```

输出：

```text
ABAAAABBBAABAAB
```

## 样例解释（英文原文）

In the first sample, if Bob puts the token on the number (not position): 
 -  $1$: Alice can move to any number. She can win by picking $7$, from which Bob has no move. 
-  $2$: Alice can move to $3$ and $5$. Upon moving to $5$, Bob can win by moving to $8$. If she chooses $3$ instead, she wins, as Bob has only a move to $4$, from which Alice can move to $8$. 
-  $3$: Alice can only move to $4$, after which Bob wins by moving to $8$. 
-  $4$, $5$, or $6$: Alice wins by moving to $8$. 
-  $7$, $8$: Alice has no move, and hence she loses immediately.

## 英文原题面

### Statement

After a long day, Alice and Bob decided to play a little game. The game board consists of $n$ cells in a straight line, numbered from $1$ to $n$, where each cell contains a number $a_i$ between $1$ and $n$. Furthermore, no two cells contain the same number. 
A token is placed in one of the cells. They take alternating turns of moving the token around the board, with Alice moving first. The current player can move from cell $i$ to cell $j$ only if the following two conditions are satisfied: 
 -  the number in the new cell $j$ must be strictly larger than the number in the old cell $i$ (i.e. $a_j  \gt  a_i$), and 
-  the distance that the token travels during this turn must be a multiple of the number in the old cell (i.e. $|i-j|\bmod a_i = 0$). 

Whoever is unable to make a move, loses. For each possible starting position, determine who wins if they both play optimally. It can be shown that the game is always finite, i.e. there always is a winning strategy for one of the players.

### Input

The first line contains a single integer $n$ ($1 \le n \le 10^5$) — the number of numbers.
The second line contains $n$ integers $a_1, a_2, \ldots, a_n$ ($1 \le a_i \le n$). Furthermore, there are no pair of indices $i \neq j$ such that $a_i = a_j$.

### Output

Print $s$ — a string of $n$ characters, where the $i$-th character represents the outcome of the game if the token is initially placed in the cell $i$. If Alice wins, then $s_i$ has to be equal to "A"; otherwise, $s_i$ has to be equal to "B".
