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

    vector<int> g[n + 1];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        g[u].push_back(v);
    }

    vector<int> vis(n + 1,0);
    vector<int> dp(n + 1, 0), par(n + 1, 0);
    function<void(int)> dfs = [&](int u) -> void {
        vis[u] = 1;
        for (int v : g[u]) {
            if (vis[v] == 0) {
                dfs(v);
            }
            if (dp[v] and dp[u] < dp[v]  + 1) { // backtrack moment, parent will be child and vice verse;
                dp[u] = dp[v] + 1;
                par[u] = v;
            }
        }
    };
    dp[n] = 1;
    dfs(1);
    if (dp[1] == 0) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        n = 1;
        cout << dp[1] << endl;
        while (n) {
            cout << n << " ";
            n = par[n];
        }
    }

    return 0;
}