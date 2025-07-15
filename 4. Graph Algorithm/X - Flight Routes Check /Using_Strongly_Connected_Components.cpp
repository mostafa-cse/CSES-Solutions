#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;

    vector<int> g[n + 1], rg[n + 1];
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;

        g[u].push_back(v);
        rg[v].push_back(u);
    }

    stack<int> s;
    vector<int> vis(n + 1, 0);
    function<void(int, bool)> dfs = [&](int u, bool ok) -> void {
        vis[u] = 1;
        if (ok) {
            for (int v : g[u]) {
                if (vis[v] == 0) {
                    dfs(v, ok);
                }
            }
            s.push(u);
        } else {
            for (int v : rg[u]) {
                if (vis[v] == 0) {
                    dfs(v, ok);
                }
            }
        }
    };
    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) {
            dfs(i, 1);
        }
    }
    vector<int> ans;
    fill(vis.begin(), vis.end(), 0);
    while (!s.empty()) {
        if (vis[s.top()] == 0) {
            ans.push_back(s.top());
            dfs(s.top(), 0);
        } else {
            s.pop();
        }
    }
    if (ans.size() == 1) {
        cout << "YES" << endl;
    }  else {
        cout << "NO" << endl;
        fill(vis.begin(), vis.end(), 0);
        dfs(ans[0], 1);

        if (vis[ans[1]]) {
            cout << ans[1] << " " << ans[0] << endl;
        } else {
            cout << ans[0] << " " << ans[1] << endl;
        }
    }
    return 0;
}