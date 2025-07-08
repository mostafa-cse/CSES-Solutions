#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;

    vector<int> g[n + 1];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> vis(n + 1, 0), par(n + 1, -1);
    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) {
            queue<int> q;
            q.push(i);
            vis[i] = 1;
            while(!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v : g[u]) {
                    if (vis[v] == 0) {
                        par[v] = u;
                        vis[v] = 1;
                        q.push(v);
                    } else if (v =)
                }
            }
        }
    }
    return 0;
}