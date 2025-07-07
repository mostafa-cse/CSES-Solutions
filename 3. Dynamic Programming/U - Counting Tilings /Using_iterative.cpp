#include <bits/stdc++.h>
using namespace std;
int dp[1 << 10][2];
const int mod = 1e9 + 7;

int main()
{
    int n, m;
    cin >> n >> m;

    if (m * n % 2) {
        return cout << 0, 0;
    } else {
        dp[0][0] = 1;
        int b = 0;
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++, b ^= 1) {
                for (int msk = 0; msk < (1 << n); msk++) {
                    if (dp[msk][b]) {
                        dp[msk ^ 1 << i][b ^ 1] = (dp[msk ^ 1 << i][b ^ 1] + dp[msk][b]) % mod;
                        if (~msk & 1 << i && ~msk & 1 << i + 1 && i + 1 < n) {
                            dp[msk ^ 1 << i + 1][b ^ 1] = (dp[msk ^ 1 << i + 1][b ^ 1] + dp[msk][b]) % mod;
                        }
                        dp[msk][b] = 0;
                    }
                }
            }
        }
        cout << dp[0][b] << '\n';
    }
    return 0;
}