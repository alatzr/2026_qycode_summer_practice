# Day 5 教师讲义：二分答案、ST 表与静态区间查询（RMQ）

适用班级：已经掌握排序、前缀和（Day1）和基础贪心（Day3/Day4），开始接触"多次查询"和"答案具有单调性"的学生。

课时定位：Day5 是"查询与判定"课，学生今天要拿到两件新武器：

1. **二分**：Day3 讲 1760F 时预告过"答案单调就能二分"，今天正式系统化——从 `lower_bound` 定位，到自己写 `check` 的二分答案。
2. **ST 表**：本期集训的**静态区间查询标准工具**。区间最大值、区间 GCD 全部用它，后面 Day20（动态结构）、Day25（二分综合）都会回头引用今天的模板。

本讲义不使用线段树：静态不修改的区间查询，ST 表更短、更快、更不容易写错；动态修改的需求等 Day20 的 set/map，线段树留给学有余力的学生自学。

配套题单（按下午训练顺序排列）：

|  顺序 | 题号    | 题目                                   | rating | 本课对应知识点              | 教学目标               |
| --: | ----- | ------------------------------------ | -----: | -------------------- | ------------------ |
|   1 | 474B  | Worms                                |   1200 | 前缀和、`lower_bound` 定位 | 学会在前缀和上找第一个 `>= x` |
|   2 | 600B  | Queries about less or equal elements |   1300 | 排序、`upper_bound` 计数  | 学会用 STL 处理排名查询     |
|   3 | 923B  | Producing Snow                       |   1600 | 前缀和、二分完成日、差分结算       | 学会把逐天过程离线成"每堆独立结算" |
|   4 | 1709D | Rorororobot                          |   1700 | ST 表区间最大值、同余可达       | 学会把路径障碍转成区间最大值查询   |
|   5 | 1548B | Integers Have Friends                |   1800 | 相邻差分、区间 GCD ST 表、双指针 | 学会"同余转差分"的建模套路     |
|   6 | 1462F | The Treasure of The Segments         |   1800 | 排序 + 两次二分统计          | 学会统计与某区间不相交的数量     |
|  选做 | 1691D | Max GEQ Sum                          |   1800 | 单调栈 + 前缀和 ST 表       | 假期包学完单调栈后回做        |

## 0. 课堂安排

上午 3 小时讲解 + 下午 3.5 小时训练。

### 0.1 上午讲解（180 分钟）

| 时间 | 内容 | 教师重点 |
|---:|---|---|
| 0-10 分钟 | 开场：两个数据范围信号 | `n,q <= 2e5` 出现"多次询问"就想预处理 |
| 10-35 分钟 | 二分答案系统课 | 单调性判断、两个模板、check 三问 |
| 35-50 分钟 | 474B 前缀和 + `lower_bound` | 二分的第一种形态：有序数组定位 |
| 50-65 分钟 | 600B 排序 + `upper_bound` | `lower_bound`/`upper_bound` 差别 |
| 65-90 分钟 | 923B 二分完成日 + 差分结算 | "每堆雪独立"这步转化是关键 |
| 90-95 分钟 | 休息 | |
| 95-125 分钟 | ST 表系统课：倍增、build、query | n=8 手动模拟表必须带学生填 |
| 125-135 分钟 | ST 表维护 min/gcd；与线段树差异表 | 口诀"静态不改用 ST 表" |
| 135-155 分钟 | 1709D 区间最大值 + 同余爬高 | 贪心"爬到最高再横移"的证明 |
| 155-170 分钟 | 1548B 建模引导 | 只讲"同余转差分 + 区间 GCD"，代码下午写 |
| 170-180 分钟 | 1462F 拆解提示 + 训练要求 | "枚举保留谁 + 数不相交"两句话点到 |

板书主线建议：

```text
问很多次 -> 预处理一次
有序才能二分：数组有序（lower_bound）/ 判定单调（二分答案）
区间 max/gcd 不会变 -> ST 表：build O(n log n)，query O(1)
建模题套路：原数组不好查 -> 造一个新数组（前缀和/差分）再查
```

### 0.2 下午训练映射（210 分钟）

| 时间 | 题目 | 训练要求 |
|---:|---|---|
| 0-20 分钟 | 474B | 独立完成，禁止看讲义模板 |
| 20-45 分钟 | 600B | 要求一次通过编译 |
| 45-85 分钟 | 923B | 卡住 20 分钟可看讲义"手动模拟"小节 |
| 85-125 分钟 | 1709D | 重点：ST 表模板默写落地 |
| 125-170 分钟 | 1548B | 上午只讲了建模，正解自己拼装 |
| 170-210 分钟 | 1462F + 补模型卡 | 每题 4 行模型卡（模型/关键变量/易错） |

### 0.3 训练顺序与预计用时

| 顺序 | 题号 | rating | 预计用时 | 练什么 |
|---:|---|---:|---:|---|
| 1 | 474B | 1200 | 15-20 分钟 | `lower_bound` 上手 |
| 2 | 600B | 1300 | 20 分钟 | `upper_bound` 计数 |
| 3 | 923B | 1600 | 35-40 分钟 | 二分 + 差分组合 |
| 4 | 1709D | 1700 | 40 分钟 | ST 表 max 第一次实战 |
| 5 | 1548B | 1800 | 40-45 分钟 | ST 表 gcd + 双指针 |
| 6 | 1462F | 1800 | 35-40 分钟 | 排序 + 两次二分 |

选做 1691D 不安排在今天：需要单调栈（假期包 B 模块 7/28 讲），学完回做，见 §9。

## 1. 二分答案系统课

### 1.1 二分的两种形态

学生先分清楚今天会遇到的两种二分：

| 形态 | 在哪里二分 | 前提 | 今天的题 |
|---|---|---|---|
| 二分查找 | 有序数组里找位置 | 数组有序 | 474B、600B、923B、1462F |
| 二分答案 | 答案范围里猜答案 | 判定函数单调 | Day25/Day27 大量出现，今天先背熟框架 |

两种形态本质相同：**把"求答案"变成"判定一个候选值行不行"，再利用单调性砍一半**。

### 1.2 能二分答案的前提：单调性

不是所有题都能二分。能二分答案至少要满足：

```text
如果 x 可行，那么比 x 更小/更大的一侧也全部可行。
```

写二分前先写两句话：

```text
check(x)：x 是否可行？
单调方向：x 越大越容易，还是越难？
```

### 1.3 最小可行值模板

求"最小的可行 x"（x 越大越容易满足）：

```cpp
int lo = 0, hi = INF, ans = INF;
while(lo <= hi){
    int mid = lo + (hi - lo) / 2;
    if(check(mid)){
        ans = mid;
        hi = mid - 1;   // 可行，尝试更小
    }else{
        lo = mid + 1;
    }
}
```

### 1.4 最大可行值模板

求"最大的可行 x"（x 越小越容易满足）：

```cpp
int lo = 0, hi = INF, ans = 0;
while(lo <= hi){
    int mid = lo + (hi - lo) / 2;
    if(check(mid)){
        ans = mid;
        lo = mid + 1;   // 可行，尝试更大
    }else{
        hi = mid - 1;
    }
}
```

教师要求学生：模板可以背，但动笔前必须先写出 `check` 的含义和单调方向。`INF` 换成题目给的答案上界。

### 1.5 lower_bound 与 upper_bound

STL 的两个函数就是封装好的二分查找（数组必须先有序）：

| 函数 | 返回位置 | 可求什么 |
|---|---|---|
| `lower_bound(first, last, x)` | 第一个 `>= x` | 小于 `x` 的个数；第一个达到 `x` 的位置 |
| `upper_bound(first, last, x)` | 第一个 `> x` | 小于等于 `x` 的个数 |

两个都可能返回 `last`（全都比 `x` 小），用之前要想清楚这种情况是否合法。

### 1.6 二分易错三条

- `mid = (lo + hi) / 2` 在 `lo + hi` 超过 `int` 上限时溢出，写 `lo + (hi - lo) / 2`。
- 循环条件 `lo <= hi` 配 `mid - 1`/`mid + 1` 收缩；漏了 `±1` 会死循环。
- `lower_bound` 返回的是迭代器/指针，转下标要减起点。

## 2. ST 表系统课：静态区间查询的标准工具

### 2.1 问题引入：为什么前缀和救不了区间最大值

有数组 `val[1..n]`，`q` 次询问区间 `[l,r]` 的最大值，`n,q <= 2e5`。

- 暴力：每次扫一遍，`O(nq) = 4e10`，超时。
- 前缀和：`max` 没有减法！知道 `[1,r]` 的最大值和 `[1,l-1]` 的最大值，推不出 `[l,r]` 的最大值。

区间和能用前缀和是因为"和"可以做减法拆区间；`max`、`gcd` 拆不了，需要新工具。

### 2.2 倍增思想：只打 2 的幂长度的表

ST 表（Sparse Table，稀疏表）的想法：

```text
不给每个区间都存答案（区间有 n^2 个，存不下），
只给"长度恰好是 2^j"的区间存答案（只有 n log n 个）。
任何区间 [l,r] 都能用两个 2^k 长的区间"从左、从右"盖住。
```

盖住时中间可能重叠。关键性质：

```text
max(x, x) = x，重复算一个数不影响最大值。
```

这类"重复贡献不影响答案"的信息（max/min/gcd）才能用 ST 表，区间和不行（重叠部分会被加两次）。

### 2.3 定义与递推：build O(n log n)

定义：

```text
stMax[j][i] = 从 i 开始、长度为 2^j 的区间 [i, i + 2^j - 1] 的最大值
```

第 0 层就是原数组：`stMax[0][i] = val[i]`。

长度 `2^j` 的区间劈成两半，每半长 `2^(j-1)`：

```text
stMax[j][i] = max(stMax[j-1][i], stMax[j-1][i + 2^(j-1)])
```

```text
[i ................. i+2^j-1]
[i ... i+2^(j-1)-1][i+2^(j-1) ... i+2^j-1]
      前一半               后一半
```

层数 `j` 最多 `log2(n)` 层，每层 `O(n)`，总预处理 `O(n log n)`。

### 2.4 查询 O(1)：两块重叠覆盖

查询 `[l,r]`，令 `len = r - l + 1`，取 `k` 为满足 `2^k <= len` 的最大整数：

```text
块一：[l, l + 2^k - 1]          从左边盖
块二：[r - 2^k + 1, r]          从右边盖
两块并起来正好盖满 [l,r]，中间重叠不影响 max
```

```cpp
int queryMax(int l, int r){
    int k = lg2v[r - l + 1];
    return max(stMax[k][l], stMax[k][r - (1 << k) + 1]);
}
```

`lg2v[len]` 表示 `len` 的对数下取整，预处理递推：`lg2v[i] = lg2v[i / 2] + 1`，避免每次调 `log2()` 的精度和速度问题。

### 2.5 手动模拟：n = 8

数组：

```text
下标 i： 1 2 3 4 5 6 7 8
val：   3 1 4 1 5 9 2 6
```

带学生把整张表填出来（`—` 表示越界不存在）：

| i | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| `stMax[0][i]`（长 1） | 3 | 1 | 4 | 1 | 5 | 9 | 2 | 6 |
| `stMax[1][i]`（长 2） | 3 | 4 | 4 | 5 | 9 | 9 | 6 | — |
| `stMax[2][i]`（长 4） | 4 | 5 | 9 | 9 | 9 | — | — | — |
| `stMax[3][i]`（长 8） | 9 | — | — | — | — | — | — | — |

抽两行验证递推：`stMax[1][5] = max(val[5], val[6]) = max(5,9) = 9`；`stMax[2][3] = max(stMax[1][3], stMax[1][5]) = max(4,9) = 9`。

再做三次查询：

| 查询 | len | k | 块一 | 块二 | 答案 |
|---|---:|---:|---|---|---:|
| `[2,5]` | 4 | 2 | `stMax[2][2]=5` | `stMax[2][2]=5`（两块重合） | 5 |
| `[4,7]` | 4 | 2 | `stMax[2][4]=9` | `stMax[2][4]=9` | 9 |
| `[3,8]` | 6 | 2 | `stMax[2][3]=9`（盖 `[3,6]`） | `stMax[2][5]=9`（盖 `[5,8]`） | 9 |

`[3,8]` 的两块重叠了 `[5,6]`，元素 5、9 被看了两遍——对 `max` 没有任何影响。这就是 2.2 说的"可重复贡献"。

### 2.6 ST 表能维护什么

| 信息 | 能否用 ST 表 | 原因 |
|---|---|---|
| 区间最大值 max | 能 | `max(x,x)=x`，重复无影响 |
| 区间最小值 min | 能 | 同上，把 `max` 全换成 `min` |
| 区间 GCD | 能 | `gcd(x,x)=x`，重复无影响 |
| 区间和 sum | 不能 | 重叠部分会被加两次；且区间和用前缀和就够了 |

换信息只改两处：递推式里的 `max` 和查询里的 `max`。1548B 就是把 `max` 换成 `__gcd` 的 ST 表。

### 2.7 与线段树的分工

| 对比项 | ST 表 | 线段树 |
|---|---|---|
| 预处理 | `O(n log n)` | `O(n)` 建树 |
| 单次查询 | `O(1)` | `O(log n)` |
| 支持修改 | 不支持 | 支持单点/区间修改 |
| 可维护信息 | 可重复贡献类（max/min/gcd） | 几乎所有可合并信息（含区间和） |
| 代码量 | 约 15 行 | 约 60 行起步 |

给学生的选择口诀：

```text
静态不改用 ST 表；动态修改等 Day20 的 set/map，线段树自学选学。
```

本期集训所有静态区间查询一律 ST 表，不许为了"炫技"上线段树——考场上代码量就是出错率。

### 2.8 完整模板（可直接编译）

输入 `n` 和 `q`，第二行 `n` 个数，接下来 `q` 行每行 `l r` 查区间最大值：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
const int LOG = 18;

int stMax[LOG][N];   // stMax[j][i]：从 i 开始、长度为 2^j 的区间最大值
int lg2v[N];         // lg2v[len]：不超过 len 的最大 2 的幂的指数
int n, q;

void buildST(){
    for(int i = 2; i <= n; i++) lg2v[i] = lg2v[i / 2] + 1;
    for(int j = 1; (1 << j) <= n; j++)
        for(int i = 1; i + (1 << j) - 1 <= n; i++)
            stMax[j][i] = max(stMax[j - 1][i], stMax[j - 1][i + (1 << (j - 1))]);
}

int queryMax(int l, int r){
    int k = lg2v[r - l + 1];
    // 两块 2^k 区间从左右盖住 [l,r]，中间重叠不影响最大值
    return max(stMax[k][l], stMax[k][r - (1 << k) + 1]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> stMax[0][i];   // 第 0 层就是原数组
    buildST();
    while(q--){
        int l, r;
        cin >> l >> r;
        cout << queryMax(l, r) << '\n';
    }
    return 0;
}
```

注意两个实现细节：

- 数组开 `stMax[LOG][N]` 而不是 `stMax[N][LOG]`：同一层 `j` 在内存里连续，build 时缓存更友好。
- `LOG = 18` 够 `n = 2e5`（`2^18 = 262144`）；`n` 上限变了要跟着改。

### 2.9 复杂度对照

| 方法 | 预处理 | 单次查询 | `n,q = 2e5` 总量 |
|---|---:|---:|---:|
| 暴力扫描 | 无 | `O(n)` | `4e10`，超时 |
| ST 表 | `O(n log n)` | `O(1)` | 约 `4e6`，稳过 |

## 3. 474B Worms（1200）：前缀和上的二分定位

**题意：** `n` 堆虫子排成一排，第 `i` 堆有 `cnt[i]` 条。所有虫子从第 1 堆开始连续编号（第 1 堆是 `1..cnt[1]`，第 2 堆接着往后编，以此类推）。`m` 次询问：编号为 `x` 的虫子在第几堆？`n,m <= 1e5`，虫子总数不超过 `1e6`。

### 3.1 题型定位

CSP 初赛/复赛第一题级别的"多次查询定位题"。信号：编号连续 + 问归属，等价于"在前缀和数组里找第一个 `>= x` 的位置"。

### 3.2 暴力与部分分

每次询问从第 1 堆开始累加，直到累加和 `>= x`。单次 `O(n)`，总 `O(nm) = 1e10`，超时。

另一条暴力思路反而能过：虫子总数 `<= 1e6`，直接开一个 `owner[1..1e6]` 桶，预处理每个编号属于哪堆，查询 `O(1)`。这提醒学生：**看数据范围，值域小的时候桶也是正解**。

### 3.3 正解升级

前缀和 `prefix[i] = cnt[1] + ... + cnt[i]` 单调不降。编号 `x` 属于第一个满足 `prefix[i] >= x` 的堆 `i`，正是 `lower_bound` 的定义。

手动模拟（官方样例）：

```text
cnt：    2 7 3 4 9
prefix： 2 9 12 16 25
询问 x=1：第一个 >=1 的是 prefix[1]=2  -> 第 1 堆
询问 x=25：第一个 >=25 的是 prefix[5]=25 -> 第 5 堆
询问 x=11：第一个 >=11 的是 prefix[3]=12 -> 第 3 堆
```

### 3.4 完整参考程序

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int pileCnt;
    cin >> pileCnt;
    vector<long long> prefix(pileCnt + 1, 0);
    for(int i = 1; i <= pileCnt; i++){
        long long worms;
        cin >> worms;
        prefix[i] = prefix[i - 1] + worms;   // prefix[i] = 前 i 堆的编号上界
    }
    int queryCnt;
    cin >> queryCnt;
    while(queryCnt--){
        long long label;
        cin >> label;
        // 第一个前缀和 >= label 的堆就是答案
        int pos = lower_bound(prefix.begin() + 1, prefix.end(), label) - prefix.begin();
        cout << pos << '\n';
    }
    return 0;
}
```

**复杂度：** 预处理 `O(n)`，每次查询 `O(log n)`。

### 3.5 赛场策略与易错点

- 卡住时先写桶版本保底，再换二分——两个都是满分做法，选自己不会写错的。
- `lower_bound` 的搜索范围从 `prefix.begin() + 1` 开始：`prefix[0]=0` 不是合法的堆。
- 询问保证不超过虫子总数，所以不用处理"找不到"；换题时这个检查不能省。

## 4. 600B（1300）：排序后 upper_bound 计数

**题意：** 给数组 `nums`（`n` 个数），再给 `m` 次询问，每次给一个值 `x`，回答 `nums` 中有多少个数 `<= x`。`n,m <= 2e5`，值域 `±1e9`。

### 4.1 题型定位

排名/计数查询裸题。信号："有多少个数不超过 x"——排序后一次 `upper_bound` 解决。这也是 Day1 复杂度课的标准复盘：`O(nm)` 不行，`O((n+m) log n)` 行。

### 4.2 暴力与部分分

每次询问扫全数组计数，`O(nm) = 4e10`，超时。

### 4.3 正解升级

把 `nums` 排序。`upper_bound` 返回第一个 `> x` 的位置，它前面的元素个数正好是 `<= x` 的数量。

手动模拟（官方样例 1）：

```text
排序后 nums：1 3 5 7 9
询问 6：第一个 >6 是 7（下标 3，0 下标），答案 3
询问 4：第一个 >4 是 5（下标 2），答案 2
```

注意：查询本身不能排序（要按输入顺序输出），只排被查的数组。

### 4.4 完整参考程序

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> nums(n);
    for(int i = 0; i < n; i++) cin >> nums[i];
    sort(nums.begin(), nums.end());
    for(int j = 0; j < m; j++){
        int limit;
        cin >> limit;
        // 第一个 > limit 的下标 = <= limit 的元素个数
        int cnt = upper_bound(nums.begin(), nums.end(), limit) - nums.begin();
        cout << cnt << " \n"[j == m - 1];
    }
    return 0;
}
```

**复杂度：** 排序 `O(n log n)`，每次查询 `O(log n)`。

### 4.5 赛场策略与易错点

- 分不清 `lower_bound`/`upper_bound` 时，回到 §1.5 的表：求 `<= x` 个数必须用 `upper_bound`，用错在"查询值恰好等于数组元素"时会少数。
- 想不起 STL 时，双指针离线做法也行：把询问带编号排序，和 `nums` 一起从小到大双指针推进，`O((n+m) log m)`。
- 本题 0 下标（`vector` + 迭代器减法直接得个数），和 474B 的 1 下标写法对比讲一句。

## 5. 923B Producing Snow（1600）：二分完成日 + 差分结算

**题意：** 共 `n` 天。第 `i` 天早上造一堆体积 `volume[i]` 的雪；每天所有还存在的雪堆各融化 `temp[day]`（当天温度），体积降到 `0` 或以下就消失。当天造的雪堆当天也参与融化。求每天所有雪堆融化量的总和。`n <= 1e5`，`volume[i], temp[i] <= 1e9`。

### 5.1 题型定位

CSP 复赛 T2 级别的"过程离线统计"题。直接按天模拟所有雪堆是 `O(n^2)`；要换视角：**不按天算，按堆算**——每堆雪独立，问它哪天融完。

### 5.2 暴力与部分分

维护所有活着的雪堆，每天逐堆减温度、删掉融完的。最坏每天都有堆活着，`O(n^2) = 1e10`，超时。考场上这个暴力值得先写：既是部分分，又是对拍标准。

### 5.3 正解升级

三步转化，每步都要在黑板上写出来：

**第一步：温度前缀和。** `prefTemp[i] = temp[1] + ... + temp[i]`。第 `i` 天到第 `pos` 天总共融掉 `prefTemp[pos] - prefTemp[i-1]`。

**第二步：二分完成日。** 第 `i` 天的雪堆在第 `pos` 天融完，`pos` 是第一个满足：

```text
prefTemp[pos] - prefTemp[i-1] >= volume[i]
```

的位置。`temp >= 0` 保证 `prefTemp` 单调不降，`lower_bound` 直接找（找不到说明到第 `n` 天还没融完）。

**第三步：差分结算贡献。** 这堆雪对每天融化量的贡献分两类：

- 第 `i .. pos-1` 天：完整贡献当天温度 `temp[day]`；
- 第 `pos` 天：只贡献剩余零头 `volume[i] - (prefTemp[pos-1] - prefTemp[i-1])`。

"完整贡献温度"的堆数用差分数组 `fullDelta` 维护（`fullDelta[i]++`，`fullDelta[pos]--`），零头单独累加到 `partial[pos]`。最后按天扫描：

```text
当天融化量 = 活跃堆数 * temp[day] + partial[day]
```

### 5.4 手动模拟（官方样例 1）

```text
volume：10 10 5    temp：5 7 2    prefTemp：5 12 14
```

| 雪堆 | 产生日 | 体积 | 完成日 pos | 完整贡献区间 | 零头 |
|---:|---:|---:|---|---|---|
| 1 | 1 | 10 | 2（`prefTemp[2]=12 >= 10`） | 第 1 天 | 第 2 天贡献 `10-5=5` |
| 2 | 2 | 10 | 没融完（需要 `>= 15`，`prefTemp[3]=14`） | 第 2-3 天 | 无 |
| 3 | 3 | 5 | 没融完（需要 `>= 17`） | 第 3 天 | 无 |

| 天 | 活跃堆数 | 当天融化量 |
|---:|---:|---|
| 1 | 1 | `1*5 + 0 = 5` |
| 2 | 1 | `1*7 + 5 = 12` |
| 3 | 2 | `2*2 + 0 = 4` |

输出 `5 12 4`，与样例一致。

### 5.5 完整参考程序

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int days;
    cin >> days;
    vector<long long> volume(days + 1), temp(days + 1), prefTemp(days + 1, 0);
    for(int i = 1; i <= days; i++) cin >> volume[i];
    for(int i = 1; i <= days; i++) cin >> temp[i];
    for(int i = 1; i <= days; i++) prefTemp[i] = prefTemp[i - 1] + temp[i];

    // fullDelta：差分维护“今天按整温度融化”的雪堆数；partial：融完当天的零头
    vector<long long> fullDelta(days + 2, 0), partial(days + 2, 0);
    for(int i = 1; i <= days; i++){
        // 找最早的 pos，使 i..pos 的温度和 >= volume[i]，即这堆雪在第 pos 天融完
        long long need = prefTemp[i - 1] + volume[i];
        int pos = lower_bound(prefTemp.begin() + i, prefTemp.end(), need) - prefTemp.begin();
        if(pos > days){
            fullDelta[i]++;              // 到最后一天都没融完，每天都贡献整温度
            fullDelta[days + 1]--;
        }else{
            fullDelta[i]++;              // i..pos-1 每天贡献整温度
            fullDelta[pos]--;
            partial[pos] += volume[i] - (prefTemp[pos - 1] - prefTemp[i - 1]);
        }
    }
    long long active = 0;
    for(int day = 1; day <= days; day++){
        active += fullDelta[day];
        long long melted = active * temp[day] + partial[day];
        cout << melted << " \n"[day == days];
    }
    return 0;
}
```

**复杂度：** `O(n log n)`。

### 5.6 赛场策略与易错点

- 想不到差分时退一步：对每堆雪二分出 `pos` 后，用两个树状"区间加"也行——但今天只学了差分，差分就够。
- `volume`、`prefTemp` 都要 `long long`：`1e5` 个 `1e9` 相加到 `1e14`；`active * temp[day]` 也到 `1e14`。
- `lower_bound` 的搜索起点是 `prefTemp.begin() + i`：这堆雪从第 `i` 天才开始融，从头找会找到更早的假位置。
- `volume[i] = 0` 的堆当天消失、贡献 0，公式里自动成立（零头算出来是 0），不需要特判——让学生代入验证一次。
- 零头只在融完当天加一次，别把 `pos` 那天也算进 `fullDelta`。

## 6. 1709D Rorororobot（1700）：ST 表区间最大值 + 同余爬高

**题意：** `n` 行 `m` 列网格，行从下往上编号 `1..n`，第 `i` 列**底部** `height[i]` 个格子是障碍（第 `1..height[i]` 行），上方全空。机器人坏了：每收到一条指令（上/下/左/右），会连续执行 `k` 步（走 `k` 格），路径中撞障碍或出界就爆炸。`q` 次询问：起点 `(xs,ys)`、终点 `(xf,yf)`、步长 `k`，机器人能否恰好停在终点？`n <= 1e9`，`m,q <= 2e5`。

### 6.1 题型定位

CSP 复赛 T2/T3 常见的"结论 + 数据结构验证"题：先用数学结论把"能否走到"压缩成两三个条件，其中一个条件是**区间最大值查询**——今天 ST 表的第一次实战。注意 `n` 到 `1e9`，任何"按格子搜索"的想法直接排除。

### 6.2 暴力与部分分

把每个格子当节点 BFS：状态数 `n*m` 到 `2e14`，不可行。小数据（`n,m <= 100`）可以写 BFS 对拍验证结论，这是赛场检验结论题的标准手段。

### 6.3 正解升级

每步移动量固定是 `k`，所以坐标模 `k` 的余数永远不变，得到必要条件一、二：

```text
|xs - xf| % k == 0 且 |ys - yf| % k == 0
```

若 `ys == yf`（同一列）：障碍只在列底部，起终点都在障碍上方，之间的格子全空，直接可达（配合条件一）。

若不同列，机器人要横穿 `[min(ys,yf), max(ys,yf)]` 这些列。贪心结论：**先爬到能到的最高行再横移，一定不亏**——障碍全在底部，走得越高越不可能撞。与 `xs` 同余、且不超过 `n` 的最高行是：

```text
topRow = xs + (n - xs) / k * k
```

横穿要求 `topRow` 这一行在沿途每一列都是空格，即：

```text
topRow > max(height[l..r])    （第 height[i] 行是障碍，必须严格大于）
```

区间最大值静态、不修改、查 `2e5` 次——ST 表 `O(1)` 查询。到达终点列后往下走到 `xf`：`topRow ≡ xs ≡ xf (mod k)`，且沿途都在该列障碍上方，畅通。

### 6.4 手动模拟（官方样例第 4、5 组询问）

```text
n=11 行，m=10 列，height：9 0 0 10 3 4 8 11 10 8
询问：xs=5, ys=3, xf=11, yf=5
```

| 步长 | 条件一 `|5-11|%k` | 条件二 `|3-5|%k` | topRow | `max(height[3..5])` | 结论 |
|---:|---|---|---:|---:|---|
| `k=3` | `6%3=0` 过 | `2%3=2` 不过 | — | — | NO |
| `k=2` | `6%2=0` 过 | `2%2=0` 过 | `5+(11-5)/2*2=11` | `max(0,10,3)=10` | `11>10`，YES |

`k=2` 时机器人从第 5 行爬到第 11 行（顶行），横穿第 4 列顶上只剩一行空隙（障碍高 10），刚好过去。

### 6.5 完整参考程序

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
const int LOG = 18;

int stMax[LOG][N];   // stMax[j][i]：从 i 开始长 2^j 的区间最大障碍高度
int lg2v[N];
int colCnt;

void buildST(){
    for(int i = 2; i <= colCnt; i++) lg2v[i] = lg2v[i / 2] + 1;
    for(int j = 1; (1 << j) <= colCnt; j++)
        for(int i = 1; i + (1 << j) - 1 <= colCnt; i++)
            stMax[j][i] = max(stMax[j - 1][i], stMax[j - 1][i + (1 << (j - 1))]);
}

int queryMax(int lcol, int rcol){
    int k = lg2v[rcol - lcol + 1];
    return max(stMax[k][lcol], stMax[k][rcol - (1 << k) + 1]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long rowCnt;
    cin >> rowCnt >> colCnt;
    for(int i = 1; i <= colCnt; i++) cin >> stMax[0][i];
    buildST();
    int queryCnt;
    cin >> queryCnt;
    while(queryCnt--){
        long long xs, ys, xf, yf, k;
        cin >> xs >> ys >> xf >> yf >> k;
        // 行差、列差都必须是 k 的倍数
        if(abs(xs - xf) % k != 0 || abs(ys - yf) % k != 0){
            cout << "NO\n";
            continue;
        }
        if(ys == yf){                    // 同一列：中间格子全部空，直接可达
            cout << "YES\n";
            continue;
        }
        // 与 xs 同余、且不超过 rowCnt 的最高行
        long long topRow = xs + (rowCnt - xs) / k * k;
        int highest = queryMax(min(ys, yf), max(ys, yf));
        cout << (topRow > highest ? "YES" : "NO") << '\n';
    }
    return 0;
}
```

**复杂度：** 预处理 `O(m log m)`，每次询问 `O(1)`。

### 6.6 赛场策略与易错点

- 忘了 ST 表时的保底方案：分块，块内存最大值，单次查询 `O(sqrt(m))`，总量约 `9e7`，勉强能过——但今天必须练 ST 表。
- `topRow > highest` 是**严格大于**：障碍占第 `1..height[i]` 行，行号等于障碍高度时正撞上。
- 同列（`ys == yf`）要在查 ST 表之前特判，否则区间长度没问题但逻辑上"横穿"不存在。
- 查询区间要 `min/max` 整理端点：起点列可能在终点列右边。
- `n` 到 `1e9`，`topRow` 用 `long long` 算最稳（本题 `int` 恰好不溢出，但不要赌）。

## 7. 1548B Integers Have Friends（1800）：差分 + 区间 GCD ST 表 + 双指针

**题意：** 给一个互不相同的正整数数组 `val[1..n]`（`val[i]` 到 `1e18`）。称一段连续子数组是"朋友组"，如果存在某个模数 `m >= 2`，使子数组内所有数模 `m` 同余。求最长朋友组的长度。多组数据，`n` 总和 `<= 2e5`。

### 7.1 题型定位

今天的压轴建模题：表面看不出任何区间查询，考"同余转差分"这步翻译。CSP 复赛 T3 常见套路——**原数组不好查，就造一个新数组来查**（Day1 前缀和、今天差分，都是这个思想）。

### 7.2 暴力与部分分

枚举区间 `O(n^2)` 个，每个区间还要判定"是否存在 m>=2"——直接做连判定都不会。暴力只能对 `n <= 100` 级别的小数据枚举 m 试除，用来对拍。

### 7.3 正解升级：同余转差分

**第一步（关键翻译）：** `x ≡ y (mod m)` 等价于 `m` 整除 `x - y`。区间内所有数两两同余，等价于所有**相邻差**都被 `m` 整除，等价于：

```text
m 整除 gcd(所有相邻差的绝对值)
```

存在 `m >= 2` 等价于这个 GCD `>= 2`（即 `> 1`）。

**第二步：** 造差分数组 `diff[i] = |val[i+1] - val[i]|`（共 `n-1` 项），问题变成：

```text
在 diff 上找最长的窗口 [left, right]，使 gcd(diff[left..right]) > 1；
答案 = 窗口长 + 1（差分窗口两端对应原数组多一个数）。
```

单独一个数永远是朋友组（`m` 随便取），所以答案至少是 1。

**第三步：区间 GCD 用 ST 表**（把模板里的 `max` 换成 `__gcd`），**最长窗口用双指针**：

- 窗口越大 GCD 越小（多一个数只会让 GCD 变小或不变）；
- 右端点右移后，原来不行的左端点仍然不行——`left` 永不回退，标准双指针成立。

也可以对每个左端点二分最远右端点（GCD 随右端点单调不增），复杂度多一个 `log`，同样能过；双指针更短。

### 7.4 手动模拟（官方样例第 4 组）

```text
val： 465 55 3 54 234 12 45 78
diff：410 52 51 180 222 33 33     （下标 1..7）
```

双指针过程（`gcd` 指当前窗口 `diff[left..right]` 的 GCD）：

| right | 窗口调整 | 最终窗口 | gcd | 原数组长度 | best |
|---:|---|---|---:|---:|---:|
| 1 | — | `[1,1]` | 410 | 2 | 2 |
| 2 | `gcd(410,52)=2`，不动 | `[1,2]` | 2 | 3 | 3 |
| 3 | `gcd=1`，left 推到 3 | `[3,3]` | 51 | 2 | 3 |
| 4 | `gcd(51,180)=3`，不动 | `[3,4]` | 3 | 3 | 3 |
| 5 | `gcd(3,222)=3` | `[3,5]` | 3 | 4 | 4 |
| 6 | `gcd(3,33)=3` | `[3,6]` | 3 | 5 | 5 |
| 7 | `gcd(3,33)=3` | `[3,7]` | 3 | 6 | 6 |

答案 6：原数组 `3 54 234 12 45 78` 全部模 3 同余（都是 3 的倍数），与官方答案一致。

### 7.5 完整参考程序

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
const int LOG = 18;

long long stGcd[LOG][N];   // stGcd[j][i]：差分数组从 i 开始长 2^j 的区间 GCD
int lg2v[N];
int diffCnt;

void buildST(){
    for(int j = 1; (1 << j) <= diffCnt; j++)
        for(int i = 1; i + (1 << j) - 1 <= diffCnt; i++)
            stGcd[j][i] = __gcd(stGcd[j - 1][i], stGcd[j - 1][i + (1 << (j - 1))]);
}

long long queryGcd(int lpos, int rpos){
    int k = lg2v[rpos - lpos + 1];
    return __gcd(stGcd[k][lpos], stGcd[k][rpos - (1 << k) + 1]);
}

void solve(){
    int n;
    cin >> n;
    vector<long long> val(n + 1);
    for(int i = 1; i <= n; i++) cin >> val[i];
    if(n == 1){
        cout << 1 << '\n';
        return;
    }
    diffCnt = n - 1;
    for(int i = 1; i <= diffCnt; i++)
        stGcd[0][i] = llabs(val[i + 1] - val[i]);   // 相邻差的绝对值
    buildST();

    // 双指针：找差分数组上 GCD > 1 的最长窗口
    int best = 1, left = 1;
    for(int right = 1; right <= diffCnt; right++){
        while(left <= right && queryGcd(left, right) == 1) left++;
        if(left <= right) best = max(best, right - left + 2);   // 差分窗口长 +1 = 原数组长度
    }
    cout << best << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for(int i = 2; i < N; i++) lg2v[i] = lg2v[i / 2] + 1;
    int T;
    cin >> T;
    while(T--) solve();
    return 0;
}
```

**复杂度：** 每组数据 build `O(n log n)`（乘一个 gcd 的小常数），双指针总查询 `O(n)` 次、每次 `O(1)` 级别，稳过。

### 7.6 赛场策略与易错点

- 建模卡住时的自救提问："同余能翻译成整除吗？整除能落到什么数组上？"——把 §7.3 第一步背成台词。
- `val[i]` 到 `1e18`：全程 `long long`，取绝对值用 `llabs`（`abs` 对 `long long` 在部分编译器上会截断）。
- `n = 1` 要特判输出 1，否则差分数组为空，build/查询越界。
- 答案是"差分窗口长度 + 1"，最常见的错是直接输出窗口长。
- 多测：ST 表按当前 `diffCnt` 重建即可，build/query 的循环边界保证不会读到上组残留，不需要 `memset`（`memset` 反而可能把复杂度拖成 `O(T * N log N)`）。
- `gcd(0,x)=x`，所以 `__gcd` 累计时用 0 当初始值是安全的（本题相邻数互不相同，差分不会是 0）。

## 8. 1462F The Treasure of The Segments（1800）：排序 + 两次二分

**题意：** 给 `n` 条线段 `[l_i, r_i]`。希望剩下的线段中存在一条"核心"线段，它与其余每条都相交（有公共点即可）。求最少删除多少条线段。多组数据，`n` 总和 `<= 2e5`。

### 8.1 题型定位

"枚举 + 快速统计"题，CSP 复赛 T2 常见结构。关键转化：**枚举谁当核心**，那么必须删掉的恰好是与它不相交的线段——问题变成"数不相交"，而不相交只有两种姿势。

### 8.2 暴力与部分分

枚举核心线段，再逐条判断相交：`O(n^2) = 4e10`，超时，但作为对拍暴力 10 分钟内能写完。

### 8.3 正解升级

两条线段 `[l1,r1]` 和 `[l2,r2]` **不相交**，当且仅当一条完全在另一条左边：

```text
r2 < l1（对方整条在左）  或  l2 > r1（对方整条在右）
```

固定核心 `[segL, segR]`，要删的数量是：

```text
cntLeft  = 右端点 < segL 的线段数
cntRight = 左端点 > segR 的线段数
```

把所有左端点排成 `lefts`、所有右端点排成 `rights`（两个独立的有序数组），每次两个 `lower_bound`/`upper_bound` 就能数出来。核心自己不会被数进去（它的右端点 `>= segL`、左端点 `<= segR`），两类也不会重复（一条线段不可能同时在左边和右边）。对所有候选核心取最小值。

### 8.4 手动模拟（官方样例第 3 组）

```text
线段：[1,2] [3,8] [4,5] [6,7] [9,10]
lefts 排序： 1 3 4 6 9
rights 排序：2 5 7 8 10
```

| 核心 | `cntLeft`（r < segL） | `cntRight`（l > segR） | 删除数 |
|---|---:|---:|---:|
| `[1,2]` | 0 | 4（l=3,4,6,9） | 4 |
| `[3,8]` | 1（r=2） | 1（l=9） | 2 |
| `[4,5]` | 1（r=2） | 2（l=6,9） | 3 |
| `[6,7]` | 2（r=2,5） | 1（l=9） | 3 |
| `[9,10]` | 4（r=2,5,7,8） | 0 | 4 |

最小值 2（保留 `[3,8]` 当核心，删 `[1,2]` 和 `[9,10]`），与官方答案一致。第一行的 `cntRight` 是 4，因为四个左端点 `3,4,6,9` 都严格大于 2。

### 8.5 完整参考程序

```cpp
#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n;
    cin >> n;
    vector<int> lefts(n), rights(n);
    vector<pair<int,int>> segs(n);
    for(int i = 0; i < n; i++){
        cin >> segs[i].first >> segs[i].second;
        lefts[i] = segs[i].first;
        rights[i] = segs[i].second;
    }
    sort(lefts.begin(), lefts.end());
    sort(rights.begin(), rights.end());
    int best = INT_MAX;
    for(auto [segL, segR] : segs){
        // 完全在左边：右端点 < segL；完全在右边：左端点 > segR
        int cntLeft = lower_bound(rights.begin(), rights.end(), segL) - rights.begin();
        int cntRight = lefts.end() - upper_bound(lefts.begin(), lefts.end(), segR);
        best = min(best, cntLeft + cntRight);
    }
    cout << best << '\n';
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

**复杂度：** 每组 `O(n log n)`。

### 8.6 赛场策略与易错点

- 想不出"数不相交"就数"相交"再用 `n-1` 减——容斥方向反而更容易重复计数，讲清"不相交只有左右两种、互斥"这个优势。
- `cntLeft` 用 `lower_bound`（严格 `<`），`cntRight` 用 `upper_bound`（严格 `>`）：端点相等算相交（公共点也算），两处一旦用混就 WA。
- 多测别忘了每组重开 `vector`（本程序 `solve` 内定义，天然干净）。
- `t` 最多 `2e5` 组但 `n` 总和受限，读入用快读风格（`ios::sync_with_stdio(false)`）。

## 9. 选做 1691D Max GEQ Sum（1800）：思路提示

**题意：** 给数组（可有负数），判断是否对**所有**子数组都满足：子数组最大值 `>=` 子数组元素和。

**思路提示（不给代码）：**

1. 逐个元素思考：设 `val[i]` 是某个子数组的最大值，这个子数组必须落在 `val[i]` 的"管辖区间"内——即左右两侧第一个比它大的元素之间。求管辖区间的标准工具是**单调栈**（假期包 B 模块 7/28 讲）。
2. 管辖区间内、包含位置 `i` 的子数组中，和最大的那个：用前缀和 `pre[]` 表示，子数组和 = `pre[r] - pre[l-1]`，右端要 `pre[r]` 尽量大、左端要 `pre[l-1]` 尽量小——**前缀和数组上的区间 max/min 查询，正是今天的 ST 表**（建两张：一张 max、一张 min）。
3. 若某个 `i` 的"最坏子数组和"超过 `val[i]`，输出 NO。

回做时机：假期包学完单调栈后（8 月初），把这题当"单调栈 + ST 表"的合体检验。今天只要求看懂第 2 步为什么是 ST 表。

## 10. 本节易错清单

二分部分：

- 二分前必须确认单调性；`check` 含义先用中文写出来再写代码。
- `mid = lo + (hi - lo) / 2` 防溢出；`lo <= hi` 配 `mid ± 1` 防死循环。
- `lower_bound`/`upper_bound` 返回迭代器要减起点；可能返回 `end()`。
- 求 `<= x` 个数用 `upper_bound`，求第一个 `>= x` 用 `lower_bound`，用反在"恰好相等"的数据上出错。

ST 表部分：

- `stMax[0][i]` 忘了赋原数组值（build 只处理 `j >= 1`）。
- `lg2v` 递推从 `i = 2` 开始，`lg2v[1] = 0` 靠全局初始化保证。
- 查询第二块起点是 `r - (1 << k) + 1`，`+1` 最容易丢。
- `LOG` 要匹配数据范围：`2e5` 用 18，`1e6` 要 21。
- ST 表不支持修改——题目一旦出现"修改"，今天的工具不适用。

题目相关：

- 1709D：`topRow > highest` 严格大于；同列先特判；端点先 `min/max` 整理。
- 1548B：`long long` + `llabs`；`n=1` 特判；答案 = 差分窗口长 + 1；多测靠循环边界重建，不用 `memset`。
- 923B：三处 `long long`；`lower_bound` 起点是 `begin() + i`；零头只加一次。
- 1462F：端点相等算相交；`cntLeft`/`cntRight` 一个用 `lower_bound` 一个用 `upper_bound`。

## 11. 课堂小结

```text
定位题：前缀和 + lower_bound。          （474B）
计数题：排序 + upper_bound。            （600B）
完成日：前缀温度 + 二分 + 差分结算。      （923B）
障碍题：同余爬高 + ST 表区间 max。       （1709D）
同余题：相邻差分 + 区间 GCD + 双指针。    （1548B）
核心题：枚举保留谁 + 两次二分数不相交。   （1462F）
静态不改用 ST 表，动态修改等 Day20。
```
