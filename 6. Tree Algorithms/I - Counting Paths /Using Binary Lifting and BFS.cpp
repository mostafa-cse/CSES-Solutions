#include <bits/stdc++.h>
#define int long long
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
signed main() {
    int n, q;
    cin >> n >> q;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<vector<int>> jump(n + 1, vector<int>(21));
    vector<int> depth(n + 1, 0);
    function<void(int, int)> dfs1 = [&](int u, int p) -> void {
        jump[u][0] = p;
        for (int v : adj[u]) {
            if (v != p) {
                depth[v] = depth[u] + 1;
                dfs1(v, u);
            }
        }
    };
    dfs1(1, 0);

    for (int b = 1; b < 21; b++) {
        for (int node = 1; node <= n; node++) {
            jump[node][b] = jump[jump[node][b - 1]][b - 1];
        }
    }
    function<int(int , int)> lca = [&](int a, int b) -> int {
        auto lift = [&](int u, int d) -> int {
            for (int i = 20; i >= 0; --i) {
                if (d & (1LL << i)) {
                    u = jump[u][i];
                }
            }
            return u;
        };
        if (depth[a] > depth[b]) {
            a = lift(a, depth[a] - depth[b]);
        } else if (depth[a] < depth[b]) {
            b = lift(b, depth[b] - depth[a]);
        }

        if (a == b) {
            return a;
        }

        for (int i = 20; i >= 0; --i) {
            if (jump[a][i] != jump[b][i]) {
                a = jump[a][i];
                b = jump[b][i];
            }
        }
        return jump[a][0];
    };

    vector<int> ans(n + 1, 0);
    while (q--) {
        int a, b;
        cin >> a >> b;

        int l = lca(a, b);
        ans[a]++; // start flow-1
        ans[b]++; // start flow-2
        ans[l]--; // ends a flow
        ans[jump[l][0]]--; // ends a flow
    }

    queue<int> qq;
    vector<int> vis(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() == 1) {
            vis[i] = 1;
            qq.push(i);
        }
    }
    dout(qq);

    while (!qq.empty()) {
        int u = qq.front();
        qq.pop();
        for (int v : adj[u]) {
            if (vis[v] == 0) {
                vis[v] = 1;
                ans[v] += ans[u];
                qq.push(v);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
