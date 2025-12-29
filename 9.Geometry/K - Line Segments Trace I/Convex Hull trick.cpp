#include <bits/stdc++.h>
#define int long long
using namespace std;
struct Line {
    int slope;
    int constant;
    int eval(int x) {
        return slope * x + constant;
    }
};
struct CHT {
    deque<Line> dq;
    CHT(vector<Line> &a) {
        sort(a.begin(), a.end(), [](Line &a, Line &b){
            if (a.slope != b.slope) return a.slope < b.slope;
            return a.constant < b.constant;
        });
        for (auto el : a) {
            addLine(el.slope, el.constant);
        }
    }
    bool bad(const Line &l1, Line &l2, Line &l3) {
        return (__int128_t)(l2.constant - l1.constant) * (l1.slope - l3.slope) >= (__int128_t)(l3.constant - l1.constant) * (l1.slope - l2.slope);
    }
    void addLine(int slope, int constant) {
        Line a{slope, constant};
        while (dq.size() >= 2 and bad(dq[dq.size() - 2], dq.back(), a)) {
            dq.pop_back();
        }
        dq.push_back(a);
    }
    int query(int x){
        while (dq.size() >= 2 and dq[0].eval(x) >= dq[1].eval(x)) { // Min
        // while (dq.size() >= 2 and dq[0].eval(x) <= dq[1].eval(x)) { // Max
            dq.pop_front();
        }
        return dq[0].eval(x);
    }

};
signed main() {
    int n, m;
    cin >> n >> m;

    vector<Line> a;
    for (int i = 0; i < n; i++) {
        int x1 = 0, y1, x2 = m, y2;
        cin >> y1 >> y2;

        int slope = (y2 - y1) / (x2 - x1);
        int constant = y1;

        a.push_back({slope, constant});
    }
    CHT cht(a);

    for (int i = 0; i <= m; i++) {
        cout << cht.query(i) << " ";
    }
    return 0;
}
