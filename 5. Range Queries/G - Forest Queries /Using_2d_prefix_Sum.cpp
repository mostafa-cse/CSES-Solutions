#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, q;
    cin >> n >> q;

    vector<vector<int>> a(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c;
            cin >> c;

            if (c == '*') {
                a[i][j] = 1;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
        }
    }

    while (q--) {
        int l1, r1; cin >> l1 >> r1;
        int l2, r2; cin >> l2 >> r2;
        cout << a[l2][r2] - a[l1 - 1][r2] - a[l2][r1 - 1] + a[l1 - 1][r1 - 1] << endl;
    }
    return 0;
}