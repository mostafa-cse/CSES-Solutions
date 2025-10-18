#include <bits/stdc++.h>
#define int long long
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
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
    void build (int node, int l, int r) {
        if (l == r) {
            sgt[node] = a[l];
            return;
        }
        int mid = l + (r - l) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        sgt[node] = combine(sgt[2 * node], sgt[2 * node + 1]);
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
    void build() { build(1, 1, n); }
    void update(int idx, int val) { update(1, 1, n, idx, val); }
    int query(int l, int r) { return query(1, 1, n, l, r); }
};
signed main() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> adj[n + 1];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> in(n + 1, 0), out(n + 1, 0);
    int cnt = 0;
    function<void(int, int)> dfs = [&](int u, int p) -> void {
        in[u] = ++cnt;
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u);
            }
        }
        out[u] = ++cnt;
    };
    dfs(1, 0);

    SegmentTree st(2 * n + 1);
    for (int i = 1; i <= n; i++) {
        st.a[in[i]] = a[i];
        st.a[out[i]] = -a[i];
    }
    st.build();

    while (q--) {
        int qt;
        cin >> qt;

        if (qt == 1) {
            int s, x;
            cin >> s >> x;
            st.update(in[s], x);
            st.update(out[s], -x);
        } else {
            int s;
            cin >> s;
            cout << st.query(in[1], in[s]) << endl;
        }
    }
    return 0;
}
