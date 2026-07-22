# CF1849C · Binary String Copying

- 难度：1600
- 标签：binary search、brute force、data structures、hashing、strings
- 链接：https://codeforces.com/problemset/problem/1849/C
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day13-字符串哈希-等价类-前后缀

## 中文题意

以下为官方英文题意（课堂讲解时请要求学生能用自己的话复述条件与目标）。

You are given a string $s$ consisting of $n$ characters 0 and/or 1.
You make $m$ copies of this string, let the $i$-th copy be the string $t_i$. Then you perform exactly one operation on each of the copies: for the $i$-th copy, you sort its substring $[l_i; r_i]$ (the substring from the $l_i$-th character to the $r_i$-th character, both endpoints inclusive). Note that each operation affects only one copy, and each copy is affected by only one operation.
Your task is to calculate the number of different strings among $t_1, t_2, \ldots, t_m$. Note that the initial string $s$ should be counted only if at least one of the copies stays the same after the operation.

**Note（官方）**：
Consider the first example. Copies below are given in order of the input operations. Underlined substrings are substrings that are sorted:
 -  101100 $\rightarrow$ 011100; 
-  101100 $\rightarrow$ 011100; 
-  101100 $\rightarrow$ 101100; 
-  101100 $\rightarrow$ 101100; 
-  101100 $\rightarrow$ 000111. 

There are three different strings among $t_1, t_2, t_3, t_4, t_5$: 000111, 011100 and 101100.
Consider the second example:
 -  100111 $\rightarrow$ 100111; 
-  100111 $\rightarrow$ 001111; 
-  100111 $\rightarrow$ 001111; 
-  100111 $\rightarrow$ 010111. 

There are three different strings among $t_1, t_2, t_3, t_4$: 001111, 010111 and 100111.


## 输入格式（中文）

The first line contains a single integer $t$ ($1 \le t \le 10^4$) — the number of test cases.
The first line of each test case contains two integers $n$ and $m$ ($1 \le n, m \le 2 \cdot 10^5$) — the length of $s$ and the number of copies, respectively.
The second line contains $n$ characters 0 and/or 1 — the string $s$.
Then $m$ lines follow. The $i$-th of them contains two integers $l_i$ and $r_i$ ($1 \le l_i \le r_i \le n$) — the description of the operation applied to the $i$-th copy.
The sum of $n$ over all test cases doesn't exceed $2 \cdot 10^5$. The sum of $m$ over all test cases doesn't exceed $2 \cdot 10^5$.


## 输出格式（中文）

Print one integer — the number of different strings among $t_1, t_2, \ldots, t_m$.


## 样例

### 样例 1

输入：

```text
3
6 5
101100
1 2
1 3
2 4
5 5
1 6
6 4
100111
2 2
1 4
1 3
1 2
1 1
0
1 1
```

输出：

```text
3
3
1
```

## 样例解释（英文原文）

Consider the first example. Copies below are given in order of the input operations. Underlined substrings are substrings that are sorted:
 -  101100 $\rightarrow$ 011100; 
-  101100 $\rightarrow$ 011100; 
-  101100 $\rightarrow$ 101100; 
-  101100 $\rightarrow$ 101100; 
-  101100 $\rightarrow$ 000111. 

There are three different strings among $t_1, t_2, t_3, t_4, t_5$: 000111, 011100 and 101100.
Consider the second example:
 -  100111 $\rightarrow$ 100111; 
-  100111 $\rightarrow$ 001111; 
-  100111 $\rightarrow$ 001111; 
-  100111 $\rightarrow$ 010111. 

There are three different strings among $t_1, t_2, t_3, t_4$: 001111, 010111 and 100111.

## 英文原题面

### Statement

You are given a string $s$ consisting of $n$ characters 0 and/or 1.
You make $m$ copies of this string, let the $i$-th copy be the string $t_i$. Then you perform exactly one operation on each of the copies: for the $i$-th copy, you sort its substring $[l_i; r_i]$ (the substring from the $l_i$-th character to the $r_i$-th character, both endpoints inclusive). Note that each operation affects only one copy, and each copy is affected by only one operation.
Your task is to calculate the number of different strings among $t_1, t_2, \ldots, t_m$. Note that the initial string $s$ should be counted only if at least one of the copies stays the same after the operation.

### Input

The first line contains a single integer $t$ ($1 \le t \le 10^4$) — the number of test cases.
The first line of each test case contains two integers $n$ and $m$ ($1 \le n, m \le 2 \cdot 10^5$) — the length of $s$ and the number of copies, respectively.
The second line contains $n$ characters 0 and/or 1 — the string $s$.
Then $m$ lines follow. The $i$-th of them contains two integers $l_i$ and $r_i$ ($1 \le l_i \le r_i \le n$) — the description of the operation applied to the $i$-th copy.
The sum of $n$ over all test cases doesn't exceed $2 \cdot 10^5$. The sum of $m$ over all test cases doesn't exceed $2 \cdot 10^5$.

### Output

Print one integer — the number of different strings among $t_1, t_2, \ldots, t_m$.
