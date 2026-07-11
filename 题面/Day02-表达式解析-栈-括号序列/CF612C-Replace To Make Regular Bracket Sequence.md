# CF612C · Replace To Make Regular Bracket Sequence

- 难度：1400
- 标签：data structures、expression parsing、math
- 链接：https://codeforces.com/problemset/problem/612/C
- 时间限制：1 second　内存限制：256 megabytes
- 出现位置：Day02-表达式解析-栈-括号序列

## 中文题意

给定一个字符串 $s$，由四种括号 `<>`、`{}`、`[]`、`()` 的左右括号组成。括号分为两类：左括号和右括号。你可以把任意括号替换为同类的另一个括号。例如，可以把 `<` 替换为 `{`，但不能替换为 `)` 或 `>`。

合法括号序列（RBS）的定义如下：空串是 RBS；若 $s_1$ 和 $s_2$ 都是 RBS，则 `<s1>s2`、`{s1}s2`、`[s1]s2`、`(s1)s2` 也都是 RBS。例如 `[[(){}]<>]` 是 RBS，而 `[)()`、`][()()` 不是。

请求出把字符串 $s$ 变成 RBS 所需的最少替换次数。

## 输入格式（中文）

仅有一行，为非空字符串 $s$，只由四种括号的左右括号组成。$s$ 的长度不超过 $10^6$。

## 输出格式（中文）

若无法把 $s$ 变成 RBS，输出 `Impossible`；否则输出把 $s$ 变成 RBS 所需的最少替换次数。

## 样例

### 样例 1

输入：

```text
[<}){}
```

输出：

```text
2
```

### 样例 2

输入：

```text
{()}[]
```

输出：

```text
0
```

### 样例 3

输入：

```text
]]
```

输出：

```text
Impossible
```

## 英文原题面

### Statement

You are given string s consists of opening and closing brackets of four kinds <>, {}, [], (). There are two types of brackets: opening and closing. You can replace any bracket by another of the same type. For example, you can replace < by the bracket {, but you can't replace it by ) or >.
The following definition of a regular bracket sequence is well-known, so you can be familiar with it.
Let's define a regular bracket sequence (RBS). Empty string is RBS. Let s1 and s2 be a RBS then the strings <s1>s2, {s1}s2, [s1]s2, (s1)s2 are also RBS.
For example the string "[[(){}]<>]" is RBS, but the strings "[)()" and "][()()" are not.
Determine the least number of replaces to make the string s RBS.

### Input

The only line contains a non empty string s, consisting of only opening and closing brackets of four kinds. The length of s does not exceed 106.

### Output

If it's impossible to get RBS from s print Impossible.
Otherwise print the least number of replaces needed to get RBS from s.
