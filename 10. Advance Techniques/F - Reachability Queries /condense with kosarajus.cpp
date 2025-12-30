#include <bits/stdc++.h>
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()

const int M = 5e4 + 5;
bitset<M> res[M];
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, m, q;
    cin >> n >> m >> q;

    vector<int> g[n + 1], rg[n + 1];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        rg[v].push_back(u);
    }

    vector<int> order, vis(n + 1, 0);
    function<void(int)> dfs1 = [&](int u) -> void {
        vis[u] = 1;
        for (int v : g[u]) {
            if (vis[v] == 0) {
                dfs1(v);
            }
        }
        order.push_back(u);
    };
    for (int i = 1; i <= n; i++) {
        res[i][i] = 1;
        if (!vis[i]) {
            dfs1(i);
        }
    }

    vector<int> condense(n + 1, 0);
    function<void(int, int)> dfs2 = [&](int u, int val) -> void {
        condense[u] = val;
        for (int v : rg[u]) {
            if (condense[v] == 0) {
                dfs2(v, val);
            }
        }
    };

    int cnt = 1;
    while (!order.empty()) {
        if (condense[order.back()] == 0) {
            dfs2(order.back(), cnt);
            cnt++;
        }
        order.pop_back();
    }

    vector<int> id(n + 1, 0);
    iota(all(id), 0);
    sort(all(id), [&](int x, int y) {
        return condense[x] < condense[y];
    });

    for (int i = 1; i <= n; i++) {
        int u = id[i];
        for (int v : g[u]) {
            res[condense[v]] |= res[condense[u]];
        }
    }
    while (q--) {
        int from, to;
        cin >> from >> to;

        if (res[condense[to]][condense[from]]) {
            cout << "YES" << '\n';
        } else {
            cout << "NO" << '\n';
        }
    }
    return 0;
}

