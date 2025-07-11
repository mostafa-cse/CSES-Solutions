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
    }

    vector<int> par(n + 1, 0), lvl(n + 1, 0);
    queue<int> q;
    set<int> vis[n + 1];
    
    vis[1].insert(1);
    vis[1].insert(2);
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == n) continue;
        for (int v : g[u]) {
            if (lvl[v] < lvl[u] + 1) {
                lvl[v] = lvl[u] + 1;
                par[v] = u;
                q.push(v);
            }
        }
    }
    if (!par[n]) {
        cout << "IMPOSSIBLE";
    } else {
        cout << lvl[n] + 1 << endl;
        vector<int> ans;
        do {
            ans.push_back(n);
            n = par[n];
        } while (n);
        reverse(ans.begin(), ans.end());
        for (int i : ans) cout << i << " ";
    }
    return 0;
}