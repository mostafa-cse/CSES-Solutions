#include <bits/stdc++.h>
#define int long long
using namespace std;
struct points {
    int x, y;
    points() {}
    points(int _x, int _y) : x(_x), y(_y) {}
    bool operator<(points &other) {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};
signed main() {
    int n;
    cin >> n;

    vector<points> a(n);
    for (auto &[x, y] : a) {
        cin >> x >> y;
    }
    sort(a.begin(), a.end());

    int mndist = 1e18;
    set<points> active;
    for (int r = 0, l = 0; r < n; r++) {
        int d = sqrtl(mndist);

        while (l < r and a[r].x - a[l].x >= d) {
            active.erase(points(a[l].y, a[l].x));
            l++;
        }

        auto it = active.lower_bound(points(a[r].y - d, -1e18));
        while (it != active.end()) {
            int dx = it->x - a[r].x;
            int dy = it->y - a[r].y;

            if (dy >= d) break;

            int cur = dx * dx + dy * dy;
            if (mndist > cur) {
                mndist = cur;
                d = sqrtl(cur);
            }
            ++it;
        }
        active.insert(points(a[r].y, a[r].x));
    }
    cout << mndist;
    return 0;
}
