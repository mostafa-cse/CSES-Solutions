#include <bits/stdc++.h>
#define int long long
using namespace std;
void solve() {
    int a, b;
    cin >> a >> b;
    if (a < b) swap(a, b);

    if ((a + b) % 3 or a > b * 2) {
        return cout << "NO" << endl, void();
    }

    int dif = a - b;
    if (a - 2 * dif == b - dif) {
        if ((a + b - 3 * dif) % 3 == 0) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    } else {
        cout << "NO" << endl;
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