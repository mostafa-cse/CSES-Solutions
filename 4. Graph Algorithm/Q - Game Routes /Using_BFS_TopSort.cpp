#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 1e9 + 7;
signed main() {
    int n, m;
    cin >> n >> m;

    vector<int> g[n + 1], in(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        in[v]++;
        g[u].push_back(v);
    }

    vector<int> dis(n + 1, 0);
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (in[i] == 0) q.push(i);
    }
    
    dis[1] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : g[u]) {
            in[v]--;
            dis[v] = (dis[u] + dis[v]) % Mod;
            if (in[v] == 0) {
                q.push(v);
            }
        }
    }
    cout << dis[n] << endl;
    return 0;
}