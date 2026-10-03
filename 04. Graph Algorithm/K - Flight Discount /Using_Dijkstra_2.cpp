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

    vector<vector<int>> dis(n + 1, vector<int>(2, 1e18));
    // dis[u][0]: min cost to u without using discount
    // dis[u][1]: min cost to u after using discount

    priority_queue<array<int, 3>, vector<array<int, 3>>, greater<>> pq;
    dis[1][0] = 0;
    pq.push({0, 1, 0}); // {cost, node, used_discount}

    while (!pq.empty()) {
        auto [cost, u, used] = pq.top(); pq.pop();
        if (dis[u][used] < cost) continue;
        for (auto [v, wt] : g[u]) {
            // Without using discount
            if (dis[v][used] > cost + wt) {
                dis[v][used] = cost + wt;
                pq.push({dis[v][used], v, used});
            }
            // Use discount if not used yet
            if (!used && dis[v][1] > cost + wt / 2) {
                dis[v][1] = cost + wt / 2;
                pq.push({dis[v][1], v, 1});
            }
        }
    }
    cout << min(dis[n][0], dis[n][1]) << endl;
    return 0;
}