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
        // return min(x, y);
        return max(x, y);
        // return x + y;
    }
    void insert(int node, int left, int right, Line newLine) {
        int mid = (left + right) / 2;
        bool betterAtMid = newLine.eval(mid) > tree[node].eval(mid); //  MAXIMUM
        // int betterAtMid = newLine.eval(mid) < tree[node].eval(mid); // MINIMUM

        // int betterAtLeft = newLine.eval(left) < tree[node].eval(left); // FOR NON-MONOTONIC MINIMUM
        int betterAtLeft = newLine.eval(left) > tree[node].eval(left); // FOR NON-MONOTONIC MAXIMUM

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
        tree.resize(size * 4 + 1, {0, 0});
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
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }

    // previous smaller element
    vector<int> left(n, -1), right(n, n);
    stack<int> st;

    // Left to Right Smaller Element
    for (int i = 0; i < n; i++) {
        while (!st.empty() and a[st.top()] >= a[i]) {
            st.pop();
        }
        if (!st.empty()) left[i] = st.top();
        st.push(i);
    }

    while (!st.empty()) st.pop();

    // Right to Left Smaller Element
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() and a[st.top()] >= a[i]) {
            st.pop();
        }
        if (!st.empty()) right[i] = st.top();
        st.push(i);
    }

    // for (int i = 0; i < n; i++) cerr << i << " "; cerr << endl;
    // for (int i = 0; i < n; i++) cerr << a[i] << " "; cerr << endl;
    // for(int i = 0; i < 20; i++) cerr << "-"; cerr << endl;
    // dout(left);
    // dout(right);

    int num_windows = n - k + 1;
    LiChaoTree lct(num_windows);

    for (int i = 0; i < n; i++) {
        int height = a[i];

        // Range
        int L = left[i] + 1;
        int R = right[i] - 1;
        // cout << L << " " << R << endl;

        // Rising
        int start_rise = L - k + 1;
        int end_rise = min(L, R - k + 1);
        // cout << "Rising : " << start_rise << " " << end_rise << endl;

        // add rising Segment
        int s = max(0ll, start_rise);
        int e = min(num_windows - 1, end_rise);
        if (s <= e) {
            lct.addSegment(s, e, height, height * (k - L));
        }

        // Falling
        int start_fall = max(L, R - k + 1) + 1;
        int end_fall = R;
        // cout << "Falling : " << start_fall << " " << end_fall << endl;

        // add falling segment
        s = max(0ll, start_fall);
        e = min(num_windows - 1, end_fall);
        if (s <= e) {
            lct.addSegment(s, e, -height, height * (R + 1));
        }

        // Plateau
        int s_plat = end_rise + 1;
        int e_plat = start_fall - 1;

        // add Plateau segment
        s = max(0ll, s_plat);
        e = min(num_windows - 1, e_plat);
        if (s <= e) {
            int span_len = R - L + 1;
            if (span_len >= k) {
                lct.addSegment(s, e, 0, height * k);
            } else {
                lct.addSegment(s, e, 0, height * span_len);
            }
        }
    }
    for (int i = 0; i < num_windows; i++) {
        cout << lct.query(i) << " ";
    }
    return 0;
}
