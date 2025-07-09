#include <bits/stdc++.h>
#define int long long
using namespace std;

const int INF = 1e15;

int32_t main() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> dis(n + 1, vector<int>(n + 1, INF));
    for (int i = 1; i <= n; i++) dis[i][i] = 0;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dis[u][v] = min(dis[u][v], w);
        dis[v][u] = min(dis[v][u], w);
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dis[i][k] < INF && dis[k][j] < INF)
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    
    while (q--) {
        int u, v;
        cin >> u >> v;
        if (dis[u][v] != 1e15) {
            cout << dis[u][v] << endl;
        } else {
            cout << -1 << endl;
        }
    }
    return 0;
}
