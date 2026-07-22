# CF2050E · Three Strings

- 难度：1500
- 标签：dp、implementation、strings
- 链接：https://codeforces.com/problemset/problem/2050/E
- 时间限制：2.5 seconds　内存限制：256 megabytes
- 出现位置：Day07-阶段模拟1-J保温-S入门衔接

## 中文题意

给定三个小写字母串 $a$、$b$、$c$，其中 $|c| = |a| + |b|$。串 $c$ 由 $a$ 和 $b$ 的字符按各自的相对顺序交织而成，但在交织后允许把 $c$ 的某些位置改成别的字符。

问：$c$ 中至少有多少个位置是被改动过的？等价地，选一种把 $a$、$b$ 交织成长度 $|c|$ 的方式，使与 $c$ 对应位置不相同的位置数最少，输出这个最小值。

本题包含 $t$ 组测试数据。

## 输入格式（中文）

第一行一个整数 $t$（$1 \le t \le 10^3$）——测试数据组数。

每组第一行字符串 $a$（$1 \le |a| \le 10^3$），第二行字符串 $b$（$1 \le |b| \le 10^3$），第三行字符串 $c$（$|c| = |a|+|b|$），均为小写字母。

保证所有数据的 $|a|$ 之和不超过 $2\cdot10^3$，$|b|$ 之和不超过 $2\cdot10^3$。

## 输出格式（中文）

对每组数据输出一行一个整数——$c$ 中最少被改动的位置数。

## 样例

### 样例 1

输入：

```text
7
a
b
cb
ab
cd
acbd
ab
ba
aabb
xxx
yyy
xyxyxy
a
bcd
decf
codes
horse
codeforces
egg
annie
egaegaeg
```

输出：

```text
1
0
2
0
3
2
3
```

## 英文原题面

### Statement

You are given three strings: $a$, $b$, and $c$, consisting of lowercase Latin letters. The string $c$ was obtained in the following way:
 -  At each step, either string $a$ or string $b$ was randomly chosen, and the first character of the chosen string was removed from it and appended to the end of string $c$, until one of the strings ran out. After that, the remaining characters of the non-empty string were added to the end of $c$. 
-  Then, a certain number of characters in string $c$ were randomly changed. 

For example, from the strings $a=\color{red}{\text{abra}}$ and $b=\color{blue}{\text{cada}}$, without character replacements, the strings $\color{blue}{\text{ca}}\color{red}{\text{ab}}\color{blue}{\text{d}}\color{red}{\text{ra}}\color{blue}{\text{a}}$, $\color{red}{\text{abra}}\color{blue}{\text{cada}}$, $\color{red}{\text{a}}\color{blue}{\text{cada}}\color{red}{\text{bra}}$ could be obtained.
Find the minimum number of characters that could have been changed in string $c$.

### Input

The first line of the input contains a single integer $t$ ($1 \le t \le 10^3$) — the number of test cases.
The first line of each test case contains one string of lowercase Latin letters $a$ ($1 \leq |a| \leq 10^3$) — the first string, where $|a|$ denotes the length of string $a$.
The second line of each test case contains one string of lowercase Latin letters $b$ ($1 \leq |b| \leq 10^3$) — the second string, where $|b|$ denotes the length of string $b$.
The third line of each test case contains one string of lowercase Latin letters $c$ ($|c| = |a| + |b|$) — the third string.
It is guaranteed that the sum of $|a|$ across all test cases does not exceed $2 \cdot 10^3$. Also, the sum of $|b|$ across all test cases does not exceed $2 \cdot 10^3$.

### Output

For each test case, output a single integer — the minimum number of characters that could have been changed in string $c$.
