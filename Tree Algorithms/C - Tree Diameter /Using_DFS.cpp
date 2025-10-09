#include <bits/stdc++.h>
#define int long long
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
signed main() {
    int n;
    cin >> n;

    vector<int>adj[n + 1];
    for (int i = 0; i < n - 1; i ++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    function<void(int, int, vector<int>&)> dfs = [&](int u, int par, vector<int>&dis) -> void {
        for (int v : adj[u]) {
            if (v != par) {
                dis[v] = dis[u] + 1;
                dfs(v, u, dis);
            }
        }
    };

    vector<int> dis(n + 1);
    dfs(1, -1, dis);

    int node = -1, d = -1;
    for (int i = 1; i <= n; i++) {
        if (dis[i] > d) {
            d = dis[i];
            node = i;
        }
    }
    vector<int> ans(n + 1);
    dfs(node, -1, ans);
    cout << *max_element(ans.begin(), ans.end()) << endl;
    return 0;
}
