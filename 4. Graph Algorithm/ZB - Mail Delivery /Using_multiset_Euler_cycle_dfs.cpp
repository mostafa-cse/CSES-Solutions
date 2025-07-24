#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;

    set<int> g[n + 1];
    vector<int> deg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].insert(v);
        g[v].insert(u);
        deg[u] ^= 1, deg[v] ^= 1;
    }

    if (accumulate(deg.begin(), deg.end(), 0ll)) {
        cout << "IMPOSSIBLE";
    } else {
        vector<int> vis(n + 1, 0);
        // check connectivity
        function<void(int)> dfs = [&](int u) -> void {
            vis[u] = 1;
            for (int v : g[u]) {
                if (vis[v] == 0) {
                    dfs(v);
                }
            }
        };
        dfs(1);
        for (int i = 1; i <= n; ++i) {
            if (deg[i] and !vis[i]) {
                cout << "IMPOSSIBLE" << endl;
                return 0;
            }
        }

        // Eular tour for Eular cycle
        vector<int> order;
        function<void(int)> walk = [&](int u) -> void {
            while (!g[u].empty()) {
                int v = *g[u].begin();
                g[u].erase(v);
                g[v].erase(u);
                walk(v);
            }
            order.push_back(u);
        };
        walk(1);
        if (order.size() == m + 1) {
            for (int i : order) {
                cout << i << " ";
            }
        } else {
            cout << "IMPOSSIBLE" << endl;
        }
    }
    return 0;
}