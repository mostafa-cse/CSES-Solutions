// Finding minimum of [0, r] only in one-dimensional array
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct FenwickTreeMin {
    vector<int> bit;
    int n;
    const int INF = (int)1e9;

    FenwickTreeMin(int n) {
        this->n = n;
        bit.assign(n, INF);
    }

    FenwickTreeMin(vector<int> a) : FenwickTreeMin(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            update(i, a[i]);
    }

    int getmin(int r) {
        int ret = INF;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret = min(ret, bit[r]);
        return ret;
    }

    void update(int idx, int val) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] = min(bit[idx], val);
    }
};
signed main() {
    int n, q;
    cin >> n >> q;
    
    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }

    FenwickTreeMin ft(a);
    while (q--) {
        int l, r;
        cin >> l >> r;
        l -= 1, r -= 1;

        // May not possible for Range minimum Query
    }

    return 0;
}