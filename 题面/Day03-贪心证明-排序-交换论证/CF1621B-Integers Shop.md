# CF1621B · Integers Shop

- 难度：1500
- 标签：data structures、greedy、implementation
- 链接：https://codeforces.com/problemset/problem/1621/B
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day03-贪心证明-排序-交换论证/选做

## 中文题意

整数商店出售 $n$ 个区间。第 $i$ 个区间包含从 $l_i$ 到 $r_i$ 的所有整数，售价为 $c_i$ 枚硬币。

明天 Vasya 会去商店买一些区间。他将得到所买区间中至少出现在一个区间里的所有整数。购买的总花费是所买所有区间的费用之和。

购物之后，Vasya 还会额外获得一些整数作为赠品。当且仅当满足以下所有条件时，他会把整数 $x$ 作为赠品获得：

- Vasya 没有买到 $x$；
- Vasya 买到了某个小于 $x$ 的整数 $l$；
- Vasya 买到了某个大于 $x$ 的整数 $r$。

Vasya 只会把整数 $x$ 作为赠品获得一次，因此获赠后不会出现重复的整数。

例如，若 Vasya 以 $20$ 枚硬币买下区间 $[2, 4]$、以 $22$ 枚硬币买下区间 $[7, 8]$，他共花费 $42$ 枚硬币，从这些区间得到整数 $2, 3, 4, 7, 8$，还会得到赠品 $5$ 和 $6$。

由于技术原因，明天商店里只有前 $s$ 个区间（即区间 $[l_1, r_1], [l_2, r_2], \ldots, [l_s, r_s]$）可用。

Vasya 想（通过购买或获赠）得到尽可能多的整数。若有多种方式可以做到，他会选择最便宜的一种。

对每个从 $1$ 到 $n$ 的 $s$，求出如果只有前 $s$ 个区间可用，Vasya 将花费多少枚硬币。

## 输入格式（中文）

本题包含 $t$ 组测试数据。第一行为单个整数 $t$（$1 \leq t \leq 1000$）——测试数据组数。

每组数据第一行为单个整数 $n$（$1 \leq n \leq 10^5$）——商店中区间的数量。

接下来 $n$ 行，每行三个整数 $l_i$、$r_i$、$c_i$（$1 \leq l_i \leq r_i \leq 10^9$，$1 \leq c_i \leq 10^9$）——第 $i$ 个区间的两端与费用。

保证所有测试数据的 $n$ 之和不超过 $2 \cdot 10^5$。

## 输出格式（中文）

对每组数据输出 $n$ 个整数：其中第 $s$ 个（$1 \leq s \leq n$）表示如果只有前 $s$ 个区间可用，Vasya 将花费的硬币数。

## 样例

### 样例 1

输入：

```text
3
2
2 4 20
7 8 22
2
5 11 42
5 11 42
6
1 4 4
5 8 9
7 8 7
2 10 252
1 11 271
1 10 1
```

输出：

```text
20
42
42
42
4
13
11
256
271
271
```

## 样例解释（英文原文）

In the first test case if $s = 1$ then Vasya can buy only the segment $[2, 4]$ for $20$ coins and get $3$ integers.
The way to get $7$ integers for $42$ coins in case $s = 2$ is described in the statement.
In the second test case note, that there can be the same segments in the shop.

## 英文原题面

### Statement

The integers shop sells $n$ segments. The $i$-th of them contains all integers from $l_i$ to $r_i$ and costs $c_i$ coins.
Tomorrow Vasya will go to this shop and will buy some segments there. He will get all integers that appear in at least one of bought segments. The total cost of the purchase is the sum of costs of all segments in it.
After shopping, Vasya will get some more integers as a gift. He will get integer $x$ as a gift if and only if all of the following conditions are satisfied: 
 -  Vasya hasn't bought $x$. 
-  Vasya has bought integer $l$ that is less than $x$. 
-  Vasya has bought integer $r$ that is greater than $x$. 

Vasya can get integer $x$ as a gift only once so he won't have the same integers after receiving a gift.
For example, if Vasya buys segment $[2, 4]$ for $20$ coins and segment $[7, 8]$ for $22$ coins, he spends $42$ coins and receives integers $2, 3, 4, 7, 8$ from these segments. He also gets integers $5$ and $6$ as a gift.
Due to the technical issues only the first $s$ segments (that is, segments $[l_1, r_1], [l_2, r_2], \ldots, [l_s, r_s]$) will be available tomorrow in the shop.
Vasya wants to get (to buy or to get as a gift) as many integers as possible. If he can do this in differents ways, he selects the cheapest of them.
For each $s$ from $1$ to $n$, find how many coins will Vasya spend if only the first $s$ segments will be available.

### Input

The first line contains a single integer $t$ ($1 \leq t \leq 1000$) — the number of test cases.
The first line of each test case contains the single integer $n$ ($1 \leq n \leq 10^5$) — the number of segments in the shop.
Each of next $n$ lines contains three integers $l_i$, $r_i$, $c_i$ ($1 \leq l_i \leq r_i \leq 10^9, 1 \leq c_i \leq 10^9$) — the ends of the $i$-th segments and its cost.
It is guaranteed that the total sum of $n$ over all test cases doesn't exceed $2 \cdot 10^5$.

### Output

For each test case output $n$ integers: the $s$-th ($1 \leq s \leq n$) of them should be the number of coins Vasia will spend in the shop if only the first $s$ segments will be available.
