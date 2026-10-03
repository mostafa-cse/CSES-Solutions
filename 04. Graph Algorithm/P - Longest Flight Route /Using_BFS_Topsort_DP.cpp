#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;

    vector<int> g[n + 1], in(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        in[v]++;
        g[u].push_back(v);
    }

    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (in[i] == 0) q.push(i);
    }

    vector<int> dp(n + 1, 0), par(n + 1, 0);
    dp[1]= 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : g[u]) {
            in[v]--;

            if (dp[u] and dp[v] < dp[u] + 1) {
                dp[v] = dp[u] + 1;
                par[v] = u;
            }
            if (in[v] == 0) {
                q.push(v);
            }
        }
    }

    if (dp[n] == 0) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << dp[n] << endl;
        stack<int> ans;
        while (n) {
            ans.push(n);
            n = par[n];
        }

        while (!ans.empty()) {
            cout << ans.top() << " ";
            ans.pop();
        }
    }
    return 0;
}