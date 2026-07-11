# CF723B · Text Document Analysis

- 难度：1100
- 标签：expression parsing、implementation、strings
- 链接：https://codeforces.com/problemset/problem/723/B
- 时间限制：1 second　内存限制：256 megabytes
- 出现位置：Day01-复杂度-STL-字符串-位运算

## 中文题意

现代文本编辑器通常会显示所编辑文档的统计信息，例如词数、页数、字符数。本题要求你实现类似的功能。

给定一个字符串，仅由以下字符组成：

- 大写和小写英文字母；
- 下划线（用作分隔符）；
- 圆括号（左括号和右括号）。

保证每个左括号后面都有与之匹配的右括号，每个右括号前面都有与之匹配的左括号，且每对匹配括号之间不含其他括号。换言之，字符串中每个括号都属于一个匹配的"开-闭"括号对，且括号对不会嵌套。

例如，"_Hello_Vasya(and_Petya)__bye_(and_OK)" 是一个合法字符串。

"单词"指极长的连续字母段，即其左侧第一个字符和右侧第一个字符要么是下划线或括号，要么不存在。例如上述字符串包含七个单词："Hello"、"Vasya"、"and"、"Petya"、"bye"、"and"、"OK"。请编写程序求出：

- 括号外最长单词的长度（若括号外没有单词，输出 0）；
- 括号内单词的个数（若括号内没有单词，输出 0）。

## 输入格式（中文）

第一行包含一个整数 n（1 ≤ n ≤ 255）——字符串的长度。第二行包含该字符串，仅由大小写英文字母、圆括号和下划线组成。

## 输出格式（中文）

输出两个以空格隔开的整数：

- 括号外最长单词的长度（若括号外没有单词，输出 0）；
- 括号内单词的个数（若括号内没有单词，输出 0）。

## 样例

### 样例 1

输入：

```text
37
_Hello_Vasya(and_Petya)__bye_(and_OK)
```

输出：

```text
5 4
```

### 样例 2

输入：

```text
37
_a_(_b___c)__de_f(g_)__h__i(j_k_l)m__
```

输出：

```text
2 6
```

### 样例 3

输入：

```text
27
(LoooonG)__shOrt__(LoooonG)
```

输出：

```text
5 2
```

### 样例 4

输入：

```text
5
(___)
```

输出：

```text
0 0
```

## 样例解释（英文原文）

In the first sample, the words "Hello", "Vasya" and "bye" are outside any of the parentheses, and the words "and", "Petya", "and" and "OK" are inside. Note, that the word "and" is given twice and you should count it twice in the answer.

## 英文原题面

### Statement

Modern text editors usually show some information regarding the document being edited. For example, the number of words, the number of pages, or the number of characters.
In this problem you should implement the similar functionality.
You are given a string which only consists of:
 -  uppercase and lowercase English letters, 
-  underscore symbols (they are used as separators), 
-  parentheses (both opening and closing). 

It is guaranteed that each opening parenthesis has a succeeding closing parenthesis. Similarly, each closing parentheses has a preceding opening parentheses matching it. For each pair of matching parentheses there are no other parenthesis between them. In other words, each parenthesis in the string belongs to a matching "opening-closing" pair, and such pairs can't be nested.
For example, the following string is valid: "_Hello_Vasya(and_Petya)__bye_(and_OK)".
Word is a maximal sequence of consecutive letters, i.e. such sequence that the first character to the left and the first character to the right of it is an underscore, a parenthesis, or it just does not exist. For example, the string above consists of seven words: "Hello", "Vasya", "and", "Petya", "bye", "and" and "OK". Write a program that finds:
 -  the length of the longest word outside the parentheses (print 0, if there is no word outside the parentheses), 
-  the number of words inside the parentheses (print 0, if there is no word inside the parentheses).

### Input

The first line of the input contains a single integer n (1 ≤ n ≤ 255) — the length of the given string. The second line contains the string consisting of only lowercase and uppercase English letters, parentheses and underscore symbols.

### Output

Print two space-separated integers:
 -  the length of the longest word outside the parentheses (print 0, if there is no word outside the parentheses), 
-  the number of words inside the parentheses (print 0, if there is no word inside the parentheses).
