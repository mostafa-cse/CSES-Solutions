#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    
    vector<int> g[n + 1], r[n + 1];
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;

        g[u].push_back(v);
        r[v].push_back(u);
    }
    vector<int> vis(n + 1);
    function<void(int, vector<int>*)> dfs = [&](int u, vector<int> *adj) -> void {
        vis[u] = 1;
        for (int v : adj[u]) {
            if (vis[v] == 0) {
                dfs(v, adj);
            }
        }
    };
    dfs(1, g);
    for (int i = 2; i <= n; i++) {
        if (vis[i] == 0) {
            cout << "NO" << endl;
            return cout << 1 << " " << i << endl, 0;
        }   
    }
    
    fill(vis.begin(), vis.end(), 0);
    dfs(1, r);
    for (int i = 2; i <= n; i++) {
        if (vis[i] == 0) {
            cout << "NO" << endl;
            return cout << i << " " << 1 << endl, 0;
        }   
    }
    cout << "YES";
    return 0;
}