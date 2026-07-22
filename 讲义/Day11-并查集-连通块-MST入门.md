# Day 11 教师讲义：并查集、连通块、MST 入门

适用班级：已学过 DFS/BFS（Day8）、树上递归（Day9）与图论建模（Day10），开始处理"动态连通性"和"把点分组"的学生。

课时定位：并查集是图论和数据结构之间的桥。今天把三个基本动作写熟：找祖先、合并集合、统计连通块，并用 Kruskal 打开最小生成树的大门。Day11 与 Day12 全部题目共用同一份 `find/merge` 模板，今天必须一字不差地写熟。

配套题单：

| 题号    | 题目                | rating | 本课对应知识点      | 教学目标              |
| ----- | ----------------- | -----: | ------------ | ----------------- |
| 1263D | Secret Passwords  |   1500 | 换对象合并：合并字母   | 学会"把关系挂到更小的对象上"   |
| 103B  | Cthulhu           |   1500 | 连通性 + 边数判环   | 学会 `m==n` 加连通判基环图 |
| 977E  | Cyclic Components |   1500 | 连通块内度数统计     | 学会把信息打到根上         |
| 1139C | Edgy Trees        |   1500 | 补集计数 + 快速幂   | 学会"总方案 - 坏方案"     |
| 1468J | Road Reform       |   1800 | Kruskal、阈值代价 | 学会"模板之后还要分析代价"    |
| 2060E | Graph Composition |   1500 | 两张图连通块对齐     | 学会双并查集比较结构        |

## 0. 课堂安排

授课日：上午 3 小时讲解 + 下午 3.5 小时限时训练。

上午讲解（180 分钟）：

| 时间 | 内容 | 教师重点 |
|---:|---|---|
| 0-15 分钟 | 复习 DFS/BFS 判连通的局限 | 引出"边一条条加进来"的动态场景 |
| 15-45 分钟 | 并查集模板：find、merge、路径压缩、按大小合并 | 手动模拟 fa/sz 变化，统一全篇写法 |
| 45-60 分钟 | 连通块三件套：块数、块大小、块上打标记 | `find(i)==i` 枚举根 |
| 60-80 分钟 | 1263D：把字母并成块 | "换合并对象"是今天第一个思维跳跃 |
| 80-95 分钟 | 103B：连通 + `m==n` | 判定题先数边数 |
| 95-115 分钟 | 977E：块内度数全为 2 | 度数是原图的，与并查集树无关 |
| 115-140 分钟 | 1139C：补集计数 + 快速幂 10 行 | "至少一条黑边"转"总减全红" |
| 140-165 分钟 | Kruskal 模板 + 1468J | 排序 + 不成环就加；模板之后的代价分类 |
| 165-180 分钟 | 2060E 思路引导 + 上午小结 | 只给模型不给代码，下午自己写 |

下午训练（210 分钟，完成顺序见 §10）：

| 时间 | 安排 |
|---:|---|
| 0-190 分钟 | 按 §10 顺序限时完成 6 题；单题卡住超 15 分钟先重读本讲义对应小节 |
| 190-210 分钟 | 对答案 + 每题写 4 行模型卡（题目/模型/关键变量/易错点） |

板书主线：

```text
连通关系只增不减 -> 并查集
块的属性（大小/度数/标记） -> 挂在根上维护
至少一条黑边 -> 总方案 - 全红方案
最小生成树 -> 边排序 + 不成环就加
两张图结构对齐 -> 该删的删，剩下按块数补边
```

## 1. 为什么需要并查集

### 1.1 从一个会超时的做法说起

任务：n 个点，边一条一条加入，随时询问"x 和 y 现在连通吗"。

朴素做法：每次询问都 BFS/DFS 一遍，单次 `O(n+m)`；询问 q 次总共 `O(q(n+m))`。n、q 都到 2e5 时约 8e10，必然超时。

问题出在：连通关系只会"越连越多"，朴素做法却每次从头搜索，大量重复劳动。

并查集就是为"只增不减的连通关系"设计的，它维护若干个不相交集合：

```text
find(x)：返回 x 所在集合的代表（祖先）
merge(x,y)：把 x 和 y 所在的两个集合合并成一个
```

| 做法 | 加一条边 | 判一次连通 | 总复杂度 |
|---|---|---|---|
| 每次重新 BFS | O(1) | O(n+m) | O(q(n+m))，超时 |
| 并查集 | 近似 O(1) | 近似 O(1) | 近似 O(n+m+q)，稳过 |

### 1.2 并查集适合的题型

- 两点是否连通、一条边加入后是否成环；
- 连通块个数、每个连通块的大小；
- Kruskal 最小生成树；
- 把字母、编号、等价关系分组。

注意：并查集只能加边、不能删边。需要删边的题一般离线倒着处理，今天不涉及。

## 2. 并查集模板：全篇统一写法

### 2.1 两个数组的含义

```text
fa[x]：x 的父亲。fa[x] == x 表示 x 是根（集合代表）。
sz[x]：只在根上有意义，表示该集合的点数。
```

`fa` 连出来的树叫"并查集树"，它只表示归属关系，和原图的边没有任何关系。这句话今天会反复用到（见 977E）。

### 2.2 统一模板

合并策略统一用**按大小合并**（按秩合并的常用实现）：把小块的根挂到大块的根下面，防止树退化成链。配合路径压缩，单次操作复杂度 `O(α(n))`，α 是反阿克曼函数，课堂上当常数即可。

本讲义与 Day12 的所有题目，`find/merge` 都是下面这份，一个字不改：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;

int fa[N], sz[N];

int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]); // 路径压缩
}

void merge(int x, int y)
{
	x = find(x), y = find(y);
	if (x == y) return;
	if (sz[x] < sz[y]) swap(x, y); // 按大小合并：小块挂到大块
	fa[y] = x;
	sz[x] += sz[y];
}

int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		fa[i] = i, sz[i] = 1;

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		cin >> u >> v;
		merge(u, v);
	}

	int blocks = 0; // 连通块个数
	for (int i = 1; i <= n; i++)
		if (find(i) == i)
			blocks++;

	cout << blocks << endl;
	return 0;
}
```

讲解重点：

- 初始化 `fa[i] = i, sz[i] = 1` 一个都不能少，多组数据每组都要重置；
- `merge` 开头先 `find`，后面的 x、y 已经是两个根；
- 需要给块维护额外信息（大小、度数标记、最大编号）时，就在 `merge` 里"顺手多合并一行"，Day12 会大量使用这个技巧。

### 2.3 手动模拟

n=5，依次执行 merge(1,2)、merge(3,4)、merge(2,4)：

| 操作 | find 出的两根 | 谁挂谁 | fa[1..5] | 根上的 sz |
|---|---|---|---|---|
| 初始 | - | - | 1 2 3 4 5 | 全为 1 |
| merge(1,2) | 1, 2 | 2 挂到 1 | 1 1 3 4 5 | sz[1]=2 |
| merge(3,4) | 3, 4 | 4 挂到 3 | 1 1 3 3 5 | sz[3]=2 |
| merge(2,4) | 1, 3 | 3 挂到 1 | 1 1 1 3 5 | sz[1]=4 |
| 之后调用 find(4) | 1 | 路径压缩 | 1 1 1 1 5 | 不变 |

结论：根是 1 和 5，共 2 个连通块。`sz[1]=4` 是真实块大小，`sz[3]` 已经失去意义——**sz 只看根**。

### 2.4 三个常用统计动作（关键代码）

```cpp
// 动作一：数连通块
int blocks = 0;
for (int i = 1; i <= n; i++)
	if (find(i) == i) blocks++;

// 动作二：查 i 所在块的大小
int size_i = sz[find(i)];

// 动作三：往块上打标记（写到根上）
flag[find(i)] = true;
```

## 3. 1263D Secret Passwords：把字母并成一块

**题型定位：** CSP 图论建模题（T2 位置常客）：关系看不见摸不着，先想清楚"合并什么对象"。

### 3.1 题目大意

有 n 个由小写字母组成的密码串（n ≤ 2e5，总长 ≤ 1e6）。两个密码"直接等价"当且仅当它们含有至少一个相同字母；等价关系可以传递。问这些密码最终分成多少个等价组。

### 3.2 从暴力到正解

**暴力/部分分：** 两两比较密码是否有公共字母，把有关系的密码 merge，最后数块。比较一对要 26 次判断，总共 `O(n^2 · 26)`，n=2e5 时约 1e12，只能过小数据。

**正解升级——换合并对象：** 密码有 2e5 个，但字母只有 26 个。一个密码里的所有字母互相等价，所以：

```text
每读一个密码，把其中所有字母 merge 到它的第一个字母上。
答案 = 出现过的字母中，不同根的个数。
```

为什么等价：两个密码有公共字母 ⇔ 它们的字母集合在并查集中连通。密码本身根本不用建点。

复杂度 `O(总串长 · α)`。

### 3.3 参考代码（已编译，样例 3/3 通过）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int LETTER = 26;

int fa[LETTER + 5], sz[LETTER + 5];
bool used[LETTER + 5];

int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]); // 路径压缩
}

void merge(int x, int y)
{
	x = find(x), y = find(y);
	if (x == y) return;
	if (sz[x] < sz[y]) swap(x, y); // 按大小合并：小块挂到大块
	fa[y] = x;
	sz[x] += sz[y];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	for (int i = 0; i < LETTER; i++)
		fa[i] = i, sz[i] = 1;

	for (int i = 1; i <= n; i++)
	{
		string pwd;
		cin >> pwd;
		int firstLetter = pwd[0] - 'a';
		for (char ch : pwd)
		{
			int letter = ch - 'a';
			used[letter] = true;
			merge(firstLetter, letter); // 同一个密码里的字母连成一块
		}
	}

	set<int> roots;
	for (int letter = 0; letter < LETTER; letter++)
		if (used[letter])
			roots.insert(find(letter));

	cout << roots.size() << endl;
	return 0;
}
```

### 3.4 赛场策略与易错点

- 赛场策略：想不出"换对象"时，先写 `O(n^2)` 暴力保底；再盯数据范围——"字母只有 26 个"就是提示。
- 易错点：没出现过的字母不能参与统计（样例 1 中 `a b ab d` 答案是 2，若把 26 个字母全数进去就错了）；统计的是"出现过字母的不同根数"，不是密码的根数。

## 4. 103B Cthulhu：连通且恰有一个环

**题型定位：** 图结构判定题（CSP T1/T2 风格）：先数边数，再查连通。

### 4.1 题目大意

给 n 个点 m 条边的无向图（无重边、无自环，n、m ≤ 100），判断它是否是"一个简单环上挂着若干棵树"的结构。是则输出 `FHTAGN!`，否则输出 `NO`。

### 4.2 从暴力到正解

**暴力/部分分：** 找出图中所有环再数个数——实现繁琐且容易写错。

**正解升级——数边数：** 这个结构等价于"连通且恰好含一个环"。结论：

```text
图合法 ⇔ m == n 且整张图是一个连通块
```

为什么：连通图至少 n-1 条边，n-1 条时是树（无环）；每多一条边恰好多一个独立环。`m == n` 意味着比树恰好多 1 条边，也就是恰好一个环。反过来，`m == n` 但不连通时，某个块内部一定有多个环，不合法。

连通性用并查集三行判掉。复杂度 `O((n+m)α)`。

### 4.3 参考代码（已编译，样例 2/2 通过）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 110;

int fa[N], sz[N];

int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]); // 路径压缩
}

void merge(int x, int y)
{
	x = find(x), y = find(y);
	if (x == y) return;
	if (sz[x] < sz[y]) swap(x, y); // 按大小合并：小块挂到大块
	fa[y] = x;
	sz[x] += sz[y];
}

int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		fa[i] = i, sz[i] = 1;

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		cin >> u >> v;
		merge(u, v);
	}

	int comp = 0; // 连通块个数
	for (int i = 1; i <= n; i++)
		if (find(i) == i)
			comp++;

	// 连通且 m == n：恰好一个环挂着若干棵树
	if (m == n && comp == 1) cout << "FHTAGN!" << endl;
	else cout << "NO" << endl;
	return 0;
}
```

### 4.4 赛场策略与易错点

- 赛场策略：结构判定题先列必要条件（边数、连通性、度数），往往列完就是充要条件。
- 易错点：只判 `m == n` 不判连通是最常见的错（两个分离的环也满足 `m == n`）；输出字符串 `FHTAGN!` 别抄错。

## 5. 977E Cyclic Components：块内度数全为 2

**题型定位：** 连通块性质统计（CSP T2 常见）：把"结构判定"翻译成"数量等式"。

### 5.1 题目大意

给 n 个点 m 条边的无向图（n、m ≤ 2e5，无重边自环），统计有多少个连通块本身是一个简单环——即块里的点恰好围成一个圈，没有任何多余的边或分叉。

### 5.2 从暴力到正解

**暴力起手：** 对每个连通块 DFS 收集所有点再逐一检查——思路可行，代码量偏大，还要小心递归深度（2e5 的链会爆栈，Day9 提醒过）。

**正解升级——性质转化：** 一个连通块是简单环，当且仅当：

```text
块内每个点的度数都恰好是 2
```

为什么：每点度数 2 ⇒ 块内边数 = 点数（每条边贡献 2 度）⇒ 连通且比树多一条边 ⇒ 恰有一个环；又因为没有度数 1 的点，环上不能挂任何分叉，所以整块就是一个圈。

实现：读边时 merge 两端点并统计度数；然后把"度数不为 2"的点所在块的根打上"出局"标记；最后数没出局的根。复杂度 `O((n+m)α)`。

### 5.3 参考代码（已编译，样例 2/2 通过）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;

int fa[N], sz[N], deg[N];
bool isCycle[N]; // 只在根下标上有意义：该连通块是否每个点度数都是 2

int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]); // 路径压缩
}

void merge(int x, int y)
{
	x = find(x), y = find(y);
	if (x == y) return;
	if (sz[x] < sz[y]) swap(x, y); // 按大小合并：小块挂到大块
	fa[y] = x;
	sz[x] += sz[y];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		fa[i] = i, sz[i] = 1, isCycle[i] = true;

	for (int i = 1; i <= m; i++)
	{
		int u, v;
		cin >> u >> v;
		merge(u, v);
		deg[u]++, deg[v]++; // 原图度数，与 DSU 树无关
	}

	for (int i = 1; i <= n; i++)
		if (deg[i] != 2)
			isCycle[find(i)] = false; // 任意一点度数不为 2，整块出局

	int ans = 0;
	for (int i = 1; i <= n; i++)
		if (find(i) == i && isCycle[i])
			ans++;

	cout << ans << endl;
	return 0;
}
```

### 5.4 赛场策略与易错点

- 赛场策略：判定"块是不是某种形状"，优先找点数、边数、度数之间的等式，比真去遍历形状省事得多。
- 易错点：`deg` 统计的是**原图度数**，和并查集树的父子关系没有任何关系（本节最重要的一句话）；`isCycle` 标记必须打在 `find(i)` 上而不是 i 上。

## 6. 1139C Edgy Trees：总方案减坏方案

**题型定位：** 组合计数 + 补集转化（CSP-S 计数题标准套路："至少一个"转"总数减全不"）。

### 6.1 题目大意

给一棵 n 个点的树（n ≤ 1e5），每条边是红色（输入色值 0）或黑色（色值 1）。统计长度为 k（k ≤ 100）的点序列 `[v1, v2, ..., vk]`（点可重复）的个数，要求按顺序走 v1→v2→…→vk 的树上路径时，至少经过一条黑边。答案对 1e9+7 取模。

### 6.2 从暴力到正解

**暴力/部分分：** 枚举全部 `n^k` 个序列逐一检查——指数级，只能过极小数据。

**正解升级——补集：** "至少一条黑边"很难直接数，反过来数"一条黑边都不碰"：

```text
总方案 = n^k
坏方案 = 序列全程只走红边 ⇔ k 个点全部落在同一个"红边连通块"里
答案   = n^k - Σ (每个红块大小 s 的 s^k)
```

做法：并查集**只合并红边**（色值 0），黑边直接忽略；每个红块贡献坏方案 `s^k`。幂次用快速幂计算。

样例验证：n=4、k=4、三条边全黑 ⇒ 红块是 4 个孤点，坏方案 `4×1^4=4`，答案 `4^4-4=252`，与官方样例一致。

复杂度 `O(n(α + log k))`。

### 6.3 快速幂 10 行回顾框

快速幂的系统课在假期包 A 模块（7/26 数学基础），今天先把这 10 行会用即可：把指数按二进制拆开，`base` 不断平方，指数当前位是 1 就乘进答案，`O(log expo)`。

```cpp
ll qmi(ll base, ll expo) // 快速幂：base^expo % MOD
{
	ll res = 1;
	base %= MOD;
	while (expo)
	{
		if (expo & 1) res = res * base % MOD;
		base = base * base % MOD;
		expo >>= 1;
	}
	return res;
}
```

### 6.4 参考代码（已编译，样例 3/3 通过）

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int N = 1e5 + 10;
const ll MOD = 1e9 + 7;

int fa[N], sz[N];

int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]); // 路径压缩
}

void merge(int x, int y)
{
	x = find(x), y = find(y);
	if (x == y) return;
	if (sz[x] < sz[y]) swap(x, y); // 按大小合并：小块挂到大块
	fa[y] = x;
	sz[x] += sz[y];
}

ll qmi(ll base, ll expo) // 快速幂：base^expo % MOD
{
	ll res = 1;
	base %= MOD;
	while (expo)
	{
		if (expo & 1) res = res * base % MOD;
		base = base * base % MOD;
		expo >>= 1;
	}
	return res;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	ll k;
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		fa[i] = i, sz[i] = 1;

	for (int i = 1; i < n; i++)
	{
		int u, v, color;
		cin >> u >> v >> color;
		if (color == 0) merge(u, v); // 只合并红边（非黑边）
	}

	ll bad = 0; // 坏方案：k 个点全落在同一个红边连通块
	for (int i = 1; i <= n; i++)
		if (find(i) == i)
			bad = (bad + qmi(sz[i], k)) % MOD;

	ll ans = ((qmi(n, k) - bad) % MOD + MOD) % MOD; // 减法后补 MOD 防负数
	cout << ans << endl;
	return 0;
}
```

### 6.5 赛场策略与易错点

- 赛场策略：看到"至少经过一条…"，第一反应就是补集；树上"只用红边可达"天然就是红边连通块，不需要真的模拟走路径。
- 易错点：只合并色值为 0 的边，黑边一条都不能合并；`n^k` 与 `s^k` 都要取模；**取模减法后必须 `(x % MOD + MOD) % MOD`** 防负数；树只有 n-1 条边，读边循环是 `i < n`。

## 7. 1468J Road Reform：Kruskal 入门与阈值代价

**题型定位：** MST 模板 + 代价分类讨论（CSP-S T3 风格：模板只是起点，代价函数要单独分析）。

### 7.1 先讲 Kruskal 模板

Kruskal 求最小生成树只有三步：

```text
1. 所有边按权值从小到大排序；
2. 依次尝试每条边：两端点若不连通（find 不同根）就把边选入树并 merge；
3. 选满 n-1 条边即为最小生成树。
```

正确性直觉（用 Day3 的交换论证）：假设最优树不含当前最小的可加边 e，把 e 加进去会形成一个环，环上必有一条不小于 e 的边，换掉它不会变差。所以"从小到大、不成环就加"是安全的。

复杂度 `O(m log m)`，瓶颈在排序。

Kruskal 核心框架（嵌进具体题目时再补输入输出）：

```cpp
sort(edges + 1, edges + 1 + m, cmpEdge); // 按 w 从小到大
for (int i = 1; i <= m; i++)
{
	int ru = find(edges[i].u), rv = find(edges[i].v);
	if (ru == rv) continue; // 成环，跳过
	merge(ru, rv);          // 选入生成树
	// 这里按题意统计：累加边权 / 更新最大边 / 维护块信息
}
```

### 7.2 题目大意

多组数据。给 n 个点 m 条边的带权连通无向图（Σn、Σm ≤ 2e5，边权 ≤ 1e9），要求保留恰好 n-1 条边构成生成树，然后可以调整所保留边的权值，每加一或减一花费 1。最终要求生成树中**最大边权恰好等于 k**。求最小总花费。

### 7.3 从暴力到正解

**暴力/部分分：** 枚举生成树不可能。先写标准 Kruskal 求出 MST，观察 MST 的最大边权 `mxTree` 与 k 的关系，能拿到第一类情形的分。

**正解升级——按 mxTree 与 k 的关系分两类：**

情形一：`mxTree >= k`。任何生成树的最大边权都 ≥ MST 的最大边权（MST 使最大边最小），所以最大边一定要被降到 k，答案就是把树上所有超过 k 的边降到 k：`Σ max(0, w - k)`。按边权从小到大的 Kruskal 恰好使"超过 k 的部分总和"最小（大边尽量不进树）。降完后最大边恰好是 k，条件满足。

情形二：`mxTree < k`。树上全部边都小于 k，必须"制造"一条恰好为 k 的边。两个候选取最小：

```text
候选 1：把树上最大边升到 k，花费 k - mxTree（升最大边最便宜）
候选 2：把任意一条边 e 调整成 k 再换进树，花费 |w(e) - k|
       （e 加入树成环，删掉环上另一条边仍是生成树）
```

### 7.4 参考代码（已编译，样例 1/1 通过，样例含 4 组子测试）

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int N = 2e5 + 10;

struct Edge
{
	int u, v;
	ll w;
} edges[N];

int n, m;
ll k;
int fa[N], sz[N];

int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]); // 路径压缩
}

void merge(int x, int y)
{
	x = find(x), y = find(y);
	if (x == y) return;
	if (sz[x] < sz[y]) swap(x, y); // 按大小合并：小块挂到大块
	fa[y] = x;
	sz[x] += sz[y];
}

bool cmpEdge(const Edge &e1, const Edge &e2)
{
	return e1.w < e2.w;
}

void solve()
{
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++)
		cin >> edges[i].u >> edges[i].v >> edges[i].w;
	for (int i = 1; i <= n; i++)
		fa[i] = i, sz[i] = 1;

	sort(edges + 1, edges + 1 + m, cmpEdge);

	ll over = 0;   // MST 中超过 k 的部分总和
	ll mxTree = 0; // MST 最大边权
	for (int i = 1; i <= m; i++)
	{
		int ru = find(edges[i].u), rv = find(edges[i].v);
		if (ru == rv) continue;
		merge(ru, rv);
		mxTree = max(mxTree, edges[i].w);
		if (edges[i].w > k) over += edges[i].w - k;
	}

	if (mxTree >= k)
	{
		// 任何生成树最大边都 >= mxTree >= k：把超出的边都降到 k
		cout << over << '\n';
		return;
	}

	// MST 全部边 < k：需要把某条边改成 k，选改动最小的边换进树
	ll best = k - mxTree;
	for (int i = 1; i <= m; i++)
		best = min(best, abs(edges[i].w - k));
	cout << best << '\n';
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;
	while (T--)
		solve();
	return 0;
}
```

### 7.5 赛场策略与易错点

- 赛场策略：拿到 MST 变形题，先把标准 Kruskal 写对跑通，再对着"额外要求"分类讨论；分类漏了至少还有一类的分。
- 易错点：边权到 1e9、求和会爆 int，`over`、`mxTree`、k 都用 `long long`；多组数据每组重置 `fa/sz`；情形二别漏"非树边也能换进树"这个候选。

## 8. 2060E Graph Composition：两张图的连通块对齐（压轴）

**题型定位：** 连通性构造题（Div2 E / CSP-S 并查集综合）：下界分析 + 构造达到下界。

### 8.1 题目大意

多组数据。同一批 n 个点上给两张无向图 F 和 G（Σn、Σ(m1+m2) ≤ 2e5）。每次操作可以在 F 中删除一条现有边，或加入一条新边。要求操作后 F 的连通性与 G 完全一致：任意两点在 F 中连通 ⇔ 在 G 中连通。求最少操作次数。

### 8.2 从暴力到正解

**暴力起手：** 逐条边试删试加再判连通——指数级，放弃。这题直接做"下界 + 构造"。

**正解升级——把 F 的边分成两类：**

```text
第一类：跨越 G 连通块的 F 边。
        最终图里这条边的两端不允许连通，而这条边直接把它们连上了——必须删。
第二类：G 块内部的 F 边。
        保留它不会连出任何"不该连"的点对——白拿的连通性，全部保留。
```

删完第一类后，看每个 G 块内部：F 的剩余边把这个块分成了若干片，把 p 片连起来需要恰好 p-1 条新边。所以：

```text
答案 = 跨块的 F 边数 + Σ (每个 G 块内 F 的片数 - 1)
     = 跨块的 F 边数 + (F 保留边形成的块数 - G 的块数)
```

下界：第一类边每条必须删（1 次操作跑不掉）；每个 G 块内部想从 p 片连成 1 片至少 p-1 条边。构造恰好达到下界，所以最优。

**实现技巧——双并查集开一个数组：** 下标 1..n 给 F 用，n+1..2n 给 G 用。先把 G 的边全部合并好，再扫 F 的边分类。

复杂度 `O((n+m1+m2)α)`。

### 8.3 手动模拟表

用官方样例第 1 组：n=3，F 边 {1-2, 2-3}，G 边 {1-3}。

| 步骤 | 动作 | 状态/结论 |
|---|---|---|
| 1 | 合并 G 的边 1-3 | G 块：{1,3}、{2}，块数 2 |
| 2 | 查 F 边 1-2：1 与 2 在 G 中不同块 | 必须删，操作数 1 |
| 3 | 查 F 边 2-3：2 与 3 在 G 中不同块 | 必须删，操作数 2 |
| 4 | F 保留边为空 | F 块：{1}、{2}、{3}，块数 3 |
| 5 | 补边 3 - 2 = 1 条（把 1 和 3 连上） | 操作数 3 |

答案 3，与官方样例一致。

### 8.4 参考代码（已编译，样例 1/1 通过，样例含 5 组子测试）

```cpp
#include <iostream>

using namespace std;

const int N = 200010;

// 全局静态数组（内存一次性分配，高效省时）
int faF[N]; // 图 F 的并查集数组
int faG[N]; // 图 G 的并查集数组
int uF[N], vF[N]; // 静态数组存储图 F 的边

// 图 G 的查找函数（带路径压缩）
int findG(int x) {
    if (faG[x] == x) return x;
    return faG[x] = findG(faG[x]);
}

// 图 F 的查找函数（带路径压缩）
int findF(int x) {
    if (faF[x] == x) return x;
    return faF[x] = findF(faF[x]);
}

void solve() {
    int n, m1, m2;
    cin >> n >> m1 >> m2;

    // 1. 多测清空：初始化静态并查集数组
    for (int i = 1; i <= n; i++) {
        faF[i] = i;
        faG[i] = i;
    }

    // 2. 读入图 F 的边
    for (int i = 1; i <= m1; i++) {
        cin >> uF[i] >> vF[i];
    }

    // 3. 构建图 G 的行政区划（并查集合并）
    for (int i = 1; i <= m2; i++) {
        int u, v;
        cin >> u >> v;
        int ru = findG(u), rv = findG(v);
        if (ru != rv) {
            faG[ru] = rv;
        }
    }

    int remove_ops = 0; // 记录必须拆除的坏路数

    // 4. 遍历图 F 的边：过滤坏路，合并好路
    for (int i = 1; i <= m1; i++) {
        int u = uF[i], v = vF[i];

        // 检查 u, v 在图纸 G 中是否属于不同行政区
        if (findG(u) != findG(v)) {
            // 坏路：跨区连通，必删！
            remove_ops++;
        } else {
            // 好路：同区安全，在 F 中合并碎片
            int ru = findF(u), rv = findF(v);
            if (ru != rv) {
                faF[ru] = rv;
            }
        }
    }

    // 5. 统计 F 和 G 的根节点总数（即连通块碎片数）
    int rootsF = 0, rootsG = 0;
    for (int i = 1; i <= n; i++) {
        if (faF[i] == i) rootsF++;
        if (faG[i] == i) rootsG++;
    }

    // 6. 最终计算：坏路数 + (rootsF - rootsG)
    cout << remove_ops + (rootsF - rootsG) << "\n";
}

int main() {
    // 快速输入输出
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }

    return 0;
}
```

### 8.5 赛场策略与易错点

- 赛场策略：两张图/两种关系的题，先固定"目标结构"（这里是 G），把当前结构的每条边分成"必须处理 / 可以保留"两类，操作数往往就是"必删数 + 补连通数"。
- 易错点：必须**先**把 G 全部合并完**再**扫 F 的边（边分类依赖 G 的最终块）；多组数据要初始化 `2n` 个位置而不是 n 个；比较的是"连通块结构"，不是边数相等。

## 9. 本节易错清单

- `find(x)` 之后才能比较两点是否同集合，直接比 `fa[x]` 是经典错误。
- `sz[x]`、块上标记只在根上有效，读取前先 `find`。
- 多组数据必须重置 `fa`、`sz`、`deg` 等所有数组，范围题（2060E）要重置到 `2n`。
- 并查集不能删边，只适合"只加边"或离线问题。
- 度数、边数是原图的量，与并查集树的父子关系无关。
- 计数题（1139C）：取模、快速幂、减法补 MOD 三件套缺一不可。
- 边权求和、点对计数用 `long long`。

## 10. 训练顺序（下午 3.5 小时）

| 顺序 | 题目 | rating | 预计用时 | 训练目标 |
|---:|---|---:|---:|---|
| 1 | 1263D Secret Passwords | 1500 | 25 分钟 | 换对象合并热身 |
| 2 | 103B Cthulhu | 1500 | 20 分钟 | 连通性 + 边数结论 |
| 3 | 977E Cyclic Components | 1500 | 25 分钟 | 块上打标记 |
| 4 | 1139C Edgy Trees | 1500 | 30 分钟 | 补集计数 + 快速幂 |
| 5 | 1468J Road Reform | 1800 | 45 分钟 | Kruskal + 代价分类 |
| 6 | 2060E Graph Composition | 1500 | 45 分钟 | 双 DSU 压轴构造 |

卡题纪律：单题超过预计用时 50% 仍无思路，回读讲义对应小节；再卡 10 分钟看题解并标记"重写"。

## 11. 小结口诀

```text
并查集两件事：find 找根，merge 并块。
块的信息挂根上，读取之前先 find。
至少一条黑边？总方案减全红。
最小生成树：排序加边不成环。
两图对齐：跨块必删，剩片补边。
```
