# Day 1 学生讲义：复杂度、STL、字符串扫描与位运算建模

适合对象：完成 CSP-J 基础、准备进入 CSP-S 训练的同学。

今天不学习一个单独的大算法，而是建立六个以后每天都会用到的工具模型：

| 题目 | 今天要学会的模型 |
|---|---|
| 166A Rank List | 多关键字排序、并列统计 |
| 90B African Crossword | 二维计数：先统计，再筛选 |
| 313B Ilya and Queries | 相邻贡献 + 前缀和 |
| 723B Text Document Analysis | 字符串扫描 + 状态 + 结算 |
| 1023A Single Wildcard Pattern Matching | 前缀、后缀与长度边界 |
| 1042B Vitamins | bitmask 表示小集合 |

## 1. 做题前的四个问题

读完题目后，先不要急着写代码。先回答：

1. 数据范围是多少？
2. 暴力做法的复杂度是多少？
3. 题目更像字符串、查询、集合、排序，还是模拟？
4. 能否维护一个状态、数组或前缀信息，把问题变简单？

这四步是 Day 1 最重要的习惯。

## 2. 复杂度：先判断能不能跑

### 2.1 常见范围和做法

| 数据范围 | 常见可接受复杂度 | 常见做法 |
|---:|---:|---|
| `n <= 20` | `O(2^n)` | 子集枚举、状态压缩 |
| `n <= 100` | `O(n^3)` | Floyd、三重循环 DP |
| `n <= 2000` | `O(n^2)` | 双重循环、二维 DP |
| `n <= 2e5` | `O(n log n)` 或 `O(n)` | 排序、二分、前缀和、扫描 |
| `n <= 1e6` | 尽量 `O(n)` | 线性扫描、计数 |

这是经验估计，不是死规则。还要看常数、时限和多组数据的总规模。

### 2.2 多次查询不能反复扫描

若 `n,q <= 2e5`，每次查询都扫一遍区间：

```text
O(nq) = 4e10
```

一定会超时。

若先预处理 `O(n)`，每次查询 `O(1)`，总复杂度就是：

```text
O(n + q)
```

313B 就是这个模型。

### 2.3 两层循环不一定是 `O(n^2)`

```cpp
for(int i = 1; i <= n; i++){
    for(int j = i; j <= n; j += i){
        cnt++;
    }
}
```

当 `i=1` 时内层约跑 `n` 次；当 `i=2` 时约跑 `n/2` 次。

```text
n/1 + n/2 + n/3 + ... + n/n = O(n log n)
```

分析复杂度时，要看循环变量怎样变化，不能只数循环层数。

## 3. 基础代码规范

### 3.1 统一模板

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    return 0;
}
```

使用了这两句加速后，不要再混用 `scanf/printf` 和 `cin/cout`。

### 3.2 下标约定

- `string`、`vector` 默认从 `0` 开始。
- 前缀和常常使用 `1` 下标。
- 若要把字符串改成 `1` 下标，可以写 `s = " " + s`。

下标题先写清楚：`pre[i]` 到底统计到哪里，`i` 是字符位置还是相邻对的左端点。

### 3.3 `int` 与 `long long`

```text
int       约到 2.1e9
long long 约到 9e18
```

出现总和、乘法、路径长度、价格累加时，要先检查是否需要 `long long`。

## 4. 常用 STL

### 4.1 `vector`

| 操作 | 含义 | 复杂度 |
|---|---|---:|
| `v.push_back(x)` | 末尾加入元素 | 均摊 `O(1)` |
| `v.pop_back()` | 删除末尾元素 | `O(1)` |
| `v[i]` | 访问元素 | `O(1)` |
| `v.size()` | 元素数量 | `O(1)` |
| `sort(v.begin(), v.end())` | 排序 | `O(n log n)` |

```cpp
vector<int> v;
for(int i = 1; i <= n; i++){
    int x;
    cin >> x;
    v.push_back(x);
}
sort(v.begin(), v.end());
```

### 4.2 `string`

| 写法 | 含义 |
|---|---|
| `s.size()` | 字符串长度 |
| `s[i]` | 第 `i` 个字符，0 下标 |
| `s.substr(pos, len)` | 从 `pos` 开始取 `len` 个字符 |
| `s += c` | 末尾追加字符 |
| `s == t` | 判断两串是否相同 |

注意：`substr(pos, len)` 的第二个参数是长度，不是右端点。

```cpp
string s = "abcdef";
cout << s.substr(2, 3) << '\n'; // cde
```

### 4.3 排序、`map`、`set`

`pair<int,int>` 默认先比较 `first`，再比较 `second`。

字符种类很少时，数组通常比 `map` 更直接：

```cpp
int cnt[26] = {};
for(char c: s) cnt[c - 'a']++;
```

`map` 和 `set` 一般是 `O(log n)`。能用数组计数时，不必强行使用它们。

## 5. 模型一：字符串扫描

### 5.1 核心想法

从左到右扫描字符，用变量维护当前状态；遇到分隔符时结算当前这一段。

```text
扫描字符 -> 更新状态 -> 遇分隔符 -> 结算 -> 清空临时状态
```

### 5.2 723B：需要维护什么

题目中的字符有字母、下划线、左右括号。要求：

1. 括号外最长单词长度；
2. 括号内单词数量。

| 变量 | 含义 |
|---|---|
| `in` | 当前是否在括号内 |
| `len` | 当前连续字母段长度 |
| `mx` | 括号外最长单词长度 |
| `cnt` | 括号内单词数量 |

### 5.3 手动模拟

字符串：

```text
ab_cd(ef_g)h
```

| 字符 | 结算或状态变化 |
|---|---|
| `ab` | 括号外单词，`mx=2` |
| `_` | 结算当前单词 |
| `cd` | 括号外单词，`mx=2` |
| `(` | 先结算 `cd`，再进入括号 |
| `ef` | 括号内第一个单词 |
| `_` | 结算，`cnt=1` |
| `g` | 括号内第二个单词 |
| `)` | 先结算 `g`，`cnt=2`，再离开括号 |
| `h` | 扫描结束后还要结算 |

关键：遇到 `(`、`)` 时，**先结算当前单词，再改变括号状态**。

### 5.4 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

bool isletter(char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;

    bool in = false;
    int len = 0, mx = 0, cnt = 0;

    auto finish = [&](){
        if(len == 0) return;
        if(in) cnt++;
        else mx = max(mx, len);
        len = 0;
    };

    for(char c: s){
        if(isletter(c)){
            len++;
        }else{
            finish();
            if(c == '(') in = true;
            if(c == ')') in = false;
        }
    }
    finish();

    cout << mx << ' ' << cnt << '\n';
    return 0;
}
```

**复杂度：** `O(n)`。

## 6. 模型二：一个 `*` 的通配符

### 6.1 1023A 的拆法

模式串只有一个 `*` 时，把它拆为：

```text
pre + * + suf
```

其中 `pre` 是 `*` 左边，`suf` 是 `*` 右边。

若模式为 `ab*cd`，原串为 `abxyzcd`，中间的 `xyz` 由 `*` 匹配。

有 `*` 时需要同时满足：

1. `t.size() >= pre.size() + suf.size()`；
2. `t` 的前缀等于 `pre`；
3. `t` 的后缀等于 `suf`。

`*` 可以匹配空串。例如 `a*b` 能匹配 `ab`。

### 6.2 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    string p, t;
    cin >> n >> m >> p >> t;

    int pos = -1;
    for(int i = 0; i < n; i++){
        if(p[i] == '*') pos = i;
    }

    if(pos == -1){
        cout << (p == t ? "YES" : "NO") << '\n';
        return 0;
    }

    string pre = p.substr(0, pos);
    string suf = p.substr(pos + 1);

    if((int)t.size() < (int)pre.size() + (int)suf.size()){
        cout << "NO\n";
        return 0;
    }

    bool ok = true;
    for(int i = 0; i < (int)pre.size(); i++){
        if(t[i] != pre[i]) ok = false;
    }

    int st = (int)t.size() - (int)suf.size();
    for(int i = 0; i < (int)suf.size(); i++){
        if(t[st + i] != suf[i]) ok = false;
    }

    cout << (ok ? "YES" : "NO") << '\n';
    return 0;
}
```

**复杂度：** `O(n+m)`。

## 7. 模型三：相邻贡献与前缀和

### 7.1 313B 统计的不是字符

给定字符串 `s`，询问 `[l,r]` 中有多少个位置 `i` 满足：

```text
l <= i < r 且 s[i] == s[i+1]
```

统计对象是相邻对的左端点 `i`。

定义：

```text
b[i] = 1，当 s[i] == s[i+1]
b[i] = 0，否则
pre[i] = b[1] + b[2] + ... + b[i]
```

那么：

```text
查询 [l,r] 的答案 = pre[r-1] - pre[l-1]
```

### 7.2 手动模拟

```text
s = aabbaa
```

| `i` | 1 | 2 | 3 | 4 | 5 |
|---:|---|---|---|---|---|
| 比较 | `a=a` | `a!=b` | `b=b` | `b!=a` | `a=a` |
| `b[i]` | 1 | 0 | 1 | 0 | 1 |
| `pre[i]` | 1 | 1 | 2 | 2 | 3 |

询问 `[2,6]` 时，最后一个可比较的左端点是 `5`：

```text
pre[5] - pre[1] = 2
```

### 7.3 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 100000 + 10;
int pre[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int n = (int)s.size();
    s = " " + s;

    for(int i = 1; i < n; i++){
        pre[i] = pre[i - 1] + (s[i] == s[i + 1]);
    }

    int q;
    cin >> q;
    while(q--){
        int l, r;
        cin >> l >> r;
        cout << pre[r - 1] - pre[l - 1] << '\n';
    }

    return 0;
}
```

**复杂度：** 预处理 `O(n)`，每次询问 `O(1)`，总计 `O(n+q)`。

## 8. 模型四：bitmask 表示小集合

### 8.1 三种维生素如何编码

| 元素 | 二进制位 | mask |
|---|---:|---:|
| `A` | 第 0 位 | 1 |
| `B` | 第 1 位 | 2 |
| `C` | 第 2 位 | 4 |
| `AB` | 第 0、1 位 | 3 |
| `BC` | 第 1、2 位 | 6 |
| `ABC` | 三位都有 | 7 |

位或 `|` 用来合并集合：

```text
AB | BC = 3 | 6 = 7
```

### 8.2 1042B 的关键观察

饮料很多，但维生素集合只有 `2^3=8` 种状态。

令：

```text
cost[mask] = 一瓶恰好包含 mask 对应维生素的最低价格
```

只需枚举三个集合状态，检查它们是否能合成 `7`。

### 8.3 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int getmask(string s){
    int m = 0;
    for(char c: s){
        if(c == 'A') m |= 1;
        if(c == 'B') m |= 2;
        if(c == 'C') m |= 4;
    }
    return m;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> cost(8, INF);
    cost[0] = 0; // 表示这个位置不买饮料

    for(int i = 1; i <= n; i++){
        int c;
        string s;
        cin >> c >> s;
        int m = getmask(s);
        cost[m] = min(cost[m], c);
    }

    int ans = INF;
    for(int a = 0; a < 8; a++){
        for(int b = 0; b < 8; b++){
            for(int c = 0; c < 8; c++){
                if(cost[a] == INF || cost[b] == INF || cost[c] == INF) continue;
                if((a | b | c) == 7){
                    ans = min(ans, cost[a] + cost[b] + cost[c]);
                }
            }
        }
    }

    cout << (ans == INF ? -1 : ans) << '\n';
    return 0;
}
```

**复杂度：** `O(n + 8^3)`，可以视为 `O(n)`。

## 9. 模型五：二维字符统计

### 9.1 90B：先统计，再判断

一个字符要被保留，当且仅当：

```text
它在所在行只出现一次；
它在所在列也只出现一次。
```

维护：

| 数组 | 含义 |
|---|---|
| `row[i][c]` | 第 `i` 行字符 `c` 的出现次数 |
| `col[j][c]` | 第 `j` 列字符 `c` 的出现次数 |

第一遍读入时统计，第二遍按原矩阵顺序筛选。

若对每个格子重新扫描一行和一列，复杂度约为 `O(nm(n+m))`；两遍统计是 `O(nm)`。

### 9.2 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 110;
char a[N][N];
int row[N][26], col[N][26];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> a[i][j];
            int x = a[i][j] - 'a';
            row[i][x]++;
            col[j][x]++;
        }
    }

    string ans;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            int x = a[i][j] - 'a';
            if(row[i][x] == 1 && col[j][x] == 1){
                ans += a[i][j];
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
```

**复杂度：** `O(nm)`。

## 10. 模型六：多关键字排序与并列统计

### 10.1 166A 的步骤

排名规则：

1. 解题数 `p` 大的在前；
2. 解题数相同，罚时 `t` 小的在前。

做法：

1. 按规则排序；
2. 记录第 `k` 名的 `(p,t)`；
3. 统计有多少队伍与它完全相同。

### 10.2 比较函数必须严格

比较函数表达的是：“`a` 是否应该排在 `b` 前面”。

```cpp
if(a.p != b.p) return a.p > b.p;
return a.t < b.t;
```

不能写：

```cpp
return a.p >= b.p;
```

因为相等时，`cmp(a,b)` 和 `cmp(b,a)` 都可能为真，排序规则会失效。

### 10.3 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

struct Node{
    int p, t;
};

bool cmp(Node a, Node b){
    if(a.p != b.p) return a.p > b.p;
    return a.t < b.t;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<Node> a(n + 1);
    for(int i = 1; i <= n; i++){
        cin >> a[i].p >> a[i].t;
    }

    sort(a.begin() + 1, a.end(), cmp);

    Node key = a[k];
    int ans = 0;
    for(int i = 1; i <= n; i++){
        if(a[i].p == key.p && a[i].t == key.t){
            ans++;
        }
    }

    cout << ans << '\n';
    return 0;
}
```

**复杂度：** 排序 `O(n log n)`，统计 `O(n)`。

## 11. 今日训练顺序

建议按下面顺序完成：

1. 166A Rank List
2. 90B African Crossword
3. 313B Ilya and Queries
4. 723B Text Document Analysis
5. 1023A Single Wildcard Pattern Matching
6. 1042B Vitamins

每题完成后，用下面的格式写一张复盘卡：

```text
题目：
模型：
关键变量：
复杂度：
易错点：
```

## 12. 自查清单

### 12.1 复杂度

- 是否考虑了多组数据的总规模？
- 是否把每次查询从 `O(n)` 降到了可接受复杂度？
- 是否只看了循环层数，却没有看变量变化？

### 12.2 字符串

- `string` 是 0 下标，前缀和是否统一成 1 下标？
- `substr(pos, len)` 的第二个参数是否写成了右端点？
- 扫描结束后，最后一段是否结算？
- `*` 是否允许匹配空串？

### 12.3 前缀和与 bitmask

- `pre[i]` 的含义能否用一句话说清？
- 相邻贡献题是否只统计到 `r-1`？
- `pre[0]` 是否已初始化？
- 集合合并是否使用 `|`，不可达状态是否跳过？

### 12.4 排序

- 比较函数是否使用严格比较，而不是 `>=`、`<=`？
- 多关键字的优先级是否正确？
- 排序后访问的是第 `k` 名还是第 `k-1` 名？

## 13. 今日总结

```text
先看范围，再选复杂度。
字符串扫描：状态 + 分隔符结算。
多次查询：贡献数组 + 前缀和。
小集合：bitmask + 位或合并。
排序题：比较函数先写对，再定位目标。
```
