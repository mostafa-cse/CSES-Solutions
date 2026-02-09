#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
signed main() {
    int n;
    cin >> n;

    vector<int> dp(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        cin >> dp[i];
    }
    // reverse(dp.begin(), dp.begin() + n);

    for (int ith = 0; ith <= 20; ith++) {
        for (int mask = 1; mask <= n; mask++) {
            if ((mask >> ith) & 1) {
                dp[mask] ^= dp[mask ^ (1 << ith)];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << dp[i] << " ";
    }
    return 0;
}
