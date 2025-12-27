#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
    ll x, y;
};

bool compareX(const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

bool compareY(const Point& a, const Point& b) {
    if (a.y != b.y) return a.y < b.y;
    return a.x < b.x;
}

ll distSq(const Point& a, const Point& b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
vector<Point> p;
ll solve(int l, int r) {
    if (r - l <= 3) {
        ll min_d = LLONG_MAX;
        for (int i = l; i < r; ++i) {
            for (int j = i + 1; j < r; ++j) {
                min_d = min(min_d, distSq(p[i], p[j]));
            }
        }
        sort(p.begin() + l, p.begin() + r, compareY);
        return min_d;
    }

    int mid = (l + r) / 2;
    ll mid_x = p[mid].x;

    ll d = min(solve(l, mid), solve(mid, r));

    inplace_merge(p.begin() + l, p.begin() + mid, p.begin() + r, compareY);

    vector<Point> strip;
    for (int i = l; i < r; ++i) {
        ll dx = p[i].x - mid_x;
        if (dx * dx < d) {
            strip.push_back(p[i]);
        }
    }

    for (int i = 0; i < strip.size(); ++i) {
        for (int j = i + 1; j < strip.size(); ++j) {
            ll dy = strip[j].y - strip[i].y;
            if (dy * dy >= d) break;

            d = min(d, distSq(strip[i], strip[j]));
        }
    }
    return d;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (cin >> n) {
        p.resize(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i].x >> p[i].y;
        }
        sort(p.begin(), p.end(), compareX);
        cout << solve(0, n) << endl;
    }

    return 0;
}
