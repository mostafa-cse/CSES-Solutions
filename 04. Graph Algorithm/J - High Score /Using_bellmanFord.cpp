#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> edges;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
        g[u].push_back(v); // for checking that it is reachable to 'N'
    }

    vector<int> dis(n + 1, -1e15);
    dis[1] = 0;

    for (int i = 1; i <= n - 1; i++) {
        for (auto [u, v, w] : edges) {
            if (dis[u] != -1e15 && dis[u] + w > dis[v]) {
                dis[v] = dis[u] + w;
            }
        }
    }

    // Mark nodes affected by positive cycle
    vector<bool> affected(n + 1, false);
    for (auto [u, v, w] : edges) {
        if (dis[u] != -1e15 && dis[u] + w > dis[v]) {
            affected[v] = true;
        }
    }

    // BFS from affected nodes to see if n is reachable
    vector<bool> vis(n + 1, false);
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (affected[i]) q.push(i), vis[i] = true;
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == n) {
            return cout << -1, 0;
        }
        for (int v : g[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
            }
        }
    }
    cout << dis[n] << endl;
    return 0;
}