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

    int ans = 0;
    map<int, int> cnt;
    for (int l = 0, r = 0; l < n; l++) {
        while (r < n and cnt.count(a[r]) == 0) {
            cnt[a[r]]++;
            r++;
        }
        ans += (r - l);
        cnt.erase(a[l]);
    }
    cout << ans;
    return 0;
}