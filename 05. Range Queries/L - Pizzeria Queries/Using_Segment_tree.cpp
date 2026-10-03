#include <bits/stdc++.h>
#define int long long
using namespace std;
const int SZ = 5e5 + 123;
vector<int> a(SZ);
vector<array<int, 2>> sgt(4 * SZ);
void merge(int node) {
    sgt[node][0] = min(sgt[node * 2][0], sgt[node * 2 + 1][0]);             // Min
    sgt[node][1] = min(sgt[node * 2][1], sgt[node * 2 + 1][1]);             // Min
}
int Ans(int &left, int &right) {
    return min(left, right);
}
void build (int node, int l, int r) {
    if (l == r) {
        sgt[node][0] = a[l] - l;
        sgt[node][1] = a[l] + l;
        return;
    }
    int mid = l + (r - l) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    merge(node);
}
void update(int node, int l, int r, int idx, int value) {
    if (l == r) {
        sgt[node][0] = value - l;
        sgt[node][1] = value + l;
        return;
    }
    int mid = l + (r - l) / 2;
    if(idx <= mid) {
        update(node * 2, l, mid, idx, value);
    } else {
        update(node * 2 + 1, mid + 1, r, idx, value);
    }
    merge(node);
}
int query(int node, int l, int r, int ql, int qr, int dir) {
    if (l > qr or r < ql) {
        return 1e15; // Edit here
    }
    if (l >= ql and r <= qr) {
        return sgt[node][dir];
    }
    int mid = l + (r - l) / 2;
    int left = query(node * 2, l, mid, ql, qr, dir);
    int right = query(node * 2 + 1, mid + 1, r, ql, qr, dir);
    return Ans(left, right);
}
signed main() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build(1, 1, n);

    while (q--) {
        int c;
        cin >> c;

        if (c & 1) {
            int idx, val;
            cin >> idx >> val;
            update(1, 1, n, idx, val);
        } else {
            int k;
            cin >> k;
            int pre = query(1, 1, n, 1, k, 0);
            int post = query(1, 1, n, k, n, 1);
            cout << min(pre + k, post - k) << endl;
        }
    }
    return 0;
}