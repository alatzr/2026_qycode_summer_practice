# CF34C · Page Numbers

- 难度：1300
- 标签：expression parsing、implementation、sortings、strings
- 链接：https://codeforces.com/problemset/problem/34/C
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day02-表达式解析-栈-括号序列

## 中文题意

某公司正在开发文本编辑器新版本。像许多编辑器一样，它应支持打印多页文档。用户会输入一串想要打印的文档页码（用逗号分隔，无空格）。

你的任务是编写程序对这串页码进行「标准化」。程序读入用户输入的序列，并将其输出为 $l_1-r_1,l_2-r_2,\ldots,l_k-r_k$ 的格式，其中对所有 $1 \le i \le k-1$ 满足 $r_i + 1 < l_{i+1}$，且 $l_i \le r_i$。新序列应恰好包含用户输入的所有页码，不多不少。若某个页码在输入中出现多次，从第二次出现起应被忽略。若新序列中某个元素满足 $l_i = r_i$，则该元素应输出为 $l_i$，而不是 $l_i-l_i$。

例如，序列 `1,2,3,1,1,2,6,6,2` 应输出为 `1-3,6`。

## 输入格式（中文）

仅有一行，为用户输入的序列。序列包含至少 $1$ 个、至多 $100$ 个正整数。保证序列由不超过 $1000$ 的正整数组成，用逗号分隔，除数字和逗号外不含其它字符，不以逗号结尾，数字无前导零，也不以逗号开头或出现连续两个逗号。

## 输出格式（中文）

按要求的格式输出序列。

## 样例

### 样例 1

输入：

```text
1,2,3,1,1,2,6,6,2
```

输出：

```text
1-3,6
```

### 样例 2

输入：

```text
3,2,1
```

输出：

```text
1-3
```

### 样例 3

输入：

```text
30,20,10
```

输出：

```text
10,20,30
```

## 英文原题面

### Statement

«Bersoft» company is working on a new version of its most popular text editor — Bord 2010. Bord, like many other text editors, should be able to print out multipage documents. A user keys a sequence of the document page numbers that he wants to print out (separates them with a comma, without spaces).
Your task is to write a part of the program, responsible for «standardization» of this sequence. Your program gets the sequence, keyed by the user, as input. The program should output this sequence in format l1-r1,l2-r2,...,lk-rk, where ri + 1 < li + 1 for all i from 1 to k - 1, and li ≤ ri. The new sequence should contain all the page numbers, keyed by the user, and nothing else. If some page number appears in the input sequence several times, its appearances, starting from the second one, should be ignored. If for some element i from the new sequence li = ri, this element should be output as li, and not as «li - li».
For example, sequence 1,2,3,1,1,2,6,6,2 should be output as 1-3,6.

### Input

The only line contains the sequence, keyed by the user. The sequence contains at least one and at most 100 positive integer numbers. It's guaranteed, that this sequence consists of positive integer numbers, not exceeding 1000, separated with a comma, doesn't contain any other characters, apart from digits and commas, can't end with a comma, and the numbers don't contain leading zeroes. Also it doesn't start with a comma or contain more than one comma in a row.

### Output

Output the sequence in the required format.
