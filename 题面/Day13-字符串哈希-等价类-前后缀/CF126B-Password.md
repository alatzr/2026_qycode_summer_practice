# CF126B · Password

- 难度：1700
- 标签：binary search、dp、hashing、string suffix structures、strings
- 链接：https://codeforces.com/problemset/problem/126/B
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day13-字符串哈希-等价类-前后缀

## 中文题意

以下为官方英文题意（课堂讲解时请要求学生能用自己的话复述条件与目标）。

Asterix, Obelix and their temporary buddies Suffix and Prefix has finally found the Harmony temple. However, its doors were firmly locked and even Obelix had no luck opening them.
A little later they found a string s, carved on a rock below the temple's gates. Asterix supposed that that's the password that opens the temple and read the string aloud. However, nothing happened. Then Asterix supposed that a password is some substring t of the string s.
Prefix supposed that the substring t is the beginning of the string s; Suffix supposed that the substring t should be the end of the string s; and Obelix supposed that t should be located somewhere inside the string s, that is, t is neither its beginning, nor its end.
Asterix chose the substring t so as to please all his companions. Besides, from all acceptable variants Asterix chose the longest one (as Asterix loves long strings). When Asterix read the substring t aloud, the temple doors opened. 
You know the string s. Find the substring t or determine that such substring does not exist and all that's been written above is just a nice legend.


## 输入格式（中文）

You are given the string s whose length can vary from 1 to 106 (inclusive), consisting of small Latin letters.


## 输出格式（中文）

Print the string t. If a suitable t string does not exist, then print "Just a legend" without the quotes.


## 样例

### 样例 1

输入：

```text
fixprefixsuffix
```

输出：

```text
fix
```

### 样例 2

输入：

```text
abcdabc
```

输出：

```text
Just a legend
```

## 英文原题面

### Statement

Asterix, Obelix and their temporary buddies Suffix and Prefix has finally found the Harmony temple. However, its doors were firmly locked and even Obelix had no luck opening them.
A little later they found a string s, carved on a rock below the temple's gates. Asterix supposed that that's the password that opens the temple and read the string aloud. However, nothing happened. Then Asterix supposed that a password is some substring t of the string s.
Prefix supposed that the substring t is the beginning of the string s; Suffix supposed that the substring t should be the end of the string s; and Obelix supposed that t should be located somewhere inside the string s, that is, t is neither its beginning, nor its end.
Asterix chose the substring t so as to please all his companions. Besides, from all acceptable variants Asterix chose the longest one (as Asterix loves long strings). When Asterix read the substring t aloud, the temple doors opened. 
You know the string s. Find the substring t or determine that such substring does not exist and all that's been written above is just a nice legend.

### Input

You are given the string s whose length can vary from 1 to 106 (inclusive), consisting of small Latin letters.

### Output

Print the string t. If a suitable t string does not exist, then print "Just a legend" without the quotes.
