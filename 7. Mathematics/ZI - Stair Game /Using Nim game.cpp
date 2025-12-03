#include <bits/stdc++.h>
#define int long long
using namespace std;
void solve() {
    int n;
    cin >> n;

    int Xor = 0;
    for (int i = 1; i <= n; i += 1) {
        int x;
        cin >> x;

        if (i & 1) continue;
        Xor ^= x;
    }

    if (Xor) cout << "first" << endl;
    else cout << "second" << endl;
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
