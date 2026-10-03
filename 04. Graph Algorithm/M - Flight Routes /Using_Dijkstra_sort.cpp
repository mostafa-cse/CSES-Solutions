#include <bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
    int n, m, k;
    cin >> n >> m >> k;
    
    int d[n + 1][k + 1];
    vector<pair<int, int>> g[n + 1];
    while (m--) {
        int x, y, z; cin >> x >> y >> z;
        g[x].push_back({y, z});
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            d[i][j] = 1e18;
        }
    }
    d[1][1] = 0;
    pq.push({1, 0});
    while (!pq.empty()) {
        auto tp = pq.top();
        pq.pop();
        int u = tp.second, du = tp.first;
        if (d[u][k] < du) continue;
        for (pair<int, int> x : g[u]) {
            int v = x.first, w = x.second;
            if (d[v][k] > du + w) {
                d[v][k] = du + w;
                sort(d[v] + 1, d[v] + k + 1);
                pq.push({v, du + w});
            }
        }
    }
    for (int i = 1; i <= k; i++) {
        cout << d[n][i] << " ";
    }
    return 0;
}