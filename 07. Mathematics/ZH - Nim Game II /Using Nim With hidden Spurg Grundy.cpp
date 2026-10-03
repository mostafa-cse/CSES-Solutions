#include <bits/stdc++.h>
#define int long long
using namespace std;
void solve() {
    int n;
    cin >> n;

    int Xor = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        Xor ^= x % 4;
    }
    cout << (Xor ? "first" : "second") << endl;
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
