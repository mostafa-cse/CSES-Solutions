#include <bits/stdc++.h>
#define int long long
using namespace std;
const int M = 1e6;
int dp[M + 1][21];
signed main() {
    cin.tie(nullptr)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;

        dp[y][0] = max(dp[y][0], x);
    }

    for (int i = 1; i <= M; i++) {
        dp[i][0] = max(dp[i][0], dp[i - 1][0]);
    }

    for (int k = 1; k <= 20; k++) {
        for (int i = 1; i <= M; i++) {
            int jump = dp[i][k - 1];
            dp[i][k] = dp[jump][k - 1];
        }
    }

    while (q--) {
        int l, r;
        cin >> l >> r;

        int ans = 0;
        while (dp[r][0] >= l) {
            int k = 1;
            for (k = 1; k < 21; k++) {
                if (dp[r][k] < l) {
                    break;
                }
            }
            k--;
            r = dp[r][k];
            ans += (1 << k);
        }
        cout << ans << endl;
    }

    return 0;
}
