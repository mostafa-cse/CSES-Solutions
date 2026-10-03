#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int x, n;
    cin >> n >> x;

    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    vector<int> dp(x + 1, -1);
    function<int(int)> Dhunir_dp = [&](int s) -> int {
        if (s <= 0) {
            return s == 0 ? 0 : 1e18;
        }
        if (dp[s] != -1) return dp[s];
        int ans = 1e18;
        for (int i = 0; i < n; i++) {
            if (c[i] <= s) ans = min(ans, 1 + Dhunir_dp(s - c[i]));
        }
        return dp[s] = ans;
    };
    int ans = Dhunir_dp(x);
    if (ans == 1e18) ans = -1;
    cout << ans;
    return 0;
}