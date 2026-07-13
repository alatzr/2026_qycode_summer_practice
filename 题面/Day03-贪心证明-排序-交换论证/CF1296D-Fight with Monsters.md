# CF1296D · Fight with Monsters

- 难度：1500
- 标签：greedy、sortings
- 链接：https://codeforces.com/problemset/problem/1296/D
- 时间限制：1 second　内存限制：256 megabytes
- 出现位置：Day03-贪心证明-排序-交换论证

## 中文题意

有 $n$ 只怪物排成一行，编号从 $1$ 到 $n$。第 $i$ 只怪物有 $h_i$ 点生命值（hp）。你的攻击力为 $a$ hp，对手的攻击力为 $b$ hp。

你和对手一起打这些怪物。首先你俩去打第一只怪物，直到它死亡；然后去打第二只，直到它死亡；依此类推。当怪物的 hp 小于等于 $0$ 时视为死亡。

与一只怪物的战斗按回合进行：

- 你对怪物造成 $a$ hp 伤害。若它在你这一击后死亡，你得 $1$ 分，然后你俩前往下一只怪物。
- 对手对怪物造成 $b$ hp 伤害。若它在他这一击后死亡，则无人得分，你俩前往下一只怪物。

你有一种秘技，可以强迫对手跳过他的回合。你总共最多可以使用这个秘技 $k$ 次（例如，若有两只怪物且 $k=4$，你可以对第一只用 $2$ 次、对第二只用 $1$ 次，但不能对第一只用 $2$ 次、对第二只用 $3$ 次）。

你的任务是求出：如果最优地使用秘技，你最多能得多少分。

## 输入格式（中文）

第一行为四个整数 $n, a, b$ 和 $k$（$1 \le n \le 2 \cdot 10^5$，$1 \le a, b, k \le 10^9$）——怪物数、你的攻击力、对手的攻击力、可使用秘技的次数。

第二行为 $n$ 个整数 $h_1, h_2, \dots, h_n$（$1 \le h_i \le 10^9$），其中 $h_i$ 为第 $i$ 只怪物的生命值。

## 输出格式（中文）

输出一个整数——如果最优地使用秘技，你能得到的最多分数。

## 样例

### 样例 1

输入：

```text
6 2 3 3
7 10 50 12 1 8
```

输出：

```text
5
```

### 样例 2

输入：

```text
1 1 100 99
100
```

输出：

```text
1
```

### 样例 3

输入：

```text
7 4 2 1
1 3 5 4 2 7 6
```

输出：

```text
6
```

## 英文原题面

### Statement

There are $n$ monsters standing in a row numbered from $1$ to $n$. The $i$-th monster has $h_i$ health points (hp). You have your attack power equal to $a$ hp and your opponent has his attack power equal to $b$ hp.
You and your opponent are fighting these monsters. Firstly, you and your opponent go to the first monster and fight it till his death, then you and your opponent go the second monster and fight it till his death, and so on. A monster is considered dead if its hp is less than or equal to $0$.
The fight with a monster happens in turns. 
 -  You hit the monster by $a$ hp. If it is dead after your hit, you gain one point and you both proceed to the next monster. 
-  Your opponent hits the monster by $b$ hp. If it is dead after his hit, nobody gains a point and you both proceed to the next monster. 

You have some secret technique to force your opponent to skip his turn. You can use this technique at most $k$ times in total (for example, if there are two monsters and $k=4$, then you can use the technique $2$ times on the first monster and $1$ time on the second monster, but not $2$ times on the first monster and $3$ times on the second monster).
Your task is to determine the maximum number of points you can gain if you use the secret technique optimally.

### Input

The first line of the input contains four integers $n, a, b$ and $k$ ($1 \le n \le 2 \cdot 10^5, 1 \le a, b, k \le 10^9$) — the number of monsters, your attack power, the opponent's attack power and the number of times you can use the secret technique.
The second line of the input contains $n$ integers $h_1, h_2, \dots, h_n$ ($1 \le h_i \le 10^9$), where $h_i$ is the health points of the $i$-th monster.

### Output

Print one integer — the maximum number of points you can gain if you use the secret technique optimally.
