#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;

    vector<int> adj[n + 1], deg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++, deg[v]++;
    }
    
    if (accumulate(deg.begin(), deg.end(), 0ll, [&](int sum, int val) { return sum + (val & 1); })) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        vector<int> path;
        set<pair<int, int>> edges;
        function<void(int)> dfs = [&](int c) -> void {
            while (!adj[c].empty()) {
                int child = adj[c].back();
                adj[c].pop_back(); // delete this edge

                int a = min(c, child), b = max(c, child);
                if (edges.count({a, b})) continue;

                edges.insert({a, b});
                dfs(child);
            }
            path.push_back(c);
        };
        dfs(1);
        if (path.size() != m + 1)  {
            cout << "IMPOSSIBLE" << endl;
        } else {
            for (int i : path) {
                cout << i << " ";
            }
        }
    }
    return 0;
}


