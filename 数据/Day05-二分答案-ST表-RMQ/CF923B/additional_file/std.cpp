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
