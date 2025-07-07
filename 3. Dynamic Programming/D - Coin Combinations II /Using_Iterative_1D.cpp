#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 1e9 + 7;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, target;
    cin >> n >> target;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    int dp[target + 2];
    memset(dp, 0, sizeof dp);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= target; j++) {
            if (j - a[i] >= 0) {
                dp[j] = (dp[j] + dp[j - a[i]]) % Mod;
            }
        }
    }
    cout << dp[target];
    return 0;
}