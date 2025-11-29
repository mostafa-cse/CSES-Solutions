#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, l, r;
    cin >> n >> l >> r;

    double dp[n + 1][n * 6 + 1]{1.0}; // probability of i'th throw of sum j
    for (int sum = 1; sum <= 6; sum++) {
        dp[1][sum] = 1.00 / 6.00;
    }

    for (int Throw = 2; Throw <= n; Throw++) {
        for (int sum = 6 * Throw; sum >= Throw; sum--) {
            for (int dice = 1; dice <= 6; dice++) {
                if (sum >= dice) {
                    dp[Throw][sum] += dp[Throw - 1][sum - dice];
                }
            }
            dp[Throw][sum] = dp[Throw][sum] / 6.00;
        }
    }

    double ans = 0;
    for (int sum = l; sum <= r; sum++) {
        ans += dp[n][sum];
    }
    cout << fixed << setprecision(6) << ans << endl;
    return 0;
}
