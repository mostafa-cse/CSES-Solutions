#include <bits/stdc++.h>
#define int long long
using namespace std;
struct Node {
    int sum, pfx;
    Node() : sum(0), pfx(0) {}
    Node(int x) : sum(x), pfx(x) {}
    Node operator+(const Node &o) {
        Node ret;
        ret.pfx = max(pfx, sum + o.pfx);
        ret.sum = sum + o.sum;
        return ret; 
    }
};
struct SegmentTree {
    vector<Node> sgt;
    vector<int> a;
    int n;
    SegmentTree(int N) {
        this->n = N;
        a.assign(N + 1, 0);
        sgt.assign(N * 4 + 1, 0);
    }
    Node combine(Node a, Node b) {
        return a + b;        // ➜ sum
    }
    void build (int node, int l, int r) {
        if (l == r) {
            sgt[node] = Node(a[l]);
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
    Node query(int node, int l, int r, int ql, int qr) {
        if (l > qr or r < ql) {
            return Node(0); // Edit here
        }
        if (l >= ql and r <= qr) {
            return sgt[node];
        }
        int mid = l + (r - l) / 2;
        Node left = query(node * 2, l, mid, ql, qr);
        Node right = query(node * 2 + 1, mid + 1, r, ql, qr);
        return combine(left, right);
    }
    void build() { build(1, 1, n); }
    void update(int idx, int val) { update(1, 1, n, idx, val); }
    int query(int l, int r) { return query(1, 1, n, l, r).pfx; }
};
signed main() {
    int n, q;
    cin >> n >> q;

    SegmentTree st(n);
    for (int i = 1; i <= n; i++) {
        cin >> st.a[i];
    }
    st.build();

    while (q--) {
        int qt;
        cin >> qt;

        if (qt == 1) { 
            int k, x;
            cin >> k >> x;
            st.update(k, x);
        } else { 
            int l, r;
            cin >> l >> r;
            cout << max(st.query(l, r), 0ll) << endl;
        }
    }
    return 0;
}