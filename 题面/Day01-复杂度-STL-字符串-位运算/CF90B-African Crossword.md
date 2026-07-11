# CF90B · African Crossword

- 难度：1100
- 标签：implementation、strings
- 链接：https://codeforces.com/problemset/problem/90/B
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day01-复杂度-STL-字符串-位运算

## 中文题意

非洲填字游戏是一个大小为 n × m 的矩形表格，每个格子里恰好有一个字母。这个表格（也称网格）中藏有一个需要解码的加密单词。

解题方法是：划掉所有在行或列中重复的字母。换言之，一个字母被划掉当且仅当它所在的列或所在的行中还存在至少一个与它完全相同的字母。所有这样的字母同时被划掉。

划掉所有重复字母后，把剩余字母连成一个字符串：位置靠上的字母排在靠下的字母之前；若在同一行，则靠左的字母在前。得到的单词即为答案。

请解出这个非洲填字游戏，输出其中加密的单词。

## 输入格式（中文）

第一行包含两个整数 n 和 m（1 ≤ n, m ≤ 100）。接下来 n 行，每行包含 m 个小写拉丁字母——即填字网格。

## 输出格式（中文）

在一行内输出加密的单词。保证答案至少包含一个字母。

## 样例

### 样例 1

输入：

```text
3 3
cba
bcd
cbc
```

输出：

```text
abcd
```

### 样例 2

输入：

```text
5 5
fcofd
ooedo
afaoa
rdcdf
eofsf
```

输出：

```text
codeforces
```

## 英文原题面

### Statement

An African crossword is a rectangular table n × m in size. Each cell of the table contains exactly one letter. This table (it is also referred to as grid) contains some encrypted word that needs to be decoded.
To solve the crossword you should cross out all repeated letters in rows and columns. In other words, a letter should only be crossed out if and only if the corresponding column or row contains at least one more letter that is exactly the same. Besides, all such letters are crossed out simultaneously.
When all repeated letters have been crossed out, we should write the remaining letters in a string. The letters that occupy a higher position follow before the letters that occupy a lower position. If the letters are located in one row, then the letter to the left goes first. The resulting word is the answer to the problem.
You are suggested to solve an African crossword and print the word encrypted there.

### Input

The first line contains two integers n and m (1 ≤ n, m ≤ 100). Next n lines contain m lowercase Latin letters each. That is the crossword grid.

### Output

Print the encrypted word on a single line. It is guaranteed that the answer consists of at least one letter.
