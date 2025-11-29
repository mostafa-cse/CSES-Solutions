#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

// fast exponentiation (for modular inverse)
long long modpow(long long a, long long e) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

long long modinv(long long a) {
    return modpow((a % MOD + MOD) % MOD, MOD - 2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<long long>> a(n, vector<long long>(m + 1));
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= m; j++)
            cin >> a[i][j];

    vector<int> where(m, -1);

    for (int col = 0, row = 0; col < m && row < n; col++) {
        int sel = row;
        for (int i = row; i < n; i++)
            if (a[i][col] != 0)
                sel = i;

        if (a[sel][col] == 0) continue;

        swap(a[sel], a[row]);
        where[col] = row;

        long long inv = modinv(a[row][col]);
        for (int j = col; j <= m; j++)
            a[row][j] = a[row][j] * inv % MOD;

        for (int i = 0; i < n; i++) {
            if (i != row && a[i][col] != 0) {
                long long factor = a[i][col];
                for (int j = col; j <= m; j++) {
                    a[i][j] = (a[i][j] - factor * a[row][j]) % MOD;
                    if (a[i][j] < 0) a[i][j] += MOD;
                }
            }
        }
        row++;
    }

    vector<long long> ans(m, 0);
    for (int i = 0; i < m; i++) {
        if (where[i] != -1)
            ans[i] = a[where[i]][m];
    }

    for (int i = 0; i < n; i++) {
        bool allZero = true;
        for (int j = 0; j < m; j++)
            if (a[i][j] != 0) {
                allZero = false;
                break;
            }
        if (allZero && a[i][m] != 0) {
            cout << -1;
            return 0;
        }
    }

    for (int i = 0; i < m; i++) {
        ans[i] = (ans[i] % MOD + MOD) % MOD;
        cout << ans[i] << " ";
    }
    return 0;
}
