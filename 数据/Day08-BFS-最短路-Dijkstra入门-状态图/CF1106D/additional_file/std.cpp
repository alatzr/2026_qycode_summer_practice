#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, m;
vector<int> graph[N];
bool vis[N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    priority_queue<int, vector<int>, greater<int>> heap;   // 小根堆：可达边界中最小编号
    vis[1] = true;
    heap.push(1);
    vector<int> order;
    while(!heap.empty()){
        int u = heap.top();
        heap.pop();
        order.push_back(u);
        for(int v : graph[u])
            if(!vis[v]){          // 入堆即标记，防止重复入堆
                vis[v] = true;
                heap.push(v);
            }
    }

    for(int i = 0; i < n; i++)
        cout << order[i] << (i + 1 < n ? ' ' : '\n');
    return 0;
}
