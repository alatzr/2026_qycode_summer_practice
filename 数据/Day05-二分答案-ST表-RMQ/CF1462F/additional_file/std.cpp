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
