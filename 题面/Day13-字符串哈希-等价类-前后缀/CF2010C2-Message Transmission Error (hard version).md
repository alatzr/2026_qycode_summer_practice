# CF2010C2 · Message Transmission Error (hard version)

- 难度：1700
- 标签：hashing、string suffix structures、strings、two pointers
- 链接：https://codeforces.com/problemset/problem/2010/C2
- 时间限制：2 seconds　内存限制：256 megabytes
- 出现位置：Day13-字符串哈希-等价类-前后缀

## 中文题意

以下为官方英文题意（课堂讲解时请要求学生能用自己的话复述条件与目标）。

This is a more difficult version of the problem. It differs from the easy one only by the constraints.
At the Berland State University, the local network between servers does not always operate without errors. When transmitting two identical messages consecutively, an error may occur, resulting in the two messages merging into one. In this merging, the end of the first message coincides with the beginning of the second. Of course, the merging can only occur at identical characters. The length of the merging must be a positive number less than the length of the message text.
For example, when transmitting two messages "abrakadabra" consecutively, it is possible that it will be transmitted with the described type of error, resulting in a message like "abrakadabrabrakadabra" or "abrakadabrakadabra' (in the first case, the merging occurred at one character, and in the second case, at four).
Given the received message t, determine if it is possible that this is the result of an error of the described type in the operation of the local network, and if so, determine a possible value of s.
A situation where two messages completely overlap each other should not be considered an error. For example, if the received message is "abcd", it should be considered that there is no error in it. Similarly, simply appending one message after another is not a sign of an error. For instance, if the received message is "abcabc", it should also be considered that there is no error in it.

**Note（官方）**：
In the second example, a suitable answer could also be the string "acacaca".


## 输入格式（中文）

The input consists of a single non-empty string t, consisting of lowercase letters of the Latin alphabet. The length of the string t does not exceed 4·105 characters.


## 输出格式（中文）

If the message t cannot contain an error, output "NO" (without quotes) in a single line of output.
Otherwise, in the first line, output "YES" (without quotes), and in the next line, output the string s — a possible message that could have led to the error. If there are multiple possible answers, any of them is acceptable.


## 样例

### 样例 1

输入：

```text
abrakadabrabrakadabra
```

输出：

```text
YES
abrakadabra
```

### 样例 2

输入：

```text
acacacaca
```

输出：

```text
YES
acacaca
```

### 样例 3

输入：

```text
abcabc
```

输出：

```text
NO
```

### 样例 4

输入：

```text
abababab
```

输出：

```text
YES
ababab
```

### 样例 5

输入：

```text
tatbt
```

输出：

```text
NO
```

## 样例解释（英文原文）

In the second example, a suitable answer could also be the string "acacaca".

## 英文原题面

### Statement

This is a more difficult version of the problem. It differs from the easy one only by the constraints.
At the Berland State University, the local network between servers does not always operate without errors. When transmitting two identical messages consecutively, an error may occur, resulting in the two messages merging into one. In this merging, the end of the first message coincides with the beginning of the second. Of course, the merging can only occur at identical characters. The length of the merging must be a positive number less than the length of the message text.
For example, when transmitting two messages "abrakadabra" consecutively, it is possible that it will be transmitted with the described type of error, resulting in a message like "abrakadabrabrakadabra" or "abrakadabrakadabra' (in the first case, the merging occurred at one character, and in the second case, at four).
Given the received message t, determine if it is possible that this is the result of an error of the described type in the operation of the local network, and if so, determine a possible value of s.
A situation where two messages completely overlap each other should not be considered an error. For example, if the received message is "abcd", it should be considered that there is no error in it. Similarly, simply appending one message after another is not a sign of an error. For instance, if the received message is "abcabc", it should also be considered that there is no error in it.

### Input

The input consists of a single non-empty string t, consisting of lowercase letters of the Latin alphabet. The length of the string t does not exceed 4·105 characters.

### Output

If the message t cannot contain an error, output "NO" (without quotes) in a single line of output.
Otherwise, in the first line, output "YES" (without quotes), and in the next line, output the string s — a possible message that could have led to the error. If there are multiple possible answers, any of them is acceptable.
