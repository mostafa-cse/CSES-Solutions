#include <bits/stdc++.h>
#define int long long
using namespace std;
#define x first
#define y second
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
signed main() {
    int n;
    cin >> n;

    vector<pair<int, int>> a(n);
    for (auto &[x, y] : a) {
        cin >> x >> y;
    }
    sort(a.begin(), a.end());

    int mndist = 8e18;
    set<pair<int, int>> active;
    for (int right = 0, left = 0; right < n; right++) {
        double d = sqrt(mndist);

        while (left < right and a[right].x - a[left].x >= d) {
            active.erase({a[left].y, a[left].x});
            left++;
        }

        auto it = active.lower_bound({a[right].y - d, -1e18});
        while (it != active.end()) {
            int dx = it->y - a[right].x;
            int dy = it->x - a[right].y;

            if (dy >= d) break;

            int cur = dx * dx + dy * dy;
            if (mndist > cur) {
                mndist = cur;
                d = sqrt(cur);
            }
            ++it;
        }
        active.insert({a[right].y, a[right].x});
    }
    cout << mndist;
    return 0;
}
