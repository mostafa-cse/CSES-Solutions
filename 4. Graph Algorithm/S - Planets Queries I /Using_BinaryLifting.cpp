#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    
    int n, q;
    cin >> n >> q;

    vector<vector<int>> up(n + 1, vector<int>(31));
    for (int u = 1; u <= n; u++) {
        cin >> up[u][0];
    }

    for (int j = 1; j < 30; j++) {
        for (int u = 1; u <= n; u++) {
            up[u][j] = up[up[u][j - 1]][j - 1];
        }
    }

    while (q--) {
        int u, k;
        cin >> u >> k;

        for (int j = 0; j <= 30; j++) {
            if (k >> j & 1) {
                u = up[u][j];
            }
        }
        cout << u << endl;
    }
    return 0;
}