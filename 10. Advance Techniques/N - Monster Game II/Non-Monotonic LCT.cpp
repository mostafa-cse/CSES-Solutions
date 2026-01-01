#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
const int INF_MAX = 2e18;
const int INF_MIN = -2e18;
struct Line {
    int slope;
    int constant;
    Line() : slope(0), constant(INF_MAX) {}
    Line(int m, int c) : slope(m), constant(c) {}
    long long eval(long long x) const {
        __int128 v = (__int128)slope * x + (__int128)constant;
        if (v > (__int128)INF_MAX) return INF_MAX;
        if (v < (__int128)INF_MIN) return INF_MIN;
        return (long long)v;
    }
};
struct LiChaoTree {
private:
    int rangeSize;
    vector<Line> tree;
    int combine(int x, int y) {
        return min(x, y);
        // return max(x, y);
        // return x + y;
    }
    void insert(int node, int left, int right, Line newLine) {
        int mid = (left + right) / 2;
        // bool betterAtMid = newLine.eval(mid) > tree[node].eval(mid); //  MAXIMUM
        int betterAtMid = newLine.eval(mid) < tree[node].eval(mid); // MINIMUM

        int betterAtLeft = newLine.eval(left) < tree[node].eval(left); // FOR NON-MONOTONIC MINIMUM
        // int betterAtLeft = newLine.eval(left) > tree[node].eval(left); // FOR NON-MONOTONIC MAXIMUM

        if (betterAtMid) {
            swap(tree[node], newLine);
        }
        if (left == right) {
            return;
        }

        // if (newLine.eval(left) > tree[node].eval(left)) { // MONOTONIC MAXIMUM
        // if (newLine.eval(left) < tree[node].eval(left)) { // MONOTONIC MINIMUM

        if (betterAtLeft != betterAtMid) { // NON-MONOTONIC
            insert(node * 2, left, mid, newLine);
        } else {
            insert(node * 2 + 1, mid + 1, right, newLine);
        }
    }


    void updateSegment(int node, int left, int right, int ql, int qr, Line newLine) {
        if (left > qr || right < ql) return;

        if (left >= ql && right <= qr) {
            insert(node, left, right, newLine);
            return;
        }
        int mid = (left + right) / 2;
        updateSegment(node * 2, left, mid, ql, qr, newLine);
        updateSegment(node * 2 + 1, mid + 1, right, ql, qr, newLine);
    }

    int query(int node, int left, int right, int x) {
        int currentVal = tree[node].eval(x);
        if (left == right) {
            return currentVal;
        }

        int mid = (left + right) / 2;

        if (x <= mid) {
            currentVal = combine(currentVal, query(node * 2, left, mid, x));
        } else {
            currentVal = combine(currentVal, query(node * 2 + 1, mid + 1, right, x));
        }
        return currentVal;
    }

public:
    LiChaoTree(int size) {
        rangeSize = size;
        tree.resize(size * 4 + 1, {0, INF_MAX});
    }

    void addSegment(int x1, int x2, int slope, int constant) {
        x1 = max(0LL, x1);
        x2 = min(rangeSize - 1, x2);
        if(x1 > x2) return;
        updateSegment(1, 0, rangeSize - 1, x1, x2, Line(slope, constant));
    }
    int query(int x) {
        return query(1, 0, rangeSize - 1, x);
    }
    void addLine(int slope, int constant) {
        insert(1, 0, rangeSize - 1, Line(slope, constant));
    }
};
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, slope;
    cin >> n >> slope;

    vector<int> x(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }

    vector<int> m(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> m[i];
    }

    int c = 0;
    LiChaoTree lct(2e6);

    lct.addLine(slope, c);
    for (int i = 1; i <= n; i++) {
        c = lct.query(x[i]);
        lct.addLine(m[i], c);
    }
    cout << c;
    return 0;
}
