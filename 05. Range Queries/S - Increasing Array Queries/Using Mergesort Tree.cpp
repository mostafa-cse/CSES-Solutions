#include <bits/stdc++.h>
#define int long long
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
struct Node {
    int sum;
    vector<int> all, preSum;
};
const int M = 1e6;
Node sgt[M];
int ar[M];
vector<int> point;
struct MergeSortTree {
    int n;
    vector<Node> sgt;
    vector<int> ar;
    MergeSortTree(int N) {
        this->n = N;
    }
    void combine(Node &a, Node &b, Node &ans) {
        ans.sum = a.sum + b.sum;
        if (a.all.empty()) {
            ans.all = b.all;
            ans.preSum = b.preSum;
            return;
        }
        ans.all = a.all;
        ans.preSum = a.preSum;

        int mx = a.all.back();
        for (int i = 0; i < (int)b.all.size(); ++i) {
            if (b.all[i] < mx) {
                ans.sum += mx - b.all[i];
                ans.all.push_back(mx);
            } else {
                ans.all.push_back(b.all[i]);
            }
            int mxx = ans.preSum.back();
            ans.preSum.push_back(mxx + ans.all.back());
        }
    }

    void build(int node, int l, int r) {
        if (l == r) {
            sgt[node].all.push_back(ar[l]);
            sgt[node].preSum.push_back(ar[l]);
            sgt[node].sum = 0;
            return;
        }
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        combine(sgt[node * 2], sgt[node * 2 + 1], sgt[node]);
    }

    void query(int node, int l, int r, int ql, int qr) {
        if (r < ql || l > qr) return;
        if (ql <= l && r <= qr) {
            point.push_back(node);
            return;
        }
        int mid = (l + r) / 2;
        query(node * 2, l, mid, ql, qr);
        query(node * 2 + 1, mid + 1, r, ql, qr);
    }

    void build() { build(1, 1, n); }
    void query(int l, int r) { query(1, 1, n, l, r); }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    int n, q;
    cin >> n >> q;

    MergeSortTree a(n);
    for (int i = 1; i <= n; ++i) {
        cin >> ar[i];
    }
    a.build();

    while (q--) {
        int l, r;
        cin >> l >> r;
        point.clear();
        a.query(l, r);


        int sum = 0;
        sum = sgt[point[0]].sum;
        int mx = sgt[point[0]].all.back();

        for (int i = 1; i < (int)point.size(); ++i) {
            sum += sgt[point[i]].sum;
            int low = lower_bound(sgt[point[i]].all.begin(), sgt[point[i]].all.end(), mx) - sgt[point[i]].all.begin();
            if (low > 0) {
                sum += low * mx - sgt[point[i]].preSum[low - 1];
            }
            mx = max(mx, sgt[point[i]].all.back());
        }
        cout << sum << endl;
    }
    return 0;
}
