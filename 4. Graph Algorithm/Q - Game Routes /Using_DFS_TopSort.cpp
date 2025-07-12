#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 1e9 + 7;
signed main() {
    int n, m;
    cin >> n >> m;

    vector<int> g[n + 1];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    list<int> order;
    vector<int> vis(n + 1, 0);
    function<void(int)> dfs = [&](int u) -> void {
        vis[u] = 1;
        for (int v : g[u]) {
            if (vis[v] == 0) {
                dfs(v);
            }
        }
        order.push_front(u);
    };
    dfs(1);
    vector<int> dp(n + 1, 0);
    dp[1] = 1;
    for (int u : order) {
        for (int v : g[u]) {
            dp[v] = (dp[u] + dp[v]) % Mod;
        }
    }
    cout << dp[n] << endl;
    return 0;
}
