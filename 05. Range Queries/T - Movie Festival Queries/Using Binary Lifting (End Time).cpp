#include <bits/stdc++.h>
#define int long long
using namespace std;
const int M = 1e6;
int up[M + 1][21];
signed main() {
    cin.tie(nullptr)->sync_with_stdio(0);
    cout.tie(nullptr);
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;

        up[y][0] = max(up[y][0], x);
    }

    for (int i = 1; i <= M; i++) {
        up[i][0] = max(up[i][0], up[i - 1][0]);
    }

    for (int k = 1; k <= 20; k++) {
        for (int i = 1; i <= M; i++) {
            int jump = up[i][k - 1];
            up[i][k] = up[jump][k - 1];
        }
    }

    while (q--) {
        int l, r;
        cin >> l >> r;

        int ans = 0;
        for (int i = 20; i >= 0; i--) {
            if (up[r][i] >= l) { // watch this move
                ans += 1 << i;
                r = up[r][i]; // go to next available movie
            }
        }
        cout << ans << endl;
    }

    return 0;
}
