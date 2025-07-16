#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 123;
int a[N], bit[4 * N], n;
void update(int i, int val) {
    while (i <= n) {
        bit[i] += val; /*store according to condition*/
        i += (i & (-i));
    }
}
void build() {
    for (int i = 1; i <= n; i++) {
        update(i, a[i]);
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
    int q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build();

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int k, u;
            cin >> k >> u;
            update(k, -a[k]);
            a[k] = u;
            update(k, a[k]);
        } else {
            int l, r;
            cin >> l >> r;
            cout << query(r) - query(l - 1) << endl;
        }
    }
    return 0;
}