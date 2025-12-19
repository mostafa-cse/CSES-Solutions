#include <bits/stdc++.h>
// #define int long long
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
    bool find(string &p) {
        int m = p.size();
        int l = 0, r = n - 1;
        while (l <= r) {
            int mid = l + r >> 1;

            int val = s.compare(sa[mid], m, p);
            if (val == 0) {
                return true;
            } else if (val < 0) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return false;
    }
};
signed main() {
    string s;
    cin >> s;

    SuffixArray sa(s);

    int q;
    cin >> q;

    while (q--) {
        string t;
        cin >> t;

        if (sa.find(t)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
