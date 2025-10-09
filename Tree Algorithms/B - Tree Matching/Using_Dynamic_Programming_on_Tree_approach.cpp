#include <bits/stdc++.h>
#define int long long
using namespace std;
pair<int, int> dfs(int u, int p, vector<int>*adj) {
    pair<int, int> dp = {0, 0};
    for (int v : adj[u]) {
        if (v != p) {
            pair<int, int> child = dfs(v, u, adj);
            dp.second = max({dp.first + child.first + 1,
                            dp.second + child.second,
                            dp.second + child.first});

            dp.first += max(child.first, child.second);
        }
    }
    return dp;
};
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;

    vector<int> adj[n + 1];
    for (int i = 1; i <= n - 1; i ++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    pair<int, int> ans = dfs(1, 1, adj);
    cout << max(ans.first, ans.second);
    return 0;
}
