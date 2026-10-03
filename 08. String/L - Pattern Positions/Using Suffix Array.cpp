#include <bits/stdc++.h>
#define int long long
using namespace std;
struct SuffixArray {
    string s;
    int n;
    vector<int> sa;
    vector<int> ra;
    vector<int> lcp;
    SuffixArray(string &x) : s(x) {
        s += "$";
        n = s.size();
        constructSA();
    }
    void countingSort(int k) {
        int mxRank = max(300ll, n);
        vector<int> count(mxRank, 0);
        vector<int> temp_sa(n);

        // Frequency count
        for (int i = 0; i < n; i++) {
            int currRank = (i + k < n) ? ra[i + k] : 0;
            count[currRank]++;
        }

        for (int i = 1; i < mxRank; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            int second_half_idx = (sa[i] + k < n) ? ra[sa[i] + k] : 0;
            // Decrement count first to get 0-based index
            temp_sa[--count[second_half_idx]] = sa[i];
        }

        sa = temp_sa;
    }

    void constructSA() {
        sa.resize(n);
        ra.resize(n);

        vector<int> temp_r(n);
        for (int i = 0; i < n; i++) {
            ra[i] = s[i];
            sa[i] = i;
        }

        for (int k = 1; k < n; k *= 2) {
            countingSort(k); // Sort by second half
            countingSort(0); // Sort by first half (stable sort preserves second half order)

            int r = 0;
            temp_r[sa[0]] = 0;
            for (int i = 1; i < n; i++) {
                pair<int, int> prev = {ra[sa[i - 1]],
                                       (sa[i - 1] + k < n) ? ra[sa[i - 1] + k] : 0};
                pair<int, int> cur = {ra[sa[i]],
                                      (sa[i] + k < n) ? ra[sa[i] + k] : 0};

                if (cur != prev) r++;
                temp_r[sa[i]] = r;
            }
            ra = temp_r;
            if (ra[sa[n - 1]] == n - 1) {
                break;
            }
        }
    }
    pair<int, int> find(string p) {
        int m = p.size();
        auto left = sa.begin();
        auto right = sa.end();
        for (int i = 0; i < m; i++) {
            auto cmp = [&](int e, int v) {
                return s[e + i] < v;
            };
            auto new_left = lower_bound(left, right, p[i], cmp);
            auto new_right = lower_bound(left, right, p[i] + 1, cmp);
            left = new_left;
            right = new_right;
        }
        return {left - sa.begin(), right - sa.begin()};
    }
};
struct SegmentTree {
    vector<int> sgt;
    vector<int> a;
    int n;
    SegmentTree(int N) {
        this->n = N;
        a.assign(N + 1, 0);
        sgt.assign(N * 4 + 1, 0);
    }
    int combine(int a, int b) {
        return min(a, b); // ➜ sum
    }
    void build (int node, int l, int r) {
        if (l == r) {
            sgt[node] = a[l];
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
    int query(int node, int l, int r, int ql, int qr) {
        if (l > qr or r < ql) {
            return 1e18; // Edit here
        }
        if (l >= ql and r <= qr) {
            return sgt[node];
        }
        int mid = l + (r - l) / 2;
        int left = query(node * 2, l, mid, ql, qr);
        int right = query(node * 2 + 1, mid + 1, r, ql, qr);
        return combine(left, right);
    }
    void build() { build(1, 1, n); }
    void update(int idx, int val) { update(1, 1, n, idx, val); }
    int query(int l, int r) { return query(1, 1, n, l, r); }
};
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string t;
    cin >> t;

    SuffixArray sa(t);

    SegmentTree st(sa.sa.size());
    st.a = sa.sa;
    st.build();

    int k;
    cin >> k;
    while (k--) {
        string p;
        cin >> p;

        auto [l, r] = sa.find(p); // [l, r - 1]
        int ans = st.query(l, r - 1);
        cout << (ans > t.size() ? -1 : ans + 1)<< endl;
    }
    return 0;
}
