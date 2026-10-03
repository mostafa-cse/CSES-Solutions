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

    vector<pair<int, int>> adj[n + 1];
    vector<int> in(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;

        adj[x].push_back({y, i});
        in[y]++;
    }

    for (int i = 1; i <= n; i++) {
        if (i == 1 or i == n) {
            if (i == 1 and adj[i].size() != in[i] + 1) {
                return cout << "IMPOSSIBLE" << endl, 0;
            } else if (i == n and adj[i].size() != in[i] - 1) {
                return cout << "IMPOSSIBLE" << endl, 0;
            }
        } else {
            if (adj[i].size() != in[i]) {
                return cout << "IMPOSSIBLE" << endl, 0;
            }
        }
    }

    // write eular path
    vector<int> order, vis(m, 0);
    function<void(int)> dfs = [&](int u) -> void {
        while (!adj[u].empty()) {
            auto [v, idx] = adj[u].back();
            adj[u].pop_back();

            if (vis[idx] == 0) {
                dfs(v);
            }
        }
        order.push_back(u);
    };
    dfs(1);
    if (order.size() != m + 1) {
        cout << "IMPOSSIBLE";
    } else {
        for (int i = order.size() - 1; i >= 0; i--) {
            cout << order[i] << " ";
        }
    }
    return 0;
}