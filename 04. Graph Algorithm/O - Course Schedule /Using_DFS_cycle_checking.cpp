#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;

    vector<int> g[n + 1];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }
    vector<int> vis(n + 1, 0), ans;
    bool has_cycle = false;
    function<void(int)> dfs = [&](int u) -> void {
        vis[u] = 1; // visiting
        for (int v : g[u]) {
            if (vis[v] == 0) {
                dfs(v);
            } else if (vis[v] == 1) {
                has_cycle = true;
            }
        }
        vis[u] = 2; // visited
        ans.push_back(u);
    };
    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) {
            dfs(i);
        }
    }
    if (has_cycle) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    reverse(ans.begin(), ans.end());
    for (int i : ans) cout << i << " ";
    return 0;
}