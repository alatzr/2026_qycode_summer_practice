# CF1042B · Vitamins

- 难度：1200
- 标签：bitmasks、brute force、dp、implementation
- 链接：https://codeforces.com/problemset/problem/1042/B
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day01-复杂度-STL-字符串-位运算

## 中文题意

Berland 的商店出售 $n$ 种果汁，第 $i$ 种价格为 $c_i$。每种果汁含有若干种维生素，维生素共三种："A"、"B"、"C"。每种果汁可以含有其中一种、两种或全部三种。

Petya 需要集齐全部三种维生素才能保持健康。只要买下并喝掉一瓶含有某种维生素的果汁，他就获得了该维生素。求 Petya 为获得全部三种维生素所需购买果汁的最小总价。

## 输入格式（中文）

第一行包含一个整数 $n$ $(1 \le n \le 1\,000)$——果汁的种数。

接下来 $n$ 行，每行包含一个整数 $c_i$ $(1 \le c_i \le 100\,000)$ 和一个字符串 $s_i$——第 $i$ 种果汁的价格及其所含的维生素。字符串 $s_i$ 的长度为 $1$ 到 $3$，只可能包含字符 "A"、"B"、"C"。保证每个字母在 $s_i$ 中至多出现一次，字母顺序任意。

## 输出格式（中文）

若无法集齐全部三种维生素，输出 `-1`；否则输出 Petya 为集齐三种维生素所需购买果汁的最小总价。

## 样例

### 样例 1

输入：

```text
4
5 C
6 B
16 BAC
4 A
```

输出：

```text
15
```

### 样例 2

输入：

```text
2
10 AB
15 BA
```

输出：

```text
-1
```

### 样例 3

输入：

```text
5
10 A
9 BC
11 CA
4 A
5 B
```

输出：

```text
13
```

### 样例 4

输入：

```text
6
100 A
355 BCA
150 BC
160 AC
180 B
190 CA
```

输出：

```text
250
```

### 样例 5

输入：

```text
2
5 BA
11 CB
```

输出：

```text
16
```

## 样例解释（英文原文）

In the first example Petya buys the first, the second and the fourth juice. He spends $5 + 6 + 4 = 15$ and obtains all three vitamins. He can also buy just the third juice and obtain three vitamins, but its cost is $16$, which isn't optimal.
In the second example Petya can't obtain all three vitamins, as no juice contains vitamin "C".

## 英文原题面

### Statement

Berland shop sells $n$ kinds of juices. Each juice has its price $c_i$. Each juice includes some set of vitamins in it. There are three types of vitamins: vitamin "A", vitamin "B" and vitamin "C". Each juice can contain one, two or all three types of vitamins in it.
Petya knows that he needs all three types of vitamins to stay healthy. What is the minimum total price of juices that Petya has to buy to obtain all three vitamins? Petya obtains some vitamin if he buys at least one juice containing it and drinks it.

### Input

The first line contains a single integer $n$ $(1 \le n \le 1\,000)$ — the number of juices.
Each of the next $n$ lines contains an integer $c_i$ $(1 \le c_i \le 100\,000)$ and a string $s_i$ — the price of the $i$-th juice and the vitamins it contains. String $s_i$ contains from $1$ to $3$ characters, and the only possible characters are "A", "B" and "C". It is guaranteed that each letter appears no more than once in each string $s_i$. The order of letters in strings $s_i$ is arbitrary.

### Output

Print -1 if there is no way to obtain all three vitamins. Otherwise print the minimum total price of juices that Petya has to buy to obtain all three vitamins.
