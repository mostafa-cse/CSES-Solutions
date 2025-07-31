#include <bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;

    int max_cap = 0;
    vector<vector<int>> adj(n + 1, vector<int>(n + 1, -1));
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        if (adj[u][v] == -1) adj[u][v] = 0;
        if (adj[v][u] == -1) adj[v][u] = 0;
        adj[u][v] += w;
        max_cap = max(max_cap, adj[u][v]);
    }

    int ans = 0;
    int delta = 1;
    // assume Bottleneck Scale
    while (delta * 2 <= max_cap) delta *= 2;
    
    while (delta > 0) {
        vector<int> path, vis(n + 1, 0);
        function<bool(int)> dfs = [&](int u) -> bool {
            vis[u] = 1;
            if (u == n) {
                path.push_back(u);
                return true;
            }
            for (int v = 1; v <= n; v++) {
                if (adj[u][v] == -1 or vis[v] or adj[u][v] < delta)
                    continue;
                if (dfs(v)) {
                    path.push_back(u);
                    return true;
                }
            }
            return false;
        };

        if (dfs(1)) {
            reverse(path.begin(), path.end());
            int bottleneck = 1e18;
            for (int i = 1; i < path.size(); ++i) {
                int u = path[i - 1];
                int v = path[i];
                bottleneck = min(bottleneck, adj[u][v]);
            }
            ans += bottleneck;
            for (int i = 1; i < path.size(); ++i) {
                int u = path[i - 1];
                int v = path[i];
                adj[u][v] -= bottleneck;
                if (adj[v][u] == -1) adj[v][u] = 0;
                adj[v][u] += bottleneck;
            }
            path.clear();
            fill(vis.begin(), vis.end(), 0);
        } else {
            delta /= 2;
        }
    }
    cout << ans << "\n";
    return 0;
}
