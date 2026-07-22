# CF2036C · Anya and 1100

- 难度：1100
- 标签：brute force、implementation
- 链接：https://codeforces.com/problemset/problem/2036/C
- 时间限制：3 seconds　内存限制：256 megabytes
- 出现位置：Day07-阶段模拟1-J保温-S入门衔接

## 中文题意

Anya 有一个只由 `0` 和 `1` 组成的字符串 $s$。她要对它进行 $q$ 次操作。

每次操作给出两个整数 $i$（$1 \le i \le |s|$）和 $v$（$v \in \{0, 1\}$），表示把字符串第 $i$ 个字符赋值为 $v$（即执行 $s_i = v$）。

Anya 喜欢数字 $1100$，所以每次操作后，她想知道当前字符串中是否存在子串 `1100`（即是否存在某个 $1 \le i \le |s| - 3$，使得 $s_i s_{i+1} s_{i+2} s_{i+3} = \texttt{1100}$）。

本题包含 $t$ 组测试数据。

## 输入格式（中文）

第一行一个整数 $t$（$1 \le t \le 10^4$）——测试数据组数。

每组数据第一行是字符串 $s$（$1 \le |s| \le 2 \cdot 10^5$），只含字符 `0` 和 `1`，$|s|$ 表示其长度。

第二行一个整数 $q$（$1 \le q \le 2 \cdot 10^5$）——操作次数。

接下来 $q$ 行，每行两个整数 $i$（$1 \le i \le |s|$）和 $v$（$v \in \{0, 1\}$），描述一次操作。

保证所有测试数据的 $|s|$ 之和不超过 $2 \cdot 10^5$，且 $q$ 之和不超过 $2 \cdot 10^5$。

## 输出格式（中文）

对每次操作输出一行：若当前字符串包含 `1100` 则输出 `YES`，否则输出 `NO`。

答案不区分大小写（`yEs`、`yes`、`Yes`、`YES` 均视为肯定回答）。

## 样例

### 样例 1

输入：

```text
4
100
4
1 1
2 0
2 0
3 1
1100000
3
6 1
7 1
4 1
111010
4
1 1
5 0
4 1
5 0
0100
4
3 1
1 1
2 0
2 1
```

输出：

```text
NO
NO
NO
NO
YES
YES
NO
NO
YES
YES
YES
NO
NO
NO
NO
```

## 英文原题面

### Statement

While rummaging through things in a distant drawer, Anya found a beautiful string $s$ consisting only of zeros and ones.
Now she wants to make it even more beautiful by performing $q$ operations on it.
Each operation is described by two integers $i$ ($1 \le i \le |s|$) and $v$ ($v \in \{0, 1\}$) and means that the $i$-th character of the string is assigned the value $v$ (that is, the assignment $s_i = v$ is performed).
But Anya loves the number $1100$, so after each query, she asks you to tell her whether the substring "1100" is present in her string (i.e. there exist such $1 \le i \le |s| - 3$ that $s_{i}s_{i + 1}s_{i + 2}s_{i + 3} = \texttt{1100}$).

### Input

The first line contains one integer $t$ ($1 \leq t \leq 10^4$) — the number of test cases.
The first line of the test case contains the string $s$ ($1 \leq |s| \leq 2 \cdot 10^5$), consisting only of the characters "0" and "1". Here $|s|$ denotes the length of the string $s$.
The next line contains an integer $q$ ($1 \leq q \leq 2 \cdot 10^5$) — the number of queries.
The following $q$ lines contain two integers $i$ ($1 \leq i \leq |s|$) and $v$ ($v \in \{0, 1\}$), describing the query.
It is guaranteed that the sum of $|s|$ across all test cases does not exceed $2 \cdot 10^5$. It is also guaranteed that the sum of $q$ across all test cases does not exceed $2 \cdot 10^5$.

### Output

For each query, output "YES", if "1100" is present in Anya's string; otherwise, output "NO".
You can output the answer in any case (upper or lower). For example, the strings "yEs", "yes", "Yes", and "YES" will be recognized as positive responses.
