#include <bits/stdc++.h>
#define int long long
using namespace std;
auto computeLPS(string &s) {
    int n = s.size();
    vector<int> pi(s.size(), 0);
    for (int i = 1; i < s.size(); i++) {
        int j = pi[i - 1];
        while (j > 0 and s[i] != s[j]) {
            j = pi[j - 1]; // back to previous best prefix
        }
        if (s[i] == s[j]) {
            j++;
        }
        pi[i] = j;
    }
    return pi;
}
signed main() {
    string s;
    cin >> s;

    vector<int> pi = computeLPS(s);

    int boarder = pi.back();
    vector<int> ans;
    while (boarder > 0) {
        ans.push_back(boarder);
        boarder = pi[boarder - 1];
    }
    sort(ans.begin(), ans.end());

    for (int i : ans) {
        cout << i << " ";
    }
    return 0;
}
