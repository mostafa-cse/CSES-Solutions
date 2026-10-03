#include <bits/stdc++.h>
#define int long long
using namespace std;
void solve() {
    int n, a, b;
    cin >> n >> a >> b;

    if (a + b > n or (!a and b) or (a and !b)) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        int draw = n - a - b;
        for (int i = 1; i <= n; i++) {
            cout << i << " \n"[i == n];
        }
        for (int i = 1; i <= draw; i++) {
            cout << i << " ";
        }
        for (int i = 1; i <= b; i++) {
            cout << draw + a + i << " ";
        }
        for (int i = 1; i <= a; i++) {
            cout << i + draw << " ";
        }
        cout << endl;
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