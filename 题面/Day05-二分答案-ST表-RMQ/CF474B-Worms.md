# CF474B · Worms

- 难度：1200
- 标签：binary search、implementation
- 链接：https://codeforces.com/problemset/problem/474/B
- 时间限制：1 second　内存限制：256 megabytes
- 出现位置：Day05-二分答案-ST表-RMQ

## 中文题意

以下为官方英文题意（课堂讲解时请要求学生能用自己的话复述条件与目标）。

It is lunch time for Mole. His friend, Marmot, prepared him a nice game for lunch.
Marmot brought Mole n ordered piles of worms such that i-th pile contains ai worms. He labeled all these worms with consecutive integers: worms in first pile are labeled with numbers 1 to a1, worms in second pile are labeled with numbers a1 + 1 to a1 + a2 and so on. See the example for a better understanding.
Mole can't eat all the worms (Marmot brought a lot) and, as we all know, Mole is blind, so Marmot tells him the labels of the best juicy worms. Marmot will only give Mole a worm if Mole says correctly in which pile this worm is contained.
Poor Mole asks for your help. For all juicy worms said by Marmot, tell Mole the correct answers.

**Note（官方）**：
For the sample input:
 -  The worms with labels from [1, 2] are in the first pile. 
-  The worms with labels from [3, 9] are in the second pile. 
-  The worms with labels from [10, 12] are in the third pile. 
-  The worms with labels from [13, 16] are in the fourth pile. 
-  The worms with labels from [17, 25] are in the fifth pile.


## 输入格式（中文）

The first line contains a single integer n (1 ≤ n ≤ 105), the number of piles.
The second line contains n integers a1, a2, ..., an (1 ≤ ai ≤ 103, a1 + a2 + ... + an ≤ 106), where ai is the number of worms in the i-th pile.
The third line contains single integer m (1 ≤ m ≤ 105), the number of juicy worms said by Marmot.
The fourth line contains m integers q1, q2, ..., qm (1 ≤ qi ≤ a1 + a2 + ... + an), the labels of the juicy worms.


## 输出格式（中文）

Print m lines to the standard output. The i-th line should contain an integer, representing the number of the pile where the worm labeled with the number qi is.


## 样例

### 样例 1

输入：

```text
5
2 7 3 4 9
3
1 25 11
```

输出：

```text
1
5
3
```

## 样例解释（英文原文）

For the sample input:
 -  The worms with labels from [1, 2] are in the first pile. 
-  The worms with labels from [3, 9] are in the second pile. 
-  The worms with labels from [10, 12] are in the third pile. 
-  The worms with labels from [13, 16] are in the fourth pile. 
-  The worms with labels from [17, 25] are in the fifth pile.

## 英文原题面

### Statement

It is lunch time for Mole. His friend, Marmot, prepared him a nice game for lunch.
Marmot brought Mole n ordered piles of worms such that i-th pile contains ai worms. He labeled all these worms with consecutive integers: worms in first pile are labeled with numbers 1 to a1, worms in second pile are labeled with numbers a1 + 1 to a1 + a2 and so on. See the example for a better understanding.
Mole can't eat all the worms (Marmot brought a lot) and, as we all know, Mole is blind, so Marmot tells him the labels of the best juicy worms. Marmot will only give Mole a worm if Mole says correctly in which pile this worm is contained.
Poor Mole asks for your help. For all juicy worms said by Marmot, tell Mole the correct answers.

### Input

The first line contains a single integer n (1 ≤ n ≤ 105), the number of piles.
The second line contains n integers a1, a2, ..., an (1 ≤ ai ≤ 103, a1 + a2 + ... + an ≤ 106), where ai is the number of worms in the i-th pile.
The third line contains single integer m (1 ≤ m ≤ 105), the number of juicy worms said by Marmot.
The fourth line contains m integers q1, q2, ..., qm (1 ≤ qi ≤ a1 + a2 + ... + an), the labels of the juicy worms.

### Output

Print m lines to the standard output. The i-th line should contain an integer, representing the number of the pile where the worm labeled with the number qi is.
