#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 123;
int a[N], bit[4 * N];
void update(int i, int val, int n) {
    while (i <= n) {
        bit[i] += val; /*store according to condition*/
        i += (i & (-i));
    }
}
void build(int n) {
    for (int i = 1; i <= n; i++) {
        update(i, a[i], n);
    }
}
int query(int idx) {
    int ans = 0;
    while (idx > 0) {
        ans += bit[idx];
        idx -= (idx & (-idx));
    }
    return ans;
}
signed main() {
    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build(n);

    while (q--) {
        int l, r;
        cin >> l >> r;

        cout << query(r) - query(l - 1) << endl;
    }
    return 0;
}