#include <bits/stdc++.h>
using namespace std;

// Persistent segment tree for range sum over positions, built by adding items in order of value.
// Allows sum of values <= k in subarray [L, R] via version corresponding to k.

struct PersistentSegTree {
    static const int MAXN = 200000 + 5;
    static const int MAXNODE = 4000000 + 50; // ~ n * log2(n) * 20% headroom

    int n{};
    int lc[MAXNODE], rc[MAXNODE];
    long long sum[MAXNODE];
    int root[MAXN];
    int ptr = 0; // 0 is the null node with zeros

    int buildEmpty(int s, int e) { return 0; }

    int update(int prev, int s, int e, int pos, long long val) {
        int cur = ++ptr;
        lc[cur] = lc[prev];
        rc[cur] = rc[prev];
        sum[cur] = sum[prev] + val;
        if (s == e) return cur;
        int m = (s + e) >> 1;
        if (pos <= m) lc[cur] = update(lc[prev], s, m, pos, val);
        else rc[cur] = update(rc[prev], m + 1, e, pos, val);
        return cur;
    }

    long long query(int node, int s, int e, int l, int r) const {
        if (!node || r < s || e < l) return 0LL;
        if (l <= s && e <= r) return sum[node];
        int m = (s + e) >> 1;
        return query(lc[node], s, m, l, r) + query(rc[node], m + 1, e, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    // Prepare value-index pairs and sort by value
    vector<pair<long long,int>> vp;
    vp.reserve(n);
    for (int i = 1; i <= n; ++i) vp.emplace_back(a[i], i);
    sort(vp.begin(), vp.end());

    // Build persistent tree versions
    static PersistentSegTree pst; // static to avoid stack issues
    pst.n = n;
    pst.root[0] = 0; // empty
    for (int i = 1; i <= n; ++i) {
        long long val = vp[i - 1].first;
        int pos = vp[i - 1].second;
        pst.root[i] = pst.update(pst.root[i - 1], 1, n, pos, val);
    }

    auto sum_leq = [&](int L, int R, long long K) -> long long {
        int idx = upper_bound(vp.begin(), vp.end(), make_pair(K, INT_MAX)) - vp.begin();
        if (idx <= 0) return 0LL;
        return pst.query(pst.root[idx], 1, n, L, R);
    };

    // Precompute total sums per range quickly via version for all values
    while (q--) {
        int L, R; cin >> L >> R;
        long long total = pst.query(pst.root[n], 1, n, L, R);
        long long sum = 0;
        for (int iter = 0; ; ++iter) {
            if (sum >= total) { cout << (sum + 1) << '\n'; break; }
            long long nextSum = sum_leq(L, R, sum + 1);
            if (nextSum == sum) { cout << (sum + 1) << '\n'; break; }
            sum = nextSum;
            if (iter > 64) { cout << (sum + 1) << '\n'; break; }
        }
    }

    return 0;
}
