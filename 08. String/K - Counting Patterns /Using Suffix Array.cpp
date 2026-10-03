#include <bits/stdc++.h>
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
        constructLCP();
    }

    void countingSort(int k) {
        int mxRank = max(300, n);
        vector<int> count(mxRank, 0);
        vector<int> temp_sa(n);

        for (int i = 0; i < n; i++) {
            int currRank = (i + k < n) ? ra[i + k] : 0;
            count[currRank]++;
        }

        for (int i = 1; i < mxRank; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            int second_half_idx = (sa[i] + k < n) ? ra[sa[i] + k] : 0;
            temp_sa[--count[second_half_idx]] = sa[i];
        }

        sa = temp_sa;
    }

    void constructSA() {
        sa.resize(n);
        ra.resize(n);

        for (int i = 0; i < n; i++) {
            ra[i] = s[i];
            sa[i] = i;
        }

        vector<int> temp_r(n);
        for (int k = 1; k < n; k *= 2) {
            countingSort(k);
            countingSort(0);

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

    int count(string &p) {
        int m = p.size();
        int l = 0, r = n - 1;

        // 1. Lower Bound: Find first index where suffix >= p
        while (l <= r) {
            int mid = l + (r - l) / 2;
            // Compare p with substring of length m starting at sa[mid]
            if (s.compare(sa[mid], m, p) >= 0) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        int start_index = l;

        // 2. Upper Bound: Find first index where suffix > p
        l = 0; r = n - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (s.compare(sa[mid], m, p) > 0) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        int end_index = l;

        return end_index - start_index;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string t;
    if (cin >> t) {
        SuffixArray sa(t);
        int k;
        if (cin >> k) {
            while (k--) {
                string p;
                cin >> p;
                cout << sa.count(p) << endl;
            }
        }
    }
    return 0;
}
