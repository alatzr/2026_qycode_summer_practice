# CF41C · Email address

- 难度：1300
- 标签：expression parsing、implementation
- 链接：https://codeforces.com/problemset/problem/41/C
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day02-表达式解析-栈-括号序列

## 中文题意

有时人们在电话里报邮箱时，会把点读成 dot，把 @ 读成 at，于是就得到形如 `vasyaatgmaildotcom` 的字符串。你的任务是把它还原成一个合法的邮箱地址（形如 `[email protected]`）。

已知合法邮箱只包含字符 `.`、`@` 和小写拉丁字母，不以点开头也不以点结尾，不以 @ 开头也不以 @ 结尾；此外邮箱中恰好包含一个 `@`，但可以包含任意多个（可能为 $0$ 个）点。

你需要进行若干次替换，使结果尽可能短且是一个合法邮箱地址。若长度相同，则输出字典序最小的结果。总共有两种替换方式：dot 可以替换为一个点，at 可以替换为一个 @。

## 输入格式（中文）

第一行给出邮箱地址的描述。保证它是由某个合法邮箱把所有点替换为 dot、@ 替换为 at 得到的。该行非空，长度不超过 $100$ 个字符。

## 输出格式（中文）

输出最短的邮箱地址，使得给定字符串可由它按上述规则替换得到。若有多个解，输出字典序最小的一个（字典序比较即现代编程语言中的 `<` 运算符）。

在 ASCII 表中，各符号顺序为：`.`、`@`、`a`、`b`、$\ldots$、`z`。

## 样例

### 样例 1

输入：

```text
vasyaatgmaildotcom
```

输出：

```text
[email protected]
```

### 样例 2

输入：

```text
dotdotdotatdotdotat
```

输出：

```text
[email protected]
```

### 样例 3

输入：

```text
aatt
```

输出：

```text
a@t
```

## 英文原题面

### Statement

Sometimes one has to spell email addresses over the phone. Then one usually pronounces a dot as dot, an at sign as at. As a result, we get something like vasyaatgmaildotcom. Your task is to transform it into a proper email address ([email protected]). 
It is known that a proper email address contains only such symbols as . @ and lower-case Latin letters, doesn't start with and doesn't end with a dot. Also, a proper email address doesn't start with and doesn't end with an at sign. Moreover, an email address contains exactly one such symbol as @, yet may contain any number (possible, zero) of dots. 
You have to carry out a series of replacements so that the length of the result was as short as possible and it was a proper email address. If the lengths are equal, you should print the lexicographically minimal result. 
Overall, two variants of replacement are possible: dot can be replaced by a dot, at can be replaced by an at.

### Input

The first line contains the email address description. It is guaranteed that that is a proper email address with all the dots replaced by dot an the at signs replaced by at. The line is not empty and its length does not exceed 100 symbols.

### Output

Print the shortest email address, from which the given line could be made by the described above replacements. If there are several solutions to that problem, print the lexicographically minimal one (the lexicographical comparison of the lines are implemented with an operator < in modern programming languages).
In the ASCII table the symbols go in this order: . @ ab...z
