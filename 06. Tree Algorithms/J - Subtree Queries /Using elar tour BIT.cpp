#include <bits/stdc++.h>
#define int long long
using namespace std;
class Fenwick {
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    
    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<vector<int>> adj(n + 1);
    for (int i = 2; i <= n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> in(n + 1, 0), out(n + 1, 0);
    int cnt = 1;
    function<void(int , int) > dfs = [&](int u, int p) -> void {
        in[u] = cnt++;
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u);
            }
        }
        out[u] = cnt++;
    };
    dfs(1, 0);

    Fenwick ft(cnt);
    for (int i = 1; i <= n; i++) {
        ft.update(in[i], a[i]);
    }

    while (q--) {
        int qt;
        cin >> qt;

        if (qt == 1) {
            int node, val;
            cin >> node >> val;

            int delta = a[node] - val;
            ft.update(in[node], -delta);
            a[node] = val;
        } else {
            int node;
            cin >> node;

            int l = in[node];
            int r = out[node];
            cout << ft.query(l, r) << endl;
        }
    }
    return 0;
}
