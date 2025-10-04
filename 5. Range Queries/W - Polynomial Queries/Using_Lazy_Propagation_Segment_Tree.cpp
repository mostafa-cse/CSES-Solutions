#include <bits/stdc++.h>
#define int long long
using namespace std;
struct Node {
    int sum;
    int add;
    int how;
    Node() : sum(0), add(0), how(0) {}
};
struct segment_tree{
    vector<int> a;
    vector<Node> sgt;
    int n;
    segment_tree(int N) {
        this->n = N;
        a.assign(n + 1, 0);
        sgt.resize((n + 1) * 4);
    }
    void push(int node, int start, int end) {
        if (sgt[node].how) { // you can use also 'add'
            int length = end - start + 1;
            sgt[node].sum += length * sgt[node].add;
            sgt[node].sum += length * (length - 1) * sgt[node].how * 0.5;
            if (start != end) {
                sgt[node * 2].add += sgt[node].add;
                sgt[node * 2].how += sgt[node].how;

                sgt[node * 2 + 1].add += sgt[node].add;

                // right element will start with different sum value
                int mid = (start + end) / 2;
                sgt[node * 2 + 1].add += sgt[node].how * (mid - start + 1);

                sgt[node * 2 + 1].how += sgt[node].how;
            }
            sgt[node].add = sgt[node].how = 0;
        }
    }
    void build(int node, int start, int end){
        if (start == end) {
            sgt[node].sum = a[start];
            return;
        }
        int mid = start + (end - start) / 2;
        build(node * 2, start, mid);
        build(node * 2 + 1, mid + 1, end);
        sgt[node].sum = sgt[2 * node].sum + sgt[2 * node + 1].sum;
    }
    void update(int node, int start, int end, int l, int r){
        push(node, start, end);
        if (start > r or end < l) {
            return;
        }
        if (start >= l and  r >= end){
            sgt[node].add += (start - l + 1);
            sgt[node].how += 1;
            push(node, start, end);
            return;
        }
        int mid = start + (end - start) / 2;
        update(node * 2, start, mid, l, r);
        update(node * 2 + 1, mid + 1, end, l, r);
        sgt[node].sum = sgt[2 * node].sum + sgt[2 * node + 1].sum;
    }
    int query(int node, int start, int end, int ql, int qr) {
        push(node, start, end);
        if (start > qr or end < ql) {
            return 0; // Edit here
        }
        if (start >= ql and end <= qr) {
            return sgt[node].sum;
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
