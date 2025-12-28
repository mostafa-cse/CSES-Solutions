#include <bits/stdc++.h>
#define int long long
using namespace std;
class Fenwick {
    int n;
    std::vector<int> bit;

public:
    explicit Fenwick(int n) : n(n), bit(n + 1, 0) {}

    void update(int idx, int delta) {
        for (; idx <= n; idx += idx & -idx)
            bit[idx] += delta;
    }

    int query(int idx) const {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx)
            res += bit[idx];
        return res;
    }

    int query(int l, int r) const {
        return query(r) - query(l - 1);
    }
};
struct event {
    int x;
    int type; // 0 -> remove, 1 -> query, 2 -> add
    int y1, y2;

    bool operator<(const event &other) const{
        if (x != other.x) return x < other.x;
        return type < other.type;
    }
};
const int offset = 1e6;
signed main() {
    int n;
    cin >> n;

    vector<event> a;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);

        if (x1 == x2) {
            a.push_back({x1, 1, y1 + offset, y2 + offset});
        } else {
            a.push_back({x1, 2, y1 + offset, y2 + offset});
            a.push_back({x2, 0, y1 + offset, y2 + offset});
        }
    }
    sort(a.begin(), a.end());

    Fenwick ft(2e6);
    int ans = 0;
    for (auto [x, t, y1, y2] : a) {
        if (t == 1) {
           ans += ft.query(y1, y2);
        } else if (t == 2) {
            ft.update(y1, 1);
        } else {
            ft.update(y2, -1);
        }
    }
    cout << ans << endl;
    return 0;
}
