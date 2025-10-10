#include <bits/stdc++.h>
#define int long long
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
signed main() {
    int n, q;
    cin >> n >> q;

    vector<vector<int>> adj(n + 1);
    for (int i = 2; i <= n; i++) {
        int u, v;
        cin >> u;
        v = i;
        adj[u].push_back(v);
    }

    vector<int> subtree(n + 1, 0);
    function<void(int, int)> dfs = [&](int u, int p) -> void {
        subtree[u] = 1;
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u);
                subtree[u] += subtree[v];
            }
        }
    };
    dfs(1, -1);
   
    return 0;
}
