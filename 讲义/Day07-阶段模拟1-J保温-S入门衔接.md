# Day 7 教师讲义：阶段模拟 1（S 入门衔接卷）——字符串维护、括号构造与线性 DP

适用班级：已完成 Day1-Day6（复杂度/STL、表达式与栈、贪心、反悔贪心、二分与 ST 表、线性 DP）的学生。

课时定位：第一阶段第一次整卷模拟。目的不是学新算法，而是检验前 6 天知识在"限时、闭卷、无提示"条件下的转化率：读题归类是否快、暴力起手是否稳、部分分意识是否建立。

## 0. 模拟考安排

### 0.1 卷型定位

| 项目 | 设定 |
|---|---|
| 卷型 | S 入门衔接卷（对应总计划 §7） |
| 时长 | 180 分钟（9:10-12:10），基础弱的班可放宽到 12:30 |
| 满分 | 600 分（每题 100） |
| 合格线 | 300 分（前三题全对） |
| 冲刺线 | 450 分以上 |

### 0.2 赛位映射与目标用时

| 赛位 | 题号 | 题目 | rating | 对应 CSP 位置 | 目标用时 |
|---|---|---|---:|---|---:|
| T1 | 2036C | Anya and 1100 | 1100 | S T1 / J T3 签到 | 20 min |
| T2 | 1996C | Sort | 1200 | S T1 | 25 min |
| T3 | 1905C | Largest Subsequence | 1400 | S T2 | 30 min |
| T4 | 2233C | Cost of a Bracket Sequence | 1400 | S T2-T3（构造输出） | 35 min |
| T5 | 2222C | Median Partition | 1500 | S T3（DP） | 35 min |
| T6 | 2050E | Three Strings | 1500 | S T3（DP） | 35 min |

### 0.3 封场规则

1. 全程闭卷：禁止题解、禁止互相讨论、禁止 AI 工具；只允许查 C++ 语法手册。
2. 每题必须先写"数据范围 + 暴力复杂度"两行再动键盘，交卷时一并上交。
3. 卡题 25 分钟无进展必须换题（监考教师提醒）。
4. 赛后先自主定位错误（对照 §8 五维复盘表填写），再听讲评。

## 1. 考中监考要点

- 开考 10 分钟：巡视每人是否先读完 6 题再动手。只做 T1 不读后面的，赛后要点名纠正。
- 开考 60 分钟：检查 T1/T2 完成率。低于一半的学生，重点看是不是在 T1 上追求"完美写法"。
- 开考 120 分钟：观察 T4-T6 是否有人开始写"输出全 0 / 输出 -1"级别的保底分代码，这是本卷要训练的赛场素养。
- 全程记录每人卡题位置，讲评时按卡点分组提问。

## 2. T1 2036C Anya and 1100：动态字符串局部维护

### 2.1 题型定位

给一个 01 串，多次单点修改，每次修改后回答串中是否存在子串 `1100`。对应 CSP 的"带修改的签到题"：暴力重扫是 `O(nq)`，会超时，需要"局部重算"意识。

### 2.2 暴力与部分分

每次修改后全串扫一遍找 `1100`，複杂度 `O(nq)`。数据 `n,q ≤ 2e5`，只能过小数据，但**先写暴力再优化**仍是正确的赛场顺序：暴力就是对拍器。

### 2.3 正解升级

单点修改位置 `pos` 只影响起点在 `[pos-3, pos]` 的 4 个窗口。维护计数器 `cnt` = 当前等于 `1100` 的窗口个数：

1. 修改前，把受影响窗口中原本是 `1100` 的从 `cnt` 扣掉；
2. 写入新字符；
3. 再把变成 `1100` 的窗口加回来。

单次修改 `O(4)`，总复杂度 `O(n + q)`。

### 2.4 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

// 判断以 pos 为起点的 4 个字符是否恰好为 "1100"
bool isPat(const string &s, int pos){
    if(pos < 0 || pos + 3 >= (int)s.size()) return false;
    return s[pos] == '1' && s[pos + 1] == '1' && s[pos + 2] == '0' && s[pos + 3] == '0';
}

void solve(){
    string s;
    cin >> s;
    int cnt = 0;                       // 当前 "1100" 窗口个数
    for(int i = 0; i + 3 < (int)s.size(); i++){
        if(isPat(s, i)) cnt++;
    }
    int q;
    cin >> q;
    while(q--){
        int pos;
        char newCh;
        cin >> pos >> newCh;
        pos--;                         // 转 0 下标
        // 只有起点在 [pos-3, pos] 的窗口会受影响
        for(int st = pos - 3; st <= pos; st++){
            if(isPat(s, st)) cnt--;    // 先扣掉旧窗口
        }
        s[pos] = newCh;
        for(int st = pos - 3; st <= pos; st++){
            if(isPat(s, st)) cnt++;    // 再加回新窗口
        }
        cout << (cnt > 0 ? "YES\n" : "NO\n");
    }
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

### 2.5 赛场策略与易错点

- 若想不到计数器，退一步"每次只重扫 `[pos-3, pos+3]` 这一小段"同样是 `O(1)`，能过。
- 易错：先改字符再扣旧窗口（顺序反了）；边界 `pos-3 < 0` 未判；修改后忘记输出。
- 模型卡：**固定长度模式串的动态存在性 = 单点修改只影响 O(模式长) 个窗口**。

## 3. T2 1996C Sort：前缀字符计数

### 3.1 题型定位

给两个等长小写字符串 `src`、`tgt` 和 q 次询问。每次询问给区间 `[l,r]`：把 `src[l..r]` 内部字符任意重排（等价于排序后比较），最少改多少个字符才能使 `src[l..r]` 重排后与 `tgt[l..r]` 重排后相同。本质：**区间字母频次差**。CSP 里的"前缀和查询"标准位。

### 3.2 暴力与部分分

每次询问把两段各自排序比较，`O(qn log n)`，小数据可过——赛场上先拿这部分分。

### 3.3 正解升级

排序后相同 ⇔ 26 个字母的出现次数完全相同。预处理 26 个字母的前缀计数 `preSrc[i][ch]`、`preTgt[i][ch]`，每次询问对 26 个字母求 `|cntSrc - cntTgt|` 之和。一次修改能同时"消掉一个多的 + 补上一个少的"，所以答案是差值和的一半。复杂度 `O(26(n + q))`。

### 3.4 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n, q;
    cin >> n >> q;
    string src, tgt;                   // src 为可修改串，tgt 为目标串
    cin >> src >> tgt;
    // preSrc[i][ch]: src 前 i 个字符中字母 ch 的出现次数，preTgt 同理
    vector<array<int, 26>> preSrc(n + 1), preTgt(n + 1);
    preSrc[0].fill(0);
    preTgt[0].fill(0);
    for(int i = 1; i <= n; i++){
        preSrc[i] = preSrc[i - 1];
        preTgt[i] = preTgt[i - 1];
        preSrc[i][src[i - 1] - 'a']++;
        preTgt[i][tgt[i - 1] - 'a']++;
    }
    while(q--){
        int l, r;
        cin >> l >> r;
        int diff = 0;                  // 两区间 26 个字母数量差的绝对值之和
        for(int ch = 0; ch < 26; ch++){
            int cntSrc = preSrc[r][ch] - preSrc[l - 1][ch];
            int cntTgt = preTgt[r][ch] - preTgt[l - 1][ch];
            diff += abs(cntSrc - cntTgt);
        }
        cout << diff / 2 << '\n';      // 一次修改同时消掉一多一少
    }
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

### 3.5 赛场策略与易错点

- "排序后相等"要立刻翻译成"字母频次相等"，这是 Day1 字符串扫描模型的直接迁移。
- 易错：答案忘记除 2；`vector<array<int,26>>` 未初始化第 0 项；多测未按组重建前缀数组。
- 为什么除 2：把 `src` 段改成 `tgt` 段的频次，多出来的字符总量 = 缺少的字符总量 = diff/2，每次修改恰好处理一对。

## 4. T3 1905C Largest Subsequence：后缀最大值链

### 4.1 题型定位

对字符串 `s`，反复执行"取出字典序最大的子序列，把它整体循环右移一位放回原位置"。问最少多少次操作能把 `s` 变成非降序；不可能输出 -1。观察 + 构造题，对应 S T2 的"结论 + 模拟验证"型。

### 4.2 关键观察

- 字典序最大子序列 = 从右往左的**后缀最大值链**（每个位置字符 ≥ 它右边所有字符）。
- 每次操作等价于把这条链循环右移一位；链上最大字符（可能有多个）转到位后就不再需要动。
- 转完 `len - cntMax` 次后（len 为链长、cntMax 为链中最大字符个数），链恰好变成升序排回原位。
- 所以：把链上的字符集合原地排序放回，检查整串是否有序。有序则答案 `len - cntMax`，否则 -1（链外字符不会被任何操作改变）。

### 4.3 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n;
    string s;
    cin >> n >> s;
    // 从右往左取"后缀最大值链"，即字典序最大子序列的下标
    vector<int> pos;
    char sufMax = 0;
    for(int i = n - 1; i >= 0; i--){
        if(s[i] >= sufMax){
            sufMax = s[i];
            pos.push_back(i);
        }
    }
    reverse(pos.begin(), pos.end());   // 下标转为从小到大
    int len = (int)pos.size();
    string chain;                      // 子序列本身，非升序
    for(int p : pos) chain += s[p];
    int cntMax = 0;                    // 链中等于最大字符的个数
    for(char ch : chain){
        if(ch == chain[0]) cntMax++;
    }
    // 把链排成升序放回原位置，模拟"转完所有操作"后的最终串
    reverse(chain.begin(), chain.end());
    for(int i = 0; i < len; i++) s[pos[i]] = chain[i];
    if(is_sorted(s.begin(), s.end())) cout << len - cntMax << '\n';
    else cout << -1 << '\n';
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

### 4.4 赛场策略与易错点

- 部分分策略：小数据直接按题意暴力模拟每次操作（取子序列、右移、放回），`O(n²)` 拿分。
- 易错：忘记减去 `cntMax`（最大字符不需要转）；链取成"前缀最大值"；判有序时只判链内不判整串。
- 模型卡：**字典序最大子序列 = 后缀最大值链，从右往左一遍扫**。

## 5. T4 2233C Cost of a Bracket Sequence：合法性优先的删除构造

### 5.1 题型定位

定义括号串的代价 = 其最长合法括号子序列的长度。给串 `s` 与预算 `k`，最多删 `k` 个字符使代价最小，**输出删除标记 01 串**（多解任意）。构造输出型，对应 CSP 近年爱考的"输出方案"题。

### 5.2 暴力与部分分

- 保底分：输出全 `0`（一个不删也是合法输出，能拿判定分的一部分）。
- 小数据：枚举删除集合 + `O(n)` 栈匹配求代价，`O(2^n · n)` 验证思路。

### 5.3 正解升级

代价 = 2 × 匹配对数。每删 1 个字符最多让匹配对数减 1，所以贪心地"每一步删掉一个能真正减少一对匹配的字符"：

- 对剩余串做栈匹配，找出所有配对 `(` `)`。
- 若存在一对完整落在"第一个未匹配 `(`"之前的匹配对，删它的 `(`——它右边没有多余的 `(` 能顶替，配对数必减一。
- 否则删"最后一个匹配的 `)`"——它后面没有未匹配的 `)` 能顶上。
- 重复 `k` 次或直到没有匹配对。

每步 `O(n)`，总 `O(nk)`，本题 `n ≤ 5000` 且 `Σn ≤ 5000`，可过。

### 5.4 参考代码（已过官方样例，输出与官方不同但经检验器验证等价最优）

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n, maxDel;
    cin >> n >> maxDel;
    string s;
    cin >> s;
    vector<int> removed(n, 0);         // removed[i]=1 表示第 i 个字符被删
    for(int step = 0; step < maxDel; step++){
        // 对剩余字符重做一次栈匹配
        vector<int> pairClose(n, -1);  // pairClose[i]: 位置 i 的 '(' 所配 ')' 的位置
        vector<int> stk;
        for(int i = 0; i < n; i++){
            if(removed[i]) continue;
            if(s[i] == '(') stk.push_back(i);
            else if(!stk.empty()){
                pairClose[stk.back()] = i;
                stk.pop_back();
            }
        }
        // 第一个未匹配 '(' 的位置；未匹配 '(' 全部在它之后
        int firstFreeOpen = stk.empty() ? n : stk[0];
        int delPos = -1;
        int lastClose = -1;            // 记录最后一个匹配 ')' 的位置
        for(int i = 0; i < n; i++){
            if(pairClose[i] == -1) continue;
            if(pairClose[i] < firstFreeOpen){
                delPos = i;            // 该对整体在未匹配 '(' 之前：删 '(' 无人补位
                break;
            }
            lastClose = max(lastClose, pairClose[i]);
        }
        // 所有匹配对都在未匹配 '(' 之后：删最后一个匹配 ')'，其后无未匹配 ')' 可补
        if(delPos == -1 && lastClose != -1) delPos = lastClose;
        if(delPos == -1) break;        // 已无匹配对，代价为 0，提前结束
        removed[delPos] = 1;
    }
    string mark(n, '0');
    for(int i = 0; i < n; i++){
        if(removed[i]) mark[i] = '1';
    }
    cout << mark << '\n';
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

### 5.5 赛场策略与易错点

- **多解题的对拍方式**：不能直接 diff 输出，要写检验器（应用删除标记 → 栈匹配算代价 → 与官方答案的代价比较）。这是本卷特意安排的教学点。
- 易错：删了字符后不重新匹配（配对关系会变）；输出的 1 个数超过 `k`；把"最小化代价"读成"最大化"。
- 讲评时向学生演示"为什么随便删一个 `(` 不一定减少匹配"：`(()` 删第一个 `(`，后面的 `(` 顶上，对数不变。

## 6. T5 2222C Median Partition：符号化 + 奇数段 DP

### 6.1 题型定位

把长度为奇数的数组分成尽量多的**奇数长度**连续段，要求每段的中位数都等于整个数组的中位数 `med`，输出最大段数。中位数符号化 + 线性 DP，对应 S T3。

### 6.2 符号化（本卷核心思想）

中位数条件不好直接维护，转成两个计数条件。对每段：

| 条件 | 符号化 | 含义 |
|---|---|---|
| 中位数 ≥ med | `a[i] >= med` 记 +1，否则 -1，段和 ≥ 1 | 大于等于 med 的数严格过半 |
| 中位数 ≤ med | `a[i] <= med` 记 +1，否则 -1，段和 ≥ 1 | 小于等于 med 的数严格过半 |

两个条件同时成立（奇数长度段和必为奇数，≥1 即"过半"）⇔ 段中位数恰为 `med`。

### 6.3 DP 设计

`dp[i]` = 前 `i` 个数分成若干合法奇数段的最大段数。转移枚举上一段结尾 `j`（`i-j` 为奇数，步长 2），用两个前缀和 `preGe`、`preLe` `O(1)` 判段合法。总复杂度 `O(n²)`（n ≤ 5000 级别可过；讲评时提一句"更大数据需要把 dp 值按前缀和分桶优化"即可，不展开）。

### 6.4 手动模拟（样例：`3 3 2 4 3`，med = 3）

| i | nums[i] | preGe（≥3 计 +1） | preLe（≤3 计 +1） | dp[i] |
|---:|---:|---:|---:|---:|
| 0 | — | 0 | 0 | 0 |
| 1 | 3 | 1 | 1 | 1（段 [1,1]） |
| 2 | 3 | 2 | 2 | 2（[1,1][2,2]） |
| 3 | 2 | 1 | 3 | 1（[1,3] 合法；[3,3] 单独不行：preGe 差 = -1） |
| 4 | 4 | 2 | 2 | 2（[1,1][2,4] 或 [1,3]+... 取最大） |
| 5 | 3 | 3 | 3 | 3（[1,1][2,2][3,5]，末段 `2 4 3` 中位数 3） |

答案 `dp[5] = 3`，与官方一致。让学生现场核对 `[3,5]` 段：preGe 差 = 1 ≥ 1、preLe 差 = 1 ≥ 1。

### 6.5 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n;
    cin >> n;
    vector<int> nums(n + 1);
    for(int i = 1; i <= n; i++) cin >> nums[i];
    // 每段中位数必须都等于整个数组的中位数 med
    vector<int> sortedNums(nums.begin() + 1, nums.end());
    sort(sortedNums.begin(), sortedNums.end());
    int med = sortedNums[(n - 1) / 2];
    // preGe[i]: 前 i 个数中 (>=med 记 +1, <med 记 -1) 的前缀和
    // preLe[i]: 前 i 个数中 (<=med 记 +1, >med 记 -1) 的前缀和
    vector<int> preGe(n + 1, 0), preLe(n + 1, 0);
    for(int i = 1; i <= n; i++){
        preGe[i] = preGe[i - 1] + (nums[i] >= med ? 1 : -1);
        preLe[i] = preLe[i - 1] + (nums[i] <= med ? 1 : -1);
    }
    const int NEG = -1e9;
    // dp[i]: 前 i 个数分成若干合法奇数段的最大段数
    vector<int> dp(n + 1, NEG);
    dp[0] = 0;
    for(int i = 1; i <= n; i++){
        for(int j = i - 1; j >= 0; j -= 2){    // 步长 2 保证段长 i-j 为奇数
            if(dp[j] == NEG) continue;
            if(preGe[i] - preGe[j] >= 1 && preLe[i] - preLe[j] >= 1)
                dp[i] = max(dp[i], dp[j] + 1);
        }
    }
    cout << dp[n] << '\n';                     // 整段划分必可行，dp[n] >= 1
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

### 6.6 赛场策略与易错点

- 部分分：直接输出 `1`（整段总是合法）稳拿最低档；`O(n³)` 暴力判每段中位数可拿中档。
- 易错：只判"≥ med 过半"忘了"≤ med 过半"（段里可能混入太多大数使中位数 > med）；`j` 步长写成 1 导致偶数段混入；`med` 取成 `sortedNums[n/2]`（本题定义取下中位）。
- 模型卡：**中位数条件 = ±1 符号化 + 前缀和**，`>` / `>=` 由题面中位数定义决定。

## 7. T6 2050E Three Strings：双串交织 DP（压轴）

### 7.1 题型定位

字符串 `strA`、`strB` 的字符按原相对顺序交织成 `strC`（|C| = |A|+|B|），交织前允许把 `strC` 的某些位置改字符。问 `strC` 最少有多少个位置是被改过的。等价问法：选一种交织方式，使与 `strC` 不匹配的位置最少。经典二维 DP，对应 S T3。

### 7.2 暴力与部分分

枚举所有交织方式是组合爆炸；但 |A|,|B| ≤ 10 的子任务可以爆搜——赛场上识别"这就是编辑距离家族"，直接上 DP 才是正解路径。

### 7.3 正解设计（DP 四问）

| 四问 | 回答 |
|---|---|
| 状态 | `dp[i][j]`：A 取走前 `i` 个、B 取走前 `j` 个，拼出 C 前 `i+j` 位的最小修改数 |
| 转移 | 下一位来自 A：`dp[i+1][j] = min(dp[i+1][j], dp[i][j] + (strA[i] != strC[i+j]))`；来自 B 同理 |
| 初值 | `dp[0][0] = 0`，其余 INF |
| 答案 | `dp[lenA][lenB]` |

复杂度 `O(|A|·|B|)`，多测按组重建。

### 7.4 手动模拟（A=`ab`，B=`cd`，C=`acbd`，全匹配情形）

| i\j | 0 | 1 | 2 |
|---:|---:|---:|---:|
| 0 | 0 | 1(c=a?否+1)…实际 `dp[0][1]`：取 B 的 `c` 对 C 第 1 位 `a`，代价 1 | 2 |
| 1 | 0（A 的 `a` 对 C[0]=`a`） | 0（再取 B 的 `c` 对 C[1]=`c`） | 1 |
| 2 | 1 | 0 + (b==b) = 0 | 0（最后取 d 对 d） |

让学生跟着箭头走一条 `A→B→A→B` 的路径，体会"pos = i + j 是 C 的当前位置"。

### 7.5 参考代码（已过官方样例）

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve(){
    string strA, strB, strC;           // 对应题面中的 a、b、c
    cin >> strA >> strB >> strC;
    int lenA = strA.size(), lenB = strB.size();
    const int INF = 1e9;
    // dp[i][j]: strA 取走前 i 个、strB 取走前 j 个，拼出 strC 前 i+j 位的最小修改数
    vector<vector<int>> dp(lenA + 1, vector<int>(lenB + 1, INF));
    dp[0][0] = 0;
    for(int i = 0; i <= lenA; i++){
        for(int j = 0; j <= lenB; j++){
            if(dp[i][j] == INF) continue;
            int pos = i + j;           // strC 中下一个要拼的位置(0 下标)
            if(i < lenA)
                dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + (strA[i] != strC[pos]));
            if(j < lenB)
                dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + (strB[j] != strC[pos]));
        }
    }
    cout << dp[lenA][lenB] << '\n';
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

### 7.6 赛场策略与易错点

- 推荐"刷表法"（从 `dp[i][j]` 向后更新），天然避免读到未初始化状态。
- 易错：`strC` 的下标写成 `i+j+1` 或 `i+j-1`（0/1 下标混用）；多测 dp 未重建；INF 用 `INT_MAX` 相加溢出。
- 模型卡：**双串交织匹配第三串：dp[i][j]，第三串位置恒为 i+j**。

## 8. 赛后五维复盘

每人对每道未满分题填写：

| 题号 | 读题误差 | 复杂度误判 | 边界漏判 | 实现 bug | 调试耗时(min) | 归因一句话 |
|---|---|---|---|---|---:|---|
| T1 |  |  |  |  |  |  |
| T2 |  |  |  |  |  |  |
| T3 |  |  |  |  |  |  |
| T4 |  |  |  |  |  |  |
| T5 |  |  |  |  |  |  |
| T6 |  |  |  |  |  |  |

教师汇总后按五维统计全班分布，作为 Day8-Day13 晚间保温的调整依据。当天必须完成未 AC 题重写（对照 §0.3 规则）。

## 9. 本卷与前期知识对照

| 赛位 | 核心模型 | 知识来源 |
|---|---|---|
| T1 2036C | 局部窗口重算 | Day1 字符串扫描 |
| T2 1996C | 26 字母前缀计数 | Day1 前缀和 |
| T3 1905C | 后缀最大值链 + 构造验证 | Day3 贪心观察 + Day1 扫描 |
| T4 2233C | 栈匹配 + 删除构造（多解输出） | Day2 括号栈 |
| T5 2222C | ±1 符号化 + 奇数段线性 DP | Day5 前缀性质 + Day6 线性 DP |
| T6 2050E | 双串交织二维 DP | Day6 状态定义四问 |

六题全部为未练过的新题；讲评后各题模型卡按上表归档。
