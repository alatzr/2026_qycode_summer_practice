# CF1709D · Rorororobot

- 难度：1700
- 标签：binary search、data structures、greedy、math
- 链接：https://codeforces.com/problemset/problem/1709/D
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day05-二分答案-ST表-RMQ

## 中文题意

有一个 $n$ 行 $m$ 列的网格。行从下到上编号 $1$ 到 $n$，列从左到右编号 $1$ 到 $m$。第 $i$ 列底部的 $a_i$ 个格子被封锁（第 $1,2,\dots,a_i$ 行），其余 $n-a_i$ 个格子畅通。

一个机器人在网格上移动，你可以向它发出指令：上、右、下、左。若机器人试图移入被封锁的格子或走出网格，它就会爆炸。

但机器人坏了——它把收到的每条指令执行 $k$ 次。比如你让它向上，它会连续向上移动 $k$ 次（$k$ 格）。机器人执行当前指令期间你不能发新指令。

有 $q$ 次询问，每次给出起点格、终点格和一个 $k$。问：能否发出任意条数（可以为 $0$）的指令，使机器人从起点恰好停在终点（每条指令执行 $k$ 次）？机器人必须**停**在终点；若只是在执行指令途中路过终点不算。

## 输入格式（中文）

第一行两个整数 $n$、$m$（$1 \le n \le 10^9$；$1 \le m \le 2\cdot10^5$）——行数与列数。

第二行 $m$ 个整数 $a_1,\dots,a_m$（$0 \le a_i \le n$）——第 $i$ 列底部被封锁的格子数。

第三行一个整数 $q$（$1 \le q \le 2\cdot10^5$）——询问数。

接下来 $q$ 行，每行五个整数 $x_s, y_s, x_f, y_f, k$（$a[y_s] < x_s \le n$；$1 \le y_s \le m$；$a[y_f] < x_f \le n$；$1 \le y_f \le m$；$1 \le k \le 10^9$）——起点的行列、终点的行列、以及每条指令被执行的次数。保证起点和终点都是畅通格子。

## 输出格式（中文）

对每次询问，若能让机器人从起点恰好停到终点则输出 `YES`，否则输出 `NO`（不区分大小写）。

## 样例

### 样例 1

输入：

```text
11 10
9 0 0 10 3 4 8 11 10 8
6
1 2 1 3 1
1 2 1 3 2
4 3 4 5 2
5 3 11 5 3
5 3 11 5 2
11 9 9 10 1
```

输出：

```text
YES
NO
NO
NO
YES
YES
```

## 英文原题面

### Statement

There is a grid, consisting of $n$ rows and $m$ columns. The rows are numbered from $1$ to $n$ from bottom to top. The columns are numbered from $1$ to $m$ from left to right. The $i$-th column has the bottom $a_i$ cells blocked (the cells in rows $1, 2, \dots, a_i$), the remaining $n - a_i$ cells are unblocked.
A robot is travelling across this grid. You can send it commands — move up, right, down or left. If a robot attempts to move into a blocked cell or outside the grid, it explodes.
However, the robot is broken — it executes each received command $k$ times. So if you tell it to move up, for example, it will move up $k$ times ($k$ cells). You can't send it commands while the robot executes the current one.
You are asked $q$ queries about the robot. Each query has a start cell, a finish cell and a value $k$. Can you send the robot an arbitrary number of commands (possibly, zero) so that it reaches the finish cell from the start cell, given that it executes each command $k$ times?
The robot must stop in the finish cell. If it visits the finish cell while still executing commands, it doesn't count.

### Input

The first line contains two integers $n$ and $m$ ($1 \le n \le 10^9$; $1 \le m \le 2 \cdot 10^5$) — the number of rows and columns of the grid.
The second line contains $m$ integers $a_1, a_2, \dots, a_m$ ($0 \le a_i \le n$) — the number of blocked cells on the bottom of the $i$-th column.
The third line contains a single integer $q$ ($1 \le q \le 2 \cdot 10^5$) — the number of queries.
Each of the next $q$ lines contain five integers $x_s, y_s, x_f, y_f$ and $k$ ($a[y_s]  \lt  x_s \le n$; $1 \le y_s \le m$; $a[y_f]  \lt  x_f \le n$; $1 \le y_f \le m$; $1 \le k \le 10^9$) — the row and the column of the start cell, the row and the column of the finish cell and the number of times each your command is executed. The start and the finish cell of each query are unblocked.

### Output

For each query, print "YES" if you can send the robot an arbitrary number of commands (possibly, zero) so that it reaches the finish cell from the start cell, given that it executes each command $k$ times. Otherwise, print "NO".
