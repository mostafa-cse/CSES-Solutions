#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, W;
    cin >> n >> W;
 
    vector<int> a(n);
    for (int &i : a) cin >> i;
 
    #define ride first
    #define weight second
    vector<pair<int, int>> dp((1 << n) + 1, {0, 0});
    dp[0] = {1, 0};
    for (int mask = 1; mask < (1 << n); mask++) {
        pair<int, int> best = {1e18, 1e18};
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) {
                pair<int, int> cur = dp[mask ^ (1 << i)];
 
                if (cur.weight + a[i] <= W) {
                    cur.weight += a[i];
                } else {
                    cur.ride += 1;
                    cur.weight = a[i];
                }
                if (best.ride >= cur.ride) {
                    best.ride = cur.ride;
                    best.weight = min(best.weight, cur.weight);
                }
            }
        }
        dp[mask] = best;
    }
    cout << dp[(1 << n) - 1].first;
    return 0;
}