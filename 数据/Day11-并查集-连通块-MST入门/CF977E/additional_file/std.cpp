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
