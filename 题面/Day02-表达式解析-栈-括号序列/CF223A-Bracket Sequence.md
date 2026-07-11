# CF223A · Bracket Sequence

- 难度：1700
- 标签：data structures、expression parsing、implementation
- 链接：https://codeforces.com/problemset/problem/223/A
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day02-表达式解析-栈-括号序列

## 中文题意

括号序列是只包含字符 `(`、`)`、`[`、`]` 的字符串。若一个括号序列能通过在原字符之间插入字符 `1` 和 `+` 变成一个合法的算术表达式，则称其为合法括号序列。例如 `()[]`、`([])` 是合法的（对应表达式为 `(1)+[1]`、`([1+1]+1)`），而 `](` 和 `[` 不是。空串按定义也是合法括号序列。

给定一个不一定合法的括号序列，请找出它的一个子串，使该子串是合法括号序列，且包含尽可能多的左方括号 `[`。

## 输入格式（中文）

仅有一行，给出括号序列，只由字符 `(`、`)`、`[`、`]` 组成。保证字符串非空，且长度不超过 $10^5$ 个字符。

## 输出格式（中文）

第一行输出一个整数——所求括号序列中左方括号 `[` 的个数。第二行输出最优的括号序列。若有多个最优解，输出任意一个即可。

## 样例

### 样例 1

输入：

```text
([])
```

输出：

```text
1
([])
```

### 样例 2

输入：

```text
(((
```

输出：

```text
0
```

## 英文原题面

### Statement

A bracket sequence is a string, containing only characters "(", ")", "[" and "]".
A correct bracket sequence is a bracket sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example, bracket sequences "()[]", "([])" are correct (the resulting expressions are: "(1)+[1]", "([1+1]+1)"), and "](" and "[" are not. The empty string is a correct bracket sequence by definition.
A substring s[l... r] (1 ≤ l ≤ r ≤ |s|) of string s = s1s2... s|s| (where |s| is the length of string s) is the string slsl + 1... sr. The empty string is a substring of any string by definition.
You are given a bracket sequence, not necessarily correct. Find its substring which is a correct bracket sequence and contains as many opening square brackets «[» as possible.

### Input

The first and the only line contains the bracket sequence as a string, consisting only of characters "(", ")", "[" and "]". It is guaranteed that the string is non-empty and its length doesn't exceed 105 characters.

### Output

In the first line print a single integer — the number of brackets «[» in the required bracket sequence. In the second line print the optimal sequence. If there are more than one optimal solutions print any of them.
