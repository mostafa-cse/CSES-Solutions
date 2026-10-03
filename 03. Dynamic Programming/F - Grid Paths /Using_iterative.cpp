#include "bits/stdc++.h"
using namespace std;
#define int long long
const int MOD = 1e9 + 7 , INF = 1e9;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n;
    cin >> n;
    vector<string> a(n);
    for (auto& x : a) cin >> x;

    vector<vector<int>> dp(n, vector<int>(n, 0));

    if (a[0][0] != '*') dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] == '*') continue;
            if (i > 0) dp[i][j] = (dp[i][j] + dp[i-1][j]) % MOD;
            if (j > 0) dp[i][j] = (dp[i][j] + dp[i][j-1]) % MOD;
        }
    }
    cout << dp[n-1][n-1] << '\n';
    return 0;
}