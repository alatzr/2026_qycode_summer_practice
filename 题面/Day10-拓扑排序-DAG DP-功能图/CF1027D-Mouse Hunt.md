# CF1027D · Mouse Hunt

- 难度：1700
- 标签：dfs and similar、graphs
- 链接：https://codeforces.com/problemset/problem/1027/D
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day10-拓扑排序-DAG DP-功能图

## 中文题意

以下为官方英文题意（课堂讲解时请要求学生能用自己的话复述条件与目标）。

Medicine faculty of Berland State University has just finished their admission campaign. As usual, about $80\%$ of applicants are girls and majority of them are going to live in the university dormitory for the next $4$ (hopefully) years.
The dormitory consists of $n$ rooms and a single mouse! Girls decided to set mouse traps in some rooms to get rid of the horrible monster. Setting a trap in room number $i$ costs $c_i$ burles. Rooms are numbered from $1$ to $n$.
Mouse doesn't sit in place all the time, it constantly runs. If it is in room $i$ in second $t$ then it will run to room $a_i$ in second $t + 1$ without visiting any other rooms inbetween ($i = a_i$ means that mouse won't leave room $i$). It's second $0$ in the start. If the mouse is in some room with a mouse trap in it, then the mouse get caught into this trap.
That would have been so easy if the girls actually knew where the mouse at. Unfortunately, that's not the case, mouse can be in any room from $1$ to $n$ at second $0$.
What it the minimal total amount of burles girls can spend to set the traps in order to guarantee that the mouse will eventually be caught no matter the room it started from?

**Note（官方）**：
In the first example it is enough to set mouse trap in rooms $1$ and $4$. If mouse starts in room $1$ then it gets caught immideately. If mouse starts in any other room then it eventually comes to room $4$.
In the second example it is enough to set mouse trap in room $2$. If mouse starts in room $2$ then it gets caught immideately. If mouse starts in any other room then it runs to room $2$ in second $1$.
Here are the paths of the mouse from different starts from the third example:
 -  $1 \rightarrow 2 \rightarrow 2 \rightarrow \dots$; 
-  $2 \rightarrow 2 \rightarrow \dots$; 
-  $3 \rightarrow 2 \rightarrow 2 \rightarrow \dots$; 
-  $4 \rightarrow 3 \rightarrow 2 \rightarrow 2 \rightarrow \dots$; 
-  $5 \rightarrow 6 \rightarrow 7 \rightarrow 6 \rightarrow \dots$; 
-  $6 \rightarrow 7 \rightarrow 6 \rightarrow \dots$; 
-  $7 \rightarrow 6 \rightarrow 7 \rightarrow \dots$; 

So it's enough to set traps in rooms $2$ and $6$.


## 输入格式（中文）

The first line contains as single integers $n$ ($1 \le n \le 2 \cdot 10^5$) — the number of rooms in the dormitory.
The second line contains $n$ integers $c_1, c_2, \dots, c_n$ ($1 \le c_i \le 10^4$) — $c_i$ is the cost of setting the trap in room number $i$.
The third line contains $n$ integers $a_1, a_2, \dots, a_n$ ($1 \le a_i \le n$) — $a_i$ is the room the mouse will run to the next second after being in room $i$.


## 输出格式（中文）

Print a single integer — the minimal total amount of burles girls can spend to set the traps in order to guarantee that the mouse will eventually be caught no matter the room it started from.


## 样例

### 样例 1

输入：

```text
5
1 2 3 2 10
1 3 4 3 3
```

输出：

```text
3
```

### 样例 2

输入：

```text
4
1 10 2 10
2 4 2 2
```

输出：

```text
10
```

### 样例 3

输入：

```text
7
1 1 1 1 1 1 1
2 2 2 3 6 7 6
```

输出：

```text
2
```

## 样例解释（英文原文）

In the first example it is enough to set mouse trap in rooms $1$ and $4$. If mouse starts in room $1$ then it gets caught immideately. If mouse starts in any other room then it eventually comes to room $4$.
In the second example it is enough to set mouse trap in room $2$. If mouse starts in room $2$ then it gets caught immideately. If mouse starts in any other room then it runs to room $2$ in second $1$.
Here are the paths of the mouse from different starts from the third example:
 -  $1 \rightarrow 2 \rightarrow 2 \rightarrow \dots$; 
-  $2 \rightarrow 2 \rightarrow \dots$; 
-  $3 \rightarrow 2 \rightarrow 2 \rightarrow \dots$; 
-  $4 \rightarrow 3 \rightarrow 2 \rightarrow 2 \rightarrow \dots$; 
-  $5 \rightarrow 6 \rightarrow 7 \rightarrow 6 \rightarrow \dots$; 
-  $6 \rightarrow 7 \rightarrow 6 \rightarrow \dots$; 
-  $7 \rightarrow 6 \rightarrow 7 \rightarrow \dots$; 

So it's enough to set traps in rooms $2$ and $6$.

## 英文原题面

### Statement

Medicine faculty of Berland State University has just finished their admission campaign. As usual, about $80\%$ of applicants are girls and majority of them are going to live in the university dormitory for the next $4$ (hopefully) years.
The dormitory consists of $n$ rooms and a single mouse! Girls decided to set mouse traps in some rooms to get rid of the horrible monster. Setting a trap in room number $i$ costs $c_i$ burles. Rooms are numbered from $1$ to $n$.
Mouse doesn't sit in place all the time, it constantly runs. If it is in room $i$ in second $t$ then it will run to room $a_i$ in second $t + 1$ without visiting any other rooms inbetween ($i = a_i$ means that mouse won't leave room $i$). It's second $0$ in the start. If the mouse is in some room with a mouse trap in it, then the mouse get caught into this trap.
That would have been so easy if the girls actually knew where the mouse at. Unfortunately, that's not the case, mouse can be in any room from $1$ to $n$ at second $0$.
What it the minimal total amount of burles girls can spend to set the traps in order to guarantee that the mouse will eventually be caught no matter the room it started from?

### Input

The first line contains as single integers $n$ ($1 \le n \le 2 \cdot 10^5$) — the number of rooms in the dormitory.
The second line contains $n$ integers $c_1, c_2, \dots, c_n$ ($1 \le c_i \le 10^4$) — $c_i$ is the cost of setting the trap in room number $i$.
The third line contains $n$ integers $a_1, a_2, \dots, a_n$ ($1 \le a_i \le n$) — $a_i$ is the room the mouse will run to the next second after being in room $i$.

### Output

Print a single integer — the minimal total amount of burles girls can spend to set the traps in order to guarantee that the mouse will eventually be caught no matter the room it started from.
