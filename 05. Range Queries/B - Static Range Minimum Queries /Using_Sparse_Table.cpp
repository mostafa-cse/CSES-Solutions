#include <bits/stdc++.h>
#define int long long
using namespace std;
struct SparseTable {
    int n;
    vector<vector<int>> st;
    SparseTable(int n) : st(26, vector<int>(n + 1)), n(n) {}
    int merge(int a, int b) {
        return a + b;
        // return min(a, b);
        // return max(a, b);
    }
    void build() {
        for (int i = 1; i <= 25; i++) {
            for (int j = 0; j + (1 << i) <= n; j++) {
                st[i][j] = merge(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    int query(int L, int R) {
        int ans = 1e18;
        for (int i = 25; i >= 0; i--) {
            if ((1 << i) <= R - L + 1) {
                ans = merge(st[i][L], ans);
                L += 1 << i;
            }
        }
        return ans;
    }
};
signed main() {
    int n, q;
    cin >> n >> q;

    SparseTable a(n);
    for (int i = 0; i < n; i++) {
        cin >> a.st[0][i];
    }
    a.build();
    while (q--) {
        int L, R;
        cin >> L >> R;
        L -= 1, R -= 1;
        cout << a.query(L, R) << endl;
    }
    return 0;
}