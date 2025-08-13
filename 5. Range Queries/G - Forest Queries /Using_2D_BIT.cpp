#include <bits/stdc++.h>
using namespace std;

struct BIT2D {
    int n;
    vector<vector<int>> bit;
    BIT2D(int n) : n(n), bit(n + 1, vector<int>(n + 1, 0)) {}
    
    void update(int x, int y, int delta) {
        for (int i = x; i <= n; i += (i & -i))
            for (int j = y; j <= n; j += (j & -j))
                bit[i][j] += delta;
    }

    int query(int x, int y) {
        int sum = 0;
        for (int i = x; i > 0; i -= (i & -i))
            for (int j = y; j > 0; j -= (j & -j))
                sum += bit[i][j];
        return sum;
    }

    int query(int x1, int y1, int x2, int y2) {
        return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) cin >> grid[i];

    BIT2D bit(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '*') bit.update(i + 1, j + 1, 1);
        }
    }

    while (q--) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        cout << bit.query(y1, x1, y2, x2) << "\n";
    }
}