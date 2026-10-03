#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 1e9 + 7;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;

    vector<int> dp(n + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 6; j++) {
            if (i - j >= 0) {
                (dp[i] += dp[i - j]) %= Mod;
            }
        }
    }
    cout << dp[n] << endl;
    return 0;
}