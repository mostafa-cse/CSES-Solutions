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
    }


    vector<int> vis(n + 1, 0), par(n + 1, 0), inStack(n + 1, 0);
    vector<int> cycle;
    function<bool(int)> dfs = [&](int u) -> bool {
        vis[u] = 1;
        inStack[u] = 1;
        for (int v : g[u]) {
            if (!vis[v]) {
                par[v] = u;
                if (dfs(v)) return true;
            } else if (inStack[v]) {
                int cur = u;
                cycle.push_back(v);
                cycle.push_back(cur);
                while (cur != v) {
                    cur = par[cur];
                    cycle.push_back(cur);
                }
                reverse(cycle.begin(), cycle.end());
                return true;
            }
        }
        inStack[u] = 0;
        return false;
    };
    bool found = false;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            if (dfs(i)) {
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