#include <bits/stdc++.h>
#define int long long
using namespace std;
struct SegmentTree {
    vector<int> sgt;
    vector<int> a;
    int n;
    SegmentTree(int N) {
        this->n = N;
        a.assign(n + 1, 0);
        sgt.assign((n + 1) * 4 + 1, 0);
    }
    int combine(int a, int b) {
        return a + b;        // ➜ sum
    }
    void update(int node, int l, int r, int idx, int value) {
        if (l == r) {
            sgt[node] = value;
            return;
        }
        int mid = l + (r - l) / 2;
        if(idx <= mid) {
            update(node * 2, l, mid, idx, value);
        } else {
            update(node * 2 + 1, mid + 1, r, idx, value);
        }
        sgt[node] = combine(sgt[2 * node], sgt[2 * node + 1]);
    }
    int query(int node, int l, int r, int ql, int qr) {
        if (l > qr or r < ql) {
            return 0; // Edit here
        }
        if (l >= ql and r <= qr) {
            return sgt[node];
        }
        int mid = l + (r - l) / 2;
        int left = query(node * 2, l, mid, ql, qr);
        int right = query(node * 2 + 1, mid + 1, r, ql, qr);
        return combine(left, right);
    }
    void update(int idx, int val) { update(1, 1, n, idx, val); }
    int query(int l, int r) { return query(1, 1, n, l, r); }
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
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> in(n + 1, 0), out(n + 1, 0);
    int cnt = 1;
    function<void(int, int)> dfs = [&](int u, int p) -> void {
        in[u] = cnt++;
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u);
            }
        }
        out[u] = cnt++;
    };

    dfs(1, 0);
    SegmentTree st(cnt);
    for (int i = 1; i <= n; i++) {
        st.update(in[i], a[i]);
    }

    while (q--) {
        int qt;
        cin >> qt;

        if (qt == 1) {
            int id, x;
            cin >> id >> x;
            st.update(in[id], x);
        } else {
            int node;
            cin >> node;

            int l = in[node];
            int r = out[node];
            cout << st.query(l, r) << endl;
        }
    }
    return 0;
}
