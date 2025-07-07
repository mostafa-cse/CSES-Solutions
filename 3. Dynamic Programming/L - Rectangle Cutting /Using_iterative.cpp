#include <bits/stdc++.h>
#define int long long
using namespace std;

int dp[501][501];
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int r, c;
    cin >> r >> c;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            if (i == j) {
                dp[i][j] = 0;
            } else {
                dp[i][j] = 1e9;
                for (int cur_r = 1; cur_r < i; cur_r++) {
                    dp[i][j] = min(dp[i][j], dp[cur_r][j] + dp[i - cur_r][j] + 1);
                }
                for (int cur_c = 1; cur_c < j; cur_c++) {
                    dp[i][j] = min(dp[i][j], dp[i][cur_c] + dp[i][j - cur_c] + 1);
                }
            }
        }
    }
    cout << dp[r][c];
    return 0;
}