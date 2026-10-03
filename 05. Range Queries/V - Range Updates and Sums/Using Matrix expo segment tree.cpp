#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    struct Node {
        long long sum;
        long long a, b; // lazy tag: f(x) = a*x + b
        Node(long long s=0, long long aa=1, long long bb=0) : sum(s), a(aa), b(bb) {}
    };
    int n;
    vector<Node> st;
    vector<long long> arr;

    SegTree(const vector<long long>& v) { init(v); }

    void init(const vector<long long>& v) {
        arr = v;
        n = (int)v.size();
        st.assign(4*n, Node());
        build(1, 0, n-1);
    }

    void build(int p, int l, int r) {
        st[p].a = 1; st[p].b = 0;
        if (l == r) {
            st[p].sum = arr[l];
            return;
        }
        int m = (l + r) >> 1;
        build(p<<1, l, m);
        build(p<<1|1, m+1, r);
        pull(p);
    }

    void pull(int p) {
        st[p].sum = st[p << 1].sum + st[p << 1 | 1].sum;
    }

    // apply affine (A,B) on node p covering [l,r]
    void apply(int p, int l, int r, long long A, long long B) {
        st[p].sum = A * st[p].sum + B * (long long)(r - l + 1);
        // compose lazy: new_f = g ∘ f, where g=(A,B), f=(a,b)
        st[p].a = A * st[p].a;
        st[p].b = A * st[p].b + B;
    }

    void push(int p, int l, int r) {
        if (st[p].a == 1 && st[p].b == 0) return;
        int m = (l + r) >> 1;
        apply(p<<1, l, m, st[p].a, st[p].b);
        apply(p<<1|1, m+1, r, st[p].a, st[p].b);
        st[p].a = 1; st[p].b = 0;
    }

    // range apply affine (A,B)
    void range_apply(int p, int l, int r, int ql, int qr, long long A, long long B) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            apply(p, l, r, A, B);
            return;
        }
        push(p, l, r);
        int m = (l + r) >> 1;
        range_apply(p<<1, l, m, ql, qr, A, B);
        range_apply(p<<1|1, m+1, r, ql, qr, A, B);
        pull(p);
    }

    long long range_sum(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return st[p].sum;
        push(p, l, r);
        int m = (l + r) >> 1;
        return range_sum(p<<1, l, m, ql, qr) + range_sum(p<<1|1, m+1, r, ql, qr);
    }

    // Public wrappers (1-indexed input ranges -> convert to 0-indexed)
    void range_add(int l, int r, long long x) { // add x to [l,r]
        range_apply(1, 0, n-1, l, r, 1, x);
    }
    void range_assign(int l, int r, long long x) { // set to x on [l,r]
        range_apply(1, 0, n-1, l, r, 0, x);
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
            st.range_add(l, r, x);
        } else if (t == 2) {
            int l, r; long long x; cin >> l >> r >> x;
            --l; --r;
            st.range_assign(l, r, x);
        } else {
            int l, r; cin >> l >> r;
            --l; --r;
            cout << st.query_sum(l, r) << '\n';
        }
    }
    return 0;
}
