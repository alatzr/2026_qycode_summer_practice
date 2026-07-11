# CF166A · Rank List

- 难度：1100
- 标签：binary search、implementation、sortings
- 链接：https://codeforces.com/problemset/problem/166/A
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day01-复杂度-STL-字符串-位运算

## 中文题意

又一场程序设计竞赛结束了，你拿到了这场比赛的最终成绩表。表中每支队伍给出两个数：过题数和总罚时，但没有给出任何队伍的最终名次。

两支队伍的比较规则你很清楚：设队伍 a 过了 pa 道题、总罚时为 ta，队伍 b 过了 pb 道题、总罚时为 tb。若队伍 a 过题更多，或过题数相同但总罚时更少，则 a 的名次高于 b。换言之，当 pa > pb，或 pa = pb 且 ta < tb 时，a 排在 b 前面。

过题数与总罚时都相同的队伍并列，共享对应的所有名次。更正式地：设有 x 支队伍的过题数与总罚时都相同，且有 y 支队伍成绩比它们好，则这 x 支队伍共同占据第 y + 1, y + 2, ..., y + x 名；成绩比它们差的队伍从第 y + x + 1 名开始排。

你的任务是统计给定名单中有多少支队伍并列第 k 名。

## 输入格式（中文）

第一行包含两个整数 n 和 k（1 ≤ k ≤ n ≤ 50）。接下来 n 行描述各队伍：第 i 行包含两个整数 pi 和 ti（1 ≤ pi, ti ≤ 50）——分别为第 i 支队伍的过题数和总罚时。同一行的数用空格隔开。

## 输出格式（中文）

输出一行一个整数——最终成绩表中占据第 k 名的队伍数量。

## 样例

### 样例 1

输入：

```text
7 2
4 10
4 10
4 10
3 20
2 1
2 1
1 10
```

输出：

```text
3
```

### 样例 2

输入：

```text
5 4
3 1
3 1
5 3
3 1
3 1
```

输出：

```text
4
```

## 样例解释（英文原文）

The final results' table for the first sample is: 
 -  1-3 places — 4 solved problems, the penalty time equals 10 
-  4 place — 3 solved problems, the penalty time equals 20 
-  5-6 places — 2 solved problems, the penalty time equals 1 
-  7 place — 1 solved problem, the penalty time equals 10 

The table shows that the second place is shared by the teams that solved 4 problems with penalty time 10. There are 3 such teams.
The final table for the second sample is:
 -  1 place — 5 solved problems, the penalty time equals 3 
-  2-5 places — 3 solved problems, the penalty time equals 1 

The table shows that the fourth place is shared by the teams that solved 3 problems with penalty time 1. There are 4 such teams.

## 英文原题面

### Statement

Another programming contest is over. You got hold of the contest's final results table. The table has the following data. For each team we are shown two numbers: the number of problems and the total penalty time. However, for no team we are shown its final place.
You know the rules of comparing the results of two given teams very well. Let's say that team a solved pa problems with total penalty time ta and team b solved pb problems with total penalty time tb. Team a gets a higher place than team b in the end, if it either solved more problems on the contest, or solved the same number of problems but in less total time. In other words, team a gets a higher place than team b in the final results' table if either pa > pb, or pa = pb and ta < tb. 
It is considered that the teams that solve the same number of problems with the same penalty time share all corresponding places. More formally, let's say there is a group of x teams that solved the same number of problems with the same penalty time. Let's also say that y teams performed better than the teams from this group. In this case all teams from the group share places y + 1, y + 2, ..., y + x. The teams that performed worse than the teams from this group, get their places in the results table starting from the y + x + 1-th place.
Your task is to count what number of teams from the given list shared the k-th place.

### Input

The first line contains two integers n and k (1 ≤ k ≤ n ≤ 50). Then n lines contain the description of the teams: the i-th line contains two integers pi and ti (1 ≤ pi, ti ≤ 50) — the number of solved problems and the total penalty time of the i-th team, correspondingly. All numbers in the lines are separated by spaces.

### Output

In the only line print the sought number of teams that got the k-th place in the final results' table.
