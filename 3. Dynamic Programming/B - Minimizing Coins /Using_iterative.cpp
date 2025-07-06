#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int x, n;
    cin >> n >> x;

    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    vector<int> dp(x + 1, 0);
    for (int i = 1; i <= x; i++) dp[i] = 1e18;
    for (int taka = 1; taka <= x; taka++) {
        for (int i = 0; i < n; i++) {
            if (taka - c[i] >= 0)
                dp[taka] = min(1 + dp[taka - c[i]], dp[taka]);
        }
    }
    cout << (dp[x] == 1e18 ? -1 : dp[x]);
    return 0;
}