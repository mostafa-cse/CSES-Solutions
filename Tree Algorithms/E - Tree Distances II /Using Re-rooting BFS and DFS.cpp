#include <bits/stdc++.h>
#define int long long
using namespace std;
void dfs(int node, vector<vector<int>> &adj, vector<int> &size, vector<int> &dp, int par) {
    for (auto it : adj[node]) {
        if (it != par) {
            dfs(it, adj, size, dp, node);
            size[node] += size[it];
            dp[node] += dp[it] + size[it];
        }
    }
}
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> dp(n, 0), size(n, 1);
    dfs(0, adj, size, dp, -1);
    queue<pair<int, int>> q;
    q.push({0, -1});
    while (!q.empty()) {
        int node = q.front().first;
        int par = q.front().second;
        q.pop();
        for (auto it : adj[node]) {
            if (it == par) {
                continue;
            }
            dp[it] = n - 2 * size[it] + dp[node];
            q.push({it, node});
        }
    }
    for (auto it : dp) {
        cout << it << " ";
    }
    return 0;
}
