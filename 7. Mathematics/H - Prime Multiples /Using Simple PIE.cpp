#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;

    vector<int> a(k);
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }

    int ans = 0;
    for (int mask = 1; mask < (1 << k); mask++) {
        int cnt = n;
        int bit = 0;
        for (int b = 0; b < k; b++) {
            if (mask >> b & 1) {
                cnt /= a[b];
                bit++;
            }
        }

        if (bit & 1) {
            ans += cnt;
        } else {
            ans -= cnt;
        }
    }
    cout << ans << endl;
    return 0;
}
