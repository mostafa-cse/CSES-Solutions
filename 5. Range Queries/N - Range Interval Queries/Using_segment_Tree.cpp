#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
#define int long long
using namespace std;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> PBDS;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
struct Node {
    PBDS val;
    Node() {}
    Node operator+(const Node &o) {
        Node ans;
        ans.val = val;
        for (auto el : o.val) {
            ans.val.insert(el);
        }
        return ans;
    }
};
struct SegmentTree {
    vector<Node> sgt;
    vector<int> a;
    int n;
    SegmentTree(int N) {
        this->n = N;
        a.assign(N + 1, 0);
        sgt.resize(4 * n);
    }
    Node combine(Node a, Node b) {
        return a + b; 
    }
    void build (int node, int l, int r) {
        if (l == r) {
            sgt[node].val.insert(a[l]);
            return;
        }
        int mid = l + (r - l) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        sgt[node] = combine(sgt[2 * node], sgt[2 * node + 1]);
    }
    int query(int node, int l, int r, int ql, int qr, int a, int b) {
        if (l > qr or r < ql) {
            return 0;
        }
        if (l >= ql and r <= qr) {
            // dout(l, r, a, b);
            // dout(sgt[node].val);
            int posr = sgt[node].val.order_of_key(b + 1);
            int posl = sgt[node].val.order_of_key(a);
            // dout(a, posl);
            // dout(b, posr);
            return posr - posl;
        }
        int mid = l + (r - l) / 2;
        int left = query(node * 2, l, mid, ql, qr, a, b);
        int right = query(node * 2 + 1, mid + 1, r, ql, qr, a, b);
        return (left + right);
    }
    void build() { build(1, 1, n); }
    int query(int l, int r, int a, int b) { return query(1, 1, n, l, r, a, b); }
};
signed main() {
    int n, q;
    cin >> n >> q;

    SegmentTree a(n);
    for (int i = 1; i <= n; i++) {
        cin >> a.a[i];
    }

    a.build();
    while(q--) {
        int l, r, la, rb;
        cin >> l >> r >> la >> rb;

        cout << a.query(l, r, la, rb) << endl;
    }
    return 0;
}
