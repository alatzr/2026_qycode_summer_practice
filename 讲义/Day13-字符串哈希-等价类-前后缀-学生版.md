# Day 13 学生讲义：字符串哈希、等价类与前后缀

> 学习方式：先理解题型的核心想法，再手算例子，随后阅读模板并独立实现。完成后复盘关键变量、复杂度和边界。


适用班级：已完成 Day1（字符串扫描）与 Day8-12（图论/并查集）的学生。

学习重点：字符串第一课。核心是**多项式哈希**（O(1) 比较任意子串）与由此衍生的"等价类、border、前后缀"问题。标题里的"Trie 替代"指：本阶段用哈希充当字符串等价工具，Trie 的系统实现在 Day24 现教。

配套题单：

| 题号 | 题目 | rating | 本课对应知识点 | 掌握目标 |
|---|---|---:|---|---|
| 1791D | Distinct Split | 1000 | 前后缀不同字符计数（热身） | 学会前后缀各扫一遍 |
| 559B | Equivalent Strings | 1700 | 递归等价类 | 学会"标准形"归并 |
| 126B | Password | 1700 | border + 中间出现 | 学会哈希判 border |
| 316G1 | Good Substrings | 1700 | 子串哈希去重 + 计数 | 学会哈希 + set 去重 |
| 1849C | Binary String Copying | 1600 | 等价键去重 | 学会"只有核心区间决定结果" |
| 2010C2 | Message Transmission Error | 1700 | 重叠自匹配 | 学会枚举重叠长度 |

## 1. 多项式哈希模板（本课的根）

把字符串看成 BASE 进制数。前缀哈希 + 幂，可 O(1) 取任意子串哈希：

```cpp
typedef unsigned long long ull;
const ull BASE = 131;
ull preHash[N], pw[N];
// 预处理：pw[i]=BASE^i，preHash[i]=前 i 个字符的哈希
ull get(int l, int r){ return preHash[r] - preHash[l - 1] * pw[r - l + 1]; }  // 子串 [l,r]，1 下标
```

用 `unsigned long long` 自然溢出当模数（省一次取模，实战够用；卡哈希时改双哈希）。

## 2. 1791D Distinct Split：前后缀计数（热身）

### 2.1 题型定位

把串在某处切成两段，最大化"前段不同字符数 + 后段不同字符数"。前后缀各扫一遍，用 bitmask 记字符集。

### 2.2 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n;
    string s;
    cin >> n >> s;
    vector<int> preCnt(n), sufCnt(n);
    int maskPre = 0, maskSuf = 0;   // 26 位标记出现过的字母
    for(int i = 0; i < n; i++){
        maskPre |= 1 << (s[i] - 'a');
        preCnt[i] = __builtin_popcount(maskPre);
    }
    for(int i = n - 1; i >= 0; i--){
        maskSuf |= 1 << (s[i] - 'a');
        sufCnt[i] = __builtin_popcount(maskSuf);
    }
    int ans = 0;
    for(int cut = 0; cut + 1 < n; cut++)   // 前段 [0,cut]，后段 [cut+1,n-1]
        ans = max(ans, preCnt[cut] + sufCnt[cut + 1]);
    cout << ans << '\n';
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

### 2.3 易错点

- 用 26 位 bitmask + popcount 数不同字符，比 set 快。
- 切点范围 `cut+1 < n`（两段都非空）。

## 3. 126B Password：border + 中间出现

### 3.1 题型定位

求最长的子串，它**既是前缀又是后缀又在中间出现**。哈希判 border + 枚举中间出现。

### 3.2 三步法

1. 找最长 border `b1`（前缀 = 后缀，长度 < n）。
2. 若 `prefix(b1)` 在中间（起点 ≥2，终点 ≤n-1）出现，答案 = `b1`。
3. 否则退到 `prefix(b1)` 的最长 border `b2`（它必在中间出现），答案 = `b2`；再无则 `Just a legend`。

### 3.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

const ull BASE = 131;
const int N = 1e6 + 10;

int n;
string s;
ull preHash[N], pw[N];

ull get(int l, int r){   // 子串 s[l..r] 的哈希值，1 下标
    return preHash[r] - preHash[l - 1] * pw[r - l + 1];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> s;
    n = s.size();
    pw[0] = 1;
    for(int i = 1; i <= n; i++){
        pw[i] = pw[i - 1] * BASE;
        preHash[i] = preHash[i - 1] * BASE + s[i - 1];
    }
    // 第一步：最长 border b1（既是前缀又是后缀，长度 < n）
    int b1 = 0;
    for(int len = n - 1; len >= 1; len--)
        if(get(1, len) == get(n - len + 1, n)){ b1 = len; break; }
    if(b1 == 0){ cout << "Just a legend\n"; return 0; }
    // 第二步：prefix(b1) 是否在中间出现（起点 2..，终点不到 n）
    bool midHit = false;
    for(int st = 2; st + b1 - 1 <= n - 1; st++)
        if(get(st, st + b1 - 1) == get(1, b1)){ midHit = true; break; }
    if(midHit){ cout << s.substr(0, b1) << '\n'; return 0; }
    // 第三步：退到次长 border b2 = prefix(b1) 的最长 border，它必然在中间出现
    int b2 = 0;
    for(int len = b1 - 1; len >= 1; len--)
        if(get(1, len) == get(b1 - len + 1, b1)){ b2 = len; break; }
    if(b2 == 0) cout << "Just a legend\n";
    else cout << s.substr(0, b2) << '\n';
    return 0;
}
```

### 3.4 赛场策略与易错点

- border 长度 < n；中间出现要求起点 ≥2 且终点 ≤ n-1（不与首尾重合）。
- 退到次长 border 是本题最巧的一步（KMP 的 fail 链思想，此处用哈希实现）。
- 输出 `Just a legend` 逐字符照抄。

## 4. 2010C2 Message Transmission Error：重叠自匹配

### 4.1 题型定位

收到的串 t 可能是原串 s 发送两次、末尾与开头重叠而成。判断 t 能否表示为 `s + s` 重叠 `ov` 个字符（`1 ≤ ov ≤ |s|-1`），求原串 s。

### 4.2 关键设计

设原串长 L，则 `|t| = 2L - ov`，重叠 `ov = 2L - n`。约束 `1 ≤ ov ≤ L-1` ⇒ `n/2 < L ≤ n-1`。枚举 L，检查 `t` 的前 L 个与后 L 个是否相等（哈希 O(1)），相等即 `s = t[1..L]`。

### 4.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

const ull BASE = 131;
const int N = 4e5 + 10;

int n;
string t;
ull preHash[N], pw[N];

ull get(int l, int r){   // 子串 t[l..r] 的哈希值，1 下标
    return preHash[r] - preHash[l - 1] * pw[r - l + 1];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> t;
    n = t.size();
    pw[0] = 1;
    for(int i = 1; i <= n; i++){
        pw[i] = pw[i - 1] * BASE;
        preHash[i] = preHash[i - 1] * BASE + t[i - 1];
    }
    // 原串长 L：重叠 ov = 2L - n 必须满足 1 <= ov <= L-1，即 n/2 < L <= n-1
    for(int L = n - 1; L * 2 > n; L--)
        if(get(1, L) == get(n - L + 1, n)){
            cout << "YES\n" << t.substr(0, L) << '\n';
            return 0;
        }
    cout << "NO\n";
    return 0;
}
```

### 4.4 赛场策略与易错点

- 重叠区间约束 `n/2 < L ≤ n-1`（严格重叠，不能整段不重叠也不能完全重合）。
- 哈希比较前 L 与后 L 是否相等（它们是重叠部分的两种表述，相等才自洽）。

## 5. 559B Equivalent Strings：递归等价类

### 5.1 题型定位

两串"等价"定义：相等，或都能对半分且（左等左右等右 或 左等右右等左）。判两串是否等价。**递归求标准形**。

### 5.2 关键设计

`norm(s)`：奇数长度直接返回自己；偶数长度递归求两半的标准形，取"较小拼接"作为标准形。两串标准形相等即等价。

### 5.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

// 求等价类的标准形：奇数长度是自己；偶数长度取两半标准形的较小拼接
string norm(const string &str){
    int len = str.size();
    if(len & 1) return str;
    string half1 = norm(str.substr(0, len / 2));
    string half2 = norm(str.substr(len / 2));
    return half1 < half2 ? half1 + half2 : half2 + half1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s1, s2;
    cin >> s1 >> s2;
    cout << (norm(s1) == norm(s2) ? "YES" : "NO") << '\n';
    return 0;
}
```

### 5.4 赛场策略与易错点

- 标准形 = 等价类的唯一代表，两串标准形相等 ⟺ 等价。
- 复杂度 `O(n log² n)` 级别（每层字符串操作），n ≤ 2e5 可过；卡常时可换哈希比较。
- 奇数长度是递归边界。

## 6. 316G1 Good Substrings：子串去重计数

### 6.1 题型定位

统计 s 的不同子串中，满足若干"在规则串中出现次数落在 [low,high]"约束的个数。哈希枚举所有子串 + set 去重 + 规则串子串计数。

### 6.2 关键设计

对每个规则串预处理"每种长度的子串哈希 → 出现次数"（map）。枚举 s 的每个子串，用 `(长度, 哈希)` 去重，对每条规则查出现次数是否在区间内。数据范围小（n ≤ 100 级），`O(n² · 规则数 · log)` 可过。

### 6.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

const ull BASE = 131;
const int N = 210;

ull pw[N];

// 求一个串的前缀哈希数组（1 下标公式）
vector<ull> buildHash(const string &raw){
    int len = raw.size();
    vector<ull> pre(len + 1, 0);
    for(int i = 1; i <= len; i++) pre[i] = pre[i - 1] * BASE + raw[i - 1];
    return pre;
}

ull getHash(const vector<ull> &pre, int l, int r){
    return pre[r] - pre[l - 1] * pw[r - l + 1];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    int ruleCnt;
    cin >> s >> ruleCnt;
    int n = s.size();
    pw[0] = 1;
    for(int i = 1; i < N; i++) pw[i] = pw[i - 1] * BASE;

    vector<string> ruleStr(ruleCnt);
    vector<int> needLow(ruleCnt), needHigh(ruleCnt);
    // occCnt[k][len]：规则串 k 中每个长度为 len 的子串哈希 -> 出现次数
    vector<vector<map<ull, int>>> occCnt(ruleCnt);
    for(int k = 0; k < ruleCnt; k++){
        cin >> ruleStr[k] >> needLow[k] >> needHigh[k];
        int plen = ruleStr[k].size();
        vector<ull> preP = buildHash(ruleStr[k]);
        occCnt[k].assign(plen + 1, map<ull, int>());
        for(int len = 1; len <= plen; len++)
            for(int st = 1; st + len - 1 <= plen; st++)
                occCnt[k][len][getHash(preP, st, st + len - 1)]++;
    }

    vector<ull> preS = buildHash(s);
    set<pair<int, ull>> seen;   // (长度, 哈希) 去重：相同子串只判一次
    long long good = 0;
    for(int len = 1; len <= n; len++)
        for(int st = 1; st + len - 1 <= n; st++){
            ull hv = getHash(preS, st, st + len - 1);
            if(!seen.insert({len, hv}).second) continue;
            bool ok = true;
            for(int k = 0; k < ruleCnt && ok; k++){
                int cnt = 0;   // 该子串在规则串 k 中的出现次数（不出现记 0）
                if(len <= (int)ruleStr[k].size()){
                    auto it = occCnt[k][len].find(hv);
                    if(it != occCnt[k][len].end()) cnt = it->second;
                }
                if(cnt < needLow[k] || cnt > needHigh[k]) ok = false;
            }
            if(ok) good++;
        }
    cout << good << '\n';
    return 0;
}
```

### 6.4 易错点

- 用 `(长度, 哈希)` 去重，避免不同长度哈希碰撞。
- 子串不出现时次数记 0（要落在 [low,high] 内才算好）。

## 7. 1849C Binary String Copying：等价键去重

### 7.1 题型定位

对 01 串多次操作"排序区间 [l,r]"，问能产生多少种不同的串。**只有区间内"第一个 1 到最后一个 0"的核心段决定结果**，用等价键去重。

### 7.2 关键设计

预处理 `nxt1[i]`（i 及右第一个 1）、`pre0[i]`（i 及左最后一个 0）。区间 [l,r] 排序的实际效果只由 `(firstOne, lastZero)` 决定：若 `firstOne > lastZero` 则排序不改变串（等价键 (0,0)），否则键为 `(firstOne, lastZero)`。用 set 去重键的数量即答案。

### 7.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n, m;
    string s;
    cin >> n >> m >> s;
    s = "#" + s;   // 改成 1 下标
    vector<int> nxt1(n + 2), pre0(n + 2);
    nxt1[n + 1] = n + 1;                    // 哨兵：右边没有 1
    for(int i = n; i >= 1; i--)
        nxt1[i] = (s[i] == '1') ? i : nxt1[i + 1];
    pre0[0] = 0;                            // 哨兵：左边没有 0
    for(int i = 1; i <= n; i++)
        pre0[i] = (s[i] == '0') ? i : pre0[i - 1];

    set<pair<int, int>> keys;               // 等价键去重
    while(m--){
        int l, r;
        cin >> l >> r;
        int firstOne = nxt1[l];             // [l,r] 内第一个 1
        int lastZero = pre0[r];             // [l,r] 内最后一个 0
        if(firstOne > lastZero) keys.insert({0, 0});        // 排序不改变串
        else keys.insert({firstOne, lastZero});             // 真正变化的核心区间
    }
    cout << keys.size() << '\n';
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

### 7.4 赛场策略与易错点

- 核心洞察：排序区间的效果只由"首个 1、末个 0"确定——把看似 O(n) 的串比较压成一个二元键。
- `firstOne > lastZero`（区间已有序）全部归为同一键 (0,0)。
- 等价类去重是本课主线（559B 递归、1849C 键、316G1 哈希）的统一思想。

## 8. 训练建议

| 顺序 | 题目 | rating | 预计用时 | 目标 |
|---:|---|---:|---:|---|
| 1 | 1791D Distinct Split | 1000 | 15 min | 前后缀计数热身 |
| 2 | 559B Equivalent Strings | 1700 | 30 min | 递归等价类 |
| 3 | 126B Password | 1700 | 40 min | border + 中间出现 |
| 4 | 2010C2 Message Transmission Error | 1700 | 35 min | 重叠自匹配 |
| 5 | 316G1 Good Substrings | 1700 | 40 min | 子串去重计数 |
| 6 | 1849C Binary String Copying | 1600 | 35 min | 等价键去重 |

## 9. 易错点清单

- 哈希模板：前缀哈希 + 幂，`get(l,r)` 用 1 下标公式；卡哈希改双哈希。
- border：长度 < n；中间出现不与首尾重合。
- 2010C2 重叠长度约束 `n/2 < L ≤ n-1`。
- 等价类去重：标准形（559B）/键（1849C）/哈希（316G1）。
- Trie 的系统实现在 Day24；本课用哈希充当字符串等价工具。

晚间任务：hash 冲突、双 hash、等价类三张卡；把 126B 的"三步 border"和 1849C 的"核心区间键"各写成 4 行卡片。
