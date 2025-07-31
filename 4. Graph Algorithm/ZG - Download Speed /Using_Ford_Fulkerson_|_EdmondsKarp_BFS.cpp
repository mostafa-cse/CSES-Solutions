#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> speed(n + 1, vector<int>(n + 1, 0)), g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        g[u].push_back(v);
        g[v].push_back(u);
        speed[u][v] += w;
    }

    int ans = 0;
    while (true) {
        vector<int> path(n + 1, -1);
        queue<int> q;
        // determine path
        q.push(1);
        path[1] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == n) break;
            for (int v : g[u]) {
                if (path[v] == -1 and speed[u][v]) {
                    path[v] = u;
                    q.push(v);
                }
            }
        }
        if (path[n] == -1) {
            break;
        }
        // Determie bottleneck 
        int bottleneck = 1e18;
        for (int y = n; y != 1; y = path[y]) {
            bottleneck = min(bottleneck, speed[path[y]][y]);
        }
        ans += bottleneck;
        // determine augmented Graph
        for (int y = n; y != 1; y = path[y]) {
            speed[path[y]][y] -= bottleneck;
            speed[y][path[y]] += bottleneck;
        }
    }
    cout << ans << endl;
    return 0;
}