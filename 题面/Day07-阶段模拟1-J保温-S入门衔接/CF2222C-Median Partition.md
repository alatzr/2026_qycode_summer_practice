# CF2222C · Median Partition

- 难度：1500
- 标签：dp、math
- 链接：https://codeforces.com/problemset/problem/2222/C
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day07-阶段模拟1-J保温-S入门衔接

## 中文题意

给定一个长度 $n$（$n$ 为奇数）的数组 $a$。设 $med$ 为整个数组的中位数（长度为奇数时取正中间的数，即排序后第 $(n+1)/2$ 个）。

把数组划分成尽可能多的**连续段**，要求每段长度都是**奇数**，且每段自身的中位数都等于 $med$。输出最多能分成多少段。

本题包含 $t$ 组测试数据。

## 输入格式（中文）

第一行一个整数 $t$（$1 \le t \le 1000$）——测试数据组数。

每组第一行一个整数 $n$（$1 \le n < 5000$，$n$ 为奇数）——数组长度。

第二行 $n$ 个整数 $a_1,\ldots,a_n$（$1 \le a_i \le 10^9$）。

保证所有数据的 $n^2$ 之和不超过 $5000^2$。

## 输出格式（中文）

对每组数据输出一行一个整数——最多可划分出的段数。

## 样例

### 样例 1

输入：

```text
10
5
3 3 2 4 3
7
9 5 7 7 4 7 7
9
1 1 1 1 1 1 1 1 1
1
5
3
1 2 3
3
2 2 2
5
1 2 3 4 5
5
2 1 3 2 2
7
2 2 1 2 3 2 2
9
2 1 2 3 2 1 2 3 2
```

输出：

```text
3
3
9
1
1
3
1
3
5
5
```

## 样例解释（英文原文）

In the first test case, it is optimal to partition $a$ into $[\underline 3, \underline 3, \underline{2, 4, 3}]$.
In the second test case, it is optimal to partition $a$ into $[\underline{9, 5, 7}, \underline 7, \underline{4, 7, 7}]$.
In the third test case, since all the elements are the same, you can partition each element into a separate subarray.

## 英文原题面

### Statement

You are given an array $a$ with an odd length $n$ consisting of positive integers. You are required to partition the sequence into several subarrays$^{\text{∗}}$ with odd lengths and the same median$^{\text{†}}$. Your task is to find the maximum number of subarrays.
More formally, you are required to find a strictly-increasing sequence $k$ with a length of $(p+1)$ where $k_1=1$ and $k_{p+1}=n+1$, such that for every $1\le i\le p$, the medians of the sequences $[a_{k_i},a_{k_i+1},\ldots,a_{k_{i+1}-1}]$ are all the same. The parity of $k_i$ and $k_{i+1}$ should be different. Your task is to find the biggest possible value of $p$.
$^{\text{∗}}$An array $b$ is a subarray of an array $a$ if $b$ can be obtained from $a$ by the deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end. 
$^{\text{†}}$The median of an array with an odd length $x$ is the $\lceil\frac{x}{2}\rceil$-th element of the array after it is sorted in non-decreasing order.

### Input

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 1000$). The description of the test cases follows. 
The first line of each test case contains a single integer $n$ ($1\le n \lt 5000$, $n$ is odd) — the length of $a$.
The second line contains $n$ integers $a_1,a_2,\ldots,a_n$ ($1\le a_i\le 10^9$) — the elements of $a$.
It is guaranteed that the sum of $n^2$ over all test cases does not exceed $5000^2$.

### Output

For each test case, output a single integer — the maximum number of subarrays.
