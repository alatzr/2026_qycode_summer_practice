# CF1572A · Book

- 难度：1800
- 标签：binary search、brute force、data structures、dp、graphs、implementation、sortings
- 链接：https://codeforces.com/problemset/problem/1572/A
- 时间限制：1.5 seconds　内存限制：256 megabytes
- 出现位置：Day10-拓扑排序-DAG DP-功能图

## 中文题意

以下为官方英文题意（课堂讲解时请要求学生能用自己的话复述条件与目标）。

You are given a book with $n$ chapters.
Each chapter has a specified list of other chapters that need to be understood in order to understand this chapter. To understand a chapter, you must read it after you understand every chapter on its required list.
Currently you don't understand any of the chapters. You are going to read the book from the beginning till the end repeatedly until you understand the whole book. Note that if you read a chapter at a moment when you don't understand some of the required chapters, you don't understand this chapter.
Determine how many times you will read the book to understand every chapter, or determine that you will never understand every chapter no matter how many times you read the book.

**Note（官方）**：
In the first example, we will understand chapters $\{2, 4\}$ in the first reading and chapters $\{1, 3\}$ in the second reading of the book.
In the second example, every chapter requires the understanding of some other chapter, so it is impossible to understand the book.
In the third example, every chapter requires only chapters that appear earlier in the book, so we can understand everything in one go.
In the fourth example, we will understand chapters $\{2, 3, 4\}$ in the first reading and chapter $1$ in the second reading of the book.
In the fifth example, we will understand one chapter in every reading from $5$ to $1$.


## 输入格式（中文）

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 2\cdot10^4$).
The first line of each test case contains a single integer $n$ ($1 \le n \le 2\cdot10^5$) — number of chapters.
Then $n$ lines follow. The $i$-th line begins with an integer $k_i$ ($0 \le k_i \le n-1$) — number of chapters required to understand the $i$-th chapter. Then $k_i$ integers $a_{i,1}, a_{i,2}, \dots, a_{i, k_i}$ ($1 \le a_{i, j} \le n, a_{i, j} \ne i, a_{i, j} \ne a_{i, l}$ for $j \ne l$) follow — the chapters required to understand the $i$-th chapter.
It is guaranteed that the sum of $n$ and sum of $k_i$ over all testcases do not exceed $2\cdot10^5$.


## 输出格式（中文）

For each test case, if the entire book can be understood, print how many times you will read it, otherwise print $-1$.


## 样例

### 样例 1

输入：

```text
5
4
1 2
0
2 1 4
1 2
5
1 5
1 1
1 2
1 3
1 4
5
0
0
2 1 2
1 2
2 2 1
4
2 2 3
0
0
2 3 2
5
1 2
1 3
1 4
1 5
0
```

输出：

```text
2
-1
1
2
5
```

## 样例解释（英文原文）

In the first example, we will understand chapters $\{2, 4\}$ in the first reading and chapters $\{1, 3\}$ in the second reading of the book.
In the second example, every chapter requires the understanding of some other chapter, so it is impossible to understand the book.
In the third example, every chapter requires only chapters that appear earlier in the book, so we can understand everything in one go.
In the fourth example, we will understand chapters $\{2, 3, 4\}$ in the first reading and chapter $1$ in the second reading of the book.
In the fifth example, we will understand one chapter in every reading from $5$ to $1$.

## 英文原题面

### Statement

You are given a book with $n$ chapters.
Each chapter has a specified list of other chapters that need to be understood in order to understand this chapter. To understand a chapter, you must read it after you understand every chapter on its required list.
Currently you don't understand any of the chapters. You are going to read the book from the beginning till the end repeatedly until you understand the whole book. Note that if you read a chapter at a moment when you don't understand some of the required chapters, you don't understand this chapter.
Determine how many times you will read the book to understand every chapter, or determine that you will never understand every chapter no matter how many times you read the book.

### Input

Each test contains multiple test cases. The first line contains the number of test cases $t$ ($1 \le t \le 2\cdot10^4$).
The first line of each test case contains a single integer $n$ ($1 \le n \le 2\cdot10^5$) — number of chapters.
Then $n$ lines follow. The $i$-th line begins with an integer $k_i$ ($0 \le k_i \le n-1$) — number of chapters required to understand the $i$-th chapter. Then $k_i$ integers $a_{i,1}, a_{i,2}, \dots, a_{i, k_i}$ ($1 \le a_{i, j} \le n, a_{i, j} \ne i, a_{i, j} \ne a_{i, l}$ for $j \ne l$) follow — the chapters required to understand the $i$-th chapter.
It is guaranteed that the sum of $n$ and sum of $k_i$ over all testcases do not exceed $2\cdot10^5$.

### Output

For each test case, if the entire book can be understood, print how many times you will read it, otherwise print $-1$.
