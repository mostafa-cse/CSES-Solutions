#include <bits/stdc++.h>
#define int long long
using namespace std;

struct points {
    int x, y;
    points() {}
    points(int _x, int _y) : x(_x), y(_y) {}

    points operator-(points other) {
        return points(x - other.x, y - other.y);
    }
    int crossProduct(points &b) {
        return x * b.y - y * b.x;
    }
    int getOrientation(points &a, points &b) {
        points A = b - a;
        points B = points(x, y) - b;
        int val = A.crossProduct(B);
        if (val > 0) return 1;
        if (val < 0) return 2;
        return 0;
    }
    bool isOnsegment(points &a, points &b) {
        if (getOrientation(a, b) != 0) return false;
        return (x <= max(a.x, b.x) && x >= min(a.x, b.x) && y <= max(a.y, b.y) && y >= min(a.y, b.y));
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, m;
    cin >> n >> m;

    vector<points> a(n);
    for (auto &[x, y] : a) {
        cin >> x >> y;
    }

    vector<points> b(m);
    for (auto &[x, y] : b) {
        cin >> x >> y;
    }

    for (points p : b) {
        bool boundary = false;
        bool inside = false;

        for (int i = 0; i < n; i++) {
            points A = a[i];
            points B = a[(i + 1) % n];

            if (p.isOnsegment(A, B)) {
                boundary = true;
                break;
            }

            if (A.y > p.y != B.y > p.y) {
                double nx = A.x + (A.x - B.x) * ((p.y - A.y) * 1.00 / (A.y - B.y));

                if (nx > p.x) {
                    inside = !inside;
                }
            }
        }

        if (boundary) {
            cout << "BOUNDARY" << "\n";
        } else if (inside) {
            cout << "INSIDE" << "\n";
        } else {
            cout << "OUTSIDE" << "\n";
        }
    }
    return 0;
}
