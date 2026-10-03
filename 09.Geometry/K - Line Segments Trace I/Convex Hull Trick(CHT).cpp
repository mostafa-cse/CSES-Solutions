#include <bits/stdc++.h>
#define int long long
using namespace std;
struct points {
    int slope;
    int constant; // y = mx + c
    int eval(int x) {
        return slope * x + constant;
    }
    bool operator<(const points &other) const{
        if (slope != other.slope) return slope < other.slope;
        return constant < other.constant;
    }
    bool operator==(const points &other) const{
        return slope == other.slope;
    }
};
signed main() {
    int n, m;
    cin >> n >> m;

    vector<points> a;
    for (int i = 0; i < n; i++) {
        int y1, y2;
        cin >> y1 >> y2;

        int x1 = 0, x2 = m;

        int slope = (y2 - y1) / (x2 - x1);
        a.push_back({slope, y1}); // starting y of line (0, y1), (m, y2) is y1
    }
    sort(a.begin(), a.end());
    // a.resize(unique(a.begin(), a.end()) - a.begin()); // it doesn't work
    vector<points> tem;
    for (auto p : a) {
        if (tem.size() >= 1 and tem.back().slope == p.slope) {
            tem.pop_back();
        }
        tem.push_back(p);
    }
    a = tem;

    function<bool(const points &, const points &, const points &)> isRedundant = [&](const points &l1, const points &l2, const points &l3) -> bool {
        __int128_t left = (l1.constant - l2.constant) * (l3.slope - l2.slope);
        __int128_t right = (l2.constant - l3.constant) * (l2.slope - l1.slope);
        return left >= right;
    };

    vector<points> hull;
    for (const auto &line : a) {
        while (hull.size() >= 2) {
            if (isRedundant(hull[hull.size() - 2], hull.back(), line)) { // what does it
                hull.pop_back();
            } else {
                break;
            }
        }
        hull.push_back(line);
    }
    for (auto el : hull) {
        cerr << el.slope << " " << el.constant << endl;
    }

    int ptr = 0;
    for (int x = 0; x <= m; x++) {
        while (ptr < hull.size() - 1 and hull[ptr + 1].eval(x) >= hull[ptr].eval(x)) {
            ptr++;
        }
        cout << hull[ptr].eval(x) << " ";
    }
    return 0;
}
