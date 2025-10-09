#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    vector<int> adj(n), deg(n, 0);
    for (int i = 0; i < n - 1; i ++) {
        int u, v;
        cin >> u >> v;
        u -= 1, v -= 1;
        deg[u]++, deg[v]++;
        adj[u] ^= v, adj[v] ^= u;
    }

    int ans = 0;
    vector<int> dis(n, 0);
    for (int i = 0; i < n; i++) {
        int u = i;
        while (deg[u] == 1) {
            int v = adj[u];
            ans = max(ans, dis[u] + dis[v] + 1);
            dis[v] = max(dis[u] + 1, dis[v]);

            deg[u]--, deg[v]--;
            adj[u] ^= v, adj[v] ^= u;
            u = v;
        }
    }
    cout << ans;
    return 0;
}
