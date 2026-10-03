#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 1e9 + 7;
signed main() {
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> g[n + 1];
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
    }

    priority_queue<pair<int, int>> pq;
    vector<int> dis(n + 1, 1e18);

    pq.push({0, 1});
    dis[1] = 0;
    vector<int> cnt(n + 1, 0), mx(n + 1, 0), mn(n + 1, 0), par(n + 1, 0);
    cnt[1] = 1;
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (-d > dis[u]) {
            continue;
        }
        for (auto &[v, w] : g[u]) {
            int cur_d = dis[u] + w;
            if (cur_d == dis[v]) {
                cnt[v] = (cnt[u] + cnt[v]) % Mod;
                mn[v] = min(mn[u] + 1, mn[v]);
                mx[v] = max(mx[u] + 1, mx[v]);
            } else if (cur_d < dis[v]) {
                par[v] = u;
                cnt[v] = cnt[u];
                mn[v] = mn[u] + 1;
                mx[v] = mx[u] + 1;
                dis[v] = cur_d;
                pq.push({-cur_d, v});
            }
        }
    }
    int P = n;
    while (P) {
        cerr << P << " ";
        P = par[P];
    }
    cout << dis[n] << " " << cnt[n] << " " << mn[n] << " " << mx[n] << endl;
    return 0;
}