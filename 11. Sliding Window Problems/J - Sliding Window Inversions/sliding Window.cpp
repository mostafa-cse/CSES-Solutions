#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
struct FenwickTree {
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }
    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, k;
    cin >> n >> k;

    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> sa = a;
    sort(all(sa));
    sa.resize(unique(all(sa)) - sa.begin());
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(all(sa), a[i]) - sa.begin();
    }

    int ans = 0;
    FenwickTree ft(sa.size() + 1);
    for (int i = 1; i <= n; i++) {
        ans += min(i - 1,k) - ft.sum(a[i]);
        ft.add(a[i], 1);

        if (i > k) {
            ft.add(a[i - k], -1);
            ans -= ft.sum(a[i - k] - 1);
        }
        if (i >= k) cout << ans << " ";
    }
    return 0;
}

