// Recursive Solution : TLE 
#include <bits/stdc++.h>
#define int long long
using namespace std;
int dp[501][501];
int rec(int r, int c) {
    if (r == c) {
        return dp[r][c] = 0;
    }
    if (dp[r][c] != -1) return dp[r][c];
    int ans = 1e8;
    for (int i = 1; i < r; i++) {
        ans = min(ans, 1 + rec(i, c) + rec(r - i, c));
    }
    for (int j = 1; j < c; j++) {
        ans = min(ans, 1 + rec(r, j) + rec(r, c - j));
    }
    return dp[r][c] = ans;
}
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int r, c;
    cin >> r >> c;
    memset(dp, -1, sizeof dp);
    cout << rec(r, c) << endl;
    return 0;
}