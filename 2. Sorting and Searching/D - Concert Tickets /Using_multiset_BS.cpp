#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;

    multiset<int> prices;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        prices.insert(x);
    }

    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;

        auto val = prices.upper_bound(x);
        if (val == prices.begin()) cout << -1 << endl;
        else {
            --val;
            cout << *val << endl;
            prices.erase(val);
        }
    }
    return 0;
}