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
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n;
    cin >> n;

    vector<points> a(n);
    for (auto &[x, y] : a) {
        cin >> x >> y;
    }
    a.push_back(a.front());

    int Boundary = 0;
    for (int i = 1; i <= n; i++) {
        Boundary += gcd(abs(a[i].x - a[i - 1].x), abs(a[i - 1].y - a[i].y));
    }

    int area = 0;
    for (int i = 0; i < n; i++) {
        area += a[i].x * a[i + 1].y;
        area -= a[i].y * a[i + 1].x;
    }
    area = abs(area);

    int Inside = (area - Boundary + 2) / 2;
    cout << Inside << " " << Boundary << endl;
    return 0;
}
