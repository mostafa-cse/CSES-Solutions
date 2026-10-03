#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
struct points {
    int x, y;
    points() {}
    points(int _x, int _y) : x(_x), y(_y) {}

    points operator-(points other) {
        return points(x - other.x, y - other.y);
    }
    int crossProduct(points &b) {
        int res = x * b.y - y * b.x;
        return res;
    }
    friend istream &operator>>(istream &is, points &p) {
        return is >> p.x >> p.y;
    }
    int getOrientation(points &a, points &b) {
        points A = b - a;
        points B = points(x, y) - b;
        int val = A.crossProduct(B);
        if (val > 0) {
            return 1;
        } else if (val < 0) {
            return 2;
        } else {
            return 0;
        }
    }
    bool isOnsegment(points &a, points &b) {
        int ans = 0;
        ans = (x <= max(a.x, b.x));
        ans &= (x >= min(a.x, b.x));
        ans &= y <= max(a.y, b.y);
        ans &= y >= min(a.y, b.y);
        return ans;
    }
};
void solve() {
    points p1, p2, p3, p4;
    cin >> p1 >> p2 >> p3 >> p4;

    int ori_p1p2_p3 = p3.getOrientation(p1, p2);
    int ori_p1p2_p4 = p4.getOrientation(p1, p2);

    int ori_p3p4_p1 = p1.getOrientation(p3, p4);
    int ori_p3p4_p2 = p2.getOrientation(p3, p4);

    if (ori_p3p4_p1 != ori_p3p4_p2 and ori_p1p2_p3 != ori_p1p2_p4) {
        cout << "YES" << endl;
    } else if (ori_p1p2_p3 == 0 and p3.isOnsegment(p1, p2)) {
        cout << "YES" << endl;
    } else if (ori_p1p2_p4 == 0 and p4.isOnsegment(p1, p2)) {
        cout << "YES" << endl;
    } else if (ori_p3p4_p1 == 0 and p1.isOnsegment(p3, p4)) {
        cout << "YES" << endl;
    } else if (ori_p3p4_p2 == 0 and p2.isOnsegment(p3, p4)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        // cout << "Case " << i << ": ";
        solve();
    }
    return 0;
}

