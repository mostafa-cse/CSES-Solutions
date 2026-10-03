/*
    Author : M0stafa
    Topic : String Algorithm
    Algorithm : KMP
*/
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
    string line, pat;
    cin >> line >> pat;

    string full = pat + "#" + line;
    vector<int> lps = computeLPS(full);
    cout << count(lps.begin(), lps.end(), pat.size());
    return 0;
}
