#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;

    vector<vector<char>> g(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];
        }
    }
    
    vector<vector<char>> a(n, vector<char>(m, -1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (auto f : {'A', 'B', 'C', 'D'}) {
                if (f == g[i][j]) continue;

                bool ok = true;
                // left [column - 1]
                if (j) ok &= (a[i][j - 1] != f);
                
                // right [column + 1]
                if (j + 1 < m) ok &= (a[i][j + 1] != f);

                // up [row - 1]
                if (i) ok &= (a[i - 1][j] != f);

                // down [row + 1]
                if (i + 1 < n) ok &= (a[i + 1][j] != f);

                if (ok) {
                    a[i][j] = f;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << a[i][j];
        }
        cout << endl;
    }
    return 0;
}