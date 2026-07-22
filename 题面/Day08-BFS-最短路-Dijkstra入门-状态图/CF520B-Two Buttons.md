# CF520B · Two Buttons

- 难度：1400
- 标签：dfs and similar、graphs、greedy、implementation、math、shortest paths
- 链接：https://codeforces.com/problemset/problem/520/B
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day08-BFS-最短路-Dijkstra入门-状态图

## 中文题意

以下为官方英文题意（课堂讲解时请要求学生能用自己的话复述条件与目标）。

Vasya has found a strange device. On the front panel of a device there are: a red button, a blue button and a display showing some positive integer. After clicking the red button, device multiplies the displayed number by two. After clicking the blue button, device subtracts one from the number on the display. If at some point the number stops being positive, the device breaks down. The display can show arbitrarily large numbers. Initially, the display shows number n.
Bob wants to get number m on the display. What minimum number of clicks he has to make in order to achieve this result?

**Note（官方）**：
In the first example you need to push the blue button once, and then push the red button once.
In the second example, doubling the number is unnecessary, so we need to push the blue button nine times.


## 输入格式（中文）

The first and the only line of the input contains two distinct integers n and m (1 ≤ n, m ≤ 104), separated by a space .


## 输出格式（中文）

Print a single number — the minimum number of times one needs to push the button required to get the number m out of number n.


## 样例

### 样例 1

输入：

```text
4 6
```

输出：

```text
2
```

### 样例 2

输入：

```text
10 1
```

输出：

```text
9
```

## 样例解释（英文原文）

In the first example you need to push the blue button once, and then push the red button once.
In the second example, doubling the number is unnecessary, so we need to push the blue button nine times.

## 英文原题面

### Statement

Vasya has found a strange device. On the front panel of a device there are: a red button, a blue button and a display showing some positive integer. After clicking the red button, device multiplies the displayed number by two. After clicking the blue button, device subtracts one from the number on the display. If at some point the number stops being positive, the device breaks down. The display can show arbitrarily large numbers. Initially, the display shows number n.
Bob wants to get number m on the display. What minimum number of clicks he has to make in order to achieve this result?

### Input

The first and the only line of the input contains two distinct integers n and m (1 ≤ n, m ≤ 104), separated by a space .

### Output

Print a single number — the minimum number of times one needs to push the button required to get the number m out of number n.
