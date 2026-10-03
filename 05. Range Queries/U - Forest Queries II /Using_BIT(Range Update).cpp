#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
struct BIT2D {
    long long M[N][N][2], A[N][N][2];
    BIT2D() {
        memset(M, 0, sizeof M);
        memset(A, 0, sizeof A);
    }
    void upd2(long long t[N][N][2], int x, int y, long long mul,
              long long add) {
        for (int i = x; i < N; i += i & -i) {
            for (int j = y; j < N; j += j & -j) {
                t[i][j][0] += mul;
                t[i][j][1] += add;
            }
        }
    }
    void upd1(int x, int y1, int y2, long long mul, long long add) {
        upd2(M, x, y1, mul, -mul * (y1 - 1));
        upd2(M, x, y2, -mul, mul * y2);
        upd2(A, x, y1, add, -add * (y1 - 1));
        upd2(A, x, y2, -add, add * y2);
    }
    void upd(int x1, int y1, int x2, int y2, long long val) {
        upd1(x1, y1, y2, val, -val * (x1 - 1));
        upd1(x2, y1, y2, -val, val * x2);
    }
    long long query2(long long t[N][N][2], int x, int y) {
        long long mul = 0, add = 0;
        for (int i = y; i > 0; i -= i & -i) {
            mul += t[x][i][0];
            add += t[x][i][1];
        }
        return mul * y + add;
    }
    long long query1(int x, int y) {
        long long mul = 0, add = 0;
        for (int i = x; i > 0; i -= i & -i) {
            mul += query2(M, i, y);
            add += query2(A, i, y);
        }
        return mul * x + add;
    }
    long long query(int x1, int y1, int x2, int y2) {
        return query1(x2, y2) - query1(x1 - 1, y2) - query1(x2, y1 - 1) + query1(x1 - 1, y1 - 1);
    }
} bit;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;

    int a[n + 1][n + 1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char k;
            cin >> k;
            a[i][j] = k == '*';
            bit.upd(i, j, i, j, k == '*');
        }
    }
    while (m--) {
        int ty, x1, y1, x2, y2;
        cin >> ty;

        if (ty == 1) {
            int i, j;
            cin >> i >> j;

            int upVal = 0;
            if (a[i][j] == 1) {
                upVal = -1;
                a[i][j] = 0;
            } else {
                upVal = 1;
                a[i][j] = 1;
            }
            bit.upd(i, j, i, j, upVal);
        } else {
            cin >> x1 >> y1 >> x2 >> y2;
            cout << bit.query(x1, y1, x2, y2) << '\n';
        }
    }
    return 0;
}
