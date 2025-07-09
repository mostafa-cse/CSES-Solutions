#include <bits/stdc++.h>
#define int long long
using namespace std;

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
    vector<int> dis(n + 1, 1e15);

    dis[1] = 0;
    pq.push({0, 1});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (-d > dis[u]) {
            continue;
        }
        for (auto [v, wt] : g[u]) {
            if (dis[v] > wt - d) {
                dis[v] = wt - d;
                pq.push({-dis[v], v});
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << dis[i] << " ";
    }
    return 0;
}