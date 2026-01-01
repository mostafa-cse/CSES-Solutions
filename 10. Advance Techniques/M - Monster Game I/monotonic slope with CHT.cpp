#include<bits/stdc++.h>
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
    CHT() {}
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
        if (!dq.empty() and dq.back().slope == slope) { return;} // if need duplicate reduction
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

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    cin >> n >> x;

    vector<int> X_cor(n + 1);
    for (int i = 1; i <= n; i++) cin >> X_cor[i];

    vector<int> slope(n + 1);
    for (int i = 1; i <= n; i++) cin >> slope[i];

    CHT cht;
    cht.addLine(x, 0);

    int constant = 0;
    for (int i = 1; i <= n; i++) {
        constant = cht.query(X_cor[i]);
        cht.addLine(slope[i], constant);
    }
    cout << constant << endl;
    return 0;
}
