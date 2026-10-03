#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    struct Mat {
        long long a00, a01; // [[a00, a01],
        // a10=0, a11=1 fixed for affine; we omit storing them
        Mat(long long _a00=1, long long _a01=0) : a00(_a00), a01(_a01) {}
    };
    struct Node {
        long long sum;
        Mat tag; // lazy: affine matrix [[a,b],[0,1]]
        Node(long long s=0) : sum(s), tag(1,0) {}
    };

    int n;
    vector<Node> st;

    SegTree(const vector<long long>& v) { init(v); }

    void init(const vector<long long>& v) {
        n = (int)v.size();
        st.assign(4*n, Node());
        build(1, 0, n-1, v);
    }

    void build(int p, int l, int r, const vector<long long>& v) {
        st[p].tag = Mat(1,0);
        if (l == r) { st[p].sum = v[l]; return; }
        int m = (l + r) >> 1;
        build(p<<1, l, m, v);
        build(p<<1|1, m+1, r, v);
        pull(p);
    }

    void pull(int p) {
        st[p].sum = st[p<<1].sum + st[p<<1|1].sum;
    }

    // Compose matrices: G * F
    Mat compose(const Mat& G, const Mat& F) {
        // [[G.a00, G.a01]] * [[F.a00, F.a01]] (affine upper-triangular)
        // = [[G.a00*F.a00, G.a00*F.a01 + G.a01]]
        return Mat(G.a00 * F.a00, G.a00 * F.a01 + G.a01);
    }

    // Apply matrix G to node p covering [l,r]
    void apply(int p, int l, int r, const Mat& G) {
        long long len = (long long)(r - l + 1);
        st[p].sum = G.a00 * st[p].sum + G.a01 * len;
        st[p].tag = compose(G, st[p].tag);
    }

    void push(int p, int l, int r) {
        Mat &T = st[p].tag;
        if (T.a00 == 1 && T.a01 == 0) return;
        int m = (l + r) >> 1;
        apply(p<<1, l, m, T);
        apply(p<<1|1, m+1, r, T);
        T = Mat(1,0);
    }

    // Range apply matrix G on [ql,qr]
    void range_apply(int p, int l, int r, int ql, int qr, const Mat& G) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) { apply(p, l, r, G); return; }
        push(p, l, r);
        int m = (l + r) >> 1;
        range_apply(p<<1, l, m, ql, qr, G);
        range_apply(p<<1|1, m+1, r, ql, qr, G);
        pull(p);
    }

    long long range_sum(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return st[p].sum;
        push(p, l, r);
        int m = (l + r) >> 1;
        return range_sum(p<<1, l, m, ql, qr) + range_sum(p<<1|1, m+1, r, ql, qr);
    }

    // Public API (1-indexed to 0-indexed)
    void add_range(int l, int r, long long x) { // add x: M(1,x)
        range_apply(1, 0, n-1, l, r, Mat(1, x));
    }
    void assign_range(int l, int r, long long x) { // set to x: M(0,x)
        range_apply(1, 0, n-1, l, r, Mat(0, x));
    }
    long long query_sum(int l, int r) {
        return range_sum(1, 0, n-1, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    if (!(cin >> n >> q)) return 0;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    SegTree st(a);
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int l, r; long long x; cin >> l >> r >> x;
            --l; --r;
            st.add_range(l, r, x);
        } else if (t == 2) {
            int l, r; long long x; cin >> l >> r >> x;
            --l; --r;
            st.assign_range(l, r, x);
        } else {
            int l, r; cin >> l >> r;
            --l; --r;
            cout << st.query_sum(l, r) << '\n';
        }
    }
    return 0;
}
