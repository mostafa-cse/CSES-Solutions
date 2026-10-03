#include <bits/stdc++.h>
#define int long long
using namespace std;
const int M = 2e5;
vector<vector<int>> adj(M);
vector<int> a(M), duplicate(M), last(M), parent(M), vis(M), dp(M);
int getP(int i) {
  if (vis[i]) return i;
  return parent[i] = getP(parent[i]);
}
int dfs(int u, int p) {
    vis[u] = 1;
    int color = a[u];
    if (last[color] > 0) {
        duplicate[getP(last[color])]++;
    }
    last[color] = u;
    int res = 1;
    for (int v : adj[u]) {
        if (v != p and !vis[v]) {
            parent[v] = u;
            res += dfs(v, u);
        }
    }
    vis[u] = 0;
    return dp[u] = res - duplicate[u];
}
signed main() {
    int n;
    cin >> n;

    vector<int> b(1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b.push_back(a[i]);
    }
    sort(b.begin() + 1, b.end());
    b.resize(unique(b.begin(), b.end()) - b.begin());

    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    }

    for (int i = 1; i <= n - 1; i ++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
        cout << dp[i] << " ";
    }
    return 0;
}
