#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, q;
    cin >> n >> q;

    vector<vector<int>> table(n + 1, vector<int>(21, -1));
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;

        table[i][0] = p;
    }

    for (int b = 1; b < 21; b++) {
        for (int node = 1; node <= n; node++) {
            if (table[node][b - 1] != -1) {
                table[node][b] = table[table[node][b - 1]][b - 1];
            }
        }
    }

    while (q--) {
        int node, k;
        cin >> node >> k;

        int ans = -1;
        for (int i = 0; i < 20; i++) {
            if (k >> i & 1) {
                ans = table[node][i];
                if (ans == -1) break;
                node = table[node][i];
            }
        }
        cout << ans << endl;
    }
    return 0;
}
