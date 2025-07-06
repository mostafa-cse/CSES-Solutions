#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, mod = 1e9 + 7;
int rec(int i, int j, vector<int> &a, vector<vector<int>>&dp) {
    if(i == n + 1) {
        return 1;
    }
    if(dp[i][j] != -1) {
        return dp[i][j];
    }
    if(a[i] == 0) {
        dp[i][j] = 0;
        if(j + 1 <= m) {
            dp[i][j] = (dp[i][j] + rec(i + 1, j + 1, a, dp)) % mod;
        }
        dp[i][j] = (dp[i][j] + rec(i + 1, j, a, dp)) % mod;
        if(j - 1  >= 1) {
            dp[i][j] = (dp[i][j] + rec(i + 1, j - 1, a, dp)) % mod;
        }
        return dp[i][j];
    } else {
        dp[i][j] = 0;
        if(abs(a[i] - j) <= 1){
            dp[i][j] = rec(i + 1, a[i], a, dp);
        }
        return dp[i][j];
    }
}
int32_t main() {
    cin >> n >> m;
    vector<int>a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    if(a[1] == 0) {
        int ans = 0;
        for(int i = 1; i <= m; i++) { /*insert i and then count number of combinarion that possible*/
            ans = (ans + rec(2, i, a, dp)) % mod;
        }
        cout << ans << endl;
    } else {
        cout << rec(2, a[1], a, dp) % mod << '\n';
    }
    return 0;
}