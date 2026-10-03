#include <bits/stdc++.h>
#define int long long
using namespace std;

struct Node {
    array<int, 32> mn;
    Node(int x = 0) {
        mn.fill((int)9e18);
        if (x) {
            int lg = 63 - __builtin_clzll((unsigned long long)x);
            mn[lg] = x;
        }
    }
};

static inline Node mergeNode(const Node &L, const Node &R) {
    Node res;
    for (int i = 0; i < 32; ++i) res.mn[i] = std::min(L.mn[i], R.mn[i]);
    return res;
}
struct SegmentTree {
    vector<Node> sgt;
    vector<int> a;
    int n;
    SegmentTree(int N) {
        this->n = N;
        a.assign(n + 1, 0);
        sgt.resize((n + 1) * 4 + 1);
    }
    void build (int node, int l, int r) {
        if (l == r) {
            sgt[node] = Node(a[l]);
            return;
        }
        int mid = l + (r - l) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);

        // combine both side
        for (int i = 0; i < 32; i++) {
            sgt[node].mn[i] = std::min(sgt[node * 2].mn[i], sgt[node * 2 + 1].mn[i]);
        }
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

        // combine both side
        for (int i = 0; i < 32; i++) {
            sgt[node].mn[i] = std::min(sgt[node * 2].mn[i], sgt[node * 2 + 1].mn[i]);
        }
    }
    Node query(int node, int l, int r, int ql, int qr) {
        if (l > qr or r < ql) {
            return Node(); // Edit here
        }
        if (l >= ql and r <= qr) {
            return sgt[node];
        }
        int mid = l + (r - l) / 2;
        Node left = query(node * 2, l, mid, ql, qr);
        Node right = query(node * 2 + 1, mid + 1, r, ql, qr);
        return mergeNode(left, right);
    }
    void build() { build(1, 1, n); }
    void update(int idx, int val) { update(1, 1, n, idx, val); }
    array<int, 32> query(int l, int r) { return query(1, 1, n, l, r).mn; }
};
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, q;
    cin >> n >> q;

    SegmentTree a(n);
    vector<array<int, 32>> sum(n + 1);
    for (int i = 0; i <= n; ++i) sum[i].fill(0);
    for (int i = 1; i <= n; i++) {
        cin >> a.a[i];
        int lg = 63 - __builtin_clzll((unsigned long long)a.a[i]);
        sum[i][lg] = a.a[i];
    }
    a.build();

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 32; j++) {
            sum[i][j] += sum[i - 1][j];
        }
    }

    while (q--) {
        int l, r;
        cin >> l >> r;

        auto res = a.query(l, r);
        int ans = 1;
        for (int i = 0; i < 32; i++) {
            if (ans < (1LL << (i + 1)) and ans < res[i]) {
                break;
            }
            ans += (sum[r][i] - sum[l - 1][i]);
        }
        cout << ans << '\n';
        break;
    }
    return 0;
}
