#include <bits/stdc++.h>
#define int long long
using namespace std;
int n;
double ans[65], dp[105][65];

signed main() {
    cin >> n;

    for (int i = 0; i < 65; i++) {
        ans[i] = 1.0;
    }

    for (int i = 0; i < 64; i++) {
        memset(dp, 0, sizeof dp);
        dp[0][i] = 1.00;

        for (int j = 0; j < n; j++) {
            for (int k = 0; k < 64; k++) {
                int cnt = 0;
                if (k % 8 != 0) cnt++;
                if (k % 8 != 7) cnt++;
                if (k / 8 != 0) cnt++;
                if (k / 8 != 7) cnt++;

                if (k % 8 != 0) dp[j + 1][k - 1] += dp[j][k] / cnt;
                if (k % 8 != 7) dp[j + 1][k + 1] += dp[j][k] / cnt;
                if (k / 8 != 0) dp[j + 1][k - 8] += dp[j][k] / cnt;
                if (k / 8 != 7) dp[j + 1][k + 8] += dp[j][k] / cnt;
            }
        }
        for (int j = 0; j < 64; j++) ans[j] *= (1 - dp[n][j]);
    }

    double expected = 0;
    for (int i = 0; i < 64; i++) {
        expected += ans[i];
    }
    cout << fixed << setprecision(6) << expected;
    return 0;
}
