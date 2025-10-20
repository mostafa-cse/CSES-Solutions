#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+4;
int n, a[maxn], in[maxn], out[maxn], last[maxn], order[maxn], ans[maxn];
vector<int> adj[maxn];

class Fenwick {
    int n;
    std::vector<int> bit;

public:
    explicit Fenwick(int n) : n(n), bit(n + 1, 0) {}

    void update(int idx, int delta) {
        for (; idx <= n; idx += idx & -idx) {
            bit[idx] += delta;
        }
    }

    int query(int idx) const {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx) {
            res += bit[idx];
        }
        return res;
    }

    int query(int l, int r) const {
        return query(r) - query(l - 1);
    }
};

int t = 0;
void dfs(int u = 1, int p = 0) {
    in[u] = ++t;
    order[t] = u;

    for (int v: adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    out[u] = t;
}
vector<int> idx[maxn];
int32_t main (){
    ios_base::sync_with_stdio (false);
    cin.tie (nullptr);

    cin >> n;
    vector<int> V;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        V.push_back(a[i]);
    }

    sort(V.begin(), V.end());
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(V.begin(), V.end(), a[i]) - V.begin() + 1;
    }

    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;

        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs();
    for (int i = 1; i <= n; i++) {
        idx[out[i]].push_back(i);
    }

    Fenwick bit(n);
    for (int r = 1; r <= n; r++) {
        bit.update(r, 1);

        int u = order[r];
        int color = a[u];

        if (last[color] > 0) {
            bit.update(last[color], -1); // delete previously added color
        }
        last[color] = r; // add last time added color 

        for (int i: idx[r]) {
            int l = in[i];
            ans[i] = bit.query(l, r);
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}
