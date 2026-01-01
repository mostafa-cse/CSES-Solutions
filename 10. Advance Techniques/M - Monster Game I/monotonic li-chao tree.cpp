#include<bits/stdc++.h>
#define int long long
using namespace std;

const int INF = 1e18;
const int MAX_VAL = 1e6 + 5; 

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

        bool betterAtMid = newLine.eval(mid) < tree[node].eval(mid);

        if (betterAtMid) {
            swap(tree[node], newLine);
        }
        if (left == right) {
            return;
        }

        if (newLine.eval(left) < tree[node].eval(left)) {
            insert(node * 2, left, mid, newLine);
        } else {
            insert(node * 2 + 1, mid + 1, right, newLine);
        }
    }

    int query(int node, int left, int right, int x) {
        int currentVal = tree[node].eval(x);
        if (left == right) {
            return currentVal;
        }
        int mid = (left + right) / 2;
        if (x <= mid) {
            return min(currentVal, query(node * 2, left, mid, x));
        } else {
            return min(currentVal, query(node * 2 + 1, mid + 1, right, x));
        }
    }

public:
    LiChaoTree(int size) {
        rangeSize = size;
        tree.resize(size * 4 + 1, {0, INF});
    }

    int query(int x) {
        return query(1, 0, rangeSize - 1, x);
    }

    void addLine(int slope, int constant) {
        insert(1, 0, rangeSize - 1, Line(slope, constant));
    }
};

const int MAXN = 200005;
int s[MAXN];
int f[MAXN];

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    int x;
    if (!(cin >> n >> x)) return 0;

    for (int i = 1; i <= n; i++) cin >> s[i];
    for (int i = 1; i <= n; i++) cin >> f[i];

    LiChaoTree lct(MAX_VAL);
    lct.addLine(x, 0);

    int current_dp = 0;

    for (int i = 1; i <= n; i++) {
        current_dp = lct.query(s[i]);
        lct.addLine(f[i], current_dp);
    }

    cout << current_dp << endl;

    return 0;
}
