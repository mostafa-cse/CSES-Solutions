#include <bits/stdc++.h>
#define int long long
using namespace std;
vector<int> a;
int Xorv = 0;
inline void add(int idx) { Xorv ^= a[idx]; }
inline void remove_(int idx) { Xorv ^= a[idx]; }
inline int calc() { return Xorv; }
vector<int> MO(const vector<pair<int, int>> &Q) {
    int q = (int)Q.size();
    int n = (int)a.size();
    int blk = max(1ll, (int)sqrt(n));
    vector<int> order(q), res(q);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int i, int j) {
        int bi = Q[i].first / blk;
        int bj = Q[j].first / blk;
        if (bi != bj) return bi < bj;
        return Q[i].second < Q[j].second; 
    });
    int L = 0, R = -1;
    Xorv = 0;
    for (int idx : order) {
        int l = Q[idx].first;
        int r = Q[idx].second;
        while (L > l) add(--L);
        while (R < r) add(++R);
        while (L < l) remove_(L++);
        while (R > r) remove_(R--);
        res[idx] = calc();
    }
    return res;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    if (!(cin >> n >> q))
        return 0;

    a.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<pair<int, int>> Q(q);
    for (int i = 0; i < q; ++i) {
        cin >> Q[i].first >> Q[i].second;
        --Q[i].first;
        --Q[i].second;
    }
    vector<int> ans = MO(Q);
    for (int i = 0; i < q; ++i) {
        cout << ans[i] << '\n';
    }
    return 0;
}
