#include <bits/stdc++.h>
#define int long long
using namespace std;
void Solve () {
    int r, c;
    cin >> r >> c;
 
    int ans = 0;
    int First;
    if (r >= c) {
        if (~r & 1) {
            First = r * r;
        } else {
            First = (r - 1) * (r - 1);
        }
 
        if (~r & 1) {
            ans = First - c + 1;
        } else {
            ans = First + c;
        }
    } else {
        if (c & 1) {
            First = c * c;
        } else {
            First = (c - 1) * (c - 1);
        }
 
        if (c & 1) {
            ans = First - r + 1;
        } else {
            ans = First + r;
        }
    }
    cout << ans << '\n';
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int tc = 0;
    cin >> tc;
    for (int i = 1; i <= tc; i++) {
        Solve();
    }
    return 0;
}
