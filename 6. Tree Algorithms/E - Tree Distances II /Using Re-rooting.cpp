#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> dis(n + 1, 0), cntNode(n + 1, 0);
    function<void(int, int)> dfs1 = [&](int u, int p) -> void {
        cntNode[u] = 1;
        dis[u] = 0;
        for (int v : adj[u]) {
            if (p != v) {
                dfs1(v, u);
                cntNode[u] += cntNode[v];
                dis[u] += dis[v] + cntNode[v]; // something batter
            }
        }
    };
    dfs1(1, 1);
    int total = dis[1];
    fill(dis.begin(), dis.end(), 0);
    function<void(int, int)>dfs2 = [&](int u, int p) -> void {
        for (int v : adj[u]) {
            if (v != p) {
                dis[v] = dis[u] - cntNode[v] + n - cntNode[v];
                dfs2(v, u);
            }
        }
    };
    dis[1] = total;
    dfs2(1, 1);

    for (int i = 1; i <= n; ++i) {
        cout << dis[i] << " ";
    }
    return 0;
}
