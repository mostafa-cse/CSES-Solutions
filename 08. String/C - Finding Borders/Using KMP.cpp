#include <bits/stdc++.h>
#define int long long
using namespace std;
vector<int> computeLPS(string &pattern) {
    int n = pattern.size();
    vector<int> lps(n, 0);

    lps[0] = 0;
    int len = 0, i = 1;
    while (i < n) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else  {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}
signed main() {
    string s;
    cin >> s;

    vector<int> lps = computeLPS(s);
    int curr = lps.back();

    vector<int> ans;
    while (curr > 0) {
        ans.push_back(curr);
        curr = lps[curr - 1];
    }

    for (int i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i] << " ";
    }
    return 0;
}
