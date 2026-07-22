# Day 12 学生讲义：并查集进阶、离线处理与 Kruskal

前置知识：会写 `find`、`merge`，理解连通块和 Kruskal 的基本过程。

今天要学的不是七个孤立技巧，而是同一个思考框架：

```text
把元素按当前关系分成连通块
    -> 在根节点维护块的附加信息
    -> 设计一个只会“合并”的处理顺序
    -> 在合并瞬间更新答案
```

## 1. 学习路线

| 顺序 | 题目 | rating | 本题只新增一件事 |
|---:|---|---:|---|
| 1 | ABC380E 1D Bucket Tool | 约 1400 | 用并查集维护连续同色段 |
| 2 | CF1167C News Distribution | 1400 | 维护连通块大小 `sz` |
| 3 | CF722C Destroying Array | 1600 | 把删除倒过来变成恢复 |
| 4 | CF1253D Harmonious Graph | 1700 | 维护块的最右编号 `mx` |
| 5 | CF1081D Maximum Distance | 1800 | 按边权逐步放开连通性 |
| 6 | CF1213G Path Queries | 1800 | 合并新增 `sz_x*sz_y` 个点对 |
| 7 | CF1095F Make It Connected | 1900 | 把 `O(n^2)` 候选边缩成 `O(n)` |

ABC380E 没有 Codeforces 官方 rating，表中的“约 1400”只表示本课程中的体感难度。

## 2. 并查集根节点是一个连通块的“档案袋”

连通块内的每个点都指向同一个根。我们可以把整个块的信息存在根上。

| 数组 | 含义 | 合并方式 |
|---|---|---|
| `sz[root]` | 块内点数 | 相加 |
| `l[root],r[root]` | 连续块的左右端点 | 取最小值、最大值 |
| `col[root]` | 连续块的颜色 | 整块染色时修改 |
| `sum[root]` | 块内权值和 | 相加 |
| `mx[root]` | 块内最大编号 | 取最大值 |
| `cnt[root]` | 块内特殊点数 | 相加 |

基本模板：

```cpp
int find(int x)
{
	if (fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
	x = find(x), y = find(y);
	if (x == y) return;
	if (sz[x] < sz[y]) swap(x, y);
	fa[y] = x;
	sz[x] += sz[y];
}
```

注意：合并后只有新根的附加量是完整的。读取块信息时先写 `root=find(x)`。

## 3. ABC380E 1D Bucket Tool：整段染色与相邻段合并

### 3.1 先看清“一次到底染哪些格子”

操作 `1 x c` 不是只修改位置 `x`。它会从 `x` 开始向左右扩展，把包含 `x` 的整个连续同色段都染成颜色 `c`。

例如：

```text
位置:  1  2  3  4  5  6
颜色:  1  2  2  2  5  6
```

执行 `1 3 5` 后，位置 `2..4` 一起变成颜色 5，并与位置 5 合并：

```text
颜色:  1  5  5  5  5  6
```

如果每次都向左右逐格扫描，最坏会达到 `O(nq)`。我们需要把一个连续同色段看成一个整体。

### 3.2 为什么可以使用并查集

一次操作总是修改整个同色段。修改以后只可能发生两件事：

- 和左边的同色段合并；
- 和右边的同色段合并。

它不会把原来的段拆开。因此所有变化都只有“合并”，正好可以使用并查集。

每个根节点维护：

| 数组 | 含义 |
|---|---|
| `l[root],r[root]` | 当前连续段的左右端点 |
| `sz[root]` | 当前段长度 |
| `col[root]` | 当前段颜色 |

再用 `num[c]` 维护整行中颜色 `c` 的格子数。

### 3.3 一次 `1 x c` 怎样处理

```text
root=find(x)，找到包含 x 的整段
若原颜色就是 c，直接结束
从 num[旧颜色] 中减去整段长度
给 num[c] 加上整段长度
把当前段颜色改为 c
尝试与左邻段合并
用合并后的新根，再尝试与右邻段合并
```

注意：相邻段本来已经统计在 `num[c]` 中。合并只是改变区间结构，不能再次增加颜色计数。

### 3.4 样例模拟

```text
初始       [1:1] [2:2] [3:3] [4:4] [5:5]
1 5 4     [1:1] [2:2] [3:3] [4..5:4]
1 4 2     [1:1] [2:2] [3:3] [4..5:2]  -> 颜色2有3格
1 3 2     [1:1] [2..5:2]               -> 同时合并左右两段
1 2 3     [1:1] [2..5:3]               -> 颜色3有4格
```

### 3.5 为什么正确

始终保持：每个并查集块恰好是一个极大连续同色段。

初始时每个格子颜色不同，结论成立。每次先找到 `x` 所在的整段并整体改色，修改范围与题意相同；再合并左右同色邻段，就重新得到极大连续同色段。计数恰好减去旧段长度、加上新段长度，所以查询答案也正确。

### 3.6 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 10;
int n, q;
int fa[N], sz[N], l[N], r[N], col[N], num[N];

int find(int x)
{
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int merge(int x, int y)
{
	x = find(x), y = find(y);
	if (x == y) return x;
	if (sz[x] < sz[y]) swap(x, y);
	fa[y] = x;
	sz[x] += sz[y];
	l[x] = min(l[x], l[y]);
	r[x] = max(r[x], r[y]);
	return x;
}

void paint(int x, int c)
{
	int root = find(x);
	int old = col[root];
	if (old == c) return;

	num[old] -= sz[root];
	num[c] += sz[root];
	col[root] = c;

	int p = l[root] - 1;
	if (p >= 1)
	{
		int y = find(p);
		if (col[y] == c) root = merge(root, y);
	}

	p = r[root] + 1;
	if (p <= n)
	{
		int y = find(p);
		if (col[y] == c) merge(root, y);
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> q;
	for (int i = 1; i <= n; i++)
	{
		fa[i] = l[i] = r[i] = col[i] = i;
		sz[i] = num[i] = 1;
	}

	while (q--)
	{
		int op, x, c;
		cin >> op;
		if (op == 1)
		{
			cin >> x >> c;
			paint(x, c);
		}
		else
		{
			cin >> c;
			cout << num[c] << '\n';
		}
	}
	return 0;
}
```

每次操作只进行常数次并查集操作。时间复杂度为 `O((n+q)alpha(n))`，空间复杂度为 `O(n)`。

自查：为什么与左右同色段合并时，不需要再次修改 `num[c]`？

## 4. CF1167C News Distribution：同群合并，查询块大小

### 4.1 题意转化

消息可以一层一层传递，所以最终能到达的人就是起点所在的整个连通块。

对于群 `{2,5,4}`，只需要：

```text
merge(2,5)
merge(2,4)
```

不需要再做 `merge(5,4)`，因为三人已经在同一块。

### 4.2 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 10;
int fa[N], sz[N];

int find(int x)
{
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
	x = find(x), y = find(y);
	if (x == y) return;
	if (sz[x] < sz[y]) swap(x, y);
	fa[y] = x;
	sz[x] += sz[y];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
	while (m--)
	{
		int k;
		cin >> k;
		if (k == 0) continue;
		int first;
		cin >> first;
		for (int i = 2, x; i <= k; i++)
			cin >> x, merge(first, x);
	}
	for (int i = 1; i <= n; i++) cout << sz[find(i)] << ' ';
	return 0;
}
```

复杂度：`O((n+sum k_i)alpha(n))`。

自查：为什么不能枚举群内所有人对？因为一个大群会产生 `O(k^2)` 次操作。

## 5. CF722C Destroying Array：从“拆分”换成“合并”

### 5.1 逆向思考

正向删除一个位置时，一个连续段可能被拆成两段。DSU 不会拆分。

从最后往前恢复位置：

```text
恢复 x
  若 x-1 已存在，合并左段
  若 x+1 已存在，合并右段
```

根节点维护连续段和 `sum`。两段合并时相加。

### 5.2 下标对应

在逆序循环的第 `i` 步，恢复 `p[i]` 之前，当前状态对应“正向已经删除前 `i` 个位置”。所以先写 `ans[i]=mx`，再恢复。

### 5.3 完整代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 1e5 + 10;
int n, fa[N], p[N];
ll a[N], sum[N], ans[N];
bool vis[N];

int find(int x)
{
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
	x = find(x), y = find(y);
	if (x == y) return;
	fa[y] = x;
	sum[x] += sum[y];
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> p[i];
	ll mx = 0;
	for (int i = n; i >= 1; i--)
	{
		ans[i] = mx;
		int x = p[i];
		vis[x] = true, fa[x] = x, sum[x] = a[x];
		if (x > 1 && vis[x-1]) merge(x, x-1);
		if (x < n && vis[x+1]) merge(x, x+1);
		mx = max(mx, sum[find(x)]);
	}
	for (int i = 1; i <= n; i++) cout << ans[i] << '\n';
	return 0;
}
```

复杂度：`O(n alpha(n))`。`sum` 和答案使用 `long long`。

## 6. CF1253D Harmonious Graph：扫描一个会自动扩展的区间

### 6.1 和谐条件的真正含义

若编号 `l` 和 `r` 连通，那么 `[l,r]` 中的所有点都必须与它们连通。也就是每个连通块最终必须占据一段连续编号。

并查集维护 `mx[root]`。从 `i` 开始，先设 `reach=mx[find(i)]`，再扫描 `[i,reach]`。

如果合并了一个最大编号更远的块，`reach` 也要跟着变大。

```text
{1,4} 要求扫到 4
  在 2 处遇到块 {2,6}
合并后必须改为扫到 6
```

### 6.2 核心代码

```cpp
int ans = 0;
for (int i = 1; i <= n; )
{
	int reach = mx[find(i)];
	for (int j = i + 1; j <= reach; j++)
	{
		if (find(j) != find(i))
		{
			merge(i, j);
			ans++;
			reach = mx[find(i)];
		}
	}
	i = reach + 1;
}
```

其中 `merge` 除了合并 `fa`、`sz`，还要执行：

```cpp
mx[x] = max(mx[x], mx[y]);
```

复杂度：每个位置只被向右扫过常数次，总体为 `O((n+m)alpha(n))`。

## 7. CF1081D Maximum Distance：把边权当成逐步放宽的限制

### 7.1 瓶颈路径

路径代价是路上最大边权。给定 `W`，只保留权值 `<=W` 的边：

- 若两点连通，说明有一条路径的代价不超过 `W`。
- 若两点不连通，说明阈值还不够大。

按边权升序处理就是 Kruskal 式的阈值扫描。根节点维护特殊点数 `cnt`，第一次出现 `cnt[root]==k` 时停止。

### 7.2 核心代码

```cpp
sort(e + 1, e + m + 1, [](Edge a, Edge b){
	return a.w < b.w;
});

int ans = 0;
for (int i = 1; i <= m; i++)
{
	int x = find(e[i].u), y = find(e[i].v);
	if (x == y) continue;
	if (sz[x] < sz[y]) swap(x, y);
	fa[y] = x;
	sz[x] += sz[y];
	cnt[x] += cnt[y];
	if (cnt[x] == k)
	{
		ans = e[i].w;
		break;
	}
}
```

输出 `k` 个相同的 `ans`。平行边和自环在原题中合法，不要在读入时假设它们不存在。

## 8. CF1213G Path Queries：合并瞬间统计贡献

### 8.1 对一个询问重新建图太慢

阈值 `q` 越大，可用边只会越多。把边和询问都排序，指针从小到大加边，之前的并查集状态可以继续使用。

### 8.2 为什么新增 `x*y`

两个块原来不连通，大小分别是 `x,y`。合并后，从第一块选一点、第二块选一点，得到 `x*y` 个新连通点对。

```text
大小 2 的块 {1,2}
大小 3 的块 {3,4,5}
合并新增 2*3=6 对
```

### 8.3 核心代码

```cpp
sort(edges + 1, edges + n, cmpEdge);
sort(queries + 1, queries + m + 1, cmpQuery);

long long cur = 0;
int ptr = 1;
for (int i = 1; i <= m; i++)
{
	while (ptr < n && edges[ptr].w <= queries[i].q)
	{
		int x = find(edges[ptr].u);
		int y = find(edges[ptr].v);
		if (x != y)
		{
			cur += 1ll * sz[x] * sz[y];
			merge(x, y);
		}
		ptr++;
	}
	ans[queries[i].id] = cur;
}
```

两个不能丢的细节：

1. 询问保存原编号 `id`，最后按原顺序输出。
2. 乘法前写 `1ll`，否则两个 `int` 会先溢出。

## 9. CF1095F Make It Connected：先删掉不可能必要的候选边

### 9.1 `O(n^2)` 完全图只是题意，不是让我们真建出来

普通边 `(u,v)` 代价为 `a_u+a_v`。设 `r` 是 `a` 最小的点。只保留：

```text
(r,1), (r,2), ..., (r,n)   除去 (r,r)
```

再加上原题给出的所有特价边。

### 9.2 割性质直觉

任意把点分成左右两组。若 `r` 在左侧，选右侧 `a` 最小的点 `v`，那么 `(r,v)` 不会比任意普通跨组边更贵。所以 MST 需要的最便宜普通跨割边始终在这个星形集合中。

### 9.3 核心代码

```cpp
int mn = min_element(a + 1, a + n + 1) - a;
vector<Edge> edges;

// 先读入 m 条特价边
for (int i = 1; i <= n; i++)
	if (i != mn)
		edges.push_back({mn, i, a[mn] + a[i]});

sort(edges.begin(), edges.end(), [](Edge x, Edge y){
	return x.w < y.w;
});

long long ans = 0;
for (Edge e : edges)
{
	int x = find(e.u), y = find(e.v);
	if (x == y) continue;
	merge(x, y);
	ans += e.w;
}
```

候选边数从 `O(n^2)` 变为 `n-1+m`，总复杂度 `O((n+m)log(n+m))`。权值和总代价都用 `long long`。

## 10. 当天训练建议

| 题目 | 建议时间 | 完成后要能回答 |
|---|---:|---|
| ABC380E | 25 min | 为什么连续段只会合并，不会拆分 |
| 1167C | 20 min | 为什么一个群只合并 `k-1` 次 |
| 722C | 30 min | 逆序第 `i` 步对应哪个正向状态 |
| 1253D | 35 min | 为什么 `reach` 可能扩大 |
| 1081D | 35 min | 为什么不是普通最短路 |
| 1213G | 45 min | `sz[x]*sz[y]` 在数什么 |
| 1095F | 45 min | 为什么只保留全局最小点的星形边 |

## 11. 易错点清单

- ABC380E 要给 `num` 加减整段长度，不是只修改一个格子。
- 与左段合并后根和右端点可能变化，必须用新根检查右段。
- 读取相邻段颜色前先 `find`，非根节点的 `col` 已经没有意义。
- CF1167C 遇到 `k=0` 时，后面没有成员编号。
- 恢复位置时要同时检查左、右邻居。
- 722C 是先记录答案，再恢复当前位置。
- 1253D 合并后要重新读取最右边界。
- DSU 块信息只读根节点。
- 询问离线排序后不能丢原编号。
- 段和、点对数、MST 总代价使用 `long long`。
- 完全图先思考如何缩减候选边，不要直接写两层循环。

## 12. 六句总结

```text
连续同色段只合不拆，整段染色后检查左右邻段。
附加信息存在根，合并两块同步更新。
删除难就倒过来，把拆分变成添加。
阈值询问先排序，边按权值逐步加入。
两块合并算贡献，新点对数量就是 x*y。
隐式完全图先证明缩边，候选集够小再跑 Kruskal。
```
