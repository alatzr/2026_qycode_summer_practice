# CF698A · Vacations

- 难度：1400
- 标签：dp
- 链接：https://codeforces.com/problemset/problem/698/A
- 时间限制：1 second　内存限制：256 megabytes
- 出现位置：Day06-线性DP-游戏DP-数位DP入口

## 中文题意

Vasya 有 $n$ 天假期，他打算利用假期提升 IT 技能和锻炼身体。对这 $n$ 天中的每一天，Vasya 都知道当天健身房是否开门、网上是否举办比赛。第 $i$ 天有四种情况：

- 健身房不开门，且没有比赛；
- 健身房不开门，但有比赛；
- 健身房开门，但没有比赛；
- 健身房开门，且有比赛。

每天 Vasya 可以选择休息、打比赛（若当天有比赛）或健身（若当天健身房开门）。

求 Vasya 休息（即既不健身也不打比赛）的最少天数。Vasya 唯一的限制是不愿连续两天做同一件事：他不会连续两天健身，也不会连续两天打比赛。

## 输入格式（中文）

第一行一个正整数 $n$（$1 \le n \le 100$）——假期天数。

第二行 $n$ 个用空格隔开的整数 $a_1, a_2, \ldots, a_n$（$0 \le a_i \le 3$），其中：

- $a_i = 0$ 表示第 $i$ 天健身房不开门且没有比赛；
- $a_i = 1$ 表示第 $i$ 天健身房不开门但有比赛；
- $a_i = 2$ 表示第 $i$ 天健身房开门但没有比赛；
- $a_i = 3$ 表示第 $i$ 天健身房开门且有比赛。

## 输出格式（中文）

输出 Vasya 休息的最少天数。注意 Vasya 拒绝：

- 连续两天健身；
- 连续两天打比赛。

## 样例

### 样例 1

输入：

```text
4
1 3 2 0
```

输出：

```text
2
```

### 样例 2

输入：

```text
7
1 3 3 2 1 2 3
```

输出：

```text
0
```

### 样例 3

输入：

```text
2
2 2
```

输出：

```text
1
```

## 样例解释（英文原文）

In the first test Vasya can write the contest on the day number 1 and do sport on the day number 3. Thus, he will have a rest for only 2 days.
In the second test Vasya should write contests on days number 1, 3, 5 and 7, in other days do sport. Thus, he will not have a rest for a single day.
In the third test Vasya can do sport either on a day number 1 or number 2. He can not do sport in two days, because it will be contrary to the his limitation. Thus, he will have a rest for only one day.

## 英文原题面

### Statement

Vasya has n days of vacations! So he decided to improve his IT skills and do sport. Vasya knows the following information about each of this n days: whether that gym opened and whether a contest was carried out in the Internet on that day. For the i-th day there are four options:
 -  on this day the gym is closed and the contest is not carried out; 
-  on this day the gym is closed and the contest is carried out; 
-  on this day the gym is open and the contest is not carried out; 
-  on this day the gym is open and the contest is carried out. 

On each of days Vasya can either have a rest or write the contest (if it is carried out on this day), or do sport (if the gym is open on this day).
Find the minimum number of days on which Vasya will have a rest (it means, he will not do sport and write the contest at the same time). The only limitation that Vasya has — he does not want to do the same activity on two consecutive days: it means, he will not do sport on two consecutive days, and write the contest on two consecutive days.

### Input

The first line contains a positive integer n (1 ≤ n ≤ 100) — the number of days of Vasya's vacations.
The second line contains the sequence of integers a1, a2, ..., an (0 ≤ ai ≤ 3) separated by space, where: 
 -  ai equals 0, if on the i-th day of vacations the gym is closed and the contest is not carried out; 
-  ai equals 1, if on the i-th day of vacations the gym is closed, but the contest is carried out; 
-  ai equals 2, if on the i-th day of vacations the gym is open and the contest is not carried out; 
-  ai equals 3, if on the i-th day of vacations the gym is open and the contest is carried out.

### Output

Print the minimum possible number of days on which Vasya will have a rest. Remember that Vasya refuses:
 -  to do sport on any two consecutive days, 
-  to write the contest on any two consecutive days.
