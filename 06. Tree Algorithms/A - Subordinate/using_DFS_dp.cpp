#include <bits/stdc++.h>
using namespace std;
signed main() {
    int n;
    cin >> n;

    vector<int> adj[n + 1];
    for (int i = 2; i <= n; i++) {
        int x;
        cin >> x;
        adj[x].push_back(i);
    }

    vector<int> dp(n + 1, 0);
    function<int(int)> dfs = [&](int u) -> int {
        for (int v : adj[u]) {
            dp[u] += 1 + dfs(v);
        }
        return dp[u];
    };
    dfs(1);
    for (int i = 1; i <= n; i++) {
        cout << dp[i] << ' ';
    }
    return 0;
}
