#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    int ans = 0;
    for (int i = 5; i <= n; i *= 5) {
        ans += n / i;
    }
    cout << ans;
    return 0;
}