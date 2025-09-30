#include <bits/stdc++.h>
using namespace std;
#define int long long

struct LazySegmentTree {
    int n;
    vector<int> tree, lazy_add, lazy_set;
    vector<bool> has_set;

    LazySegmentTree(vector<int> &arr) {
        n = arr.size() - 1; // 1-indexed
        tree.resize(4 * n + 1);
        lazy_add.resize(4 * n + 1);
        lazy_set.resize(4 * n + 1);
        has_set.resize(4 * n + 1);
        build(1, 1, n, arr);
    }

    void build(int node, int start, int end, vector<int> &arr) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(2 * node, start, mid, arr);
            build(2 * node + 1, mid + 1, end, arr);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    void push(int node, int start, int end) {
        if (has_set[node]) {
            tree[node] = lazy_set[node] * (end - start + 1);
            if (start != end) {
                lazy_set[2 * node] = lazy_set[node];
                lazy_set[2 * node + 1] = lazy_set[node];
                has_set[2 * node] = has_set[2 * node + 1] = true;
                lazy_add[2 * node] = lazy_add[2 * node + 1] = 0;
            }
            has_set[node] = false;
            lazy_set[node] = 0;
        }

        if (lazy_add[node] != 0) {
            tree[node] += lazy_add[node] * (end - start + 1);
            if (start != end) {
                if (has_set[2 * node]) {
                    lazy_set[2 * node] += lazy_add[node];
                } else {
                    lazy_add[2 * node] += lazy_add[node];
                }
                if (has_set[2 * node + 1]) {
                    lazy_set[2 * node + 1] += lazy_add[node];
                } else {
                    lazy_add[2 * node + 1] += lazy_add[node];
                }
            }
            lazy_add[node] = 0;
        }
    }

    void updateRange(int node, int start, int end, int l, int r, int val, int type) {
        push(node, start, end);
        if (start > r || end < l) return;

        if (start >= l && end <= r) {
            if (type == 1) { // increment
                lazy_add[node] += val;
            } else { // set
                lazy_set[node] = val;
                has_set[node] = true;
                lazy_add[node] = 0;
            }
            push(node, start, end);
            return;
        }

        int mid = (start + end) / 2;
        updateRange(2 * node, start, mid, l, r, val, type);
        updateRange(2 * node + 1, mid + 1, end, l, r, val, type);

        push(2 * node, start, mid);
        push(2 * node + 1, mid + 1, end);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    int queryRange(int node, int start, int end, int l, int r) {
        if (start > r || end < l) return 0;

        push(node, start, end);
        if (start >= l && end <= r) {
            return tree[node];
        }

        int mid = (start + end) / 2;
        int left = queryRange(2 * node, start, mid, l, r);
        int right = queryRange(2 * node + 1, mid + 1, end, l, r);
        return left + right;
    }

    void update(int l, int r, int val, int type) {
        updateRange(1, 1, n, l, r, val, type);
    }

    int query(int l, int r) {
        return queryRange(1, 1, n, l, r);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    LazySegmentTree seg(a);

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) { // increment
            int l, r, val;
            cin >> l >> r >> val;
            seg.update(l, r, val, 1);
        } else if (type == 2) { // set
            int l, r, val;
            cin >> l >> r >> val;
            seg.update(l, r, val, 2);
        } else { // query
            int l, r;
            cin >> l >> r;
            cout << seg.query(l, r) << "\n";
        }
    }

    return 0;
}
