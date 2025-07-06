#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 1e9 + 7;
int n;
char g[1001][1001];
int dp[1001][1001];
int rec(int i, int j) {
    if (i < 0 or j < 0 or g[i][j] == '*') return 0;
    if (i == 0 and j == 0) {
        return 1;
    }
    if (dp[i][j] != -1) return dp[i][j];
    return dp[i][j] = (rec(i - 1, j) + rec(i, j - 1)) % Mod;
}
signed main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> g[i][j];
        }
    }
    memset(dp, -1, sizeof dp);
    cout << rec(n - 1, n - 1);
    return 0;
}