#include <bits/stdc++.h>
#define int long long
using namespace std;
struct FenwickTree {
    vector<int> bit, a;
    int n;
    FenwickTree(int _nN) : n(_nN), bit(_nN + 1), a(_nN + 1) {}
    void update(int i, int val) {
        while (i <= n) {
            bit[i] += val;
            i += (i & (-i));
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
    void build() {
        for (int i = 1; i <= n; i++) {
            update(i, a[i]);
        }
    }
};
signed main() {
    int n;
    cin >> n;
    
    vector<int> a(n + 1);
    FenwickTree ft(n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ft.a[i] = 1;
    }
    ft.build();

    for (int i = 0; i < n; i += 1) {
        int x;
        cin >> x;

        int l = 1, r = n, ans = n;
        while (l <= r) {
            int mid = (l + r) >> 1;

            if (x <= ft.query(mid)) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << a[ans] << " ";
        ft.update(ans, -1);
    }
    return 0;
}