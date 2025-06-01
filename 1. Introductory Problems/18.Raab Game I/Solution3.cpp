#include <bits/stdc++.h>
#define int long long
using namespace std;
void solve() {
    int n, x, y;
    cin >> n >> x >> y;
    
    if (((x + y == x || x + y == y) && x + y != 0) || x + y > n) {
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;
    for (int i = 1; i <= n; i++) {
        cout << i << " \n"[i == n];
    }

    // win
    for (int i = 1; i <= y; i++) {
        cout << i + x << " ";
    }

    // lose
    for (int i = 1; i <= x; i++) {
        cout << i << " ";
    }

    // ties
    for (int i = x + y + 1; i <= n; i++)
        cout << i << " ";
    cout << endl;
}
signed main() {
    int tc;
    cin >> tc;

    for (int t = 1; t <= tc; t++) {
        // cout << "Case " << t << ": ";
        solve();
    }
    return 0;
}