#include <bits/stdc++.h>
#define int long long
#define pb push_back
const int maxn=1e5+5;
int n,m,k;
vector<vector<pair<int, int>>> a(maxn);
vector<vector<pair<int, int>>>b(maxn);
vector<int> dji(vector<vector<pair<int, int>>> &e,int S){
    vector<int> dis;
    dis.resize(1e5 + 10);
    vector<int> vis;
    vis.resize(1e5 + 10);
    dis.resize(e.size());
    vis.resize(e.size());
    priority_queue<pair<int, int>> pq;
    pq.push({0, S});
    for (auto &d : dis) d = 1e18;
    while (pq.size()) {
        auto tp = pq.top();
        pq.pop();
        if (vis[tp.second]) continue;
        vis[tp.second] = 1;
        dis[tp.second] = -tp.first;
        for (auto v : e[tp.second]) {
            if (dis[v.first] > dis[tp.second] + v.second) {
                dis[v.first] = dis[tp.second] + v.second;
                pq.push({-dis[v.first], v.first});
            }
        }
    }
    return dis;
}
struct node{
    int u,v,w;
    bool operator<(const node&bb)const {
        return w>bb.w;
    }
};
signed main(){
    ios::sync_with_stdio(false);cin.tie(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        a[u].push_back({v, w});
        b[v].push_back({u, w});
    }
    vector<int> ans;
    vector<int> invis = dji(b, 1);
    priority_queue<node> pq;
    pq.push({1, 1, invis[1]});
    int cnt = 0;
    while(pq.size()){
        auto tp = pq.top();
        pq.pop();
        if (tp.u == n) {
            ans.push_back(tp.w);
        }
        cnt++;
        if (cnt == k) {
            break;
        }
        for (auto to : a[tp.u]) {
            pq.push({to.first, tp.v + 1, invis[to.first]});
        }
    }    
    return 0;
}