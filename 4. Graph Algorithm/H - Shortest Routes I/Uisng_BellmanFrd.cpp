// This is just implementation of Bellman Ford : TLE
#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }

    vector<int> dis(n + 1, 1e15);
    dis[1] = 0; // source node is 1

    for (int i = 1; i <= n - 1; i++) {
        for (auto [u, v, w] : edges) {
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
            }
        }
    }

    // Optional: Check for negative cycles
    // bool hasNegativeCycle = false;
    // for (auto [u, v, w] : edges) {
    //     if (dis[u] + w < dis[v]) {
    //         hasNegativeCycle = true;
    //         break;
    //     }
    // }
    // if (hasNegativeCycle) cout << "Negative cycle detected!\n";

    for (int i = 1; i <= n; i++) {
        cout << dis[i] << " ";
    }
    return 0;
}