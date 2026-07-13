# CF246B · Increase and Decrease

- 难度：1300
- 标签：greedy、math
- 链接：https://codeforces.com/problemset/problem/246/B
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day03-贪心证明-排序-交换论证

## 中文题意

Polycarpus 有一个由 $n$ 个整数 $a_1, a_2, \ldots, a_n$ 组成的数组。他喜欢数组里的数相同，因此希望数组中相等的数尽可能多。为此他会多次执行如下操作：

- 选择数组中的两个元素 $a_i$、$a_j$（$i \ne j$）；
- 同时把 $a_i$ 加 $1$、把 $a_j$ 减 $1$，即执行 $a_i = a_i + 1$、$a_j = a_j - 1$。

该操作恰好改变两个不同的数组元素。Polycarpus 可以执行任意多次该操作。

现在他想知道，若执行任意多次这样的操作，最多能得到多少个相等的数组元素。请帮帮 Polycarpus。

## 输入格式（中文）

第一行为整数 $n$（$1 \le n \le 10^5$）——数组大小。第二行为以空格分隔的整数 $a_1, a_2, \ldots, a_n$（$|a_i| \le 10^4$）——原始数组。

## 输出格式（中文）

输出一个整数——执行任意多次给定操作后，最多能得到的相等数组元素个数。

## 样例

### 样例 1

输入：

```text
2
2 1
```

输出：

```text
1
```

### 样例 2

输入：

```text
3
1 4 1
```

输出：

```text
3
```

## 英文原题面

### Statement

Polycarpus has an array, consisting of n integers a1, a2, ..., an. Polycarpus likes it when numbers in an array match. That's why he wants the array to have as many equal numbers as possible. For that Polycarpus performs the following operation multiple times:
 -  he chooses two elements of the array ai, aj (i ≠ j); 
-  he simultaneously increases number ai by 1 and decreases number aj by 1, that is, executes ai = ai + 1 and aj = aj - 1. 

The given operation changes exactly two distinct array elements. Polycarpus can apply the described operation an infinite number of times. 
Now he wants to know what maximum number of equal array elements he can get if he performs an arbitrary number of such operation. Help Polycarpus.

### Input

The first line contains integer n (1 ≤ n ≤ 105) — the array size. The second line contains space-separated integers a1, a2, ..., an (|ai| ≤ 104) — the original array.

### Output

Print a single integer — the maximum number of equal array elements he can get if he performs an arbitrary number of the given operation.
