#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    int ans = 0;
    for (int i = 0; i < n; i += 1) {
        int x;
        cin >> x;
        if (((n - 1) & i) == i) { // submask xor
            ans ^= x;
        }
    }
    cout << ans << endl;
    return 0;
}
