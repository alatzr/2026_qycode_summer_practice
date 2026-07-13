# CF1285B · Just Eat It!

- 难度：1300
- 标签：dp、greedy、implementation
- 链接：https://codeforces.com/problemset/problem/1285/B
- 时间限制：1 second　内存限制：256 megabytes
- 出现位置：Day03-贪心证明-排序-交换论证

## 中文题意

今天 Yasser 和 Adel 在商店买纸杯蛋糕。货架上有 $n$ 种纸杯蛋糕，从 $1$ 到 $n$ 排列，每种都有无限多个。第 $i$ 种纸杯蛋糕的美味度为整数 $a_i$。既有好吃的也有难吃的，因此美味度可正、可零、可负。

Yasser 当然想全部尝一遍，所以他会每种恰好买一个。

而 Adel 会选择某个区间 $[l, r]$（$1 \le l \le r \le n$），且这个区间不能包含所有种类（即不能选 $[l, r] = [1, n]$），并把第 $l, l+1, \dots, r$ 种各买恰好一个。

之后他们比较各自所买纸杯蛋糕的美味度总和。若无论 Adel 如何选择，Yasser 所买蛋糕的美味度总和都严格大于 Adel 所买蛋糕的美味度总和，Yasser 就会开心。

例如，设各蛋糕美味度为 $[7, 4, -1]$。Yasser 全买，总美味度为 $7 + 4 - 1 = 10$。Adel 可选区间 $[7]$、$[4]$、$[-1]$、$[7, 4]$ 或 $[4, -1]$，其总美味度分别为 $7$、$4$、$-1$、$11$、$3$。Adel 可以选总美味度为 $11$ 的区间，而 $10$ 并不严格大于 $11$，因此 Yasser 不会开心。

请判断逛完商店后 Yasser 是否会开心。

## 输入格式（中文）

本题包含 $t$ 组测试数据。第一行为测试数据组数 $t$（$1 \le t \le 10^4$）。

每组数据第一行为 $n$（$2 \le n \le 10^5$）。

第二行为 $n$ 个整数 $a_1, a_2, \dots, a_n$（$-10^9 \le a_i \le 10^9$），其中 $a_i$ 表示第 $i$ 种纸杯蛋糕的美味度。

保证所有测试数据的 $n$ 之和不超过 $10^5$。

## 输出格式（中文）

对每组数据，若无论 Adel 如何选择，Yasser 所买蛋糕的美味度总和都严格大于 Adel 所买蛋糕的美味度总和，输出 `YES`；否则输出 `NO`。

## 样例

### 样例 1

输入：

```text
3
4
1 2 3 4
3
7 4 -1
3
5 -5 5
```

输出：

```text
YES
NO
NO
```

## 样例解释（英文原文）

In the first example, the total tastiness of any segment Adel can choose is less than the total tastiness of all cupcakes.
In the second example, Adel will choose the segment $[1, 2]$ with total tastiness $11$, which is not less than the total tastiness of all cupcakes, which is $10$.
In the third example, Adel can choose the segment $[3, 3]$ with total tastiness of $5$. Note that Yasser's cupcakes' total tastiness is also $5$, so in that case, the total tastiness of Yasser's cupcakes isn't strictly greater than the total tastiness of Adel's cupcakes.

## 英文原题面

### Statement

Today, Yasser and Adel are at the shop buying cupcakes. There are $n$ cupcake types, arranged from $1$ to $n$ on the shelf, and there are infinitely many of each type. The tastiness of a cupcake of type $i$ is an integer $a_i$. There are both tasty and nasty cupcakes, so the tastiness can be positive, zero or negative.
Yasser, of course, wants to try them all, so he will buy exactly one cupcake of each type.
On the other hand, Adel will choose some segment $[l, r]$ $(1 \le l \le r \le n)$ that does not include all of cupcakes (he can't choose $[l, r] = [1, n]$) and buy exactly one cupcake of each of types $l, l + 1, \dots, r$.
After that they will compare the total tastiness of the cupcakes each of them have bought. Yasser will be happy if the total tastiness of cupcakes he buys is strictly greater than the total tastiness of cupcakes Adel buys regardless of Adel's choice.
For example, let the tastinesses of the cupcakes be $[7, 4, -1]$. Yasser will buy all of them, the total tastiness will be $7 + 4 - 1 = 10$. Adel can choose segments $[7], [4], [-1], [7, 4]$ or $[4, -1]$, their total tastinesses are $7, 4, -1, 11$ and $3$, respectively. Adel can choose segment with tastiness $11$, and as $10$ is not strictly greater than $11$, Yasser won't be happy :(
Find out if Yasser will be happy after visiting the shop.

### Input

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 10^4$). The description of the test cases follows.
The first line of each test case contains $n$ ($2 \le n \le 10^5$).
The second line of each test case contains $n$ integers $a_1, a_2, \dots, a_n$ ($-10^9 \le a_i \le 10^9$), where $a_i$ represents the tastiness of the $i$-th type of cupcake.
It is guaranteed that the sum of $n$ over all test cases doesn't exceed $10^5$.

### Output

For each test case, print "YES", if the total tastiness of cupcakes Yasser buys will always be strictly greater than the total tastiness of cupcakes Adel buys regardless of Adel's choice. Otherwise, print "NO".
