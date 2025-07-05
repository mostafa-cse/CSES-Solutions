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
    sort(a.begin(), a.end());

    int ans = 0;
    for (int i = 1; i < n; i++) {
        ans += (a[i - 1] != a[i]);
    }
    cout << ans + 1;
    return 0;
}