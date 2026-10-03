#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
struct event {
    int x;
    int type; // +1 left, -1 right edge/line

    int y_low;
    int y_high;
    bool operator<(const event &other) const {
        return x < other.x;
    }
};
struct SegmentTree {
    int n;
    vector<int> count;
    vector<int> len;
    vector<int> y_raw;

    SegmentTree (const vector<int> &y) {
        y_raw = y;
        n = y.size();

        count.resize(4 * n + 1, 0);
        len.resize(4 * n + 1, 0);
    }

    void push_up(int node, int start, int end) {
        if (count[node] > 0) {
            len[node] = y_raw[end] - y_raw[start];
        } else {
            if (end - start == 1) {
                len[node] = 0;
            } else {
                len[node] = len[node * 2] + len[node * 2 + 1];
            }
        }
    }
    void update(int node, int start, int end, int l, int r, int val) {
        if (l >= r) {
            return ;
        }

        if (l <= y_raw[start] and r >= y_raw[end]) {
            count[node] += val;
            push_up(node, start, end);
            return;
        }

        int mid = (start + end) / 2;
        if (l < y_raw[mid]) {
            update(node * 2, start, mid, l, min(r, y_raw[mid]), val);
        }
        if (r > y_raw[mid]) {
            update(node * 2 + 1, mid, end, max(l, y_raw[mid]), r, val);
        }
        push_up(node, start, end);
    }

    void addRect(int yl, int yh, int type) {
        update(1, 0, n - 1, yl, yh, type);
    }
    int get_Len() {
        return len[1];
    }
};
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n;
    cin >> n;

    vector<event> a;
    vector<int> y_cord;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        a.push_back({x1, +1, y1, y2});
        a.push_back({x2, -1, y1, y2});

        y_cord.push_back(y1);
        y_cord.push_back(y2);
    }
    sort(all(y_cord));
    y_cord.resize(unique(all(y_cord)) - y_cord.begin());

    sort(all(a));

    int ans = 0;
    SegmentTree st(y_cord);
    for (int i = 0; i < a.size(); i++) {
        if (i) {
            int dx = a[i].x - a[i - 1].x;
            int activeLen = st.get_Len();

            ans += dx * activeLen;
        }
        st.addRect(a[i].y_low, a[i].y_high, a[i].type);
    }
    cout << ans << endl;
    return 0;
}

