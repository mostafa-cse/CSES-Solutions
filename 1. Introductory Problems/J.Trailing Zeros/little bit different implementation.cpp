#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    int ans = 0;
    while (n) {
        ans += n / 5;
        n /= 5;
    }
    cout << ans;
    return 0;
}