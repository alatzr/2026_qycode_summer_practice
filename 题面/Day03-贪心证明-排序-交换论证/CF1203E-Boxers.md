# CF1203E · Boxers

- 难度：1500
- 标签：greedy、sortings
- 链接：https://codeforces.com/problemset/problem/1203/E
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day03-贪心证明-排序-交换论证

## 中文题意

以下为官方英文题意（课堂讲解时请要求学生能用自己的话复述条件与目标）。

There are $n$ boxers, the weight of the $i$-th boxer is $a_i$. Each of them can change the weight by no more than $1$ before the competition (the weight cannot become equal to zero, that is, it must remain positive). Weight is always an integer number.
It is necessary to choose the largest boxing team in terms of the number of people, that all the boxers' weights in the team are different (i.e. unique).
Write a program that for given current values ​$a_i$ will find the maximum possible number of boxers in a team.
It is possible that after some change the weight of some boxer is $150001$ (but no more).

**Note（官方）**：
In the first example, boxers should not change their weights — you can just make a team out of all of them.
In the second example, one boxer with a weight of $1$ can be increased by one (get the weight of $2$), one boxer with a weight of $4$ can be reduced by one, and the other can be increased by one (resulting the boxers with a weight of $3$ and $5$, respectively). Thus, you can get a team consisting of boxers with weights of $5, 4, 3, 2, 1$.


## 输入格式（中文）

The first line contains an integer $n$ ($1 \le n \le 150000$) — the number of boxers. The next line contains $n$ integers $a_1, a_2, \dots, a_n$, where $a_i$ ($1 \le a_i \le 150000$) is the weight of the $i$-th boxer.


## 输出格式（中文）

Print a single integer — the maximum possible number of people in a team.


## 样例

### 样例 1

输入：

```text
4
3 2 4 1
```

输出：

```text
4
```

### 样例 2

输入：

```text
6
1 1 1 4 4 4
```

输出：

```text
5
```

## 样例解释（英文原文）

In the first example, boxers should not change their weights — you can just make a team out of all of them.
In the second example, one boxer with a weight of $1$ can be increased by one (get the weight of $2$), one boxer with a weight of $4$ can be reduced by one, and the other can be increased by one (resulting the boxers with a weight of $3$ and $5$, respectively). Thus, you can get a team consisting of boxers with weights of $5, 4, 3, 2, 1$.

## 英文原题面

### Statement

There are $n$ boxers, the weight of the $i$-th boxer is $a_i$. Each of them can change the weight by no more than $1$ before the competition (the weight cannot become equal to zero, that is, it must remain positive). Weight is always an integer number.
It is necessary to choose the largest boxing team in terms of the number of people, that all the boxers' weights in the team are different (i.e. unique).
Write a program that for given current values ​$a_i$ will find the maximum possible number of boxers in a team.
It is possible that after some change the weight of some boxer is $150001$ (but no more).

### Input

The first line contains an integer $n$ ($1 \le n \le 150000$) — the number of boxers. The next line contains $n$ integers $a_1, a_2, \dots, a_n$, where $a_i$ ($1 \le a_i \le 150000$) is the weight of the $i$-th boxer.

### Output

Print a single integer — the maximum possible number of people in a team.
