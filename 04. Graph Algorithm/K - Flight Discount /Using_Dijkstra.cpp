#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> g[n + 1];
    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        g[u].push_back({v, wt});
    }


    priority_queue<array<int, 3>> pq;
    vector<vector<int>> dis(n + 1, vector<int>(2, 1e18));

    pq.push({0, 1, 0});
    dis[1][0] = 0;
    while (!pq.empty()) {
        auto [d, u, use] = pq.top();
        pq.pop();

        if (-d > dis[u][use]) {
            continue;
        }

        for (auto [v, wt] : g[u]) {
            if (dis[v][use] > dis[u][use] + wt) {
                dis[v][use] = dis[u][use] + wt;
                pq.push({-dis[v][use], v, use});
            }
            if (!use and dis[v][!use] > dis[u][use] + wt / 2) {
                dis[v][!use] = dis[u][use] + wt / 2;
                pq.push({-dis[v][!use], v, !use});
            }
        }
    }
    cout << dis[n][1];
    return 0;
}