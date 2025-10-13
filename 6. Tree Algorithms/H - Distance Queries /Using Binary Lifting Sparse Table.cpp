#include <bits/stdc++.h>
#define int long long
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n, q;
    cin >> n >> q;

    vector<vector<int>> up(n + 1, vector<int>(21, 0));
    vector<vector<int>> adj(n + 1);
    for (int i = 2; i <= n; i++) {
        int u, v;
        cin >> u >> v;
        up[v][0] = u;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int b = 1; b < 21; b++) {
        for (int node = 1; node <= n; node++) {
            up[node][b] = up[ up[node][b - 1] ][b - 1];
        }
    }

    vector<int> lvl(n + 1, 0), parent(n + 1, -1);
    queue<int> qq;
    qq.push(1);
    lvl[1] = 1;
    parent[1] = 1;
    while (!qq.empty()) {
        int u = qq.front();
        qq.pop();
        for (int v : adj[u]) {
            if (lvl[v] == 0) {
                lvl[v] = lvl[u] + 1;
                parent[v] = u;
                qq.push(v);
            }
        }
    }

    while (q--) {
        int u, v;
        cin >> u >> v;

        int lu = lvl[u];
        int lv = lvl[v];
        auto lift = [&](int a, int d) -> int {
            for (int i = 20; i >= 0; --i) {
                if (d & (1LL << i)) a = up[a][i];
            }
            return a;
        };
        if (lvl[u] > lvl[v]) {
            u = lift(u, lvl[u] - lvl[v]);
        } else if (lvl[u] < lvl[v]) {
            v = lift(v, lvl[v] - lvl[u]);
        }

        int LCAnode = -1;
        if (lu == lv) {
            cout << 0 << endl;
        } else {
            int ans = abs(lu - lv) - 1;
            for (int i = 20; i >= 0; --i) {
                if (up[u][i] != up[v][i]) {
                    u = up[u][i];
                    v = up[v][i];
                }
            }
            LCAnode = up[u][0];
            ans += min(lu, lv) - lvl[LCAnode];
            cout << ans << endl;
        }
    }
    return 0;
}
