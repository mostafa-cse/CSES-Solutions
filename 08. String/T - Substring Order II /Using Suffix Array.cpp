#include <bits/stdc++.h>
using namespace std;

#define int long long

struct SuffixArray {
    string s;
    int n;
    vector<int> sa;
    vector<int> ra;

    SuffixArray(string &x) : s(x) {
        s += "$";
        n = s.size();
        constructSA();
    }

    void countingSort(int k) {
        int mxRank = max(300ll, n);
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
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    int k;
    cin >> s >> k;

    int n = s.size();
    SuffixArray sa_struct(s);
    const vector<int>& sa = sa_struct.sa;

    vector<int> len_sum(sa_struct.n + 1, 0);
    for (int i = 0; i < sa_struct.n; i++) {
        len_sum[i+1] = len_sum[i] + (sa_struct.n - 1 - sa[i]);
    }

    int L = 0, R = sa_struct.n - 1;
    int depth = 0;
    string ans = "";

    while (true) {
        for (char c = 'a'; c <= 'z'; c++) {

            int nL = lower_bound(sa.begin() + L, sa.begin() + R + 1, c, [&](int sa_idx, char val) {
                if (sa_idx + depth >= sa_struct.n) return true; // Treat exhausted suffix as smaller
                return sa_struct.s[sa_idx + depth] < val;
            }) - sa.begin();

            int nR = lower_bound(sa.begin() + L, sa.begin() + R + 1, c + 1, [&](int sa_idx, char val) {
                if (sa_idx + depth >= sa_struct.n) return true;
                return sa_struct.s[sa_idx + depth] < val;
            }) - sa.begin();

            nR--;

            if (nL > nR) continue;

            int total_len_sum = len_sum[nR + 1] - len_sum[nL];
            int range_count = (nR - nL + 1);
            int substrings_in_branch = total_len_sum - (range_count * depth);

            if (k <= substrings_in_branch) {
                ans += c;
                if (k <= range_count) {
                    cout << ans << endl;
                    return 0;
                }

                k -= range_count;
                L = nL;
                R = nR;
                depth++;
                break;
            } else {
                k -= substrings_in_branch;
            }
        }
    }
    return 0;
}
