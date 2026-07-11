# CF727B · Bill Total Value

- 难度：1600
- 标签：expression parsing、implementation、strings
- 链接：https://codeforces.com/problemset/problem/727/B
- 时间限制：1 second　内存限制：256 megabytes
- 出现位置：Day02-表达式解析-栈-括号序列

## 中文题意

Vasily 走出商店后想重新核对账单上所有购买项的总价。账单是一个字符串，其中各购买项的名称与价格依次排列，中间没有空格。账单格式为 `name1price1name2price2...namenpricen`，其中 $name_i$（第 $i$ 个购买项的名称）是长度不超过 $10$ 的非空字符串，只由小写英文字母组成；$price_i$（第 $i$ 个购买项的价格）是只由数字和点（小数点）组成的非空字符串。名称相同的购买项也可能有不同的价格。

每个价格的书写格式如下：若价格为整数美元，则不写分；否则在美元数之后写一个点（小数点），再以两位格式写分（若分数在 $1$ 到 $9$ 之间，则有一个前导零）。此外，美元部分从低位到高位每三位用一个点（小数点）分隔。不允许多余的前导零。价格总是以数字开头、以数字结尾。

例如：`234`、`1.544`、`149.431.10`、`0.99`、`123.05` 是合法价格；而 `.333`、`3.33.11`、`12.00`、`.33`、`0.1234`、`1.2` 不合法。

请编写程序求出给定账单中所有购买项的总价。

## 输入格式（中文）

仅有一行，为非空字符串 $s$，长度不超过 $1000$——账单的内容。保证账单符合上述格式，且账单中每个价格不少于一分、不超过 $10^6$ 美元。

## 输出格式（中文）

按与输入中价格完全相同的格式输出总价。

## 样例

### 样例 1

输入：

```text
chipsy48.32televizor12.390
```

输出：

```text
12.438.32
```

### 样例 2

输入：

```text
a1b2c3.38
```

输出：

```text
6.38
```

### 样例 3

输入：

```text
aa0.01t0.03
```

输出：

```text
0.04
```

## 英文原题面

### Statement

Vasily exited from a store and now he wants to recheck the total price of all purchases in his bill. The bill is a string in which the names of the purchases and their prices are printed in a row without any spaces. Check has the format "name1price1name2price2...namenpricen", where namei (name of the i-th purchase) is a non-empty string of length not more than 10, consisting of lowercase English letters, and pricei (the price of the i-th purchase) is a non-empty string, consisting of digits and dots (decimal points). It is possible that purchases with equal names have different prices.
The price of each purchase is written in the following format. If the price is an integer number of dollars then cents are not written.
Otherwise, after the number of dollars a dot (decimal point) is written followed by cents in a two-digit format (if number of cents is between 1 and 9 inclusively, there is a leading zero).
Also, every three digits (from less significant to the most) in dollars are separated by dot (decimal point). No extra leading zeroes are allowed. The price always starts with a digit and ends with a digit.
For example:
 -  "234", "1.544", "149.431.10", "0.99" and "123.05" are valid prices, 
-  ".333", "3.33.11", "12.00", ".33", "0.1234" and "1.2" are not valid. 

Write a program that will find the total price of all purchases in the given bill.

### Input

The only line of the input contains a non-empty string s with length not greater than 1000 — the content of the bill.
It is guaranteed that the bill meets the format described above. It is guaranteed that each price in the bill is not less than one cent and not greater than 106 dollars.

### Output

Print the total price exactly in the same format as prices given in the input.
