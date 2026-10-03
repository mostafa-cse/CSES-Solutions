#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;

    vector<int> adj[n + 1], in(n + 1, 0);
    vector<pair<int, int>> edges;
    bool selfLoop = false;
    for (int i = 0; i < m; i++) {
        int  u, v;
        cin >> u >> v;
        if (u == v) { // self loop
            selfLoop = true;
        }
        adj[u].push_back(v);
    }
    if (selfLoop) {
        return cout << "IMPOSSIBLE" << endl, 0;
    }

    vector<int> order, vis(n + 1, 0);
    function<void(int)> dfs = [&](int u) -> void {
        vis[u] = 1;
        for (int v : adj[u]) {
            if (vis[v]) continue;
            dfs(v);
        }
        order.push_back(u);
    };
    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) {
            dfs(i);
        }
    }
    reverse(order.begin(), order.end());
    
    vector<int> mapping(n + 1, -1);
    for (int i = 0; i < n; i++) {
        mapping[order[i]] = i;
    }

    bool ok = false;
    for (int u = 1; u <= n; u++) {
        for (int v : adj[u]) {
            ok |= (mapping[v] < mapping[u]);
        }
    }
    
    if (ok) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        for (int i : order) {
            cout << i << " ";
        }
    }
    return 0;
}