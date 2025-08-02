#include <bits/stdc++.h>
#define int long long
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
signed main() {
    int n, m;
    cin >> n >> m;

    vector<unordered_map<int, int>> adj(n + 1);
    vector<vector<int>> ase(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < m; i++) {
        int u, v, w = 1;
        cin >> u >> v;
        adj[u][v] += w;
        adj[v][u] += w;
        ase[u][v] = ase[v][u] = 1;
    }

    int Flow = 0;
    while (true) {
        vector<int> par(n + 1, -1);
        queue<int> q;

        q.push(1);
        par[1] = 0;
        
        bool colbe = true;
        while (q.size() and colbe) {
            int u = q.front();
            q.pop();
            for (auto [v, w] : adj[u]) {
                if (w > 0 and par[v] == -1) {
                    par[v] = u;
                    q.push(v);
                    if (v == n) {
                        colbe = false;
                        break;
                    }
                }
            }
        }
        
        if (par[n] == -1) {
            break;
        }

        int btlenk = 1e18;
        for (int p = n; p != 1; p = par[p]) {
            int u = par[p];
            int v = p;
            btlenk = min(btlenk, adj[u][v]);
        }
        Flow += btlenk;
        for (int p = n; p != 1; p = par[p]) {
            int u = par[p];
            int v = p;
            adj[u][v] -= btlenk;
            adj[v][u] += btlenk;
        }
    }
    cout << Flow << endl;

    set<int> nodes;
    vector<int> vis(n + 1, 0);
    function<void(int)> dfs = [&](int u) -> void {
        nodes.insert(u);
        vis[u] = 1;
        for (auto [v, w] : adj[u]) {
            if (w and vis[v] == 0) {
                dfs(v);
            }
        }
    };
    dfs(1);
    for (int u : nodes) {
        for (int v = 1; v <= n; v++) {
            if (adj[u][v] == 0 and nodes.count(v) == 0 and ase[u][v]) {
                cout << u << " " << v << endl;
            }
        }
    }
    return 0;
}