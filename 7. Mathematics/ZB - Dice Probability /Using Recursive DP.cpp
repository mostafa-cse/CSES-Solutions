#include <bits/stdc++.h>
#define int long long
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
int n, l, r;
double dp[605][105];
double rec(int sum, int took) {
    if (took >= n) {
        return took == n and sum >= l and sum <= r;
    }
    if (dp[sum][took] != -1) return dp[sum][took];
    double ans = 0;
    for (int i = 1; i <= 6; i++) {
        ans += (rec(sum + i, took + 1) / 6);
    }
    return dp[sum][took] = ans;
}
signed main() {
    cin >> n >> l >> r;
    for (int i =0; i <= 600; i++) {
        for (int j = 0; j <= 100; j++) {
            dp[i][j] = -1;
        }
    }
    double ans = rec(0, 0);
    cout << fixed << setprecision(6) << ans << endl;
    return 0;
}
