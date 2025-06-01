#include <bits/stdc++.h>
#define int long long
using namespace std;
void solve() {
    int n, a, b;
    cin >> n >> a >> b;
    int games = a + b;
    int ties = n - games;

    if (games > n || (a == 0 && b > 0) || (a > 0 && b == 0)) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        for(int i = 1; i <= n; i++){
            cout << i << " \n"[i == n];
        }
        for(int i = 0; i < games; i++){
            cout << (games - b + i) % games + 1 << " ";
        }
        for(int i = 1; i <= ties; i++){
            cout << games + i << " ";
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