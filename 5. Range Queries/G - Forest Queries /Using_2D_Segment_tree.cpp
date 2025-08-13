#include <bits/stdc++.h>
#define int long long
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
struct SegmentTree2D {
    vector<vector<int>> seg, a;
    int n;
    SegmentTree2D(int n, vector<vector<int>> &_a) : n(n) {
        seg.resize(4 * n, vector<int>(4 * n));
        a = _a;
    }
    void buildY(int nodex, int lx, int rx, int nodey, int ly, int ry) {
        if (ly == ry) {
            if (lx == rx) {
                seg[nodex][nodey] = a[lx][ly];
            } else {
                seg[nodex][nodey] = seg[nodex * 2][nodey] + seg[nodex * 2 + 1][nodey];
            }
            return;
        }
        int mid = ly + ry >> 1;
        buildY(nodex, lx, rx, nodey * 2, ly, mid);        
        buildY(nodex, lx, rx, nodey * 2 + 1, mid + 1, ry);
        seg[nodex][nodey] = seg[nodex][nodey * 2] + seg[nodex][nodey * 2 + 1];
    }
    void buildX(int nodex, int lx, int rx) {
        if (lx != rx) {
            int mid = lx + rx >> 1;
            buildX(nodex * 2, lx, mid);
            buildX(nodex * 2 + 1, mid + 1, rx);
        }
        buildY(nodex, lx, rx, 1, 0, n - 1);
    }

    int queryY(int nodex, int nodey, int ly, int ry, int qly, int qry) {
        if (qly > ry or qry < ly) {
            return 0;
        } else if (ly >= qly and ry <= qry) {
            return seg[nodex][nodey];
        } else {
            int mid = ly + ry >> 1;
            int left = queryY(nodex, nodey * 2, ly, mid, qly, qry);
            int right = queryY(nodex, nodey * 2 + 1, mid + 1, ry, qly, qry);
            return left + right;
        }
    }
    int queryX(int nodex, int lx, int rx, int qx1, int qx2, int qy1, int qy2) {
        if (qx1 > rx or qx2 < lx) return 0;
        if (qx1 <= lx and rx <= qx2) {
            return queryY(nodex, 1, 0, n - 1, qy1, qy2);
        }
        int mid = lx + rx >> 1;
        int left = queryX(nodex * 2, lx, mid, qx1, qx2, qy1, qy2);
        int right = queryX(nodex * 2 + 1, mid + 1, rx, qx1, qx2, qy1, qy2);
        return left + right;
    }
    void build() {
        buildX(1, 0, n - 1);
    }
    int query(int r1, int c1, int r2, int c2) {
        return queryX(1, 0, n - 1, r1 - 1, r2 - 1, c1 - 1, c2 - 1);
    }
};
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;

    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c;
            a[i][j] = c == '*';
        }
    }
    SegmentTree2D st(n, a);
    st.build();

    while (q--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        
        cout << st.query(r1, c1, r2, c2) << endl;
    }
    return 0;
}