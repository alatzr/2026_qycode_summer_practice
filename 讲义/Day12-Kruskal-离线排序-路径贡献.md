# Day 12 教师讲义：并查集进阶、离线处理与 Kruskal

适用班级：已完成 Day11 并查集、连通块和 MST 入门的学生。

本日目标：不再只问“两点是否连通”，而是学会在连通块合并时维护附加信息，并通过逆序、排序和候选边缩减解决更复杂的图论问题。

## 0. 题单调整与难度曲线

原题单虽然 rating 集中在 1700-1800，但知识线从二分图跳到功能图，又跳回 Kruskal，学生每道题都要重新建模。rating 持平不等于体感平滑。

调整后七道题共用一条主线：

```text
连续同色段动态合并
    -> 直接统计连通块大小
    -> 逆序恢复元素
    -> 连通块维护区间边界
    -> 按边权逐步连通
    -> 合并瞬间统计点对贡献
    -> 缩减完全图候选边再做 Kruskal
```

|  顺序 | 题目                        | rating | 课堂体感 | 新增能力                  |
| --: | ------------------------- | -----: | ---: | --------------------- |
|   1 | ABC380E 1D Bucket Tool    | 约 1400 |  1/7 | 连续同色段的边界、大小与颜色计数      |
|   2 | CF1167C News Distribution |   1400 |  2/7 | 直接维护连通块大小 `sz`        |
|   3 | CF722C Destroying Array   |   1600 |  3/7 | 删除转逆序恢复，块和 `sum`      |
|   4 | CF1253D Harmonious Graph  |   1700 |  4/7 | 块右端点 `mx`，动态扩展区间      |
|   5 | CF1081D Maximum Distance  |   1800 |  5/7 | Kruskal 阈值连通，特殊点计数    |
|   6 | CF1213G Path Queries      |   1800 |  6/7 | 离线询问，`sz_x * sz_y` 贡献 |
|   7 | CF1095F Make It Connected |   1900 |  7/7 | 用割性质缩减候选边             |

其中 ABC380E 没有 Codeforces 官方 rating，表中的“约 1400”只表示课堂体感难度。

### 0.1 课时建议

| 时间 | 内容 | 教师检查点 |
|---:|---|---|
| 0-20 分钟 | 并查集附加量与合并不变式 | 附加量只在根上有意义 |
| 20-45 分钟 | ABC380E | 为什么染色只会合并区间，不会拆分区间 |
| 45-65 分钟 | CF1167C | 群内只需 `k-1` 次合并 |
| 65-90 分钟 | CF722C | 为什么正向删除不好做 |
| 90-115 分钟 | CF1253D | 合并后右边界会扩大 |
| 115-135 分钟 | CF1081D | “第一次全连通”就是最小阈值 |
| 135-160 分钟 | CF1213G | 手算 `x*y` 点对贡献 |
| 160-180 分钟 | CF1095F | 为什么只连全局最小点 |

## 1. 统一框架：合并连通块时还要维护什么

Day11 的并查集只维护 `fa`。Day12 的关键是：每个根节点还代表一个连通块的摘要信息。

| 信息 | 含义 | 合并规则 | 对应题目 |
|---|---|---|---|
| `sz[root]` | 块内点数 | `sz[x] += sz[y]` | ABC380E、1167C、1213G |
| `l[root],r[root]` | 连续块的左右端点 | 分别取最小值、最大值 | ABC380E |
| `col[root]` | 连续块当前颜色 | 整块染色时修改 | ABC380E |
| `sum[root]` | 块内权值和 | `sum[x] += sum[y]` | 722C |
| `mx[root]` | 块内最大编号 | `mx[x] = max(mx[x],mx[y])` | 1253D |
| `cnt[root]` | 块内特殊点数 | `cnt[x] += cnt[y]` | 1081D |

统一合并模板：

```cpp
int merge(int x, int y)
{
	x = find(x), y = find(y);
	if (x == y) return x;
	if (sz[x] < sz[y]) swap(x, y);
	fa[y] = x;
	sz[x] += sz[y];
	// 其他附加量也在这里合并
	return x;
}
```

必须反复强调：`sz[y]`、`sum[y]`等在 `y` 挂到 `x` 之后已经不再代表整个块。后续取数前先 `find`。

## 2. ABC380E 1D Bucket Tool：把连续同色段当成并查集

### 2.1 操作真正修改的是一个连续段

设位置 `x` 当前颜色为 `old`。与 `x` 相邻且颜色相同的格子会继续向左右扩展，因此一次 `1 x c` 修改的是包含 `x` 的**极大连续同色段**，而不只是位置 `x`。

直接从 `x` 向两边扫描虽然容易写，但同一批位置可能被反复经过。最坏情况下每次操作都扫描接近 `n` 个格子，总复杂度会达到 `O(nq)`。

本题有一个非常重要的性质：

```text
一次操作会把整个旧颜色段一起染色；
染色后，只可能与左右相邻的同色段合并；
已经合并的段以后仍然整段染色，所以永远不需要拆开。
```

“只合并、不拆分”正好适合并查集。

### 2.2 根节点维护哪些信息

每个并查集连通块表示一个极大连续同色段，只在根节点维护：

| 数组 | 含义 |
|---|---|
| `l[root],r[root]` | 该段的左右端点 |
| `sz[root]` | 该段的格子数 |
| `col[root]` | 该段当前颜色 |

另外，`num[c]` 表示整行中颜色 `c` 的格子总数。它不是某个连通块的信息，不应放在根节点上。

初始时每个位置单独成段：

```text
[1:颜色1] [2:颜色2] [3:颜色3] ... [n:颜色n]
```

因此 `l[i]=r[i]=i`，`sz[i]=1`，`col[i]=i`，`num[i]=1`。

### 2.3 一次染色的完整步骤

处理 `1 x c`：

1. 令 `root=find(x)`，找到包含 `x` 的整个同色段。
2. 若 `col[root]==c`，颜色没有变化，直接结束。
3. 设旧颜色为 `old`，先更新颜色总数：

   ```cpp
   num[old] -= sz[root];
   num[c] += sz[root];
   col[root] = c;
   ```

4. 检查位置 `l[root]-1` 所在段。若存在且颜色也是 `c`，合并。
5. 左侧合并后根节点和右端点都可能改变，重新使用新根，再检查 `r[root]+1`。

为什么只检查左右各一次？在操作前，每个块已经是极大同色段，所以同一种颜色不可能以两个相邻块存在。染色后最多只会碰到一个左邻段和一个右邻段。

### 2.4 样例手动模拟

`n=5` 时，初始颜色为：

```text
位置:  1  2  3  4  5
颜色:  1  2  3  4  5
```

| 操作 | 操作后的连续段 | 计数变化 |
|---|---|---|
| `1 5 4` | `[1:1] [2:2] [3:3] [4..5:4]` | 颜色 4 变为 2 个 |
| `1 4 2` | `[1:1] [2:2] [3:3] [4..5:2]` | 颜色 2 共 3 个 |
| `2 2` | 不变 | 输出 `3` |
| `1 3 2` | `[1:1] [2..5:2]` | 左右两边都发生合并 |
| `1 2 3` | `[1:1] [2..5:3]` | 整段 4 个格子一起变色 |
| `2 3` | 不变 | 输出 `4` |

### 2.5 正确性说明

始终维护如下不变式：**每个并查集连通块恰好对应一个极大连续同色段。**

- 初始每个格子颜色不同，单点块显然满足不变式。
- 查询时，`find(x)` 找到的块正是题目要求染色的全部格子，因此修改范围正确。
- 染色后，只有左右相邻段可能与当前段同色。把这些段合并后，当前块重新成为极大同色段，其他块不受影响。
- `num` 先减去整段的旧颜色贡献，再加到新颜色中；后续合并的邻段本来就已经计入颜色 `c`，不应再次修改计数。

所以两类询问得到的结果都正确。

### 2.6 参考代码

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

每次染色只有常数次 `find/merge`。总时间复杂度为 `O((n+q)alpha(n))`，空间复杂度为 `O(n)`。

## 3. CF1167C News Distribution：从群组建连通块

### 3.1 从传播过程翻译为图

消息能到达的人，正是起点所在连通块的全部顶点。因此问题只剩两步：

1. 把每个群的成员合并到一个块中。
2. 输出每个人所在块的 `sz`。

一个有 `k` 人的群不要枚举 `O(k^2)` 对好友。选群内第一个人，与其余 `k-1` 人合并即可。

### 3.2 手动模拟

群 A 为 `{2,5,4}`，群 B 为 `{1,2}`。

```text
处理 A: {2} + {5} + {4} -> {2,4,5}, sz=3
处理 B: {1} + {2,4,5} -> {1,2,4,5}, sz=4
```

所以 1、2、4、5 的答案都是 4。

### 3.3 参考代码

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

复杂度：`O((n+sum k_i)alpha(n))`。检查点：`k=0` 时不能继续读群首。

## 4. CF722C Destroying Array：删除不好做，就倒过来恢复

### 4.1 为什么正向卡住

删除一个位置可能把一个连续段拆成两个。普通并查集只支持合并，不支持拆分。

把时间倒过来：初始所有位置都不存在，按删除顺序的逆序逐个恢复。每次恢复只会与左右已存在的段合并，正好适合 DSU。

### 4.2 答案下标是本题最容易错的地方

恢复 `p[i]` 之前，当前存在的元素是 `p[i+1..n]`，这正是正向删除前 `i` 个位置后的状态。所以先记 `ans[i]`，再恢复 `p[i]`。

| 逆序步骤 | 恢复前状态 | 记录的正向答案 |
|---:|---|---|
| `i=n` | 全空 | 删完 `n` 个后的 0 |
| `i=n-1` | 只有 `p[n]` | 删完 `n-1` 个后的答案 |
| ... | ... | ... |

### 4.3 参考代码

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

复杂度：`O(n alpha(n))`。段和可达 `10^14`，必须用 `long long`。

## 5. CF1253D Harmonious Graph：连通块要占满整个编号区间

### 5.1 关键转化

若连通块中有编号 `l` 和 `r`，那么和谐条件要求 `[l,r]` 中的每个点都必须在同一块。

一个块可以由它的编号范围表示：

```text
块 A = {1,4}      必须覆盖 [1,4]
块 B = {2,6}      与 A 要求的区间交叉
合并 A,B 后   新范围扩大到 [1,6]
```

因此从左往右扫，当前块必须吃掉自己最大编号之前的所有其他块。每吃掉一块就补一条边。

### 5.2 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int fa[N], sz[N], mx[N];

int find(int x)
{
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
	x = find(x), y = find(y);
	if (x == y) return;
	if (sz[x] < sz[y]) swap(x, y);
	fa[y] = x, sz[x] += sz[y], mx[x] = max(mx[x], mx[y]);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1, mx[i] = i;
	while (m--)
	{
		int u, v;
		cin >> u >> v;
		merge(u, v);
	}
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
	cout << ans << endl;
	return 0;
}
```

复杂度：`O((n+m) alpha(n))`。核心易错点：合并后必须更新 `reach`。

## 6. CF1081D Maximum Distance：Kruskal 是一个不断增大的边权阈值

### 6.1 不要先想最短路

本题路径代价是“路径上的最大边权”。给定阈值 `W`，只保留权值 `<=W` 的边，两点连通就说明它们之间存在代价不超过 `W` 的路径。

按边权升序加边，等价于让 `W` 从小到大增长。所有特殊点第一次连通时的边权，就是最小可行阈值。

### 6.2 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
struct Edge { int u, v, w; } e[N];
int fa[N], sz[N], cnt[N];

int find(int x)
{
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
	for (int i = 1, x; i <= k; i++) cin >> x, cnt[x] = 1;
	for (int i = 1; i <= m; i++) cin >> e[i].u >> e[i].v >> e[i].w;
	sort(e + 1, e + m + 1, [](Edge a, Edge b){ return a.w < b.w; });
	int ans = 0;
	for (int i = 1; i <= m; i++)
	{
		int x = find(e[i].u), y = find(e[i].v);
		if (x == y) continue;
		if (sz[x] < sz[y]) swap(x, y);
		fa[y] = x, sz[x] += sz[y], cnt[x] += cnt[y];
		if (cnt[x] == k)
		{
			ans = e[i].w;
			break;
		}
	}
	for (int i = 1; i <= k; i++) cout << ans << ' ';
	return 0;
}
```

讲课时追问：为什么 `k` 个输出全部相同？因为瓶颈距离构成超度量，特殊点集合的直径对每个点的最远距离都相同。

## 7. CF1213G Path Queries：一次合并产生多少新点对

### 7.1 从阈值询问到离线排序

对询问 `q`，只保留边权 `<=q` 的树边。同一连通块内任意两点都是合法点对。

边和询问都按权值升序。当一条边连接大小为 `x` 和 `y` 的两块时：

- 块内原有点对已经统计过。
- 新增点对必须一端在左块，一端在右块。
- 方案数恰好是 `x*y`。

### 7.2 手算

边 `(1,2,1)`、`(2,3,3)`，询问阈值依次为 1、3。

| 加入边 | 合并块大小 | 新贡献 | 累计 |
|---|---|---:|---:|
| `(1,2)` | 1 与 1 | 1 | 1 |
| `(2,3)` | 2 与 1 | 2 | 3 |

### 7.3 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 2e5 + 10;
struct Edge { int u, v, w; } e[N];
struct Query { int q, id; } ask[N];
int fa[N], sz[N];
ll ans[N];

int find(int x)
{
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i < n; i++) cin >> e[i].u >> e[i].v >> e[i].w;
	for (int i = 1; i <= m; i++) cin >> ask[i].q, ask[i].id = i;
	sort(e + 1, e + n, [](Edge a, Edge b){ return a.w < b.w; });
	sort(ask + 1, ask + m + 1, [](Query a, Query b){ return a.q < b.q; });
	for (int i = 1; i <= n; i++) fa[i] = i, sz[i] = 1;
	ll cur = 0;
	int j = 1;
	for (int i = 1; i <= m; i++)
	{
		while (j < n && e[j].w <= ask[i].q)
		{
			int x = find(e[j].u), y = find(e[j].v);
			if (x != y)
			{
				cur += 1ll * sz[x] * sz[y];
				if (sz[x] < sz[y]) swap(x, y);
				fa[y] = x, sz[x] += sz[y];
			}
			j++;
		}
		ans[ask[i].id] = cur;
	}
	for (int i = 1; i <= m; i++) cout << ans[i] << ' ';
	return 0;
}
```

易错点：询问排序后要按原 `id` 输出；`sz[x]*sz[y]` 要先转 `long long`。

## 8. CF1095F Make It Connected：完全图不能建，先证明哪些边才可能有用

### 8.1 朴素建图为什么不可行

任意两点 `u,v` 都有一条代价 `a_u+a_v` 的普通边，总数是 `O(n^2)`，`n=2e5` 时无法建出。

设 `r` 为 `a_r` 全局最小的点。只加入 `r` 到其他每个点的 `n-1` 条普通边。

### 8.2 为什么这样不会丢失 MST

考虑任意一个割，假设 `r` 在左侧。若右侧 `v` 的 `a_v` 最小，那么所有跨割的普通边中，`(r,v)` 不会比任意 `(u,v)` 更贵：

```text
a_r + a_v <= a_u + a_v
```

因此每个割所需的最便宜普通边都在这个星形候选集中。再加上所有特价边，跑一次 Kruskal。

### 8.3 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 2e5 + 10;
struct Edge { int u, v; ll w; };
int fa[N], sz[N];
ll a[N];

int find(int x)
{
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i], fa[i] = i, sz[i] = 1;
	int mn = min_element(a + 1, a + n + 1) - a;
	vector<Edge> e;
	e.reserve(n + m - 1);
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		ll w;
		cin >> u >> v >> w;
		e.push_back({u, v, w});
	}
	for (int i = 1; i <= n; i++)
		if (i != mn) e.push_back({mn, i, a[mn] + a[i]});
	sort(e.begin(), e.end(), [](Edge x, Edge y){ return x.w < y.w; });
	ll ans = 0;
	for (Edge now : e)
	{
		int x = find(now.u), y = find(now.v);
		if (x == y) continue;
		if (sz[x] < sz[y]) swap(x, y);
		fa[y] = x, sz[x] += sz[y], ans += now.w;
	}
	cout << ans << endl;
	return 0;
}
```

复杂度：候选边共 `n-1+m` 条，总复杂度 `O((n+m)log(n+m))`。

## 9. 下午训练与部分分路线

| 题目 | 预计时间 | 正解卡住时的可运行方案 |
|---|---:|---|
| ABC380E | 25 min | 小数据直接向左右扫描并逐格染色 |
| 1167C | 20 min | 显式建图 BFS，在 `sum k_i` 不大时可过 |
| 722C | 30 min | `O(n^2)` 每次重新扫描连续段 |
| 1253D | 35 min | 先 BFS 求块区间，小数据重复合并 |
| 1081D | 35 min | 小图 minimax Floyd |
| 1213G | 45 min | 每个询问单独加边统计 |
| 1095F | 45 min | 小 `n` 显式建完全图跑 MST |

建议课堂验收线：全员完成前 3 题，进阶组完成前 6 题，第 7 题允许课后完成。

## 10. 统一易错点

1. 块的边界、大小和颜色只在根节点上有意义。
2. ABC380E 染色后先用新根、新边界检查右邻段，合并邻段时不要重复修改 `num`。
3. CF1167C 遇到 `k=0` 时，后面没有群首可以读取。
4. 删除问题要先考虑能否逆序变成添加。
5. 按权处理时，当前状态代表“所有权值不超过当前阈值的边”。
6. 合并两块的新点对是 `1ll*sz[x]*sz[y]`。
7. 输入权值到 `10^12` 时，单边和 MST 总和都用 `long long`。
8. 出现隐式完全图时，不要立即建边，先用割性质判断哪些候选边必须保留。

## 11. 课后回顾

```text
同色段只合不拆：整段染色，更新计数，再合并左右邻段。
群组只连 k-1 次：块大小留在根上，查询前先找根。
块信息：只存在根上，合并时同步更新。
删除变恢复：把拆分问题改成合并问题。
阈值变加边：排序后用 DSU 维护当前状态。
合并算贡献：两块交叉点对数是 x*y。
完全图先缩边：证明候选集后再跑 Kruskal。
```
