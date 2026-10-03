#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
void solve() {
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
    };

    points p1, p2, p3;
    cin >> p1.x >> p1.y;
    cin >> p2.x >> p2.y;
    cin >> p3.x >> p3.y;


    points A = p2 - p1;
    points B = p3 - p1;

    int cp = A.crossProduct(B);

    if (cp == 0) {
        cout << "TOUCH" << endl;
    } else if (cp > 0) {
        cout << "LEFT" << endl;
    } else {
        cout << "RIGHT" << endl;
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

