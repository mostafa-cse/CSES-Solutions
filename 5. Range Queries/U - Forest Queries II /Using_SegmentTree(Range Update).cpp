#include <bits/stdc++.h>
using namespace std;

struct SegTree1D {
    int n;
    vector<int> t; // 4*n
    SegTree1D(int n=0): n(n), t(4*n, 0) {}
    void init(int N) { n = N; t.assign(4*n, 0); }
    void update(int v, int tl, int tr, int pos, int delta) {
        if (tl == tr) { t[v] += delta; return; }
        int tm = (tl + tr) >> 1;
        if (pos <= tm) update(v<<1, tl, tm, pos, delta);
        else update(v<<1|1, tm+1, tr, pos, delta);
        t[v] = t[v<<1] + t[v<<1|1];
    }
    int query(int v, int tl, int tr, int l, int r) const {
        if (l > r) return 0;
        if (l == tl && r == tr) return t[v];
        int tm = (tl + tr) >> 1;
        return query(v<<1, tl, tm, l, min(r, tm))
             + query(v<<1|1, tm+1, tr, max(l, tm+1), r);
    }
};

struct SegTree2D {
    int n;
    vector<SegTree1D> tree;
    SegTree2D(int N=0): n(N), tree(4*N, SegTree1D(N)) {}
    void init(int N) { n = N; tree.assign(4*n, SegTree1D()); for (auto &st: tree) st.init(n); }

    void _upd_x(int v, int x, int delta) { tree[v].update(1, 1, n, x, delta); }

    void update(int v, int tl, int tr, int y, int x, int delta) {
        _upd_x(v, x, delta);
        if (tl == tr) return;
        int tm = (tl + tr) >> 1;
        if (y <= tm) update(v<<1, tl, tm, y, x, delta);
        else update(v<<1|1, tm+1, tr, y, x, delta);
    }

    int query_x(int v, int x1, int x2) const { return tree[v].query(1, 1, n, x1, x2); }

    int query(int v, int tl, int tr, int y1, int y2, int x1, int x2) const {
        if (y1 > y2) return 0;
        if (y1 == tl && y2 == tr) return query_x(v, x1, x2);
        int tm = (tl + tr) >> 1;
        return query(v<<1, tl, tm, y1, min(y2, tm), x1, x2)
             + query(v<<1|1, tm+1, tr, max(y1, tm+1), y2, x1, x2);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<string> g(n+1);
    for (int i = 1; i <= n; ++i) {
        string s; cin >> s;
        g[i] = " " + s;
    }

    SegTree2D st(n);
    st.init(n);

    vector<vector<int>> a(n+1, vector<int>(n+1, 0));

    for (int y = 1; y <= n; ++y) {
        for (int x = 1; x <= n; ++x) {
            if (g[y][x] == '*') {
                a[y][x] = 1;
                st.update(1, 1, n, y, x, +1);
            }
        }
    }

    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int y, x; cin >> y >> x;
            int newv = 1 - a[y][x];
            int delta = newv - a[y][x];
            a[y][x] = newv;
            st.update(1, 1, n, y, x, delta);
        } else {
            int y1, x1, y2, x2; cin >> y1 >> x1 >> y2 >> x2;
            cout << st.query(1, 1, n, y1, y2, x1, x2) << '\n';
        }
    }
    return 0;
}
