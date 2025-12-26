#include <bits/stdc++.h>
using namespace std;
#define int long long
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

            k = max(k - 1, 0ll);
        }
    }
};
signed main() {
    ios_base::sync_with_stdio(false);
    string s;
    int k;
    cin >> s >> k;

    int n = s.size();

    SuffixArray sa(s);

    int sum = 0;
    for (int i = 1; i <= n; i++) {
        int cur = n - sa.sa[i] - sa.lcp[i];

        if (cur + sum >= k) {
            int rest = k - sum;
            for (int j = sa.sa[i]; j < sa.sa[i] + sa.lcp[i] + rest; j++) {
                cout << s[j];
            }
            return 0;
        }
        sum += cur;
    }

    return 0;
}
