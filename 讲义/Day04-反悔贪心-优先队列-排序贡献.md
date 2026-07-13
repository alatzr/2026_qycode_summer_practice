# Day 4 教师讲义：反悔贪心、优先队列与排序贡献

适用班级：已完成 Day3（贪心与交换论证）的学生。

课时定位：贪心第二课。核心是把 Day3 的"一次做对"升级为"先做了再说，错了反悔"——**反悔贪心**。工具是优先队列（堆）。同日配套：前缀可达（1490E）、双资源区间贪心（845C）。树上贪心（原 1466D）移至树基础之后，扫描线类（原 1249D2）移至 Day23 正式讲授。

配套题单（按训练顺序）：

| 题号 | 题目 | rating | 本课对应知识点 | 教学目标 |
|---|---|---:|---|---|
| 1490E | Accidental Victory | 1400 | 排序 + 前缀可达 | 学会"吃下前 i 名再挑战下一名" |
| 845C | Two TVs | 1500 | 双资源区间贪心 | 学会维护"先空出来的资源" |
| 1526C1 | Potions (Easy) | 1500 | 反悔贪心模板 | 学会"先喝，变负吐最小" |
| 960B | Minimize the error | 1500 | 堆削峰 | 学会合并两组操作 |
| 1140C | Playlist | 1600 | 排序 + 堆维护前 k 大 | 学会"枚举最小值，堆管其余" |
| 1526C2 | Potions (Hard) | 1600 | 同一模板换数据范围 | 体会 easy→hard 的复杂度视角 |

## 0. 课堂安排

| 时间 | 内容 | 教师重点 |
|---:|---|---|
| 0-15 分钟 | 复盘 Day3：贪心为什么要证明 | 引出"证不出来怎么办 → 反悔" |
| 15-45 分钟 | 优先队列语法 + 反悔贪心思想 | 大根堆/小根堆的三行声明 |
| 45-85 分钟 | 1526C1 精讲（含手动模拟） | 反悔三步：先做、检查、吐出 |
| 85-105 分钟 | 1526C2 对比：n 从 2000 到 2e5 | 同一算法，数据范围只是吓人 |
| 105-135 分钟 | 1140C：排序定最小值 + 堆管前 k | "枚举一维、数据结构管另一维" |
| 135-160 分钟 | 960B 削峰 + 845C 双资源 | 堆顶永远是"最值得动的" |
| 160-180 分钟 | 1490E 前缀可达 + 模型卡总结 | 排序贡献思想 |
| 下午 | 六题训练 + 讲评 | 按题单顺序 |

## 1. 反悔贪心：先做了再说

### 1.1 思想（板书）

```text
普通贪心：每步都要证明"当前选择永远不后悔"。
反悔贪心：允许先选，之后发现不行时，撤销"损失最大的一次选择"。
工具：堆——O(log n) 找到最该撤销的那一个。
```

三步套路：**先做 → 检查约束 → 违约就吐出堆顶**。

### 1.2 优先队列速查

```cpp
priority_queue<long long> maxHeap;                                  // 大根堆
priority_queue<long long, vector<long long>, greater<long long>> minHeap; // 小根堆
```

只有 `push / top / pop / size / empty`，没有遍历——所以只适合"永远只动最值"的贪心。

## 2. 1526C1 Potions (Easy)：反悔贪心模板题

### 2.1 题意与模型

从左到右喝药水（可跳过），每瓶改变生命值 `potion`（可为负），全程生命值不能为负。最多喝几瓶？

**反悔贪心**：每瓶都先喝；生命值变负时，吐掉**已喝中最伤的一瓶**（小根堆堆顶）。

### 2.2 正确性（交换论证一句话）

吐掉已喝中最小（最负）的一瓶，剩余生命值最高、瓶数只少一；任何"少喝别的一瓶"的方案瓶数相同但生命值不会更高，后续可行集不会更大。

### 2.3 手动模拟（药水：4 -4 1 -3 1 -3）

| 步骤 | 喝下 | hp | 堆内（已喝） | 动作 |
|---:|---:|---:|---|---|
| 1 | 4 | 4 | {4} | — |
| 2 | -4 | 0 | {-4, 4} | hp ≥ 0，保留 |
| 3 | 1 | 1 | {-4, 1, 4} | — |
| 4 | -3 | -2 | {-4, -3, 1, 4} | **hp < 0，吐 -4**，hp = 2 |
| 5 | 1 | 3 | {-3, 1, 1, 4} | — |
| 6 | -3 | 0 | {-3, -3, 1, 1, 4} | hp ≥ 0，保留 |

答案 5 瓶——与官方样例一致，堆里此刻恰好是被喝下的 5 瓶。

### 2.4 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // 已喝药水的小根堆：堆顶是最伤生命值的一瓶
    priority_queue<long long, vector<long long>, greater<long long>> chosen;
    long long hp = 0; // 当前生命值 = 已喝药水之和

    for(int i = 1; i <= n; i++){
        long long potion;
        cin >> potion;
        hp += potion;
        chosen.push(potion); // 先喝下去
        if(hp < 0){          // 生命值变负：反悔，吐掉最小的一瓶
            hp -= chosen.top();
            chosen.pop();
        }
    }

    cout << chosen.size() << '\n';
    return 0;
}
```

### 2.5 易错点

- 吐出时 `hp -= top` 是"减去负数"（生命值回升），符号别想反；
- 生命值和会超 int（2e5 × 1e9），long long；
- "先喝再检查"顺序不能换成"先检查再喝"（会漏掉"喝了这瓶反而应该吐别的"的情形）。

## 3. 1526C2 Potions (Hard)：同一模板的压力测试

### 3.1 教学定位

C2 与 C1 唯一区别：n 从 2000 升到 2e5。C1 允许 `O(n²)` DP；C2 逼你用 `O(n log n)` 的反悔贪心——**同一份代码直接过两题**。

课堂话术：CSP 的"数据范围分档"就是这个结构。先问自己"我的做法在大档还活着吗"，活着就不用换算法。

### 3.2 参考代码（与 C1 相同，已分别过两题官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // 已喝药水的小根堆：堆顶是最伤生命值的一瓶
    priority_queue<long long, vector<long long>, greater<long long>> chosen;
    long long hp = 0; // 当前生命值 = 已喝药水之和

    for(int i = 1; i <= n; i++){
        long long potion;
        cin >> potion;
        hp += potion;
        chosen.push(potion); // 先喝下去
        if(hp < 0){          // 生命值变负：反悔，吐掉最小的一瓶
            hp -= chosen.top();
            chosen.pop();
        }
    }

    cout << chosen.size() << '\n';
    return 0;
}
```

### 3.3 对比表（板书）

| | C1 | C2 |
|---|---|---|
| n | ≤ 2000 | ≤ 2e5 |
| 可行做法 | `O(n²)` DP / 反悔贪心 | 只剩反悔贪心 |
| 结论 | 学反悔贪心，一次吃两题 | |

## 4. 1140C Playlist：枚举最小值 + 堆管前 k

### 4.1 题意与模型

每首歌有时长 `len` 与美观度 `beauty`，选至多 k 首，得分 = 时长和 × 美观度最小值。最大化得分。

**套路**：按美观度**降序**扫描；扫到第 i 首时强制它是"最小美观度"，则前面所有歌美观度都 ≥ 它，随便选——用小根堆维护"时长最大的至多 k 首"的时长和。

### 4.2 四段式

- **暴力**：枚举选集 `O(2^n)`；或枚举最小值后排序取前 k 长 `O(n² log n)`——n 3e5 不可行。
- **正解**：排序 `O(n log n)` + 每首进堆一次出堆至多一次，总 `O(n log n)`。
- **赛场策略**："积 × 最小值"型目标 ⇒ 第一反应就是"枚举最小值那一维，另一维交给数据结构"。
- **易错**：`lenSum × beauty` 溢出（双 1e9 级，long long）；堆超员再弹（先 push 后判 size）；美观度相同的歌不需要特殊处理（都 ≥ 当前值）。

### 4.3 手动模拟（k=2，歌 {时长,美观}：{4,7} {15,1} {3,6} {6,8}）

按美观降序：{6,8} {4,7} {3,6} {15,1}。

| 扫到 | 堆（时长） | lenSum | 得分 = lenSum×beauty |
|---|---|---:|---:|
| {6,8} | {6} | 6 | 48 |
| {4,7} | {4,6} | 10 | 70 |
| {3,6} | {4,6}（3 进堆即弹出） | 10 | 60 |
| {15,1} | {6,15} | 21 | 21 |

答案是 70。第 3 行中，长度 3 入堆后立刻被弹出，因此时长和仍为 10；这正是“堆超员时撤销最短歌曲”的作用。

### 4.4 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<pair<long long, long long>> songs(n); // {美观度, 时长}
    for(int i = 0; i < n; i++){
        long long len, beauty;
        cin >> len >> beauty;
        songs[i] = {beauty, len};
    }
    // 按美观度从大到小排：扫到第 i 首时，它的美观度就是当前集合的最小值
    sort(songs.begin(), songs.end(), greater<pair<long long, long long>>());

    // 已选歌曲时长的小根堆：超员时反悔，扔掉最短的
    priority_queue<long long, vector<long long>, greater<long long>> lenHeap;
    long long lenSum = 0, ans = 0;

    for(auto &[beauty, len] : songs){
        lenHeap.push(len); // 先把当前歌选进来
        lenSum += len;
        if((int)lenHeap.size() > k){ // 超过 k 首：删时长最短的一首
            lenSum -= lenHeap.top();
            lenHeap.pop();
        }
        ans = max(ans, lenSum * beauty);
    }

    cout << ans << '\n';
    return 0;
}
```

## 5. 960B Minimize the error：堆削峰

### 5.1 题意与模型

两个数组，必须在 arr1 上恰好操作 k1 次、arr2 上恰好 k2 次（每次给某元素 ±1），最小化 `Σ(arr1[i]-arr2[i])²`。

**转化**：对 arr1 加 1 与对 arr2 减 1 对差值 `|arr1[i]-arr2[i]|` 完全等价 ⇒ 合并成 `ops = k1+k2` 次"把某个差值 ±1"。每次贪心削**最大的差值**（大根堆）；全为 0 还剩操作时，只能把一个 0 变 1。

### 5.2 正确性

平方函数的边际收益递增：把 d 削成 d-1 减少 `2d-1`，d 越大收益越大 ⇒ 每次动最大差值最优（交换论证：把一次"削小的"换成"削大的"总误差不增）。

### 5.3 参考代码（已过官方样例；样例含"操作数用不完"与"恰好用完"两侧）

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k1, k2;
    cin >> n >> k1 >> k2;

    vector<long long> arr1(n), arr2(n);
    for(auto &x : arr1) cin >> x;
    for(auto &x : arr2) cin >> x;

    // 大根堆：堆顶是当前最大的差值
    priority_queue<long long> diffHeap;
    for(int i = 0; i < n; i++) diffHeap.push(llabs(arr1[i] - arr2[i]));

    int ops = k1 + k2; // 两个数组上的操作对差值完全等价，合并使用
    while(ops--){
        long long top = diffHeap.top();
        diffHeap.pop();
        if(top > 0) top--; // 把最大差值削 1
        else top = 1;      // 差值全为 0 仍必须操作，只能造出一个 1
        diffHeap.push(top);
    }

    long long error = 0;
    while(!diffHeap.empty()){
        error += diffHeap.top() * diffHeap.top(); // 平方和会爆 int，用 long long
        diffHeap.pop();
    }
    cout << error << '\n';
    return 0;
}
```

### 5.4 易错点

- 操作**必须恰好用完**（全 0 时被迫制造 1）；
- 平方和 `1e4 × (2e4)²` 级别，long long；
- "两组操作等价"这步转化不写就会做成二维问题。

## 6. 845C Two TVs：双资源区间贪心

### 6.1 题意与模型

n 个节目 `[start, finish]`，两台电视，同一台上节目不能重叠（**端点相同也算冲突**）。能否全部看完？

**贪心**：按开始时间排序；每个节目优先放到"先空出来的那台"（维护 `endEarly ≤ endLate`）。若先空的都放不下，则两台都放不下 ⇒ NO。

### 6.2 正确性与延伸

放到先空的一台，留下的"较晚空档"最宽松（交换论证）。延伸一句：电视数不定时就是经典"最少会议室"问题（小根堆管所有结束时间）——Day23 扫描线还会回来。

### 6.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<pair<int, int>> shows(n); // {开始时刻, 结束时刻}
    for(auto &show : shows) cin >> show.first >> show.second;
    sort(shows.begin(), shows.end()); // 按开始时刻升序

    // 两台电视各自的结束时刻，始终保持 endEarly <= endLate
    long long endEarly = -1, endLate = -1;
    bool ok = true;
    for(auto &[start, finish] : shows){
        if(start > endEarly){ // 只需和先空出来的电视比较；端点相同不能接
            endEarly = finish;
            if(endEarly > endLate) swap(endEarly, endLate);
        }else{ // 两台电视都还没结束，第三个节目冲突
            ok = false;
            break;
        }
    }
    cout << (ok ? "YES" : "NO") << '\n';
    return 0;
}
```

### 6.4 易错点

- `start > endEarly` 是严格大于（端点相同不能同台）；
- 更新后要重新维持 `endEarly ≤ endLate`（swap）；
- 排序键是开始时间，不是结束时间（与"最多活动数"问题区分——今天板书画对比表）。

## 7. 1490E Accidental Victory：排序 + 前缀可达

### 7.1 题意与模型

n 名选手各有代币数，每轮任意两人比，多者胜（平局任意）并**吞下**败者全部代币。问哪些选手有可能夺冠（升序输出编号）。

**结论**：按代币升序排序后，选手 i 可能夺冠 ⇔ 前 i 名代币总和 ≥ 第 i+1 名，且这个条件一路传递到第 n 名。从右往左找"断档"位置：`prefix[i] < tokens[i+1]` 处断开，断点右侧全体可夺冠。

### 7.2 四段式

- **暴力**：对每人模拟"先吞小的再挑战大的"，`O(n²)`——多测总和限制下会超。
- **正解**：排序 + 前缀和 + 从右往左一遍扫，`O(n log n)`。
- **赛场策略**："能不能赢"= 最优策略下模拟 ⇒ 最优策略显然是"从小吃到大"，这一步要在草稿上写出来再编码。
- **易错**：前缀和 long long；答案按**原始编号**升序（排序时带编号）；断档判断是 `≥`（平局可胜）。

### 7.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n;
    cin >> n;
    vector<long long> tokens(n + 1);
    vector<int> order(n + 1);
    for(int i = 1; i <= n; i++){
        cin >> tokens[i];
        order[i] = i;
    }
    // 按代币数从小到大排序，order 里存原编号
    sort(order.begin() + 1, order.end(), [&](int lhs, int rhs){
        return tokens[lhs] < tokens[rhs];
    });

    vector<long long> prefix(n + 1, 0); // 排序后前 i 名的代币总和
    for(int i = 1; i <= n; i++) prefix[i] = prefix[i - 1] + tokens[order[i]];

    // pos：排序后最靠左的能夺冠位置
    int pos = n;
    for(int i = n - 1; i >= 1; i--){
        if(prefix[i] >= tokens[order[i + 1]]) pos = i; // 吃下前 i 名后能打赢第 i+1 名
        else break; // 断档：再往左都跨不过这里
    }

    vector<int> winners(order.begin() + pos, order.begin() + n + 1);
    sort(winners.begin(), winners.end()); // 按原编号升序输出
    cout << winners.size() << '\n';
    for(int i = 0; i < (int)winners.size(); i++)
        cout << winners[i] << (i + 1 == (int)winners.size() ? '\n' : ' ');
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--) solve();
    return 0;
}
```

## 8. 训练顺序与预计用时

| 顺序 | 题目 | rating | 预计用时 |
|---:|---|---:|---:|
| 1 | 1490E Accidental Victory | 1400 | 25 min |
| 2 | 845C Two TVs | 1500 | 25 min |
| 3 | 1526C1 Potions (Easy) | 1500 | 30 min |
| 4 | 960B Minimize the error | 1500 | 30 min |
| 5 | 1140C Playlist | 1600 | 35 min |
| 6 | 1526C2 Potions (Hard) | 1600 | 10 min（若 C1 用反悔贪心则直接提交） |

## 9. 易错点清单与模型卡

- 反悔贪心三步：先做 → 检查 → 吐堆顶；吐的是"损失最大"的那个。
- 堆里放什么，想清楚"我反悔时想撤销的是什么量"。
- "积 × 最小值"目标 ⇒ 枚举最小值那一维。
- 双资源分配 ⇒ 永远和"先空出来的"比较。
- 今天四张模型卡：反悔堆（1526C1/C2）、枚举最小值 + 堆（1140C）、削峰堆（960B）、前缀可达（1490E）。
- 晚间任务：J 组 90 分钟满分速度训练 2 题（从 Day26 卷型抽样）。
