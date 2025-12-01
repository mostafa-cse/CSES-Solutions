#include <bits/stdc++.h>
using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;

    double ans = k;
    for (long long i = 1; i < k; i++) {
        ans -= pow(i, n) / pow(k, n);
        ans -= pow(i * 1.00 / k, n);
    }
    cout << fixed << setprecision(6) << ans;
}
