#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, q;
    cin >> n >> q;

    vector<vector<int>> up(n + 1, vector<int>(20));
    for (int i = 1; i <= n; i++) {
        cin >> up[i][0];
    }

    vector<int> vis(n + 1, 0), depth(n + 1, 0);
    function<void(int)> dfs = [&](int u) -> void {
        if (vis[u] == 0) {
            vis[u] = 1;
            dfs(up[u][0]);
            depth[u] = depth[up[u][0]] + 1;
        }
    };
    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) {
            dfs(i);
        }
    }
    for (int j = 1; j < 20; j++) { // Adjusted range to match up vector size
        for (int u = 1; u <= n; u++) {
            up[u][j] = up[up[u][j - 1]][j - 1];
        }
    }
    function<int(int u, int d)> Go = [&](int u, int d) -> int {
        for (int bit = 18; bit >= 0; bit--) {
            if (d >> bit & 1) {
                u = up[u][bit];
            }
        }
        return u;
    };
    while (q--) {
        int u, v; // u -> v
        cin >> u >> v;

        int du = depth[u], dv = depth[v];
        if (du >= dv && Go(u, du - dv) == v) {
            cout << du - dv << endl;
        } else {
            int ancestor = Go(u, du); // Find the ancestor of u
            if (Go(ancestor, depth[ancestor] - dv) == v) {
                cout << du + depth[ancestor] - dv << endl;
            } else {
                cout << -1 << endl;
            }
        }
    }
    return 0;
}