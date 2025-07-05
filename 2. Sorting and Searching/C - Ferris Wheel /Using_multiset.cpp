#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, x;
    cin >> n >> x;

    multiset<int> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        a.insert(x);
    }

    int ans = 1, Weight = x, cnt = 0;
    while (!a.empty()) {
        auto val = a.upper_bound(Weight);
        if (val != a.begin()) {
            val--;
        }

        if (Weight - *val >= 0 and cnt < 2) {
            Weight -= *val;
            cnt++;
            a.erase(val);
        } else {
            cnt = 0;
            ans++;
            Weight = x;
        }
    }
    cout << ans << endl;
    return 0;
}