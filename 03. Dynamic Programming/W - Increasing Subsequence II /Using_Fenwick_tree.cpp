#include <bits/stdc++.h>
#define int long long
using namespace std;

const int Mod = 1e9 + 7;

class FenwickTree {
  public:
    vector<int> bit;
    int n;
    FenwickTree(int n) : n(n), bit(n + 1, 0) {}
    void update(int x, int v) {
        for (; x <= n; x += x & -x)
            bit[x] = (bit[x] + v) % Mod;
    }
    int get(int x) const {
        int res = 0;
        for (; x >= 1; x -= x & -x)
            res = (res + bit[x]) % Mod;
        return res;
    }
};

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    vector<int> b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());

    FenwickTree ft(b.size());
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int c = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
        int cnt = (ft.get(c - 1) + 1) % Mod;
        ft.update(c, cnt);
        ans = (ans + cnt) % Mod;
    }
    cout << ans << '\n';
    return 0;
}