#include <bits/stdc++.h>
using namespace std;
#define int long long
const int V = 200001;
int n;
int b0[V], b1[V], b2[V];
void add(int b[], int i, int x) {
    for (int j = 0; j < 20 && i <= n; ++j, i += i & -i) {
        b[i] += x;
    }
}
int sum(int b[], int i) {
    int ans = 0;
    for (int j = 0; j < 20 && i > 0; ++j, i -= i & -i) {
        ans += b[i];
    }
    return ans;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int q;
    cin >> n >> q;

    for (int i = 1; i <= n; ++i) {
        int t;
        cin >> t;
        add(b0, i, t << 1);
    }

    for (int i = 0; i < q; ++i) {
        int ops, a, b;
        cin >> ops >> a >> b;

        if (ops & 1) {

            add(b0, a, (a - 2) * (a - 1));
            add(b1, a, 3 - (a << 1));
            add(b2, a, 1);

            add(b0, b + 1, b * (b + 3 - (a << 1)));
            add(b1, b + 1, (a << 1) - 3);
            add(b2, b + 1, -1);
        } else {
            int ans = 0;
            ans += sum(b0, b) + sum(b1, b) * b + sum(b2, b) * b * b;

            --a;
            ans -= sum(b0, a) + sum(b1, a) * a + sum(b2, a) * a * a;
            cout << (ans >> 1) << '\n';
        }
    }
    return 0;
}
