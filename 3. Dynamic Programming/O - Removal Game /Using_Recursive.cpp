#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, a[5000];
int dp[5000][5000];
int rec(int first, int last) {
    if (first == last) {
        return a[last];
    }
    if (dp[first][last] != -1) return dp[first][last];
    return dp[first][last] = max(a[first] - rec(first + 1, last), a[last] - rec(first, last - 1));
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    memset(dp, -1, sizeof dp);
    int sum = accumulate(a, a + n, 0ll);
    cout << (sum + rec(0, n - 1)) / 2;
    return 0;
}