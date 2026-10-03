#include <bits/stdc++.h>
#define int long long
using namespace std;
void solve() {
    int x, y;
    cin >> x >> y;

    if (x >= y) {
        if (x & 1) {
            cout << (x - 1) * (x - 1) + y << endl;
        } else {
            cout << (x * x) - y + 1 << endl;
        }
    } else {
        if (y & 1) {
            cout << (y * y) - x + 1 << endl;
        } else {
            cout << (y - 1) * (y - 1) + x << endl;
        }
    }
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
