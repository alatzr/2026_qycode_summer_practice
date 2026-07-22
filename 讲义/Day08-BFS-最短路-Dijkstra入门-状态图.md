# Day 8 教师讲义：BFS、Dijkstra 堆优化入门与状态图

适用班级：已完成 Day1-Day7（工具课、栈、贪心、二分与 ST 表、线性 DP、阶段模拟 1）的学生。

课时定位：图论第一课。三件事：**把图存下来**（邻接表）、**无权最短路 = BFS**（第一次到达就是最短）、**非负带权最短路 = Dijkstra 堆优化**（为 Day19 分层图提前铺路）。"状态图"思想贯穿全天：点不一定是"位置"，可以是任何状态。

配套题单：

| 题号 | 题目 | rating | 本课对应知识点 | 教学目标 |
|---|---|---:|---|---|
| 520B | Two Buttons | 1400 | 数值状态图 BFS | 学会"点=状态，边=操作" |
| 35C | Fire Again | 1500 | 多源 BFS + 文件读写 | 学会多起点一起入队 |
| 1106D | Lunar New Year and a Wander | 1500 | BFS 变形：小根堆贪心 | 学会"队列换堆"改变扩展顺序 |
| 954D | Fight Against Traffic | 1600 | 双向 BFS 预处理 + 枚举 | 学会"从两端各跑一遍" |
| 601A | The Two Routes | 1600 | 补图 BFS | 学会不建补图直接枚举 |
| 1037D | Valid BFS? | 1700 | BFS 序验证 | 学会"按目标顺序逼迫扩展" |
| 选做 20C | Dijkstra? | 1900 | Dijkstra + 路径还原 | 当天模板的直接应用 |

## 0. 课堂安排

上午讲解（180 分钟）：

| 时间 | 内容 | 教师重点 |
|---:|---|---|
| 0-20 分钟 | 图的存储：邻接表 vs 邻接矩阵 | `vector<int> graph[N]`，无向边存两遍 |
| 20-50 分钟 | BFS 模板 + 为什么第一次到达就是最短 | 队列里的距离单调不减 |
| 50-80 分钟 | **Dijkstra 堆优化系统模板（新增）** | 手动模拟 + 三个易错位 |
| 80-100 分钟 | 520B：数值状态图 | 状态上界的估计 |
| 100-125 分钟 | 35C 多源 + 601A 补图 | 多源一起入队；补图不显式建 |
| 125-155 分钟 | 954D：双向 BFS + 枚举加边 | `distS/distT` 分工 |
| 155-180 分钟 | 1037D + 1106D 思路串讲 | 验证类与扩展顺序变形 |

下午训练（210 分钟）：按 §9 顺序完成；选做 20C 供先做完的学生练 Dijkstra。

## 1. BFS：无权图最短路

### 1.1 模板（全篇统一写法）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, m, start;
int dist[N];              // dist[u]：起点到 u 的最少边数，-1 表示没到过
vector<int> graph[N];     // 邻接表

void bfs(int src){
    memset(dist, -1, sizeof dist);
    queue<int> q;
    dist[src] = 0;
    q.push(src);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v : graph[u])
            if(dist[v] == -1){        // 入队即标记：第一次到达就是最短
                dist[v] = dist[u] + 1;
                q.push(v);
            }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> start;
    for(int i = 1; i <= m; i++){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);    // 无向图两个方向都存
        graph[v].push_back(u);
    }
    bfs(start);
    for(int i = 1; i <= n; i++)
        cout << dist[i] << " \n"[i == n];
    return 0;
}
```

### 1.2 为什么第一次到达就是最短

队列中的距离值**单调不减**（先进队的距离 ≤ 后进队的）。若 v 第一次被 u 扩展到，任何以后再到 v 的路径经过的都是距离 ≥ dist[u] 的点，不可能更短。板书一句话：**BFS 按"距离分层"扫描，层内先后无所谓，层间顺序不可乱**。

### 1.3 状态图思想（今天的灵魂）

点不必是"格子/城市"，可以是任何状态：520B 的点是"屏幕上的数"，操作是边。做题三问：状态是什么？操作把状态变成什么？状态空间多大（能不能开数组）？

## 2. Dijkstra 堆优化：非负带权最短路（新增系统课）

### 2.1 从 BFS 到 Dijkstra

边有了权值，BFS 的"层"失效——先出队的不再保证最短。Dijkstra 的对策：**每次取当前距离最小的点定型**（贪心），用小根堆维护。适用条件：**边权非负**（有负权会破坏"取最小即定型"的论证）。

### 2.2 模板（与 BFS 对照着背）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> Node;    // (距离, 点编号)，pair 默认按第一维比较

const int N = 1e5 + 5;
const ll INF = 1e18;          // 用大数表示"还没到达"
int n, m;
ll dist[N];
bool vis[N];                  // vis[u]=true 表示 u 的最短路已确定
vector<pair<int,int>> graph[N];   // graph[u] = {(v, w), ...}

void dijkstra(int start){
    for(int i = 1; i <= n; i++) dist[i] = INF;
    priority_queue<Node, vector<Node>, greater<Node>> heap;   // 小根堆
    dist[start] = 0;
    heap.push({0, start});
    while(!heap.empty()){
        int u = heap.top().second;
        heap.pop();
        if(vis[u]) continue;      // 过期记录：u 早已确定，直接丢弃
        vis[u] = true;
        for(auto [v, w] : graph[u])
            if(dist[u] + w < dist[v]){       // 松弛：经 u 走到 v 更近
                dist[v] = dist[u] + w;
                heap.push({dist[v], v});
            }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});    // 无向图两个方向都存
        graph[v].push_back({u, w});
    }
    dijkstra(1);
    for(int i = 1; i <= n; i++)
        cout << (dist[i] == INF ? -1 : dist[i]) << " \n"[i == n];
    return 0;
}
```

### 2.3 手动模拟（5 点小图）

边：1-2(2)、1-3(5)、2-3(1)、2-4(4)、3-5(3)、4-5(1)。从 1 出发：

| 步骤 | 出堆 | 动作 | dist 快照 [1..5] |
|---:|---|---|---|
| 1 | (0, 1) | 松弛 2、3 | 0, 2, 5, INF, INF |
| 2 | (2, 2) | 松弛 3(2+1=3 更优)、4(6) | 0, 2, 3, 6, INF |
| 3 | (3, 3) | 松弛 5(3+3=6) | 0, 2, 3, 6, 6 |
| 4 | (5, 3) | **过期记录，vis[3] 已 true，丢弃** | 不变 |
| 5 | (6, 4) | 松弛 5(6+1=7 不更优) | 不变 |
| 6 | (6, 5) | 终点定型 | 0, 2, 3, 6, 6 |

第 4 步是理解堆优化的关键：同一个点可能多次入堆，**旧记录靠 `vis` 丢弃**，不是从堆里删。

### 2.4 BFS 与 Dijkstra 对照表（板书）

| | BFS | Dijkstra 堆优化 |
|---|---|---|
| 适用 | 边权全为 1（或全相等） | 边权非负 |
| 容器 | 队列 | 小根堆 |
| 定型时机 | 出队即定型 | 出堆且未 vis 才定型 |
| 复杂度 | O(n + m) | O(m log m) |
| dist 类型 | int | **long long**（路径和会大） |

三个易错位：dist 初值 INF 用 `1e18` 级别（int 的 0x3f 不够）；`if(vis[u]) continue` 不能漏；无向图两个方向都建边。

### 2.5 什么时候用（预告 Day19）

Day19 的分层图最短路 = Dijkstra + "点带状态"（`dist[u][state]`）。今天把一维模板写熟，Day19 只是把 dist 加一维。选做 20C 就是模板 + 路径还原，先做完的学生今天就能消化。

## 3. 520B Two Buttons：数值状态图

### 3.1 题目大意

屏幕显示 n，红键乘 2、蓝键减 1（结果必须为正数）。最少几次按键变成 m。

### 3.2 从暴力到正解

状态 = 屏幕上的数，操作 = 两条出边。关键是**状态上界**：超过 2m 的数只会靠减 1 回来，绝不划算，所以状态开到 2e4 就够。BFS 第一次到 m 即答案。（逆向贪心"从 m 往回走"也可，讲评时提一句即可。）

### 3.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int LIMIT = 20000;    // 状态上界：m <= 1e4，乘 2 超过 2m 一定不划算
int dist[LIMIT + 5];

int main(){
    int start, target;
    cin >> start >> target;

    memset(dist, -1, sizeof dist);   // -1 表示还没到达过
    queue<int> q;
    dist[start] = 0;
    q.push(start);

    while(!q.empty()){
        int cur = q.front();
        q.pop();
        if(cur == target) break;          // 第一次到达 = 最少按键数

        int doubled = cur * 2;            // 红键：乘 2
        int minusOne = cur - 1;           // 蓝键：减 1
        if(doubled <= LIMIT && dist[doubled] == -1){
            dist[doubled] = dist[cur] + 1;
            q.push(doubled);
        }
        if(minusOne >= 1 && dist[minusOne] == -1){   // 数字必须保持正数
            dist[minusOne] = dist[cur] + 1;
            q.push(minusOne);
        }
    }

    cout << dist[target] << '\n';
    return 0;
}
```

### 3.4 赛场策略与易错点

- 状态上界想不清就取宽（2 倍 m 再多一点），先过再说。
- 减 1 的下界是 1（0 和负数非法）。
- 模型卡：**数值操作最少步数 = 状态图 BFS，先估状态上界**。

## 4. 35C Fire Again：多源 BFS + 文件读写

### 4.1 题目大意

rows × cols 的田地，k 个起火点同时烧，火向四邻扩散。求最晚起火的格子（任意一个）。**本题强制文件读写 input.txt/output.txt**。

### 4.2 从暴力到正解

对每个起火点各跑一遍 BFS 取 min 是 `O(k·rc)`；**多源 BFS**：所有起火点距离 0 同时入队，一遍 `O(rc)` 得到每格的最早起火时间——本质是加一个虚拟超级源点。

### 4.3 参考代码（已过官方样例；答案多解，检验方式：输出格子的 dist 等于全场最大值）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2005;
int rows, cols, srcCnt;
int dist[N][N];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int main(){
    freopen("input.txt", "r", stdin);     // 本题强制文件读写，交题别忘了
    freopen("output.txt", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> rows >> cols >> srcCnt;

    memset(dist, -1, sizeof dist);
    queue<pair<int,int>> q;
    for(int i = 1; i <= srcCnt; i++){     // 多源：所有起火点距离 0，一起入队
        int x, y;
        cin >> x >> y;
        dist[x][y] = 0;
        q.push({x, y});
    }

    while(!q.empty()){
        auto [x, y] = q.front();
        q.pop();
        for(int d = 0; d < 4; d++){
            int nx = x + dx[d], ny = y + dy[d];
            if(nx < 1 || nx > rows || ny < 1 || ny > cols) continue;
            if(dist[nx][ny] != -1) continue;
            dist[nx][ny] = dist[x][y] + 1;
            q.push({nx, ny});
        }
    }

    int bestX = 1, bestY = 1;             // 找最晚起火的格子（任意一个即可）
    for(int i = 1; i <= rows; i++)
        for(int j = 1; j <= cols; j++)
            if(dist[i][j] > dist[bestX][bestY]){
                bestX = i;
                bestY = j;
            }
    cout << bestX << ' ' << bestY << '\n';
    return 0;
}
```

### 4.4 赛场策略与易错点

- **文件读写是 CSP 考场规则的预演**：freopen 两行写在 main 最上面，交前检查文件名拼写。
- 多源就是"多个点距离 0 一起入队"，没有更多花样。
- 本题多解——对拍时比较"输出格子的 dist 是否等于最大 dist"，不是比坐标。

## 5. 1106D Lunar New Year and a Wander：队列换堆

### 5.1 题目大意

从 1 号点出发游走（可重复经过），按**首次到达**的顺序记录点编号，要求记录序列字典序最小。

### 5.2 从暴力到正解

BFS 的队列改成**小根堆**：每次从"当前可达的边界点"中取编号最小的定型。正确性：序列字典序最小 ⇔ 每一步都选当前能选的最小编号点，而"可达边界"恰好是堆里的内容——本质是 Prim 式贪心而非最短路。

### 5.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, m;
vector<int> graph[N];
bool vis[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    priority_queue<int, vector<int>, greater<int>> heap;   // 小根堆：可达边界中最小编号
    vis[1] = true;
    heap.push(1);
    vector<int> order;
    while(!heap.empty()){
        int u = heap.top();
        heap.pop();
        order.push_back(u);
        for(int v : graph[u])
            if(!vis[v]){          // 入堆即标记，防止重复入堆
                vis[v] = true;
                heap.push(v);
            }
    }

    for(int i = 0; i < n; i++)
        cout << order[i] << (i + 1 < n ? ' ' : '\n');
    return 0;
}
```

### 5.4 赛场策略与易错点

- 与 Dijkstra 同款容器、不同语义：堆权是**点编号**不是距离，课堂上把两段代码并排放，让学生说出差别。
- 重边自环不影响（vis 挡掉）。
- 模型卡：**扩展顺序有要求 ⇒ 换容器（队列/栈/堆）**。

## 6. 601A The Two Routes：补图 BFS

### 6.1 题目大意

n 个镇，铁路图与公路图互为补图。火车走铁路、汽车走公路，同时从 1 出发去 n，两车不能在中途同镇相遇（1、n 除外）。求两车都到 n 的最早时间（每条边 1 小时），不可达输出 -1。

### 6.2 关键观察

1 和 n 之间必有一条边——铁路或公路。走这条边的车 **1 小时直达**，之后永远待在 n；另一辆车在自己的图上跑 BFS 即可，**相遇约束自动消失**。答案 = `max(1, 另一图的 dist[n])` = 另一图的 dist[n]（≥1）。

### 6.3 补图技巧

公路图边数可达 `O(n²)`，不显式建图：BFS 扩展时**枚举所有点**，用邻接矩阵判"这条边在不在当前图里"。n ≤ 400，`O(n²)` 扩展没问题。

### 6.4 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 405;
int n, m, dist[N];
bool rail[N][N];      // rail[u][v]=true 表示 u、v 之间有铁路

int main(){
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u, v;
        cin >> u >> v;
        rail[u][v] = rail[v][u] = true;
    }

    // 1 和 n 之间必有一条边（铁路或公路），走这条边的车 1 小时直达，
    // 只需给另一辆车在它自己的图上跑 BFS，两车不可能在中途相遇
    bool useRail = !rail[1][n];   // true 表示需要 BFS 的是铁路图

    memset(dist, -1, sizeof dist);
    queue<int> q;
    dist[1] = 0;
    q.push(1);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v = 1; v <= n; v++){      // 补图不显式建边，直接枚举所有点
            if(v == u || dist[v] != -1) continue;
            bool hasEdge = useRail ? rail[u][v] : !rail[u][v];
            if(!hasEdge) continue;
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }

    cout << dist[n] << '\n';    // 不可达时 dist[n] 仍是 -1，直接输出
    return 0;
}
```

### 6.5 赛场策略与易错点

- 先找"让约束消失的结构性观察"（1-n 必有边），再写代码——观察 30 秒省 30 行。
- 补图 BFS 的复杂度是 `O(n²)`，n 大时要用"未访问点集合 + set 删除"技巧（提一句，Day20 后再回看）。

## 7. 954D Fight Against Traffic：双向 BFS 预处理 + 枚举

### 7.1 题目大意

n 点 m 边无向图，给定 s、t。要新修一条边（不能是已有边），且不能使 s 到 t 的最短距离变短。问有多少种修法。

### 7.2 从暴力到正解

- **暴力**：枚举每条候选边，加进去重跑 BFS，`O(n² · (n+m))`——n=1000 会超。
- **正解**：预处理 `distS`（从 s）与 `distT`（从 t）两遍 BFS。新边 (u,v) 不缩短距离 ⇔ 两个方向都不更短：`distS[u]+1+distT[v] ≥ 原最短` 且 `distS[v]+1+distT[u] ≥ 原最短`。枚举点对 `O(n²)` 判定 `O(1)`。
- **模型卡**：**"加一条边对最短路的影响" = 起点树 + 终点树两遍预处理**。

### 7.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1005;
int n, m, src, dst;
bool adj[N][N];
vector<int> graph[N];
int distS[N], distT[N];

void bfs(int start, int dist[]){
    for(int i = 1; i <= n; i++) dist[i] = -1;
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v : graph[u])
            if(dist[v] == -1){
                dist[v] = dist[u] + 1;
                q.push(v);
            }
    }
}

int main(){
    cin >> n >> m >> src >> dst;
    for(int i = 1; i <= m; i++){
        int u, v;
        cin >> u >> v;
        adj[u][v] = adj[v][u] = true;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    bfs(src, distS);              // distS[x]：s 到 x 的最短距离
    bfs(dst, distT);              // distT[x]：t 到 x 的最短距离
    int shortest = distS[dst];

    int ans = 0;
    for(int u = 1; u <= n; u++)
        for(int v = u + 1; v <= n; v++){    // 枚举 u<v 避免无向边重复计数
            if(adj[u][v]) continue;         // 只统计原本没有直接道路的点对
            // 新边两个方向都不能让 s->t 变短
            if(distS[u] + 1 + distT[v] >= shortest &&
               distS[v] + 1 + distT[u] >= shortest)
                ans++;
        }
    cout << ans << '\n';
    return 0;
}
```

### 7.4 易错点

- 两个方向都要判（新边无向）。
- `u < v` 枚举避免重复；已有边跳过；u == v 自环不算。

## 8. 1037D Valid BFS?：验证类问题

### 8.1 题目大意

给一棵树和一个序列，问该序列是否可能是从 1 出发的某次合法 BFS 的访问序。

### 8.2 关键思路

BFS 的自由度只在"同一父亲的孩子扩展顺序"。**把每个点的邻居按目标序列中的位置排序**，再跑一遍标准 BFS：如果这样"顺着目标的意愿"扩展出来的序列都对不上，那就没有任何一种顺序能对上。

### 8.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, seq[N], pos[N];
vector<int> graph[N];
bool vis[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for(int i = 1; i < n; i++){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for(int i = 1; i <= n; i++){
        cin >> seq[i];
        pos[seq[i]] = i;      // 每个点在给定序列中出现的位置
    }

    // 把每个点的邻居按"给定序列中的位置"排序，逼 BFS 按目标顺序扩展
    for(int i = 1; i <= n; i++)
        sort(graph[i].begin(), graph[i].end(), [](int lhs, int rhs){
            return pos[lhs] < pos[rhs];
        });

    vector<int> order;
    queue<int> q;
    vis[1] = true;
    q.push(1);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        order.push_back(u);
        for(int v : graph[u])
            if(!vis[v]){
                vis[v] = true;
                q.push(v);
            }
    }

    for(int i = 1; i <= n; i++)
        if(order[i - 1] != seq[i]){       // 模拟结果与给定序列逐位比较
            cout << "No\n";
            return 0;
        }
    cout << "Yes\n";
    return 0;
}
```

### 8.4 赛场策略与易错点

- 验证类问题的通用心法：**把自由度按目标"钉死"，再模拟一遍比对**。
- 序列第一个必须是 1（比对循环天然覆盖，无需特判）。
- 首行 `Yes/No` 大小写照抄题面。

## 9. 当天训练顺序

| 顺序 | 题目 | rating | 预计用时 | 目标 |
|---:|---|---:|---:|---|
| 1 | 520B Two Buttons | 1400 | 25 min | 状态图入门 |
| 2 | 35C Fire Again | 1500 | 30 min | 多源 + 文件读写 |
| 3 | 1106D Lunar New Year and a Wander | 1500 | 30 min | 队列换堆 |
| 4 | 601A The Two Routes | 1600 | 35 min | 补图观察 |
| 5 | 954D Fight Against Traffic | 1600 | 40 min | 双向 BFS |
| 6 | 1037D Valid BFS? | 1700 | 40 min | 验证类压轴 |
| 选做 | 20C Dijkstra? | 1900 | — | 今日新模板直接应用 |

### 选做 20C 参考代码（已过官方样例；路径多解，检验方式：路径合法且总长等于最短距离）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,int> Node;    // (距离, 点编号)

const int N = 1e5 + 5;
const ll INF = 1e18;
int n, m, pre[N];             // pre[v]：最短路上 v 的前驱，用于还原路径
ll dist[N];
bool vis[N];
vector<pair<int,int>> graph[N];   // graph[u] = {(v, w), ...}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    // 边权最大 1e6、点数 1e5，路径和可达 1e11，必须 long long
    for(int i = 1; i <= n; i++) dist[i] = INF;
    priority_queue<Node, vector<Node>, greater<Node>> heap;
    dist[1] = 0;
    heap.push({0, 1});
    while(!heap.empty()){
        int u = heap.top().second;
        heap.pop();
        if(vis[u]) continue;      // 旧记录：u 的最短路早已确定
        vis[u] = true;
        for(auto [v, w] : graph[u])
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pre[v] = u;       // 记录前驱
                heap.push({dist[v], v});
            }
    }

    if(dist[n] == INF){
        cout << -1 << '\n';
        return 0;
    }
    vector<int> path;
    for(int cur = n; cur != 0; cur = pre[cur])   // 从 n 沿前驱走回 1（pre[1]=0 结束）
        path.push_back(cur);
    reverse(path.begin(), path.end());
    for(int i = 0; i < (int)path.size(); i++)
        cout << path[i] << (i + 1 < (int)path.size() ? ' ' : '\n');
    return 0;
}
```

## 10. 易错点清单

- 无向图建边两个方向；重边自环按题意处理（BFS 天然无碍）。
- `dist` 数组：BFS 用 -1 表示未访问；Dijkstra 用 INF（long long 的 1e18）。
- BFS **入队即标记**；Dijkstra **出堆判 vis**——两者标记时机不同，混用会错。
- 多测/多轮 BFS 记得重置 dist、vis。
- 文件读写题（35C）freopen 忘写 = 0 分，这是 CSP 考场规则的直接预演。
- 网格 BFS 的 dx/dy 与边界判断先写再用。

晚间任务：图的存储、dist 定义、队列边界三张模型卡；把 Dijkstra 模板默写一遍并跑通 20C。
