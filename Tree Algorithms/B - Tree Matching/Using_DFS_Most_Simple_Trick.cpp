#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    vector<int> adj[n + 1];
    for (int i = 1; i < n; i ++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int ans = 0;
    vector<int> done(n + 1, 0);
    function<void(int, int)> dfs = [&](int u, int p) -> void {
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u);
            }
        }
        if (p != -1 and !done[u] and !done[p]) {
            done[u] = done[p] = 1;
            ans++;
        }
    };
    dfs(1, -1);
    cout << ans << endl;
    return 0;
}
