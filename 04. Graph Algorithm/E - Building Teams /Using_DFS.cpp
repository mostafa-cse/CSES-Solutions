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
        g[v].push_back(u);
    }

    vector<int> color(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            color[i] = 1;
            function<bool(int)> dfs = [&](int u) -> bool {
                for (int v : g[u]) {
                    if (color[v] == -1) {
                        color[v] = color[u] ^ 1;
                        if (dfs(v)) {
                            return true;
                        }
                    } else if (color[u] == color[v]) {
                        return true;
                    }
                }
                return false;
            };
            if (dfs(i)) {
                return cout << "IMPOSSIBLE" << endl, 0;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << color[i] + 1 << " ";
    }
    return 0;
}