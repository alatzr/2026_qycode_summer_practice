# Day 6 教师讲义：线性 DP、状态定义、游戏 DP 与数位 DP 入口

适用班级：已完成 Day1-Day5（工具、栈、贪心、反悔贪心、二分与 ST 表）的学生。

课时定位：DP 第一课。核心是**状态定义的四问**（状态是什么、怎么转移、初值、答案在哪），从最简单的线性 DP 一路带到数位 DP 入口。数位 DP（1036C）作为"识读级"目标——会套模板即可，不要求第一遍手写。

配套题单：

| 题号    | 题目                             | rating | 本课对应知识点      | 教学目标            |
| ----- | ------------------------------ | -----: | ------------ | --------------- |
| 698A  | Vacations                      |   1400 | 多状态线性 DP     | 学会"当前状态 + 昨天约束" |
| 489C  | Given Length and Sum of Digits |   1400 | 贪心构造（DP 课热身） | 学会最大/最小数构造      |
| 1881E | Block Sequence                 |   1500 | 后缀线性 DP      | 学会"从后往前删/留"     |
| 766C  | Mahmoud and a Message          |   1700 | 分段 DP 三问     | 学会一次 DP 求三个量    |
| 1033C | Permutation Game               |   1600 | 博弈 DP（必胜态）   | 学会"存在必败后继则必胜"   |
| 1036C | Classy Numbers                 |   1900 | 数位 DP 入口     | 学会记忆化数位模板       |

## 0. 课堂安排

上午讲解（180 分钟）：

| 时间 | 内容 | 教师重点 |
|---:|---|---|
| 0-20 分钟 | DP 四问框架 | 状态/转移/初值/答案 |
| 20-45 分钟 | 698A 多状态线性 DP | "昨天不能同项目" |
| 45-65 分钟 | 489C 构造热身 | 最大数贪心 + 最小数首位处理 |
| 65-90 分钟 | 1881E 后缀 DP | 删/留两决策 |
| 90-120 分钟 | 766C 一次 DP 求三量 | 方案数/最少段/最长段 |
| 120-145 分钟 | 1033C 博弈 DP | 必胜/必败态 |
| 145-180 分钟 | 1036C 数位 DP 入口 | 记忆化模板识读 |

下午训练（210 分钟）：按 §8 顺序，1036C 允许只交"识读级"实现。

## 1. DP 四问框架（本课的根）

每道 DP 题动手前先回答四问：

```text
1) 状态 dp[...] 表示什么？（一句话，含边界含义）
2) 转移方程？（从哪些更小的状态推来）
3) 初值？（dp[0] / 边界）
4) 答案在哪个状态？
```

板书要求：学生每道题先写这四行再写代码，交卷时一并上交。

## 2. 698A Vacations：多状态线性 DP

### 2.1 题型定位

n 天，每天可能开放"比赛/健身/都开/都关"，同一项目不能连续两天做，求最少休息天数。**状态含"今天做什么"**。

### 2.2 四问

| 四问 | 回答 |
|---|---|
| 状态 | `dp[i][0/1/2]`：第 i 天 休息/比赛/健身 时前 i 天最少休息数 |
| 转移 | 休息 = 昨天三态最小 +1；比赛 = 昨天(休息/健身)最小；健身对称 |
| 初值 | `dp[0]={0,0,0}` |
| 答案 | `min(dp[n][0..2])` |

### 2.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> act(n + 1);      // 每天开放情况：0 全关 1 只有比赛 2 只有健身 3 都开
    for(int i = 1; i <= n; i++) cin >> act[i];

    // dp[i][0/1/2]：第 i 天休息/比赛/健身时，前 i 天最少休息天数
    vector<array<int, 3>> dp(n + 1, {INF, INF, INF});
    dp[0] = {0, 0, 0};

    for(int i = 1; i <= n; i++){
        dp[i][0] = min({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]}) + 1; // 今天休息
        if(act[i] == 1 || act[i] == 3)
            dp[i][1] = min(dp[i - 1][0], dp[i - 1][2]);  // 今天比赛，昨天不能比赛
        if(act[i] == 2 || act[i] == 3)
            dp[i][2] = min(dp[i - 1][0], dp[i - 1][1]);  // 今天健身，昨天不能健身
    }

    cout << min({dp[n][0], dp[n][1], dp[n][2]}) << '\n';
    return 0;
}
```

### 2.4 易错点

- 休息永远可行（三态取最小 +1）；比赛/健身受当天开放与昨天约束限制。
- INF 不参与非法转移（当天不开放该项目就保持 INF）。

## 3. 489C Given Length and Sum of Digits：构造热身

### 3.1 题型定位

给位数 len 与数位和 sum，求满足的最小数与最大数（或 -1 -1）。贪心构造，放 DP 课热身"状态即位置"的思维。

### 3.2 关键设计

- **无解**：`sum > 9*len`，或 `sum==0 且 len>1`（首位不能 0）。
- **最大数**：从高位尽量放 9。
- **最小数**：首位先放 1（无前导零），剩余和从最低位往回尽量放 9。

### 3.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int len, sum;
    cin >> len >> sum;

    // 无解：数位和超过 9*len；或和为 0 但位数超过 1（首位不能为 0）
    if(sum > 9 * len || (sum == 0 && len > 1)){
        cout << "-1 -1\n";
        return 0;
    }
    if(sum == 0){                // 此时必有 len==1，唯一答案是 0
        cout << "0 0\n";
        return 0;
    }

    // 最大数：从最高位开始尽量放 9
    string mx(len, '0');
    int rest = sum;
    for(int i = 0; i < len; i++){
        int digit = min(9, rest);
        mx[i] = char('0' + digit);
        rest -= digit;
    }

    // 最小数：首位先放 1 保证无前导零，剩余的和从最低位往回尽量放 9
    string mn(len, '0');
    mn[0] = '1';
    rest = sum - 1;
    for(int i = len - 1; i >= 0 && rest > 0; i--){
        int add = min(9 - (mn[i] - '0'), rest);
        mn[i] = char(mn[i] + add);
        rest -= add;
    }

    cout << mn << ' ' << mx << '\n';
    return 0;
}
```

### 3.4 易错点

- 两个无解条件都要判；`sum==0 && len==1` 输出 `0 0`。
- 最小数首位占 1，剩余从低位补，别忘 `rest = sum - 1`。

## 4. 1881E Block Sequence：后缀线性 DP

### 4.1 题型定位

数组"合法"当且仅当能划成若干块，每块首元素 = 块内后续元素个数。求最少删除数使之合法。**从后往前的后缀 DP**。

### 4.2 四问

| 四问 | 回答 |
|---|---|
| 状态 | `f[i]`：把 `i..n` 整理合法的最少删除数 |
| 转移 | 删当前：`f[i+1]+1`；保留整块（长 val[i]+1）：`f[i+val[i]+1]` |
| 初值 | `f[n+1]=0` |
| 答案 | `f[1]` |

### 4.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
int n, val[N], f[N];

void solve(){
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> val[i];

    // f[i]：把 i..n 整理成合法块序列的最少删除数，从后往前推
    f[n + 1] = 0;
    for(int i = n; i >= 1; i--){
        f[i] = f[i + 1] + 1;                     // 决策一：删掉当前元素
        if(i + val[i] <= n)                      // 决策二：保留以 val[i] 为块长的整块
            f[i] = min(f[i], f[i + val[i] + 1]);
    }
    cout << f[1] << '\n';
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

### 4.4 易错点

- 块长 = `val[i] + 1`（首元素 + val[i] 个后续），转移到 `f[i+val[i]+1]`。
- 后缀 DP 边界 `f[n+1]=0`；多测数组用到 n+1。

## 5. 766C Mahmoud and a Message：一次 DP 求三个量

### 5.1 题型定位

每个字母有"所在段最大长度"限制，把串分段。同时求：**方案数、最少段数、最长段长**。一次 DP 求三个量。

### 5.2 关键设计

`ways[i]/minCnt[i]` 分别是前 i 个字符的分割方案数、最少段数；枚举最后一段 `[j,i]`，段长受段内所有字母限制 `lim` 约束。最长段 `bestLen` 因单字符段永远合法而必可出现在某完整方案里。

### 5.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int INF = 1e9;
const int N = 1010;

long long ways[N];   // ways[i]：前 i 个字符的分割方案数
int minCnt[N];       // minCnt[i]：前 i 个字符最少分成几段
int limitOf[26];     // 每个字母允许所在段的最大长度

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;
    s = ' ' + s;                      // 转成 1 下标
    for(int i = 0; i < 26; i++) cin >> limitOf[i];

    ways[0] = 1;
    minCnt[0] = 0;
    int bestLen = 0;

    for(int i = 1; i <= n; i++){
        ways[i] = 0;
        minCnt[i] = INF;
        int lim = INF;

        for(int j = i; j >= 1; j--){              // 枚举最后一段 [j, i]
            lim = min(lim, limitOf[s[j] - 'a']);  // 段内每个字母都限制段长
            int len = i - j + 1;
            if(len > lim) break;                  // 再往左扩只会更长，直接停

            ways[i] = (ways[i] + ways[j - 1]) % MOD;
            minCnt[i] = min(minCnt[i], minCnt[j - 1] + 1);
            bestLen = max(bestLen, len);          // 单字符段永远合法，该段必能拼进某个完整方案
        }
    }

    cout << ways[n] << '\n' << bestLen << '\n' << minCnt[n] << '\n';
    return 0;
}
```

### 5.4 易错点

- 三个答案输出顺序：方案数、最长段、最少段（照题面）。
- 段长限制 `lim` 是段内**所有**字母限制的最小值，随左扩递减。
- 方案数取模，最少段用 INF 初值。

## 6. 1033C Permutation Game：博弈 DP（必胜态）

### 6.1 题型定位

排列上博弈：从某位置只能跳到**数值更大**的位置（步长为当前位置数值的倍数）。判每个起点先手是否必胜。**博弈 DP：存在必败后继则当前必胜**。

### 6.2 关键设计

按数值从大到小处理（后继状态先算好）。`win[cur]` = 存在一个可达且必败（`!win[nxt]`）的后继。数值最大的位置无处可跳 ⇒ 必败。

### 6.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, perm[N], posOf[N];
bool win[N];   // win[i]：轮到走的人面对位置 i 是否必胜

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i = 1; i <= n; i++){
        cin >> perm[i];
        posOf[perm[i]] = i;
    }

    // 只能跳向数值更大的位置，按数值从大到小处理，后继状态一定已算好
    for(int val = n; val >= 1; val--){
        int cur = posOf[val];
        win[cur] = false;
        for(int nxt = cur + val; nxt <= n && !win[cur]; nxt += val)
            if(perm[nxt] > val && !win[nxt]) win[cur] = true;  // 存在必败后继则必胜
        for(int nxt = cur - val; nxt >= 1 && !win[cur]; nxt -= val)
            if(perm[nxt] > val && !win[nxt]) win[cur] = true;
    }

    string result(n, 'B');
    for(int i = 1; i <= n; i++)
        if(win[i]) result[i - 1] = 'A';
    cout << result << '\n';
    return 0;
}
```

### 6.4 易错点

- 处理顺序必须保证"后继先算"（按数值降序）。
- 博弈基本判定：**存在必败后继 ⇒ 必胜；所有后继必胜 ⇒ 必败**。
- 跳的目标要求 `perm[nxt] > val`（数值更大）。

## 7. 1036C Classy Numbers：数位 DP 入口（识读级）

### 7.1 题型定位

求 `[lo,hi]` 内"非零数字不超过 3 个"的数的个数。数位 DP 模板题——本课作为**入口**，目标是**看懂并会套模板**，不要求第一遍默写。

### 7.2 模板三要素

- **按位填**：从高位到低位，`pos` 表示当前位。
- **tight（贴上界）**：前面每位都等于上界时，本位上限是上界数字，否则 9。
- **记忆化**：不贴上界的状态 `memo[pos][cnt]` 与具体上界无关，可复用。

`countClassy(x)` = `[0,x]` 内满足条件的个数，答案 `countClassy(hi) - countClassy(lo-1)`。

### 7.3 参考代码（已过官方样例，作识读模板）

```cpp
#include<bits/stdc++.h>
using namespace std;

int dig[20];                 // 上界的每一位，低位存在下标 0
long long memo[20][4];       // memo[pos][cnt]：不贴上界时的方案数，与具体上界无关

// pos：当前填第几位（从高往低，填完为 -1）
// cnt：已经用掉的非零数字个数
// tight：前面每一位是否都贴着上界
long long dfs(int pos, int cnt, bool tight){
    if(cnt > 3) return 0;                  // 非零数字超过 3 个，直接剪掉
    if(pos < 0) return 1;                  // 所有位填完，得到一个合法数
    if(!tight && memo[pos][cnt] != -1) return memo[pos][cnt];

    int up = tight ? dig[pos] : 9;         // 本位能填的最大数字
    long long total = 0;
    for(int d = 0; d <= up; d++)
        total += dfs(pos - 1, cnt + (d != 0), tight && d == up);

    if(!tight) memo[pos][cnt] = total;     // 只有不贴上界的状态才能复用
    return total;
}

// 统计 [0, x] 中非零数字不超过 3 个的数的个数
long long countClassy(long long x){
    if(x < 0) return 0;
    int len = 0;
    if(x == 0) dig[len++] = 0;
    while(x > 0){
        dig[len++] = x % 10;
        x /= 10;
    }
    return dfs(len - 1, 0, true);
}

void solve(){
    long long lo, hi;
    cin >> lo >> hi;
    cout << countClassy(hi) - countClassy(lo - 1) << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(memo, -1, sizeof memo);         // memo 不依赖上界，整个程序只需清一次
    int T;
    cin >> T;
    while(T--) solve();
    return 0;
}
```

### 7.4 赛场策略与易错点

- 差分 `f(hi) - f(lo-1)`，`lo-1` 可能为 0，`countClassy` 要能处理 x=0。
- `memo` 只在 **不贴上界** 时存/取（贴上界的状态受具体上界影响不可复用）。
- 数位 DP 是"入口"：J→S 过渡阶段会套模板即可，深入留到后续。

## 8. 当天训练顺序

| 顺序 | 题目 | rating | 预计用时 | 目标 |
|---:|---|---:|---:|---|
| 1 | 698A Vacations | 1400 | 25 min | 多状态线性 DP |
| 2 | 489C Given Length... | 1400 | 25 min | 构造热身 |
| 3 | 1881E Block Sequence | 1500 | 30 min | 后缀 DP |
| 4 | 766C Mahmoud and a Message | 1700 | 40 min | 一次 DP 三量 |
| 5 | 1033C Permutation Game | 1600 | 35 min | 博弈 DP |
| 6 | 1036C Classy Numbers | 1900 | 45 min | 数位 DP 入口 |

## 9. 易错点清单

- DP 四问先写再编码。
- 多状态 DP：非法状态保持 INF，别参与转移。
- 后缀 DP 边界 `f[n+1]`；块长含首元素。
- 博弈 DP 处理顺序保证后继先算。
- 数位 DP 记忆化只在不贴上界时用。
- 取模、long long（数位 DP 计数）。

晚间任务：DP 状态卡片（定义、转移、边界、答案）；把 1881E 后缀 DP 与 1036C 数位模板各写成 4 行卡片。
