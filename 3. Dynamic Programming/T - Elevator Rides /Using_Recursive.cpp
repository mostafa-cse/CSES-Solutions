#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, W;
vector<int> a;
vector<pair<int, int>> dp;

pair<int, int> solve(int mask) {
    if (mask == 0) return {1, 0};
    if (dp[mask].first != -1) return dp[mask];
    pair<int, int> best = {1e18, 1e18};
    for (int i = 0; i < n; i++) {
        if (mask >> i & 1) {
            pair<int, int> cur = solve(mask ^ (1 << i));
            if (cur.second + a[i] <= W) {
                cur.second += a[i];
            } else {
                cur.first += 1;
                cur.second = a[i];
            }
            if (best.first > cur.first || (best.first == cur.first && best.second > cur.second)) {
                best = cur;
            }
        }
    }
    return dp[mask] = best;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> W;
    a.resize(n);
    for (int &x : a) cin >> x;
    dp.assign((1 << n), {-1, -1});
    cout << solve((1 << n) - 1).first;
    return 0;
}
