#include <bits/stdc++.h>
using namespace std;

string manacher(const string &s) {
    int n = s.size();
    vector<int> P(n, 0);
    int C = 0, R = 0;

    for (int i = 0; i < n; i++) {
        int mir = 2*C - i;

        if (i < R) {
            P[i] = min(R - i, P[mir]);
        }

        // expand
        while ( i - P[i] - 1 >= 0 &&
                i + P[i] + 1 < n &&
                s[i - P[i] - 1] == s[i + P[i] + 1]) {
            P[i]++;
        }

        // update center + right
        if (i + P[i] > R) {
            C = i;
            R = i + P[i];
        }
    }

    // find longest
    int center = 0, best = 0;
    for (int i = 0; i < n; i++) {
        if (P[i] > best) {
            best = P[i];
            center = i;
        }
    }

    int start = (center - best) / 2;
    return s.substr(center - best, 2 * best + 1);
}

signed main() {
    string s;
    cin >> s;

    // preprocess
    string t;
    for (char c : s) {
        t.push_back('#');
        t.push_back(c);
    }
    t.push_back('#');

    string out = manacher(t);

    // remove #
    string ans;
    for (char c : out)
        if (c != '#') ans.push_back(c);

    cout << ans;
}
