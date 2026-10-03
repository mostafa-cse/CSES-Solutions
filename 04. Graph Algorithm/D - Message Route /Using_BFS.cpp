#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;

    list<int> g[n + 1];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> lvl(n + 1, -1), par(n + 1, -1);
    queue<int> q;

    q.push(1);
    lvl[1] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : g[u]) {
            if (lvl[v] == -1) {
                lvl[v] = lvl[u] + 1;
                par[v] = u;
                q.push(v);
            }
        }
    }

    if (lvl[n] == -1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << lvl[n] << endl;
        
        stack<int> ans;
        ans.push(n);
        while (par[n] != -1) {
            ans.push(par[n]);
            n = par[n];
        }

        while (!ans.empty()) cout << ans.top() << " ", ans.pop();
    }
    return 0;
}