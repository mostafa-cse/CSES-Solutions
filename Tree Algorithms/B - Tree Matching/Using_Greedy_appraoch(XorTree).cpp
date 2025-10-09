#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;

    vector<int> deg(n, 0), vis(n, 0), adj(n + 1, 0);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u -= 1, v -= 1;

        deg[u]++, deg[v]++;
        adj[u] ^= v, adj[v] ^= u;
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int u = i;

        while (deg[u] == 1) {
            deg[u] = 0;

            int  v = adj[u];
            if (!vis[v] and !vis[u]) {
                vis[u] = vis[v] = 1;
                ans++;
            }
            adj[v] ^= u;
            --deg[v];
            u = v;

        }
    }
    cout << ans << endl;
    return 0;
}
