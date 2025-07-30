#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }

    int ans = 1e18;
    for (int mask = 0; mask < (1 << n); mask++) {
        int A = 0, B = 0;
        for (int b = 0; b < n; b++) {
            if (mask >> b & 1) {
                A += a[b];
            } else {
                B += a[b];
            }
        }
        ans = min(ans, abs(A - B));
    }
    cout << ans << endl;
    return 0;
}