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

    vector<int> nodes, vis(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) {
            nodes.push_back(i);
            queue<int> q;

            vis[i] = 1;
            q.push(i);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : g[u]) {
                    if (vis[v] == 0) {
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
    }
    cout << nodes.size() - 1 << endl;
    for (int i = 1; i < nodes.size(); i++) {
        cout << nodes[i - 1] << " " << nodes[i] << endl;
    }
    return 0;
}