#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
void solve() {
    struct points {
        int x, y;
    };

    points p1, p2, p3;
    cin >> p1.x >> p1.y;
    cin >> p2.x >> p2.y;
    cin >> p3.x >> p3.y;

    /*
        area = 1/2|x1 x2 x3 x1|
                  |y1 y2 y3 y1|
    */

    int xMul = p1.x * p2.y + p2.x * p3.y + p3.x * p1.y;
    int yMul = p1.y * p2.x + p2.y * p3.x + p3.y * p1.x;
    if (xMul == yMul) cout << "TOUCH" << endl;
    else if (xMul > yMul) cout << "LEFT" << endl;
    else cout << "RIGHT" << endl;
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

