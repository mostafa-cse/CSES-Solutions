#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, q;
    cin >> n >> q;

    vector<int> Sum(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        Sum[i] = Sum[i - 1] ^ x;
    }

    while (q--) {
        int l, r;
        cin >> l >> r;

        cout << (Sum[r] ^ Sum[l - 1]) << endl;
    }
    return 0;
}