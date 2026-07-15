# CF923B Producing Snow 题解

**题目大意：** 第 $i$ 天造体积 $volume[i]$ 的雪堆，每天所有存活雪堆各融 $temp[day]$，求每天总融化量。

**思路：** 按堆独立结算。温度前缀和 $prefTemp$，对每堆二分其融完日 $pos$；用差分维护"当天按整温度融化的堆数"，融完当天单独加零头 $volume[i]-(prefTemp[pos-1]-prefTemp[i-1])$。逐天 $当天融化量 = 活跃堆数 \times temp[day] + partial[day]$。

**复杂度：** $O(n\log n)$。注意全程 long long。
