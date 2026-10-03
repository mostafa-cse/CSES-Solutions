#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, q;
    cin >> n >> q;

    long long st[26][n];
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    std::copy(a.begin(), a.end(), st[0]);

    for (int i = 1; i <= 25; i++)
        for (int j = 0; j + (1 << i) <= n; j++)
            st[i][j] = (st[i - 1][j] ^ st[i - 1][j + (1 << (i - 1))]);

    while (q--) {
        int L, R;
        cin >> L >> R;
        L -= 1, R -= 1;
        
        long long sum = 0;
        for (int i = 25; i >= 0; i--) {
            if ((1 << i) <= R - L + 1) {
                sum ^= st[i][L];
                L += 1 << i;
            }
        }
        cout << sum << endl;
    }
    return 0;
}