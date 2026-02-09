#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }

    int up = n - k;
    for (int i = 0; i < 18; i++) {
        if (up >> i & 1) {
            for (int j = 0; j < n - (1 << i); j++) {
                a[j] ^= a[j + (1 << i)];
            }
            n -= (1 << i);
        }
    }
    for (int i = 0; i < k; i++) {
        cout << a[i] << " ";
    }
    return 0;
}
