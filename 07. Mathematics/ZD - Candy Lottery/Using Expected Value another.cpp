#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;

    long double ans = 0.00;
    for (int i = 0; i < k; i++) {
        long double val = (long double)i / k;
        ans += ((long double)1.00 - pow(val, n));
    }
    cout << fixed << setprecision(6) << ans;
    return 0;
}
