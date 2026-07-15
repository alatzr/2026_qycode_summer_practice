# CF766C · Mahmoud and a Message

- 难度：1700
- 标签：brute force、dp、greedy、strings
- 链接：https://codeforces.com/problemset/problem/766/C
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day06-线性DP-游戏DP-数位DP入口

## 中文题意

Mahmoud 写了一条长度为 $n$ 的消息 $s$，想把它作为生日礼物送给喜欢字符串的朋友 Moaz。他把消息写在一张魔法纸上，却惊讶地发现一些字符消失了。原因是这张魔法纸不允许英文字母表中第 $i$ 个字母出现在长度超过 $a_i$ 的字符串中。例如若 $a_1 = 2$，则字母 `a` 不能写在长度大于等于 $3$ 的字符串中：字符串 `aa` 允许，而 `aaa` 不允许。

Mahmoud 决定把消息切分成若干非空子串，把每个子串写在一张独立的魔法纸上并满足上述条件。这些子串互不重叠，长度之和为 $n$。例如若 $a_1 = 2$ 且要发送 `aaa`，可以切成 `a` 和 `aa` 用 $2$ 张纸，或切成 `a`、`a`、`a` 用 $3$ 张纸；不能切成 `aa` 和 `aa`，因为长度之和超过 $n$。若整条消息本身满足条件，也可以不切分（视为一个子串）。

字符串 $s$ 的子串是由 $s$ 中连续字符组成的字符串：`ab`、`abc`、`b` 是 `abc` 的子串，而 `acb`、`ac` 不是。任何字符串都是自身的子串。

Mahmoud 问你三个问题：

- 有多少种切分方案，使每个子串满足魔法纸的条件、互不重叠且长度之和为 $n$？答案对 $10^9 + 7$ 取模。
- 所有合法切分方案中，出现的子串的最大长度是多少？
- 所有合法切分方案中，子串数量最少是多少？

两种切分方案不同，当且仅当切分位置的集合不同。例如 `aa|a` 与 `a|aa` 是消息 `aaa` 的两种不同切分。

## 输入格式（中文）

第一行一个整数 $n$（$1 \le n \le 10^3$）——消息的长度。

第二行为长度为 $n$ 的消息 $s$，仅由小写英文字母组成。

第三行 $26$ 个整数 $a_1, a_2, \ldots, a_{26}$（$1 \le a_x \le 10^3$）——每个字母允许出现的子串的最大长度。

## 输出格式（中文）

输出三行。

第一行输出满足条件的切分方案数，对 $10^9 + 7$ 取模。

第二行输出所有合法方案中最长子串的长度。

第三行输出所有合法方案中子串的最少数量。

## 样例

### 样例 1

输入：

```text
3
aab
2 3 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
```

输出：

```text
3
2
2
```

### 样例 2

输入：

```text
10
abcdeabcde
5 5 5 5 4 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
```

输出：

```text
401
4
3
```

## 样例解释（英文原文）

In the first example the three ways to split the message are: 
 -  a|a|b 
-  aa|b 
-  a|ab 

The longest substrings are "aa" and "ab" of length 2.
The minimum number of substrings is 2 in "a|ab" or "aa|b".
Notice that "aab" is not a possible splitting because the letter 'a' appears in a substring of length 3, while a1 = 2.

## 英文原题面

### Statement

Mahmoud wrote a message s of length n. He wants to send it as a birthday present to his friend Moaz who likes strings. He wrote it on a magical paper but he was surprised because some characters disappeared while writing the string. That's because this magical paper doesn't allow character number i in the English alphabet to be written on it in a string of length more than ai. For example, if a1 = 2 he can't write character 'a' on this paper in a string of length 3 or more. String "aa" is allowed while string "aaa" is not.
Mahmoud decided to split the message into some non-empty substrings so that he can write every substring on an independent magical paper and fulfill the condition. The sum of their lengths should be n and they shouldn't overlap. For example, if a1 = 2 and he wants to send string "aaa", he can split it into "a" and "aa" and use 2 magical papers, or into "a", "a" and "a" and use 3 magical papers. He can't split it into "aa" and "aa" because the sum of their lengths is greater than n. He can split the message into single string if it fulfills the conditions.
A substring of string s is a string that consists of some consecutive characters from string s, strings "ab", "abc" and "b" are substrings of string "abc", while strings "acb" and "ac" are not. Any string is a substring of itself.
While Mahmoud was thinking of how to split the message, Ehab told him that there are many ways to split it. After that Mahmoud asked you three questions: 
 -  How many ways are there to split the string into substrings such that every substring fulfills the condition of the magical paper, the sum of their lengths is n and they don't overlap? Compute the answer modulo 109 + 7. 
-  What is the maximum length of a substring that can appear in some valid splitting? 
-  What is the minimum number of substrings the message can be spit in? 

Two ways are considered different, if the sets of split positions differ. For example, splitting "aa|a" and "a|aa" are considered different splittings of message "aaa".

### Input

The first line contains an integer n (1 ≤ n ≤ 103) denoting the length of the message.
The second line contains the message s of length n that consists of lowercase English letters.
The third line contains 26 integers a1, a2, ..., a26 (1 ≤ ax ≤ 103) — the maximum lengths of substring each letter can appear in.

### Output

Print three lines.
In the first line print the number of ways to split the message into substrings and fulfill the conditions mentioned in the problem modulo 109  +  7.
In the second line print the length of the longest substring over all the ways.
In the third line print the minimum number of substrings over all the ways.
