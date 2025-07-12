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

    vector<int> vis(n + 1), order;
    function<void(int)> dfs = [&](int u) -> void {
        for (int v : g[u]) {
            if (vis[v] == 0) {
                dfs(v);
            }
        }
        vis[u] = 1;
        order.push_back(u);
    };
    dfs(1);
    reverse(order.begin(), order.end());

    vector<int> dp(n + 1, 0), par(n + 1, 0);
    dp[1] = 1;
    for (int u : order) {
        for (int v : g[u]) {
            if (dp[v] < dp[u] + 1) {
                dp[v] = dp[u] + 1;
                par[v] = u;
            }
        }
    }
    
    if (dp[n] == 0) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        stack<int> ans;
        while (n) {
            ans.push(n);
            n = par[n];
        }

        cout << ans.size() << endl;
        while (!ans.empty()) {
            cout << ans.top() << " ";
            ans.pop();
        }
    }

    return 0;
}