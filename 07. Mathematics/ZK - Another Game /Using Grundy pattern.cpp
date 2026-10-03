#include <bits/stdc++.h>
#define int long long
using namespace std;
void solve() {
    int n;
    cin >> n;
    bool hasOdd = false;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x % 2 != 0) {
            hasOdd = true;
        }
    }

    if (hasOdd) {
        cout << "first" << endl;
    } else {
        cout << "second" << endl;
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
