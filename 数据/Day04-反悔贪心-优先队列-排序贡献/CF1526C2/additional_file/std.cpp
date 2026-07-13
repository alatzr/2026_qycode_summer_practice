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
