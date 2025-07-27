#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    
    vector<int> coin(n);
    for (int &i : coin) {
        cin >> i;
    }

    vector<int> adj[n], radj[n];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u -= 1, v -= 1;
        adj[u].push_back(v);
        radj[v].push_back(u);
    }

    stack<int> st;
    vector<int> vis(n, 0);
    function<void(int)> dfs = [&](int u) -> void {
        vis[u] = 1;
        for (int v : adj[u]) {
            if (vis[v] == 0) {
                dfs(v);
            }
        }
        st.push(u);
    };
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (vis[i] == 0) {
            dfs(i);
            cnt++;
        }
    }

    fill(vis.begin(), vis.end(), 0);
    vector<int> comp(n, 0), total(cnt, 0);
    vector<set<int>> condence(cnt);
    cnt = 0;
    function<void(int)> dfsr = [&](int u) -> void {
        vis[u] = 1;
        comp[u] = cnt;
        total[comp[u]] += coin[u];
        for (int v : radj[u]) {
            if (vis[v] == 0) {
                dfsr(v);
            } else if (comp[u] != comp[v]) {
                condence[comp[u]].insert(comp[v]); // condensing
            }
        }
    };
    
    while (!st.empty()) {
        int u = st.top();
        if (vis[u] == 0) {
            dfsr(u);
            cnt++;
        }
        st.pop();
    }

    vector<int> dp(cnt);
    int ans = 0;
    for (int u = cnt - 1; u >= 0; u--) {
        dp[u] = total[u];
        for (int v : condence[u]) {
            dp[u] = max(dp[u], dp[v] + total[u]);
        }
        ans = max(ans, dp[u]);
    }
    cout << ans << endl;
    return 0;
}