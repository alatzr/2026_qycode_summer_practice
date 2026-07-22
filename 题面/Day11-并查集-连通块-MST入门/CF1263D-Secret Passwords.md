# CF1263D · Secret Passwords

- 难度：1500
- 标签：dfs and similar、dsu、graphs
- 链接：https://codeforces.com/problemset/problem/1263/D
- 时间限制：1 second　内存限制：256 megabytes
- 出现位置：Day11-并查集-连通块-MST入门

## 中文题意

黑客偷到一份含 $n$ 个口令的列表，每个口令是由小写拉丁字母组成的字符串。系统按如下规则判定口令等价：

- 若口令 $a$ 与 $b$ 存在公共字母，则 $a$ 与 $b$ 等价；
- 若列表中存在口令 $c$ 同时与 $a$、$b$ 等价，则 $a$ 与 $b$ 等价。

只要输入的口令与系统设置的口令等价，即可登录系统。例如列表为 "a"、"b"、"ab"、"d" 时，"a"、"b"、"ab" 两两等价，而 "d" 不与任何其他口令等价：若管理员口令是 "b"，则用 "a"、"b"、"ab" 中任意一个都能登录；若是 "d"，则只有 "d" 能登录。

管理员的口令是列表中的某一个，但黑客不知道是哪一个。求黑客最少需要尝试多少个口令，才能保证一定登录成功。

## 输入格式（中文）

第一行一个整数 $n$（$1 \le n \le 2 \cdot 10^5$），表示列表中口令的数量。

接下来 $n$ 行，每行一个非空字符串 $s_i$，为列表中的口令，长度至多 $50$。口令之间可能相同。

保证所有口令的总长度不超过 $10^6$，且全部由小写拉丁字母组成。

## 输出格式（中文）

输出一行一个整数，表示保证能登录系统所需尝试的最少口令数。

## 样例

### 样例 1

输入：

```text
4
a
b
ab
d
```

输出：

```text
2
```

### 样例 2

输入：

```text
3
ab
bc
abc
```

输出：

```text
1
```

### 样例 3

输入：

```text
1
codeforces
```

输出：

```text
1
```

## 样例解释（英文原文）

In the second example hacker need to use any of the passwords to access the system.

## 英文原题面

### Statement

One unknown hacker wants to get the admin's password of AtForces testing system, to get problems from the next contest. To achieve that, he sneaked into the administrator's office and stole a piece of paper with a list of $n$ passwords — strings, consists of small Latin letters.
Hacker went home and started preparing to hack AtForces. He found that the system contains only passwords from the stolen list and that the system determines the equivalence of the passwords $a$ and $b$ as follows:
 -  two passwords $a$ and $b$ are equivalent if there is a letter, that exists in both $a$ and $b$; 
-  two passwords $a$ and $b$ are equivalent if there is a password $c$ from the list, which is equivalent to both $a$ and $b$. 

If a password is set in the system and an equivalent one is applied to access the system, then the user is accessed into the system.
For example, if the list contain passwords "a", "b", "ab", "d", then passwords "a", "b", "ab" are equivalent to each other, but the password "d" is not equivalent to any other password from list. In other words, if:
 -  admin's password is "b", then you can access to system by using any of this passwords: "a", "b", "ab"; 
-  admin's password is "d", then you can access to system by using only "d". 

Only one password from the list is the admin's password from the testing system. Help hacker to calculate the minimal number of passwords, required to guaranteed access to the system. Keep in mind that the hacker does not know which password is set in the system.

### Input

The first line contain integer $n$ ($1 \le n \le 2 \cdot 10^5$) — number of passwords in the list. Next $n$ lines contains passwords from the list – non-empty strings $s_i$, with length at most $50$ letters. Some of the passwords may be equal.
It is guaranteed that the total length of all passwords does not exceed $10^6$ letters. All of them consist only of lowercase Latin letters.

### Output

In a single line print the minimal number of passwords, the use of which will allow guaranteed to access the system.
