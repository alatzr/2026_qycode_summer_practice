# Day 9 教师讲义：树上 DFS、DFS 序、子树区间与树形递归

适用班级：已完成 Day8（BFS/Dijkstra/状态图）的学生。

课时定位：树论第一课。核心是**树上 DFS 的后序合并**（子树信息汇到父亲）与 **DFS 序**（子树 = 时间戳连续区间）。全天强调"父子关系、子树大小、根的选择"三件事，并提醒递归深度风险。

配套题单：

| 题号 | 题目 | rating | 本课对应知识点 | 教学目标 |
|---|---|---:|---|---|
| 930A | Peculiar apple-tree | 1500 | 按层计数 | 学会"同层两两抵消" |
| 580C | Kefa and Park | 1500 | DFS 路径状态 | 学会"沿路径累计再剪枝" |
| 982C | Cut 'em all! | 1500 | 子树大小奇偶 | 学会"偶子树可切" |
| 1056D | Decorate Apple Tree | 1600 | 叶子计数 + 排序 | 学会"叶子数即答案序列" |
| 1006E | Military Problem | 1600 | DFS 序定位 | 学会"子树是连续区间" |
| 763A | Timofey and a tree | 1600 | 找冲突边 + 检查根 | 学会"根必是冲突边端点" |

## 0. 课堂安排

上午讲解（180 分钟）：

| 时间 | 内容 | 教师重点 |
|---:|---|---|
| 0-20 分钟 | 树的存储 + DFS 后序 | 邻接表、`v==parent` 防回走 |
| 20-40 分钟 | 930A 按层计数 | BFS 求深度（防爆栈） |
| 40-65 分钟 | 982C 子树大小 | 后序累加 siz |
| 65-90 分钟 | 580C 路径状态 DFS | 连续猫计数 + 剪枝 |
| 90-110 分钟 | 1056D 叶子计数 | 后序 + 排序 |
| 110-145 分钟 | 1006E DFS 序 | tin + siz = 连续区间 |
| 145-180 分钟 | 763A 找冲突边 | 根必是冲突边端点 |

下午训练（210 分钟）：按 §8 顺序，1006E/763A 允许先交部分分。

## 1. 树上 DFS 的两种基本形态

```text
后序合并：先递归所有孩子，再把孩子信息汇总到父亲（siz、leafCnt、dp）
DFS 序：进入时打时间戳 tin[u]，子树 = [tin[u], tin[u]+siz[u]-1] 连续区间
```

**递归深度风险**：链状树递归 DFS 深度可达 n，n=2e5 时可能爆栈。本课多数题递归可过（数据允许），但 930A 特意用 BFS 求深度示范"防爆栈"写法；正式比赛遇深链要改迭代或手写栈。

## 2. 930A Peculiar apple-tree：按层计数

### 2.1 题型定位

苹果从各点同时向根移动，同一时刻到同一点的两个苹果抵消。求最终到根的苹果数。**同深度的苹果两两抵消，只留奇偶性**。

### 2.2 参考代码（已过官方样例，BFS 求深度防爆栈）

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> children(n + 1);
    for(int i = 2; i <= n; i++){
        int par;
        cin >> par;
        children[par].push_back(i);
    }

    // BFS 按层求深度（Day8 模板），链状树也不会爆栈
    vector<int> cntAtDepth(n + 1, 0);
    vector<int> depth(n + 1, 0);
    queue<int> que;
    que.push(1);
    cntAtDepth[0] = 1;

    while(!que.empty()){
        int u = que.front();
        que.pop();
        for(int v : children[u]){
            depth[v] = depth[u] + 1;
            cntAtDepth[depth[v]]++;
            que.push(v);
        }
    }

    // 同层苹果同时到根，两两抵消只留奇偶性；不同层苹果永不相遇
    int ans = 0;
    for(int d = 0; d <= n; d++) ans += cntAtDepth[d] & 1;

    cout << ans << '\n';
    return 0;
}
```

### 2.3 易错点

- 深度从根 0 开始，`cntAtDepth[0]=1`（根自己）。
- 答案是各层数量的**奇偶和**（每层剩 0 或 1 个）。
- 用 BFS 求深度天然防爆栈。

## 3. 982C Cut 'em all!：子树大小奇偶

### 3.1 题型定位

删边使每个连通块点数为偶，求最多删几条边。**子树大小为偶 ⇒ 可切掉它与父亲的边**。

### 3.2 关键设计

后序求 `siz[u]`。若 `siz[u]` 为偶且 u 非根，答案 +1（切这条边两侧都偶）。总点数为奇则无解 -1。

### 3.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, siz[N], ans;
vector<int> g[N];

void dfs(int u, int parent){
    siz[u] = 1;
    for(int v : g[u]){
        if(v == parent) continue;
        dfs(v, u);
        siz[u] += siz[v];
    }
    // 子树大小为偶数：切掉 u 与父亲之间的边，两侧都还是偶数
    if(u != 1 && siz[u] % 2 == 0) ans++;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i = 1; i < n; i++){
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    if(n % 2 == 1){          // 总点数是奇数，无论怎么切都会剩奇数块
        cout << -1 << '\n';
        return 0;
    }

    dfs(1, 0);
    cout << ans << '\n';
    return 0;
}
```

### 3.4 易错点

- 总点数奇数直接 -1。
- 根不计（根与"父亲"无边）。

## 4. 580C Kefa and Park：DFS 路径状态

### 4.1 题型定位

从根到叶的路径上"连续猫"数不能超过 m。求满足的叶子数。**DFS 沿路径维护连续猫计数，超限剪枝**。

### 4.2 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, m, hasCat[N], ans;
vector<int> g[N];

void dfs(int u, int parent, int catRun){
    catRun = hasCat[u] ? catRun + 1 : 0;   // 连续猫计数：有猫加一，无猫清零
    if(catRun > m) return;                 // 超限后整棵子树都到不了，直接剪掉

    bool isLeaf = true;
    for(int v : g[u]){
        if(v == parent) continue;
        isLeaf = false;
        dfs(v, u, catRun);
    }
    if(isLeaf && u != 1) ans++;            // 根不算叶子
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> hasCat[i];
    for(int i = 1; i < n; i++){
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0, 0);
    cout << ans << '\n';
    return 0;
}
```

### 4.3 易错点

- 连续猫：**有猫累加、无猫清零**（不是总猫数）。
- 超限直接 return（子树全不可达），这是剪枝也是正确性。
- 叶子判定：除根外无未访问孩子。

## 5. 1056D Decorate Apple Tree：叶子计数 + 排序

### 5.1 题型定位

用 k 种颜色染叶子，使每个点子树内叶子颜色互异的点尽量多。求 k=1..n 的答案。**答案序列 = 各点子树叶子数排序**。

### 5.2 关键设计

后序求 `leafCnt[u]`。用 k 种颜色能让 `leafCnt[u] ≤ k` 的点全部"满足"，所以把所有 `leafCnt` 排序，第 k 个答案 = 排序后 ≤ k 的个数——直接输出排序后的 leafCnt 序列即为每个 k 的临界。

### 5.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, leafCnt[N];
vector<int> children[N];

void dfs(int u){
    if(children[u].empty()){   // 没有孩子就是叶子
        leafCnt[u] = 1;
        return;
    }
    leafCnt[u] = 0;
    for(int v : children[u]){  // 后序：先算孩子，再累加到父亲
        dfs(v);
        leafCnt[u] += leafCnt[v];
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i = 2; i <= n; i++){
        int par;
        cin >> par;
        children[par].push_back(i);
    }

    dfs(1);

    // 用 k 种颜色能让 leafCnt[u] <= k 的点全部开心，故第 k 小的 leafCnt 就是第 k 个答案
    sort(leafCnt + 1, leafCnt + n + 1);
    for(int i = 1; i <= n; i++)
        cout << leafCnt[i] << " \n"[i == n];
    return 0;
}
```

### 5.4 易错点

- 叶子 leafCnt=1；内部点后序累加。
- 排序后直接输出即每个 k 的答案序列（想清"≤k 的点数"这层转化）。

## 6. 1006E Military Problem：DFS 序定位（重点）

### 6.1 题型定位

给定树（孩子按编号升序遍历），多次询问"从 u 开始 DFS 的第 k 个点"。**子树在 DFS 序里是连续区间**。

### 6.2 关键设计

一遍 DFS 求 `tin[u]`（进入时间）、`siz[u]`（子树大小）、`ord[t]`（DFS 序第 t 个点）。u 子树 = `[tin[u], tin[u]+siz[u]-1]`，第 k 个就是 `ord[tin[u]+k-1]`；`siz[u] < k` 输出 -1。

### 6.3 手动模拟（树 1-2,1-3,2-4，孩子升序）

DFS 序：1(tin=1) → 2(tin=2) → 4(tin=3) → 3(tin=4)。`ord=[_,1,2,4,3]`，`siz[1]=4,siz[2]=2`。查询 (u=2,k=2)：`ord[tin[2]+1]=ord[3]=4`。查询 (u=2,k=3)：`siz[2]=2<3` ⇒ -1。

### 6.4 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
vector<int> g[N];
int tin[N], siz[N], ord[N], timeStamp;

void dfs(int u){
    tin[u] = ++timeStamp;   // 进入时间
    ord[timeStamp] = u;     // DFS 序第 timeStamp 个点是 u
    siz[u] = 1;

    for(int v : g[u]){
        dfs(v);
        siz[u] += siz[v];
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    for(int i = 2; i <= n; i++){
        int par;
        cin >> par;
        g[par].push_back(i);   // 孩子按编号从小到大加入，天然满足遍历顺序
    }

    dfs(1);

    while(q--){
        int u, k;
        cin >> u >> k;

        if(siz[u] < k) cout << -1 << '\n';
        else cout << ord[tin[u] + k - 1] << '\n';   // 子树是连续区间，第 k 个直接定位
    }

    return 0;
}
```

### 6.5 赛场策略与易错点

- DFS 序 = 树论最核心工具之一（Day28/Day29 树上路径查询都用它）。
- 孩子遍历顺序要与题面一致（本题按编号升序）。
- 深链递归风险：本题数据可过，但记住"tin/siz 也可迭代 DFS 求"（Day29 用迭代版）。

## 7. 763A Timofey and a tree：找冲突边 + 检查根

### 7.1 题型定位

能否选一个根，使删除根后每个子树内部颜色一致。**根必是某条"两端颜色不同"的冲突边的端点**。

### 7.2 关键设计

找任意一条冲突边 (u,v)。根只可能是 u 或 v（否则该冲突边落在某个子树内，破坏一致性）。对 u、v 各做一次 `goodRoot` 检查（删它后每个邻接部分内部同色）。无冲突边则全树同色，任意根都行。

### 7.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, color[N];
vector<int> g[N];

// 检查 u 所在的整个部分（不往回走）颜色是否全为 col
bool dfsSame(int u, int parent, int col){
    if(color[u] != col) return false;
    for(int v : g[u]){
        if(v == parent) continue;
        if(!dfsSame(v, u, col)) return false;
    }
    return true;
}

// 以 root 为根：删掉 root 后，每个相邻部分内部颜色必须一致
bool goodRoot(int root){
    for(int v : g[root])
        if(!dfsSame(v, root, color[v])) return false;
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    vector<pair<int,int>> edges(n - 1);
    for(auto &[u, v] : edges){
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 1; i <= n; i++) cin >> color[i];

    // 找一条两端颜色不同的冲突边；根必须是它的某个端点
    int endU = -1, endV = -1;
    for(auto &[u, v] : edges){
        if(color[u] != color[v]){
            endU = u;
            endV = v;
            break;
        }
    }

    if(endU == -1){                 // 全树同色，任何点都能当根
        cout << "YES\n" << 1 << '\n';
    }else if(goodRoot(endU)){       // 只需检查冲突边的两个端点
        cout << "YES\n" << endU << '\n';
    }else if(goodRoot(endV)){
        cout << "YES\n" << endV << '\n';
    }else{
        cout << "NO\n";
    }
    return 0;
}
```

### 7.4 赛场策略与易错点

- **关键洞察**：候选根只有 2 个（冲突边两端），把 `O(n)` 个候选压到 2 个。
- 全同色特判输出任意点（如 1）。
- `goodRoot` 只需对每个邻居检查其部分内部同色，`O(n)`。

## 8. 当天训练顺序

| 顺序 | 题目 | rating | 预计用时 | 目标 |
|---:|---|---:|---:|---|
| 1 | 930A Peculiar apple-tree | 1500 | 25 min | 按层计数 |
| 2 | 982C Cut 'em all! | 1500 | 25 min | 子树大小奇偶 |
| 3 | 580C Kefa and Park | 1500 | 30 min | 路径状态 DFS |
| 4 | 1056D Decorate Apple Tree | 1600 | 30 min | 叶子计数 |
| 5 | 1006E Military Problem | 1600 | 40 min | DFS 序定位 |
| 6 | 763A Timofey and a tree | 1600 | 40 min | 找冲突边 |

## 9. 易错点清单

- DFS 防回走：`if(v == parent) continue`。
- 后序合并：先递归孩子再汇总父亲。
- DFS 序：子树 = `[tin[u], tin[u]+siz[u]-1]`。
- 路径状态（580C）：连续计数遇断清零。
- 递归深度风险：深链可能爆栈，930A 用 BFS 求深度示范防爆栈；大数据可改迭代 DFS。
- 候选压缩（763A）：根只可能是冲突边端点。

晚间任务：树题三张模型卡（父子关系、子树大小、根的选择）；把 1006E 的"DFS 序 = 连续区间"和 763A 的"根必是冲突边端点"各写成 4 行卡片。
