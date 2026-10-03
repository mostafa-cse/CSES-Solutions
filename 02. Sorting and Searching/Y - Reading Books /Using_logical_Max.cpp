#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    int ans = 0, sum = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        sum += x;
        ans = max(ans, x << 1);
    }
    cout << max(ans, sum);
    return 0;
}