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

    int ans = -1e18, sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
        ans = max(ans, sum);
        sum = max(0ll, sum);
    }
    cout << ans << endl;
    return 0;
}