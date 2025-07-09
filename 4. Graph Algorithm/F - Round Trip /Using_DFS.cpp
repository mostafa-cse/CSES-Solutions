#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;

    vector<int> g[n + 1];
    int u, v;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> vis(n + 1, 0), par(n + 1, -1);
    vector<int> cycle;
    function<bool(int, int)> dfs = [&](int u, int p) -> bool {
        vis[u] = 1;
        for (int v : g[u]) {
            if (v == p) continue;
            if (!vis[v]) {
                par[v] = u;
                if (dfs(v, u)) return true;
            } else {
                cycle.push_back(v);
                int cur = u;
                while (cur != v) {
                    cycle.push_back(cur);
                    cur = par[cur];
                }
                cycle.push_back(v);
                return true;
            }
        }
        return false;
    };

    bool found = false;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            if (dfs(i, -1)) {
                found = true;
                break;
            }
        }
    }
    if (found) {
        cout << cycle.size() << endl;
        for (int x : cycle) cout << x << " ";
        cout << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}