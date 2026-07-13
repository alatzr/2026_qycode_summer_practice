# CF135A · Replacement

- 难度：1300
- 标签：greedy、implementation、sortings
- 链接：https://codeforces.com/problemset/problem/135/A
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day03-贪心证明-排序-交换论证

## 中文题意

小 Petya 很喜欢由 $n$ 个整数组成的数组，其中每个数都在 $1$ 到 $10^9$（含）之间。最近他从妈妈那里得到了这样一个数组作为礼物，但他一开始并不喜欢它。他决定从数组中恰好选一个元素，把它替换为另一个同样在 $1$ 到 $10^9$（含）之间的整数。不允许把一个数替换成它自己，也不允许什么都不改。

替换之后，Petya 把数组按非降序排序。现在他想知道，对于每个位置，替换并排序之后该位置上可能出现的最小数是多少。

## 输入格式（中文）

第一行为单个整数 $n$（$1 \le n \le 10^5$），表示数组中数的个数。第二行为 $n$ 个以空格分隔的整数——数组的描述。数组所有元素都在 $1$ 到 $10^9$（含）之间。

## 输出格式（中文）

输出 $n$ 个以空格分隔的整数——执行一次替换并排序后，每个数组元素可能的最小值。

## 样例

### 样例 1

输入：

```text
5
1 2 3 4 5
```

输出：

```text
1 1 2 3 4
```

### 样例 2

输入：

```text
5
2 3 4 5 6
```

输出：

```text
1 2 3 4 5
```

### 样例 3

输入：

```text
3
2 2 2
```

输出：

```text
1 2 2
```

## 英文原题面

### Statement

Little Petya very much likes arrays consisting of n integers, where each of them is in the range from 1 to 109, inclusive. Recently he has received one such array as a gift from his mother. Petya didn't like it at once. He decided to choose exactly one element from the array and replace it with another integer that also lies in the range from 1 to 109, inclusive. It is not allowed to replace a number with itself or to change no number at all. 
After the replacement Petya sorted the array by the numbers' non-decreasing. Now he wants to know for each position: what minimum number could occupy it after the replacement and the sorting.

### Input

The first line contains a single integer n (1 ≤ n ≤ 105), which represents how many numbers the array has. The next line contains n space-separated integers — the array's description. All elements of the array lie in the range from 1 to 109, inclusive.

### Output

Print n space-separated integers — the minimum possible values of each array element after one replacement and the sorting are performed.
