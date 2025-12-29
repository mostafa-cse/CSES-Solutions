#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()

const int INF_MIN = -2e18;
struct Line {
    int slope;
    int constant;
    Line() {}
    Line(int m, int c) : slope(m), constant(c) {}
    int eval(int x) {
        return slope * x + constant;
    }
};
struct LiChaoTree {
private:
    int rangeSize;
    vector<Line> tree;
    void insert(int node, int left, int right, Line newLine) {
        int mid = (left + right) / 2;
        bool betterAtMid = newLine.eval(mid) > tree[node].eval(mid);
        if (betterAtMid) {
            swap(tree[node], newLine);
        }
        if (left == right) {
            return;
        }
        if (newLine.eval(left) > tree[node].eval(left)) {
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
            return max(currentVal, query(node * 2, left, mid, x));
        } else {
            return max(currentVal, query(node * 2 + 1, mid + 1, right, x));
        }
    }

public:
    LiChaoTree(int size) {
        rangeSize = size;
        tree.resize(size * 4 + 1, {0, INF_MIN});
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
    int n;
    cin >> n;

    LiChaoTree lct(200005);
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;

        if (t == 1) {
            int slope, constant;
            cin >> slope >> constant;
            lct.addLine(slope, constant);
        } else {
            int x;
            cin >> x;

            cout << lct.query(x) << endl;
        }
    }
    return 0;
}

