#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = (1ll << 60);

struct Node {
    int sum, pref, suff, ans;
};
Node merge(const Node& L, const Node& R) {
    Node res;
    res.sum = L.sum + R.sum;
    res.pref = max(L.pref, L.sum + R.pref);
    res.suff = max(R.suff, R.sum + L.suff);
    res.ans = max({L.ans, R.ans, L.suff + R.pref});
    return res;
}
vector<Node> seg;
void build(const vector<int>& a, int v, int tl, int tr) {
    if (tl == tr) {
        int x = a[tl];
        seg[v] = {x, x, x, x};
    } else {
        int tm = (tl + tr) >> 1;
        build(a, v * 2, tl, tm);
        build(a, v * 2 + 1, tm + 1, tr);
        seg[v] = merge(seg[v * 2], seg[v * 2 + 1]);
    }
}
int maxSubarraySeg(const vector<int>& a) {
    int n = a.size();
    seg.assign(4 * n, {0, 0, 0, -INF});
    build(a, 1, 0, n - 1);
    return seg[1].ans;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    cout << maxSubarraySeg(a) << '\n';
    return 0;
}
