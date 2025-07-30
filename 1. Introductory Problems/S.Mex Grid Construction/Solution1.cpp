#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    vector<vector<int>> a(n, vector<int>(n, n * n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            vector<int> hsh(n * n + 1, 0);
            for (int r = 0; r < i; r++) hsh[a[r][j]] = 1;
            for (int c = 0; c < j; c++) hsh[a[i][c]] = 1;

            for (int val = 0; val < n * n; val++) {
                if (hsh[val] == 0) {
                    a[i][j] = val;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << " \n"[j + 1 == n];
        }
    }
    return 0;
}