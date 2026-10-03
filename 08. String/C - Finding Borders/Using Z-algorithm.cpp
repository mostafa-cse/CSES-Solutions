/*
    Author : M0stafa
    Topic : String Algorithm
    Algorithm : Z-Algorithm
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
vector<int> z_algo(string &s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n and s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}
signed main() {
    string s;
    cin >> s;

    int n = s.size();
    auto z = z_algo(s);
    dout(z);
    
    for (int i = n - 1; i > 0; i--) {
        if (z[i] == n - i) {
            cout << n - i << " ";
        }
    }
    return 0;
}
