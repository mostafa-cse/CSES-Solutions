#include <bits/stdc++.h>
#define int long long
using namespace std;
class Fenwick { // just understand, is it maintained by asociativity rules
    int n;
    std::vector<int> bit;

public:
    explicit Fenwick(int n) : n(n), bit(n + 1, 0) {}

    void update(int idx, int delta) {
        for (; idx <= n; idx += idx & -idx)
            bit[idx] += delta;
    }

    int query(int idx) const {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx)
            res += bit[idx];
        return res;
    }

    int query(int l, int r) const {
        return query(r) - query(l - 1);
    }
};
signed main() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> adj[n + 1];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> depth(n + 1, 0), in(n + 1), out(n + 1), parent(n + 1, 0);
    int cnt = 1;
    function<void(int, int)> dfs = [&](int u, int p) -> void {
        in[u] = cnt++; // just realize that what is logic
        // in[u] = ++cnt;
        for (int v : adj[u]) {
            if (v != p) {
                depth[v] = depth[u] + 1;
                parent[v] = u;
                dfs(v, u);
            }
        }
        out[u] = cnt;
    };
    dfs(1, 0);

    Fenwick ft(n);
    for (int i = 1; i <= n; i++) {
        ft.update(in[i], a[i]);
        ft.update(out[i], -a[i]);
        // ft.update(out[i] + 1, -a[i]);
    }


    while (q--) {
        int qt;
        cin >> qt;

        if (qt == 1) {
            int s, x;
            cin >> s >> x;
            ft.update(in[s], x - a[s]);
            ft.update(out[s], a[s] - x);
            a[s] = x;
        } else {
            int s;
            cin >> s;

            cout << ft.query(in[s]) << endl;
        }
    }
    return 0;
}
