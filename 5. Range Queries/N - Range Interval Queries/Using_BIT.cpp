#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 123;
int bit[4 * N], n;
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
signed main() {
    int q;
    cin >> n >> q;

    vector<pair<int, int>> a(n + 1);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[i] = {x, i};
    }
    sort(a.begin() + 1, a.end());
    struct Query {
        int val, l, r, qt, idx;
        const bool operator<(const Query &other) const {
            return val < other.val;
        }
    };
    vector<Query> qry;
    for (int i = 0; i < q; i++) {
        int l, r, a, b;
        cin >> l >> r >> a >> b;
        qry.push_back({b, l, r, +1, i});
        qry.push_back({a - 1, l, r, -1, i});
    }
    sort(qry.begin(), qry.end());

    int i = 1;
    vector<int> ans(q, 0);
    for (auto [val, l, r, qt, idx] : qry) {
        while (i <= n and a[i].first <= val) {
            update(a[i].second, 1);
            i++;
        }
        ans[idx] += qt * (query(r) - query(l - 1));
    }

    for (int i : ans) {
        cout << i << "\n";
    }
    cout << endl;
    return 0;
}
