#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    multiset<pair<int, int>> a;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a.insert({x, i});
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        auto it = a.lower_bound({i, 0});

        if (it == a.end())
            continue;

        ans += 1;
        int val = it->first, pos = it->second;
        a.erase(it);

        while (it != a.end()) {
            it = a.upper_bound({val, pos});
            if (it == a.end() or it->second < pos)
                break;
            val = it->first, pos = it->second;
            a.erase(it);
        }
    }
    cout << ans << endl;
    return 0;
}