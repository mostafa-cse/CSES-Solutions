#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n + 1), r(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;

        g[u].push_back(v);
        r[v].push_back(u);
    }
    
    stack<int> order;
    vector<int> vis(n + 1, 0);
    vector<int> ans(n + 1);
    function<void(int, vector<vector<int>>&, int)> dfs = [&](int u, vector<vector<int>> &adj, int mark) -> void {
        vis[u] = 1;
        ans[u] = mark;
        for (int v : adj[u]) {
            if (vis[v] == 0) {
                dfs(v, adj, mark);
            }
        }
        order.push(u);
    };
    
    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) {
            dfs(i, g, 0);
        }
    }

    fill(vis.begin(), vis.end(), 0);
    int cnt = 0;
    while (!order.empty()) {
        if (vis[order.top()] == 0) {
            cnt++;
            dfs(order.top(), r, cnt);
        } else {
            order.pop();
        }
    }
    cout << cnt << endl;
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}