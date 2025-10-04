#include <bits/stdc++.h>
#define int long long
using namespace std;
struct segment_tree{
    vector<int> a;
    vector<int> sum, lazy_a, lazy_d;
    int n;
    segment_tree(int N) {
        this->n = N;
        a.assign(n + 1, 0);
        sum.assign((n + 1)* 4, 0);
        lazy_a.assign((n + 1) * 4, 0);
        lazy_d.assign((n + 1) * 4, 0);
    }
    void push(int node, int start, int end) {
        if (lazy_a[node] || lazy_d[node]) {
            int len = end - start + 1;
            sum[node] += lazy_a[node] * len + lazy_d[node] * len * (len - 1) / 2;
            if (start != end) {
                int mid = (start + end) / 2;
                int left = node * 2, right = node * 2 + 1;
                int left_len = mid - start + 1;

                // Left child
                lazy_a[left] += lazy_a[node];
                lazy_d[left] += lazy_d[node];

                // Right child
                // mid'th element, n'th = a + (n - 1) * d
                lazy_a[right] += lazy_a[node] + lazy_d[node] * left_len;
                lazy_d[right] += lazy_d[node];
            }
            lazy_a[node] = 0;
            lazy_d[node] = 0;
        }
    }
    void build(int node, int start, int end){
        if (start == end) {
            sum[node] = a[start];
            return;
        }
        int mid = start + (end - start) / 2;
        build(node * 2, start, mid);
        build(node * 2 + 1, mid + 1, end);
        sum[node] = sum[2 * node] + sum[2 * node + 1];
    }
    void update(int node, int start, int end, int l, int r){
        push(node, start, end);
        if (start > r || end < l) {
            return;
        }
        if (start >= l && end <= r){
            lazy_a[node] += (start - l + 1);
            lazy_d[node] += 1;
            push(node, start, end);
            return;
        }
        int mid = start + (end - start) / 2;
        update(node * 2, start, mid, l, r);
        update(node * 2 + 1, mid + 1, end, l, r);
        sum[node] = sum[2 * node] + sum[2 * node + 1];
    }
    int query(int node, int start, int end, int ql, int qr) {
        push(node, start, end);
        if (start > qr or end < ql) {
            return 0; // Edit here
        }
        if (start >= ql and end <= qr) {
            return sum[node];
        }
        int mid = start + (end - start) / 2;
        int left = query(node * 2, start, mid, ql, qr);
        int right = query(node * 2 + 1, mid + 1, end, ql, qr);
        return (left + right);
    }
    void build() { build(1, 1, n); }
    void update(int l, int r) { update(1, 1, n, l, r); }
    int query(int l, int r) { return query(1, 1, n, l, r); }
};

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, q;
    cin >> n >> q;

    segment_tree a(n);
    for (int i = 1; i <= n; i++) {
        cin >> a.a[i];
    }
    a.build();
    for (int i = 0; i < q; i++) {
        int qt, l, r;
        cin >> qt >> l >> r;

        if (qt == 1) {
            a.update(l, r);
        } else {
            cout << a.query(l, r) << endl;
        }
    }
    return 0;
}
