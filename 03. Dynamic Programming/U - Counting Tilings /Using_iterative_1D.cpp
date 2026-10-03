#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int m, n;
    cin >> m >> n;
    int vert = 3, hori = 1 | (1 << m);
    vector<int> dp(1 << m);
    dp[0] = 1;
    for (int j = (0); j < (n); j++) {
        for (int i = (0); i < (m); i++) {
            vector<int> ndp(1 << m);
            for (int mask = (0); mask < (1 << m); mask++) {
                if (mask & 1) {
                    ndp[mask >> 1] = (ndp[mask >> 1] + dp[mask]) % MOD;
                } else {
                    if (i + 1 < m && (mask & vert) == 0) {
                        ndp[(mask | vert) >> 1] = (ndp[(mask | vert) >> 1] + dp[mask]) % MOD;
                    }
                    if ((mask & hori) == 0) {
                        ndp[(mask | hori) >> 1] = (ndp[(mask | hori) >> 1] + dp[mask]) % MOD;
                    }
                }
            }
            dp = ndp;
        }
    }
    cout << dp[0] % MOD << endl;
    return 0;
}