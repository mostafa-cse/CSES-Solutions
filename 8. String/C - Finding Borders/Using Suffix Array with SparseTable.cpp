#include <bits/stdc++.h>
using namespace std;

struct SparseTable {
    int n, K;
    vector<int> lg;
    vector<vector<int>> st; // st[k][i] covers range [i, i + 2^k - 1]              
    SparseTable() : n(0), K(0) {}

    explicit SparseTable(const vector<int> &a) { build(a); }

    void build(const vector<int>& a) {
        n = (int)a.size();
        if (n == 0) { K = 0; lg.clear(); st.clear(); return; }
        K = 32 - __builtin_clz((unsigned)n); // number of levels
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;

        st.assign(K, vector<int>(n));
        st[0] = a;
        for (int k = 1; k < K; ++k) {
            int len = 1 << k;
            int half = len >> 1;
            for (int i = 0; i + len - 1 < n; ++i) {
                st[k][i] = min(st[k - 1][i], st[k - 1][i + half]);
            }
        }
    }

    int query(int l, int r) const {
        if (l > r) swap(l, r);
        int len = r - l + 1;
        int k = lg[len];
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }
};
struct SuffixArray {
    string s;
    int n;
    vector<int> sa;
    vector<int> ra;
    vector<int> lcp;
    SparseTable getlcp;

    SuffixArray(string &x) : s(x) {
        s += "$";
        n = s.size();

        constructSA();
        constructLCP();
    }

    void countingSort(int k) {
        int mxRank = max(300, n);
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

    void constructLCP() {
        lcp.assign(n, 0);
        int k = 0;

        for (int i = 0; i < n - 1; i++) {
            int pi = ra[i];

            if(pi == 0) {
                k = 0;
                continue;
            }

            int j = sa[pi - 1];
            while (s[i + k] == s[j + k]) k++;
            lcp[pi] = k;

            k = max(k - 1, 0);
        }
        getlcp = SparseTable(lcp);
    }

    int LCP(int i, int j) {
        if (i == j)
            return n - i - 1;
        return getlcp.query(min(ra[i], ra[j]) + 1, max(ra[i], ra[j]));
    }
};
signed main() {
    string s;
    cin >> s;

    SuffixArray sa(s);
    for (int i = s.size() - 1; i > 0; i--) {
        if (sa.LCP(i, 0) == s.length() - i) {
            cout << s.size() - i << " ";
        }
    }
    return 0;
}
