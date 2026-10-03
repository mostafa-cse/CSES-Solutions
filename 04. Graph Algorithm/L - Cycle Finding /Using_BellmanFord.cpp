#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;

    vector<array<int, 3>> edge(m);
    for (auto &[u, v, wt] : edge) {
        cin >> u >> v >> wt;
    }
    
    vector<long long> dis(n + 1, 1e18);
    dis[1] = 0;
    vector<long long> par(n + 1, -1);
    int x = -1;
    for (int i = 1; i <= n; i++) {
        x = -1; // after each update of n'th Update is it chnage or not
        for (auto &[u, v, wt] : edge) {
            if (dis[u] + wt < dis[v]) {
                dis[v] = dis[u] + wt;
                par[v] = u;
                x = v;
            }
        }
    }
    if (x == -1) {
        cout << "NO" << endl;
    } else {
        vector<int> cycle;
        // To ensure we are inside the cycle, move n times from x
        for (int i = 0; i < n; ++i) {
            x = par[x];
        }
        int cur = x;
        do {
            cycle.push_back(cur);
            cur = par[cur];
        } while (cur != x);
        cycle.push_back(x);
        cout << "YES" << endl;
        reverse(cycle.begin(), cycle.end()); // For directed graph, therwise we don't need to reverse it
        for (int i : cycle) {
            cout << i << ' ';
        }
    }
    return 0;
}