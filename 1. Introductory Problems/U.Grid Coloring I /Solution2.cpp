#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m, -1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            a[i][j] = (int)(c - 'A');
        }
    }
    vector<vector<int>> ans(n, vector<int>(m, -1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (auto el : {0, 1, 2, 3}) {
                if (el != a[i][j]) {
                    bool ok = true;
                    if (j) ok &= (ans[i][j - 1] != el);
                    if (j + 1 < m) ok &= (ans[i][j + 1] != el);
                    if (i) ok &= (ans[i - 1][j] != el);
                    if (i + 1 < n) ok &= (ans[i + 1][j] != el);
                    if (ok) {
                        ans[i][j] = el;
                        break;
                    }
                }
            }
            cout << char(ans[i][j] + 'A');
        }
        cout << endl;
    }
    return 0;
}