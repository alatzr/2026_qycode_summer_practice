# Day 3 教师讲义：贪心证明、排序与交换论证

适用班级：已完成 Day1（工具/前缀和）、Day2（栈/括号）的学生。

课时定位：贪心第一课。重点不是"猜到贪心策略"，而是**会证明**：交换论证、反例构造、按某个键排序后局部最优即全局最优。1760F 会用到"答案单调 + 简单判定"的思想，但**二分答案的系统课在 Day5**，本课只把它当"从大到小找可行值"来处理。

配套题单：

| 题号 | 题目 | rating | 本课对应知识点 | 教学目标 |
|---|---|---:|---|---|
| 135A | Replacement | 1300 | 排序 + 极值替换 | 学会最简单的"改一个最优" |
| 246B | Increase and Decrease | 1300 | 不变量（总和） | 学会"操作保持什么不变" |
| 1285B | Just Eat It! | 1300 | 前后缀和判定 | 学会"去掉前后缀比较" |
| 1203E | Boxers | 1500 | 排序 + 贪心占位 | 学会"排序后取最小可用" |
| 1296D | Fight with Monsters | 1500 | 代价排序贪心 | 学会"算代价再排序取小" |
| 1760F | Quests | 1500 | 单调 + 判定 | 学会"从大到小找最大可行 k" |

## 0. 课堂安排

上午讲解（180 分钟）：

| 时间 | 内容 | 教师重点 |
|---:|---|---|
| 0-20 分钟 | 贪心为什么对：交换论证框架 | "把最优解逐步调成贪心解，答案不变差" |
| 20-40 分钟 | 135A 极值替换 | 排序 + 换最大 |
| 40-60 分钟 | 246B 不变量 | 操作保持总和 |
| 60-90 分钟 | 1285B 前后缀和 | 去前缀/后缀比较 |
| 90-120 分钟 | 1203E 排序占位 | 取最小可用重量 |
| 120-150 分钟 | 1296D 代价排序 | 算跳过次数再贪心 |
| 150-180 分钟 | 1760F 单调判定 | 二分找最大 k（系统二分在 Day5） |

下午训练（210 分钟）：按 §7 顺序完成。

## 1. 贪心为什么对：交换论证

贪心的正确性靠**交换论证**：假设存在一个最优解与贪心解不同，找到第一个不同的决策，证明把最优解在该处"换成贪心的选择"后答案不变差 ⇒ 贪心解也最优。今天每道题都要求学生说出"为什么这样贪不会错"。

## 2. 135A Replacement：排序 + 极值替换

### 2.1 题型定位

给数组，把**最大元素替换为最小可能值 1**，输出排序后的数组。最简单的"改一处最优"。

### 2.2 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    scanf("%d", &n);
    vector<int> a(n);
    int mxPos = 0;
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
        if(a[i] > a[mxPos]) mxPos = i;
    }
    a[mxPos] = 1;                       // 最大元素替换为 1（最小可能值）
    sort(a.begin(), a.end());
    for(int i = 0; i < n; i++) printf("%d%c", a[i], i + 1 == n ? '\n' : ' ');
    return 0;
}
```

### 2.3 易错点

- 只替换**一个**最大元素（有重复时任一个）。
- 输出要排序（非降序）。

## 3. 246B Increase and Decrease：不变量

### 3.1 题型定位

每次操作对两个元素一个 +1 一个 -1（总和不变）。求最多能让多少个元素相等。**关键不变量：总和**。

### 3.2 结论与证明

操作保持总和 `sum` 不变。若 `sum % n == 0`，可全部变成 `sum/n`（n 个相等）；否则最多 `n-1` 个（余数那一个凑不齐）。

### 3.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    scanf("%d", &n);
    long long sum = 0;
    for(int i = 0; i < n; i++){
        long long x;
        scanf("%lld", &x);
        sum += x;
    }
    // 操作保持总和不变；能全相等当且仅当 sum 能被 n 整除
    printf("%d\n", sum % n == 0 ? n : n - 1);
    return 0;
}
```

### 3.4 易错点

- 找准不变量（总和）是这类"操作题"的通用第一步。
- sum 可能为负/大，用 long long。

## 4. 1285B Just Eat It!：前后缀和判定

### 4.1 题型定位

Yasser 吃全部（和 S）；Adhband 挑一个**真子段**（非整段）。问是否 S 严格大于所有真子段和。前后缀和判定。

### 4.2 关键推导（板书）

存在真子段和 ≥ S ⟺ 去掉某非空前缀或后缀后剩余 ≥ S ⟺ 存在**非空前缀和 ≤ 0** 或**非空后缀和 ≤ 0**。任一成立则输出 NO。

### 4.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve(){
    int n;
    scanf("%d", &n);
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
    // 存在真子段和 >= 全段和，等价于去掉某非空前缀或后缀后剩余 >= 全段
    // 即某个非空前缀和 <= 0，或某个非空后缀和 <= 0，则 Yasser 不开心
    ll pre = 0;
    bool bad = false;
    for(int i = 1; i <= n - 1; i++){ pre += a[i]; if(pre <= 0) bad = true; }  // 去掉的前缀
    ll suf = 0;
    for(int i = n; i >= 2; i--){ suf += a[i]; if(suf <= 0) bad = true; }      // 去掉的后缀
    printf("%s\n", bad ? "NO" : "YES");
}
int main(){
    int t;
    scanf("%d", &t);
    while(t--) solve();
    return 0;
}
```

### 4.4 手动模拟

- `[1,2,3,4]`：前缀 1,3,6 全 >0；后缀 9,7,4 全 >0 ⇒ YES。
- `[5,-5,5]`：前缀 5,0 出现 ≤0 ⇒ NO（子段 `[3,3]`=5 ≥ 全段 5）。

### 4.5 易错点

- 前缀只到 `n-1`、后缀只到 2（都是"真"子段，去掉的部分非空）。
- long long。

## 5. 1203E Boxers：排序 + 贪心占位

### 5.1 题型定位

每个拳手重量可 -1/不变/+1，要求最终重量**互不相同且 ≥1**，最大化保留人数。**排序后从小到大取最小可用重量**。

### 5.2 交换论证

按重量升序处理，每人取 `max(w-1, last+1)`（不小于已占用的下一个、且在 [w-1,w+1] 内）。为何最优：给靠前的人尽量占小重量，给后面留最大空间——若某最优解让前面的人占了更大重量，把它换小不会让后面变差。

### 5.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    scanf("%d", &n);
    vector<int> weight(n);
    for(int i = 0; i < n; i++) scanf("%d", &weight[i]);
    sort(weight.begin(), weight.end());
    int last = 0, cnt = 0;              // last：上一个已占用的最终重量
    for(int i = 0; i < n; i++){
        int cand = max(weight[i] - 1, last + 1);   // 尽量取最小的可用重量
        if(cand <= weight[i] + 1){                 // 落在 [w-1,w+1] 内才合法
            last = cand;
            cnt++;
        }
    }
    printf("%d\n", cnt);
    return 0;
}
```

### 5.4 易错点

- 重量 ≥1（`last` 初值 0 保证 `last+1 ≥1`）。
- 排序是贪心成立的前提。

## 6. 1296D Fight with Monsters：代价排序贪心

### 6.1 题型定位

你打 a、怪打 b、有 k 次跳过怪的机会。对每只怪算"抢到最后一击需要的跳过次数"，**排序后从小到大用 k**。输入格式 `n a b k`。

### 6.2 关键推导

每 `a+b` 为一轮（你先手）。最后一轮剩余 `rem = ((h-1) % (a+b)) + 1`。你需要 `ceil(rem/a)` 次你的攻击才能打完，其中第一次是白给的，其余 `ceil(rem/a)-1` 次需跳过怪。按跳过次数升序，能用 k 覆盖多少只就抢多少只。

### 6.3 手动模拟（a=2,b=3,k=3，h=[7,10,50,12,1,8]）

跳过次数：`[0,2,2,0,0,1]` → 排序 `[0,0,0,1,2,2]` → 累计 0,0,0,1,3（≤3），第 6 只需再 +2=5>3 停 ⇒ 抢 5 只。

### 6.4 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n, a, b, k;
    scanf("%lld %lld %lld %lld", &n, &a, &b, &k);
    vector<long long> need;             // 每只怪需要的跳过次数
    for(int i = 0; i < n; i++){
        long long h;
        scanf("%lld", &h);
        long long rem = ((h - 1) % (a + b)) + 1;    // 最后一轮剩余血量
        long long skip = (rem + a - 1) / a - 1;     // 需要跳过对手的次数
        need.push_back(skip);
    }
    sort(need.begin(), need.end());
    int cnt = 0;
    for(long long s : need){
        if(k >= s){ k -= s; cnt++; }    // 跳过次数够就抢这只怪的最后一击
        else break;
    }
    printf("%d\n", cnt);
    return 0;
}
```

### 6.5 易错点

- 输入顺序 `n a b k`。
- `rem` 用 `((h-1)%(a+b))+1` 避免整除时算成 0。
- long long（h 可达 1e9，跳过次数累计大）。

## 7. 1760F Quests：单调 + 判定（二分入口）

### 7.1 题型定位

n 个任务，做任务 i 得 `a_i` 金币，同一任务做完后 k 天内不能再做。给 c、d，求**最大的冷却 k**，使 d 天内能挣到 ≥ c 金币；不可能输出 `Impossible`，k 可任意大输出 `Infinity`。输入格式 `n c d`。

### 7.2 关键推导

固定 k：周期为 `k+1` 天，一个周期里可轮转做**前 min(k+1, n) 大**的任务各一次。d 天的金币 = `(d/(k+1)) * pref[usable] + pref[min(d%(k+1), n)]`（pref 是降序前缀和）。

- **Infinity**：只用不同任务（永不重复）就够 c，即 `pref[min(n,d)] ≥ c` ⇒ k 可无限大。
- **Impossible**：连 k=0（每天做最大任务）都不够，即 `coins(0) < c`。
- 否则 `coins(k)` 关于 k **单调不增**，二分最大可行 k。

### 7.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll c, d;
vector<ll> pref;                        // 降序前缀和
// 冷却为 k 时 d 天最多金币：周期 k+1 天，用前 min(k+1,n) 大的任务轮转
ll coins(ll k){
    ll cyc = k + 1;
    ll usable = min(cyc, (ll)n);
    ll full = d / cyc;
    ll rem = d % cyc;
    return full * pref[usable] + pref[min(rem, (ll)n)];
}
void solve(){
    scanf("%d %lld %lld", &n, &c, &d);
    vector<ll> a(n);
    for(auto &x : a) scanf("%lld", &x);
    sort(a.rbegin(), a.rend());
    pref.assign(n + 1, 0);
    for(int i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];
    // 只用不同任务（永不重复）就够 c：k 可任意大
    if(pref[min((ll)n, d)] >= c){ printf("Infinity\n"); return; }
    // 连 k=0（每天打最大任务）都不够：无解
    if(coins(0) < c){ printf("Impossible\n"); return; }
    ll lo = 0, hi = d, ans = 0;         // coins(k) 关于 k 单调不增，二分最大可行 k
    while(lo <= hi){
        ll mid = (lo + hi) / 2;
        if(coins(mid) >= c){ ans = mid; lo = mid + 1; }
        else hi = mid - 1;
    }
    printf("%lld\n", ans);
}
int main(){
    int t;
    scanf("%d", &t);
    while(t--) solve();
    return 0;
}
```

### 7.4 赛场策略与易错点

- 输入顺序 `n c d`；金币和 c 到 1e16 ⇒ 全程 long long。
- Infinity/Impossible 大小写照抄题面。
- 本题的"二分最大可行 k"是二分答案的雏形——**系统的二分答案在 Day5**，这里先建立"答案单调 → 二分"的直觉。

## 8. 当天训练顺序

| 顺序 | 题目 | rating | 预计用时 | 目标 |
|---:|---|---:|---:|---|
| 1 | 135A Replacement | 1300 | 15 min | 极值替换 |
| 2 | 246B Increase and Decrease | 1300 | 20 min | 不变量 |
| 3 | 1285B Just Eat It! | 1300 | 30 min | 前后缀和判定 |
| 4 | 1203E Boxers | 1500 | 30 min | 排序占位 |
| 5 | 1296D Fight with Monsters | 1500 | 35 min | 代价排序 |
| 6 | 1760F Quests | 1500 | 40 min | 单调判定 |

## 9. 易错点清单

- 每道贪心题都要能口述交换论证。
- 找不变量（246B 总和）。
- 前后缀真子段边界（1285B 到 n-1 / 从 2）。
- 排序是贪心成立前提（1203E/1296D）。
- long long：和、血量、金币。
- 1760F 输入顺序 `n c d`，Infinity/Impossible 大小写。

晚间任务：写一份贪心证明模板（交换论证四步）；把 1285B 的"前后缀判定"和 1760F 的"单调二分 k"各写成 4 行卡片。
