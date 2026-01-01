#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Line {
    mutable int m, c, p; // slope, constant, intersection point

    bool operator<(const Line& o) const {
        return m < o.m;
    }

    bool operator<(int x) const {
        return p < x;
    }
};
struct LineContainer : multiset<Line, less<>> {
    static const int INF = LLONG_MAX;

    int div(int a, int b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }

    bool isect(iterator x, iterator y) {
        if (y == end()) {
            x->p = INF;
            return false;
        }

        if (x->m == y->m) {
            x->p = (x->c > y->c) ? INF : -INF;
        } else {
            int num = y->c - x->c;
            int den = x->m - y->m;


            __int128 numer = (__int128)y->c - (__int128)x->c;
            x->p = numer / den - ((numer ^ den) < 0 && numer % den);
        }
        return x->p >= y->p;
    }

    void add_max(int m, int c) {
        auto z = insert({m, c, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) {
            isect(x, y = erase(y));
        }
        while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
    }

    int query_max(int x) {
        if (empty()) return 0;
        auto l = *lower_bound(x);
        return l.m * x + l.c;
    }

    void add_min(int m, int c) {
        add_max(-m, -c);
    }

    int query_min(int x) {
        return -query_max(x);
    }
};

signed main() {
    // ফাস্ট I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    int start_slope;
    cin >> n >> start_slope;

    vector<int> x(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }

    vector<int> m(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> m[i];
    }

    LineContainer lc;

    lc.add_min(start_slope, 0);

    int c = 0;

    for (int i = 1; i <= n; i++) {
        c = lc.query_min(x[i]);

        lc.add_min(m[i], c);
    }
    cout << c << endl;

    return 0;
}
