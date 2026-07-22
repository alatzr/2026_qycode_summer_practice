# CF316G1 · Good Substrings

- 难度：1700
- 标签：hashing、strings
- 链接：https://codeforces.com/problemset/problem/316/G1
- 时间限制：4 seconds　内存限制：256 megabytes
- 出现位置：Day13-字符串哈希-等价类-前后缀

## 中文题意

以下为官方英文题意（课堂讲解时请要求学生能用自己的话复述条件与目标）。

Smart Beaver recently got interested in a new word game. The point is as follows: count the number of distinct good substrings of some string s. To determine if a string is good or not the game uses rules. Overall there are n rules. Each rule is described by a group of three (p, l, r), where p is a string and l and r (l ≤ r) are integers. We’ll say that string t complies with rule (p, l, r), if the number of occurrences of string t in string p lies between l and r, inclusive. For example, string "ab", complies with rules ("ab", 1, 2) and ("aab", 0, 1), but does not comply with rules ("cd", 1, 2) and ("abab", 0, 1).
A substring s[l... r] (1 ≤ l ≤ r ≤ |s|) of string s = s1s2... s|s| (|s| is a length of s) is string slsl + 1... sr.
Consider a number of occurrences  of string t in string p as a number of pairs of integers l, r (1 ≤ l ≤ r ≤ |p|) such that p[l... r] = t.
We’ll say that string t is good if it complies with all n rules. Smart Beaver asks you to help him to write a program that can calculate the number of distinct good substrings of string s. Two substrings s[x... y] and s[z... w] are cosidered to be distinct iff s[x... y] ≠ s[z... w].

**Note（官方）**：
There are three good substrings in the first sample test: «aab», «ab» and «b».
In the second test only substrings «e» and «t» are good.


## 输入格式（中文）

The first line contains string s. The second line contains integer n. Next n lines contain the rules, one per line. Each of these lines contains a string and two integers pi, li, ri, separated by single spaces (0 ≤ li ≤ ri ≤ |pi|). It is guaranteed that all the given strings are non-empty and only contain lowercase English letters.
The input limits for scoring 30 points are (subproblem G1): 
 -  0 ≤ n ≤ 10. 
-  The length of string s and the maximum length of string p is  ≤ 200. 

The input limits for scoring 70 points are (subproblems G1+G2): 
 -  0 ≤ n ≤ 10. 
-  The length of string s and the maximum length of string p is  ≤ 2000. 

The input limits for scoring 100 points are (subproblems G1+G2+G3): 
 -  0 ≤ n ≤ 10. 
-  The length of string s and the maximum length of string p is  ≤ 50000.


## 输出格式（中文）

Print a single integer — the number of good substrings of string s.


## 样例

### 样例 1

输入：

```text
aaab
2
aa 0 0
aab 1 1
```

输出：

```text
3
```

### 样例 2

输入：

```text
ltntlnen
3
n 0 0
ttlneenl 1 4
lelllt 1 1
```

输出：

```text
2
```

### 样例 3

输入：

```text
a
0
```

输出：

```text
1
```

## 样例解释（英文原文）

There are three good substrings in the first sample test: «aab», «ab» and «b».
In the second test only substrings «e» and «t» are good.

## 英文原题面

### Statement

Smart Beaver recently got interested in a new word game. The point is as follows: count the number of distinct good substrings of some string s. To determine if a string is good or not the game uses rules. Overall there are n rules. Each rule is described by a group of three (p, l, r), where p is a string and l and r (l ≤ r) are integers. We’ll say that string t complies with rule (p, l, r), if the number of occurrences of string t in string p lies between l and r, inclusive. For example, string "ab", complies with rules ("ab", 1, 2) and ("aab", 0, 1), but does not comply with rules ("cd", 1, 2) and ("abab", 0, 1).
A substring s[l... r] (1 ≤ l ≤ r ≤ |s|) of string s = s1s2... s|s| (|s| is a length of s) is string slsl + 1... sr.
Consider a number of occurrences  of string t in string p as a number of pairs of integers l, r (1 ≤ l ≤ r ≤ |p|) such that p[l... r] = t.
We’ll say that string t is good if it complies with all n rules. Smart Beaver asks you to help him to write a program that can calculate the number of distinct good substrings of string s. Two substrings s[x... y] and s[z... w] are cosidered to be distinct iff s[x... y] ≠ s[z... w].

### Input

The first line contains string s. The second line contains integer n. Next n lines contain the rules, one per line. Each of these lines contains a string and two integers pi, li, ri, separated by single spaces (0 ≤ li ≤ ri ≤ |pi|). It is guaranteed that all the given strings are non-empty and only contain lowercase English letters.
The input limits for scoring 30 points are (subproblem G1): 
 -  0 ≤ n ≤ 10. 
-  The length of string s and the maximum length of string p is  ≤ 200. 

The input limits for scoring 70 points are (subproblems G1+G2): 
 -  0 ≤ n ≤ 10. 
-  The length of string s and the maximum length of string p is  ≤ 2000. 

The input limits for scoring 100 points are (subproblems G1+G2+G3): 
 -  0 ≤ n ≤ 10. 
-  The length of string s and the maximum length of string p is  ≤ 50000.

### Output

Print a single integer — the number of good substrings of string s.
