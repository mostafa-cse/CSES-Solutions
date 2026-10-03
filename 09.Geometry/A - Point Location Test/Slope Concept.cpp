#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
void solve() {
    struct points {
        int x, y;
    };

    points p1, p2, p3;
    cin >> p1.x >> p1.y;
    cin >> p2.x >> p2.y;
    cin >> p3.x >> p3.y;

    int m1_p1p2 = (p2.y - p1.y) * (p3.x - p2.x);
    int m2_p2p3 = (p3.y - p2.y) * (p2.x - p1.x);

    if (m1_p1p2 == m2_p2p3) {
        cout << "TOUCH" << endl;
    } else if (m1_p1p2 > m2_p2p3) {
        cout << "RIGHT" << endl;
    } else {
        cout << "LEFT" << endl;
    }
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        // cout << "Case " << i << ": ";
        solve();
    }
    return 0;
}

