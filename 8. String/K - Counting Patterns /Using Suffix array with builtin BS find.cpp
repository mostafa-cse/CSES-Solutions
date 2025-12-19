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

        auto left = sa.begin();
        auto right = sa.end();
        for (int i = 0; i < m; i++) {
            auto cmp = [&](int e, char v) {
                return s[e + i] < v;
            };
            auto newLeft = lower_bound(left, right, p[i], cmp);
            auto newRight = lower_bound(left, right, p[i] + 1, cmp);

            left = newLeft;
            right = newRight;
        }
        int l = left - sa.begin();
        int r = right - sa.begin();
        return r - l;
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
