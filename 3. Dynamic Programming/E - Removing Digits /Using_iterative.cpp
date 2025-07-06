#include <bits/stdc++.h>
#define int long long
using namespace std;
const int M = 1e6 + 6;
int dp[M];

signed main() {
    int n;
    cin >> n;
    for (int i = 1; i < M; i++) dp[i] = 1e18;
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (char d : to_string(i)) {
            dp[i] = min(dp[i], dp[i - (d - '0')] + 1);
        }
    }
    cout << dp[n];
    return 0;
}