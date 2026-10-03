#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, x;
int a[101], dp[1000006];
const int Mod = 1e9 + 7;
int rec(int s) {
    if (s <= 0) {
        return s == 0;
    }
    if (~dp[s]) return dp[s];
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (s - a[i] >= 0) ans = (ans + rec(s - a[i])) % Mod;
    }
    return dp[s] = ans;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> x;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    memset(dp, -1, sizeof dp);
    cout << rec(x);
    return 0;
}