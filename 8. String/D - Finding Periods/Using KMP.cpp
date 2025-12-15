// If a string has a border of length L, it has a period of length (N - L)
#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
auto computeLPS(string &line) {
    int n = line.size();
    vector<int> lps(n, 0);
    lps[0] = 0;
    int len = 0, i = 1;
    while (i < n) {
        if (line[i] == line[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    string s;
    cin >> s;

    vector<int> lps = computeLPS(s);

    int len = lps[s.size() - 1];

    vector<int> ans;
    while (len > 0) {
        ans.push_back(s.size() - len);
        len = lps[len - 1];
    }
    ans.push_back(s.size());
    sort(all(ans));

    for (int i : ans) {
        cout << i << " ";
    }
    return 0;
}
