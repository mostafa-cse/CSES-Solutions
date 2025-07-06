#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    vector<int> dp(n + 1, -1);
    function<int(int)> rec = [&](int v) -> int {
        if (v <= 0) return v == 0;
        if (dp[v] != -1) {
            return dp[v];
        }

        int ans = 0;
        for (int i = 1; i <= 6; i++) {
            (ans += rec(v - i)) %= Mod;
        }
        return dp[v] = ans;
    };
    cout << rec(n) << endl;
    return 0;
}