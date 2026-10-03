#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
struct Manacher {
    string s;
    vector<int> p;
    int n, m;
    Manacher(const string &t) {
        n = t.size();
        if (n == 0) {
            m = 0;
            return;
        }

        m = 2 * n + 1;
        s.assign(m, '#');
        for (int i = 0; i < n; i++) {
            s[2 * i + 1] = t[i];
        }

        p.assign(m, 0);

        int L = 0, R = 0;
        for (int i = 0; i < m; i++) {
            int k = (i > R) ? 1 : min(p[L + R - i], R - i + 1);

            while (i - k >= 0 && i + k < m && s[i - k] == s[i + k]) k++;

            p[i] = k;
            if (i + k - 1 > R) {
                L = i - k + 1;
                R = i + k - 1;
            }
        }
    }

    bool isPalindrome(int l, int r) const {
        if (l > r) return true;
        if (n == 0) return true;

        int center = l + r + 1;        // transformed string index
        int need = r - l + 1;

        return p[center] >= need;
    }

    // Longest palindrome ending at each index
    vector<int> getEndingLengths() const {
        dout(p);
        vector<int> ret(n);
        ret[0] = 1;
        for (int i = 1; i < n; i++) {
            ret[i] = min(ret[i - 1] + 2, i + 1);

            while (!isPalindrome(i - ret[i] + 1, i))
                ret[i]--;
        }
        return ret;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;

    Manacher M(s);
    vector<int> ending = M.getEndingLengths();
    for (int x : ending) {
        cout << x << " ";
    }
    return 0;
}
