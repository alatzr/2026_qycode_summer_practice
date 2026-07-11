# CF1195C · Basketball Exercise

- 难度：1400
- 标签：dp
- 链接：https://codeforces.com/problemset/problem/1195/C
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day01-复杂度-STL-字符串-位运算/选做

## 中文题意

SIS 新开了篮球场，Demid 决定组织一次篮球训练。$2 \cdot n$ 名学生前来参加，他将学生排成两行，每行恰好 $n$ 人。每行学生从左到右编号为 $1$ 到 $n$。

现在 Demid 要挑选一支球队。他从左往右依次选人：除第一个被选中的人以外，每个被选中的人的编号必须严格大于上一个被选中的人的编号。为了不偏向某一行，相邻两个被选中的学生不能来自同一行。第一个人可以在全部 $2n$ 名学生中任选（没有额外限制），球队人数不限。

Demid 认为完美的球队应使所有被选中学生的身高总和最大。请帮他求出可以选出的球队的最大身高总和。

## 输入格式（中文）

第一行包含一个整数 $n$（$1 \le n \le 10^5$）——每行的学生数。

第二行包含 $n$ 个整数 $h_{1, 1}, h_{1, 2}, \ldots, h_{1, n}$（$1 \le h_{1, i} \le 10^9$），其中 $h_{1, i}$ 为第一行第 $i$ 名学生的身高。

第三行包含 $n$ 个整数 $h_{2, 1}, h_{2, 2}, \ldots, h_{2, n}$（$1 \le h_{2, i} \le 10^9$），其中 $h_{2, i}$ 为第二行第 $i$ 名学生的身高。

## 输出格式（中文）

输出一个整数——Demid 可以选出的球队的最大身高总和。

## 样例

### 样例 1

输入：

```text
5
9 3 5 7 3
5 8 1 4 5
```

输出：

```text
29
```

### 样例 2

输入：

```text
3
1 2 9
10 1 1
```

输出：

```text
19
```

### 样例 3

输入：

```text
1
7
4
```

输出：

```text
7
```

## 样例解释（英文原文）

In the first example Demid can choose the following team as follows: 
  
In the second example Demid can choose the following team as follows:

## 英文原题面

### Statement

Finally, a basketball court has been opened in SIS, so Demid has decided to hold a basketball exercise session. $2 \cdot n$ students have come to Demid's exercise session, and he lined up them into two rows of the same size (there are exactly $n$ people in each row). Students are numbered from $1$ to $n$ in each row in order from left to right.
  
Now Demid wants to choose a team to play basketball. He will choose players from left to right, and the index of each chosen player (excluding the first one taken) will be strictly greater than the index of the previously chosen player. To avoid giving preference to one of the rows, Demid chooses students in such a way that no consecutive chosen students belong to the same row. The first student can be chosen among all $2n$ students (there are no additional constraints), and a team can consist of any number of students. 
Demid thinks, that in order to compose a perfect team, he should choose students in such a way, that the total height of all chosen students is maximum possible. Help Demid to find the maximum possible total height of players in a team he can choose.

### Input

The first line of the input contains a single integer $n$ ($1 \le n \le 10^5$) — the number of students in each row.
The second line of the input contains $n$ integers $h_{1, 1}, h_{1, 2}, \ldots, h_{1, n}$ ($1 \le h_{1, i} \le 10^9$), where $h_{1, i}$ is the height of the $i$-th student in the first row.
The third line of the input contains $n$ integers $h_{2, 1}, h_{2, 2}, \ldots, h_{2, n}$ ($1 \le h_{2, i} \le 10^9$), where $h_{2, i}$ is the height of the $i$-th student in the second row.

### Output

Print a single integer — the maximum possible total height of players in a team Demid can choose.
