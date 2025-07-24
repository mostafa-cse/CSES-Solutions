#include <bits/stdc++.h>
#define int long long
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
signed main() {
    int n, m;
    cin >> n >> m;

    struct Node {
        int node, idx;
        Node(int _v, int _idx) : node(_v), idx(_idx) {}
    };
    
    vector<Node> adj[n + 1];
    vector<int> deg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        deg[u] ^= 1, deg[v] ^= 1;
        adj[u].push_back(Node(v, i));
        adj[v].push_back(Node(u, i));
    }

    if (accumulate(deg.begin(), deg.end(), 0ll)) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        vector<int> vis(m, 0), ans;
        function<void(int)> dfs = [&](int u) -> void {
            while (adj[u].size()) {
                Node v = adj[u].back();
                adj[u].pop_back();

                if (vis[v.idx]) continue;
                vis[v.idx] = 1;
                dfs(v.node);
            }
            ans.push_back(u);
        };
        dfs(1);
        if (ans.size() == m + 1) {
            for (int i : ans) {
                cout << i << " ";
            }
        } else {
            cout << "IMPOSSIBLE" << endl;
        }
    }
    return 0;
}