# Day 10 学生讲义：拓扑排序、DAG 上的 DP 与功能图找环

> 学习方式：先理解题型的核心想法，再手算例子，随后阅读模板并独立实现。完成后复盘关键变量、复杂度和边界。


适用班级：已完成 Day8（BFS/Dijkstra）与 Day9（树上 DFS）的学生。

学习重点：图论第三课，聚焦三条主线——**拓扑排序模板**、**DAG 上做 DP**、**功能图（每点一条出边）找环**。Floyd 全源最短路移至假期自习包 E 模块，期望类题目不在本期主线。

配套题单（按训练顺序）：

| 题号 | 题目 | rating | 本课对应知识点 | 掌握目标 |
|---|---|---:|---|---|
| 1020B | Badge | 1000 | 功能图热身 | 看懂"每点唯一出边"的结构 |
| 1851E | Nastya and Potions | 1500 | 拓扑序结算成本 | 学会"前置全部就绪再结算" |
| 510C | Fox And Names | 1600 | 约束建图 + 拓扑 | 学会把顺序约束翻译成边 |
| 1027D | Mouse Hunt | 1700 | 功能图找环 | 学会三色标记沿边走 |
| 919D | Substring | 1700 | DAG 计数 DP | 学会拓扑序上推 dp |
| 1572A | Book | 1800 | DAG DP + 轮次代价 | 学会给边附加代价条件 |

## 1. 拓扑排序：模板与判环

### 1.1 入度队列版模板（板书核心）

```text
1. 统计每个点的入度 indeg[v]。
2. 所有 indeg == 0 的点入队。
3. 出队 u，处理 u；把 u 的每条出边 u->v 的 indeg[v] 减 1，减到 0 就入队。
4. 出队总数 < n  ⇔  图中有环。
```

### 1.2 手动模拟（5 点小图）

边：1→3，2→3，3→4，2→5。

| 步骤 | 队列 | 出队 | indeg 变化 |
|---:|---|---|---|
| 初始 | [1, 2] | — | indeg: 3:2, 4:1, 5:1 |
| 1 | [2] | 1 | 3 的入度 2→1 |
| 2 | [] | 2 | 3: 1→0 入队；5: 1→0 入队 |
| 3 | [3, 5] | 3 | 4: 1→0 入队 |
| 4 | [5, 4] | 5、4 | 出队总数 5 = n，无环 |

拓扑序 `1 2 3 5 4`（不唯一）。

### 1.3 三个必答问题

1. 为什么无环图一定存在入度 0 的点？（若人人有前驱，沿前驱走 n+1 步必重复 ⇒ 有环）
2. 拓扑序为什么适合做 DP？（处理 u 时它的所有前驱已处理完）
3. 队列换成栈/优先队列会怎样？（仍是合法拓扑序 / 得到字典序最小拓扑序）

## 2. 1020B Badge：功能图热身

### 2.1 题意与模型

每个学生指认一个"下一个"（可能指自己）。从每个起点沿指认链走，输出第一个被走到两次的学生。**功能图**：每点恰一条出边 ⇒ 从任意点出发必进入唯一的环。

### 2.2 思路与部分分

n ≤ 1000 ⇒ 对每个起点直接走，`visMark` 记"本轮起点编号"避免每轮 memset，总 `O(n²)`。数据再大就需要环检测 + 记忆化（给学有余力的学生留口子）。

### 2.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1010;
int nxt[N];      // nxt[i]：学生 i 指认的下一个学生
int visMark[N];  // visMark[i]：i 最近一次被访问时的起点编号，0 表示没访问过

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> nxt[i];
    for(int start = 1; start <= n; start++){
        int cur = start;
        while(visMark[cur] != start){  // 第一个被走到第二次的点就是答案
            visMark[cur] = start;
            cur = nxt[cur];
        }
        cout << cur << " \n"[start == n];
    }
    return 0;
}
```

### 2.4 易错点

- `visMark` 用起点编号打标，省去每轮清空（常用小技巧）。
- 自环（指自己）天然被处理，别特判。

## 3. 1851E Nastya and Potions：拓扑序结算成本

### 3.1 题意与模型

每种药水可以直接买（价 `buyPrice`），或用配方原料调配（成本 = 原料成本之和）；k 种药水免费。求每种药水最小成本。配方无环 ⇒ **原料→成品建边，拓扑序结算**。

### 3.2 四段式

- **暴力**：记忆化搜索同样正确（DAG 上 DFS），但多测下拓扑写法不易爆栈。
- **正解**：入度 = 配方原料数。出队时该点所有原料成本已定：`cost[u] = min(buyPrice[u], mixSum[u])`，免费则强制 0；再把 `cost[u]` 累进每个成品的 `mixSum`。
- **赛场策略**：识别关键词"配方无环"⇒ 拓扑；累加和用 long long（原料上万种、价 1e9）。
- **易错**：免费药水也要参与向后累加（免费 ≠ 删除）；`mixSum` 开 long long；多测重建所有数组。

### 3.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n, k;
    cin >> n >> k;
    vector<long long> buyPrice(n + 1), cost(n + 1, 0);
    vector<bool> freeSupply(n + 1, false);
    vector<vector<int>> product(n + 1);  // product[u]：以 u 为原料的成品列表
    vector<int> indeg(n + 1, 0);         // 拓扑入度 = 配方原料个数
    vector<int> recipeLen(n + 1, 0);     // 配方长度，0 表示只能购买
    vector<long long> mixSum(n + 1, 0);  // 已结算原料的成本累加

    for(int i = 1; i <= n; i++) cin >> buyPrice[i];
    for(int i = 0; i < k; i++){
        int id;
        cin >> id;
        freeSupply[id] = true;
    }
    for(int i = 1; i <= n; i++){
        cin >> recipeLen[i];
        indeg[i] = recipeLen[i];
        for(int j = 0; j < recipeLen[i]; j++){
            int ingredient;
            cin >> ingredient;
            product[ingredient].push_back(i);  // 边：原料 -> 成品
        }
    }

    queue<int> q;
    for(int i = 1; i <= n; i++)
        if(indeg[i] == 0) q.push(i);

    while(!q.empty()){
        int u = q.front();
        q.pop();
        // 弹出时 u 的全部原料都已结算，确定 u 的最小成本
        if(recipeLen[u] == 0) cost[u] = buyPrice[u];
        else cost[u] = min(buyPrice[u], mixSum[u]);
        if(freeSupply[u]) cost[u] = 0;  // 免费药水强制为 0
        for(int v : product[u]){
            mixSum[v] += cost[u];
            if(--indeg[v] == 0) q.push(v);
        }
    }

    for(int i = 1; i <= n; i++) cout << cost[i] << " \n"[i == n];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--) solve();
    return 0;
}
```

## 4. 510C Fox And Names：把顺序约束翻译成边

### 4.1 题意与模型

给 n 个名字，问是否存在一种字母表顺序，使名字序列按新字典序恰好非降；输出任意合法字母表或 `Impossible`。**约束建图经典**：相邻两名字找第一个不同字符 `u, v` ⇒ 边 `u→v`；跑 26 个点的拓扑。

### 4.2 建图细节（本题全部分数都在细节里）

1. 只比较**相邻**两串（传递性由拓扑保证）；
2. 第一个不同字符产生唯一约束，后面的字符无约束；
3. **前缀陷阱**：若无不同字符且前串更长（`abc` 排在 `ab` 前），任何字母表都救不了 ⇒ 直接 `Impossible`；
4. 重边判掉，避免入度重复累加。

### 4.3 手动模拟（名字：`rivest`、`shamir`、`adleman`）

| 相邻对 | 第一个不同 | 约束边 |
|---|---|---|
| rivest / shamir | r vs s | r→s |
| shamir / adleman | s vs a | s→a |

拓扑后 `r` 在 `s` 前、`s` 在 `a` 前，其余 23 个字母自由——输出任意含该链的排列即可（多解）。

### 4.4 参考代码（已过官方样例；多解，经检验器核验：输出为 26 字母排列且满足全部相邻约束）

```cpp
#include<bits/stdc++.h>
using namespace std;

vector<int> g[26];
int indeg[26];
bool hasEdge[26][26];  // 判重边，避免入度重复累加

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<string> names(n);
    for(auto &name : names) cin >> name;

    for(int i = 0; i + 1 < n; i++){
        const string &pre = names[i], &nxt = names[i + 1];
        int len = (int)min(pre.size(), nxt.size());
        int pos = 0;
        while(pos < len && pre[pos] == nxt[pos]) pos++;
        if(pos == len){
            // 一串是另一串的前缀：长串排在自己前缀之前必然非法
            if(pre.size() > nxt.size()){
                cout << "Impossible\n";
                return 0;
            }
            continue;  // 前缀在前天然合法，产生不了字母约束
        }
        int u = pre[pos] - 'a', v = nxt[pos] - 'a';  // 约束：u 必须排在 v 前面
        if(!hasEdge[u][v]){
            hasEdge[u][v] = true;
            g[u].push_back(v);
            indeg[v]++;
        }
    }

    queue<int> q;
    for(int i = 0; i < 26; i++)
        if(indeg[i] == 0) q.push(i);

    string order;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        order += char('a' + u);
        for(int v : g[u])
            if(--indeg[v] == 0) q.push(v);
    }

    if((int)order.size() < 26) cout << "Impossible\n";  // 约束成环
    else cout << order << '\n';
    return 0;
}
```

### 4.5 易错点

- 前缀陷阱方向搞反（`ab` 在 `abc` 前是合法的）；
- 约束建成双向边；
- 输出不足 26 个字母（没把无约束字母并入）。

## 5. 1027D Mouse Hunt：功能图找环

### 5.1 题意与模型

每个房间的老鼠每秒跑向固定房间（功能图）。在若干房间放捕鼠器（费用 `trapCost`），保证无论老鼠初始在哪都会被捕。老鼠最终必进入某个环 ⇒ **每个环上放一个最便宜的**，链上不用放。

### 5.2 三色标记找环

```text
state = 0 未访问 / 1 在本轮路径上 / 2 已封存
从每个未访问点沿唯一出边走：
  撞到 state==1 的点 ⇒ 发现新环，从撞点绕环一圈取最小费用
  撞到 state==2 的点 ⇒ 汇入旧结构，本轮无新环
  最后把本轮路径全部标 2
```

这是功能图找环的标准写法，比 DFS 递归更稳（无爆栈风险）。

### 5.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int trapCost[N], nxt[N];
int state[N];  // 0 未访问，1 在本轮路径上，2 已处理完

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> trapCost[i];
    for(int i = 1; i <= n; i++) cin >> nxt[i];

    long long ans = 0;
    for(int i = 1; i <= n; i++){
        if(state[i] != 0) continue;
        int cur = i;
        while(state[cur] == 0){  // 沿唯一出边走，路径上的点标 1
            state[cur] = 1;
            cur = nxt[cur];
        }
        if(state[cur] == 1){     // 撞上本轮路径：发现一个新环
            int cycleMin = trapCost[cur];
            for(int p = nxt[cur]; p != cur; p = nxt[p])
                cycleMin = min(cycleMin, trapCost[p]);
            ans += cycleMin;
        }
        for(int p = i; state[p] == 1; p = nxt[p]) state[p] = 2;  // 本轮路径全部封存
    }
    cout << ans << '\n';
    return 0;
}
```

### 5.4 易错点

- 撞到 `state==2` 的点也要把本轮路径封存（第三个循环的终止条件写 `state[p]==1`）；
- 费用总和 long long；
- 自环是长度 1 的环。

## 6. 919D Substring：DAG 计数 DP（压轴一）

### 6.1 题意与模型

有向图每点一个小写字母，路径价值 = 路径上出现最多的字母次数。求最大价值；若有环输出 -1（可无限刷）。**先判环，再在拓扑序上推 `dp[v][ch]`** = 以 v 结尾的路径中字母 ch 的最大出现次数。

### 6.2 转移与结算顺序（本题的教学核心）

```text
u 出队时（前驱已全部转移给它）：
  1. dp[u][字母(u)] += 1     ← 结算自己
  2. 用 dp[u][*] 更新答案
  3. 对每条 u->v：dp[v][ch] = max(dp[v][ch], dp[u][ch])
```

"先收完再结算自己、结算完再外发"——DAG DP 的通用节奏，写反顺序就会把自己的字母算给前驱。

### 6.3 手动模拟（3 点：字母 a b a，边 1→2, 2→3）

| 出队 | 结算后 dp | 外发 |
|---|---|---|
| 1 | dp[1] = {a:1} | dp[2][a] ← 1 |
| 2 | dp[2] = {a:1, b:1} | dp[3][a] ← 1, dp[3][b] ← 1 |
| 3 | dp[3] = {a:2, b:1} | 答案 = 2（路径 1→2→3 上两个 a） |

### 6.4 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 10;
vector<int> g[N];
int indeg[N];
int dp[N][26];  // dp[v][ch]：以 v 结尾的路径中字母 ch 的最多出现次数

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    string letters;
    cin >> letters;
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        indeg[v]++;
    }

    queue<int> q;
    for(int i = 1; i <= n; i++)
        if(indeg[i] == 0) q.push(i);

    int done = 0, ans = 0;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        done++;
        dp[u][letters[u - 1] - 'a']++;  // 所有前驱都转移完，此刻结算 u 自己的字母
        for(int ch = 0; ch < 26; ch++) ans = max(ans, dp[u][ch]);
        for(int v : g[u]){
            for(int ch = 0; ch < 26; ch++)
                dp[v][ch] = max(dp[v][ch], dp[u][ch]);
            if(--indeg[v] == 0) q.push(v);
        }
    }

    if(done < n) cout << -1 << '\n';  // 有环：字母次数可以无限大
    else cout << ans << '\n';
    return 0;
}
```

### 6.5 易错点

- 判环就是"出队数 < n"，不需要额外 DFS；
- 重边/自环：自环即环，输出 -1（模板天然处理）；
- `dp` 数组 26 倍空间，`3e5 × 26` 个 int ≈ 30MB，内存估算要过一遍。

## 7. 1572A Book：DAG DP + 轮次代价（压轴二）

### 7.1 题意与模型

一本书 n 章，第 v 章要先懂它的全部前置章。每一轮从第 1 章翻到第 n 章，能懂就懂。问最少读几轮全懂；矛盾（有环）输出 -1。

**关键翻译**：`dp[v]` = 懂第 v 章的最早轮次。对前置 u→v：若 `u < v`（本轮先翻到 u）代价 +0，否则（u 在 v 后面，得等下一轮）代价 +1：

```text
dp[v] = max(dp[u] + (u > v ? 1 : 0))
```

这是"边上带条件代价"的 DAG 最长路——CSP 里常见的"轮次/趟数"模型。

### 7.2 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n;
    cin >> n;
    vector<vector<int>> g(n + 1);
    vector<int> indeg(n + 1, 0);
    vector<int> dp(n + 1, 1);  // dp[v]：理解第 v 章至少要读到第几轮
    for(int v = 1; v <= n; v++){
        int need;
        cin >> need;
        indeg[v] = need;
        for(int j = 0; j < need; j++){
            int u;
            cin >> u;
            g[u].push_back(v);  // 先懂 u 才能懂 v
        }
    }

    queue<int> q;
    for(int i = 1; i <= n; i++)
        if(indeg[i] == 0) q.push(i);

    int done = 0, ans = 0;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        done++;
        ans = max(ans, dp[u]);
        for(int v : g[u]){
            // 前置编号更大：本轮读到 v 时 u 还没读完，只能等下一轮
            dp[v] = max(dp[v], dp[u] + (u > v ? 1 : 0));
            if(--indeg[v] == 0) q.push(v);
        }
    }

    if(done < n) cout << -1 << '\n';
    else cout << ans << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--) solve();
    return 0;
}
```

### 7.3 易错点

- 代价条件是 `u > v` 而不是 `u >= v`；
- `dp` 初值 1（第一轮就在读）；
- Σ前置数有总和上限，邻接表按 n 开、多测重建。

## 8. 训练建议与复盘

| 顺序 | 题目 | rating | 预计用时 |
|---:|---|---:|---:|
| 1 | 1020B Badge | 1000 | 15 min |
| 2 | 1851E Nastya and Potions | 1500 | 30 min |
| 3 | 510C Fox And Names | 1600 | 35 min |
| 4 | 1027D Mouse Hunt | 1700 | 35 min |
| 5 | 919D Substring | 1700 | 40 min |
| 6 | 1572A Book | 1800 | 40 min |

## 9. 易错点清单与模型卡

- 拓扑判环 = 出队数 < n，一行搞定，别再写 DFS 判环。
- DAG DP 节奏：**收完 → 结算自己 → 外发**。
- 功能图三件套：唯一出边、必入环、三色标记。
- 约束题先问"约束是谁对谁"，再问"违反约束长什么样"（510C 的前缀陷阱）。
- 今天四张模型卡：拓扑模板 / 约束建图 / 功能图找环 / DAG 轮次 DP。
- Floyd 与"路径经过点集限制"类问题 → 假期自习包 E 模块（7/31）。
