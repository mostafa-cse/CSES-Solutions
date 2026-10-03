#include <bits/stdc++.h>
using namespace std;
#define int long long

class PersistentSegmentTree {
private:
    struct node {
        int x = 0;
        int l = 0, r = 0;
        node() {};
    };

    int new_node() {
        st.push_back(node());
        return (int)st.size() - 1;
    }

    int build(int L, int R) {
        int p = new_node();
        if (L == R) {
            st[p].x = A[L];
            return p;
        }

        int m = (L + R) >> 1;
        int lc = build(L, m);
        int rc = build(m + 1, R);
        st[p].l = lc;
        st[p].r = rc;
        st[p].x = st[lc].x + st[rc].x;
        return p;
    }

    int upd(int prev, int L, int R, int i, int val) {
        int p = new_node();
        st[p] = st[prev];
        if (L == R) {
            st[p].x = val;
            return p;
        }
        int m = (L + R) >> 1;
        if (i <= m) {
            st[p].l = upd(st[prev].l, L, m, i, val);
        } else {
            st[p].r = upd(st[prev].r, m + 1, R, i, val);
        }
        st[p].x = st[st[p].l].x + st[st[p].r].x;
        return p;
    }

    int query(int p, int L, int R, int i, int j) {
        if (!p || j < L || R < i) {
            return 0;
        }
        if (i <= L && R <= j) {
            return st[p].x;
        }
        int m = (L + R) >> 1;
        int left = query(st[p].l, L, m, i, j);
        int right = query(st[p].r, m + 1, R, i, j);
        return left + right;
    }

public:
    int n;
    vector<int> A;
    vector<node> st;
    PersistentSegmentTree(int sz) : n(sz), A(n + 1) {
        st.reserve((size_t)n * 25 + 10);
        st.push_back(node());
    }
    int build() { return build(1, n); }
    int upd(int root, int i, int val) { return upd(root, 1, n, i, val); }
    int query(int root, int i, int j) { return query(root, 1, n, i, j); }
};

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, q;
    cin >> n >> q;
    PersistentSegmentTree st(n);
    for (int i = (1); i < (n + 1); i++) {
        cin >> st.A[i];
    }

    int root0 = st.build();
    vector<int> root;
    root.push_back(0); // make 1-Based
    root.push_back(root0);

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int k, a, x;
            cin >> k >> a >> x;
            int newRoot = st.upd(root[k], a, x);
            root[k] = newRoot;
        } else if (t == 2) {
            int k, a, b;
            cin >> k >> a >> b;
            cout << st.query(root[k], a, b) << endl;
        } else { // t == 3
            int k;
            cin >> k;
            root.push_back(root[(int)k]);
        }
    }
    return 0;
}
