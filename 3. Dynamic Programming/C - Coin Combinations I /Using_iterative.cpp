#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, x;
int a[101], dp[1000006];
const int Mod = 1e9 + 7;
signed main() {
    cin >> n >> x;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    dp[0] = 1;
    for (int taka = 1; taka <= 1e6; taka++) {
        for (int i = 0; i < n; i++) {
            if (taka - a[i] >= 0) {
                dp[taka] = (dp[taka] + dp[taka - a[i]]) % Mod;
            }
        }
    }
    cout << dp[x];
    return 0;
}