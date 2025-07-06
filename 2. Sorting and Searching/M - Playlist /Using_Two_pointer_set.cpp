#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int& i : a) {
        cin >> i;
    }

    int ans = 0;
    set<int> s;
    int l = 0;

    for (int r = 0; r < n; r++) {
        while (s.count(a[r])) {
            s.erase(a[l]);
            l++;
        }
        s.insert(a[r]);
        ans = max(ans, r - l + 1);
    }

    cout << ans;
    return 0;
}