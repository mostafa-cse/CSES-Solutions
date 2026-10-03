#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 1e9 + 7;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
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