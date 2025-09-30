#include <bits/stdc++.h>
using namespace std;

struct BIT2D {
    int n;
    vector<vector<int>> t;
    BIT2D(int n=0): n(n), t(n+1, vector<int>(n+1, 0)) {}
    void init(int N) { n = N; t.assign(n+1, vector<int>(n+1, 0)); }
    // Add val at (y,x)
    void add(int y, int x, int val) {
        for (int i = y; i <= n; i += i & -i)
            for (int j = x; j <= n; j += j & -j)
                t[i][j] += val;
    }
    // Prefix sum on [1..y] x [1..x]
    int sum(int y, int x) const {
        int res = 0;
        for (int i = y; i > 0; i -= i & -i)
            for (int j = x; j > 0; j -= j & -j)
                res += t[i][j];
        return res;
    }
    // Rectangle sum [y1..y2] x [x1..x2]
    int rect(int y1, int x1, int y2, int x2) const {
        if (y1 > y2 || x1 > x2) return 0;
        return sum(y2, x2) - sum(y1 - 1, x2) - sum(y2, x1 - 1) + sum(y1 - 1, x1 - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    if (!(cin >> n >> q)) return 0;
    vector<string> g(n+1);
    for (int i = 1; i <= n; ++i) {
        string s; cin >> s;
        g[i] = " " + s;
    }
    BIT2D bit(n);
    vector<vector<int>> a(n+1, vector<int>(n+1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (g[i][j] == '*') {
                a[i][j] = 1;
                bit.add(i, j, 1);
            }
        }
    }
    while (q--) {
        int type; cin >> type;
        if (type == 1) {
            int y, x; cin >> y >> x;
            int newv = 1 - a[y][x];
            int delta = newv - a[y][x];
            a[y][x] = newv;
            bit.add(y, x, delta);
        } else {
            int y1, x1, y2, x2; cin >> y1 >> x1 >> y2 >> x2;
            cout << bit.rect(y1, x1, y2, x2) << '\n';
        }
    }
    return 0;
}
