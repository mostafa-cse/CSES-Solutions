#include <bits/stdc++.h>
// #define int long long // got tle
using namespace std;
#define all(x) x.begin(), x.end()

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
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    string s;
    cin >> s;

    SuffixArray sa(s);
    int n = s.size();

    int full_str_pos = sa.ra[0];

    vector<int> borders;
    int cur_min_lcp = sa.n;

    for (int i = full_str_pos; i > 0; i--) {
        cur_min_lcp = min(cur_min_lcp, sa.lcp[i]);
        if(cur_min_lcp == 0) {
            break;
        }

        int suffix_idx = sa.sa[i - 1];
        int suffix_len = n - suffix_idx;
        if (cur_min_lcp == suffix_len) {
            borders.push_back(suffix_len);
        }
    }
    sort(all(borders));
    for (int i : borders) {
        cout << i << " ";
    }
    return 0;
}
