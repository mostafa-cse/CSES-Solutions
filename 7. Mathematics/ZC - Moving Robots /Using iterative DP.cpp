#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    vector<double> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = 1.0;
    }

    int dp[101][65];
    for (int start = 0; start < 8 * 8; start++) {
        memset(dp, 0, sizeof dp);
        dp[0][start] = 1.00;

        for (int k = 0; k < n; k++) {
            for (int u = 0; u < 8 * 8; u++) {
                int cnt = 0;
                vector<int> points;
                if (u >= 8) points.push_back(u - 8);
                if (u % 8 != 0) points.push_back(u - 1);
                if (u % 8 != 7) points.push_back(u + 1);
                if (u < 8 * 7) points.push_back(u + 8);

                for (int v : points) {
                    dp[k + 1][v] += dp[k][u] / points.size();
                }
            }
        }
        for (int u = 0; u < 8 * 8; u++) {
            ans[u] *= (1 - dp[n][u]);
        }
    }

    double expected = 0;
    for (int i = 0; i < 64; i++) {
        expected += ans[i];
    }
    cout << expected;
    return 0;
}
