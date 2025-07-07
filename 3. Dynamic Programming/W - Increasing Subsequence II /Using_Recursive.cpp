#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }
    vector<int> dp(n, -1);
    function<int(int, int)> fun = [&](int i, int val) -> int {
        if (i == n) {
            return 1;
        }
        if (dp[i] != -1) return dp[i];
        int ans = 0;
        if (a[i] > val) {
            ans += fun(i + 1, a[i]);
        } else {
            ans += fun(i + 1, val);
            ans += fun(i + 1, a[i]);
        }
        return dp[i] = ans;
    };
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += fun(i, a[i]);
    }
    cout << ans << endl;
    return 0;
}