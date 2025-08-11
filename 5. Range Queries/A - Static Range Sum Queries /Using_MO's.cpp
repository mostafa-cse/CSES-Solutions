#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }

    vector<pair<int, int>> qry(q);
    for (int i = 0; i < q; i++) {
        cin >> qry[i].first >> qry[i].second;
        qry[i].first--;  
        qry[i].second--; 
    }

    int blk = 350;
    function<pair<int, int>(pair<int, int>)> K = [&](pair<int, int> x) -> pair<int, int> {
        int first = x.first / blk;
        int second = x.second ^ -(x.first / blk & 1);
        return make_pair(first, second);
    };
    
    int Sum = 0;
    function<int(void)> calc = [&]() -> int {
        return Sum;
    };

    function<void(int, int)> add = [&](int ind, int end) -> void {
        Sum += a[ind];
    };

    function<void(int, int)> remove = [&](int ind, int end) -> void {
        Sum -= a[ind];
    };
    
    int L = 0, R = -1;
    vector<int> s(q), res(q);
    iota(s.begin(), s.end(), 0);
    sort(s.begin(), s.end(), [&](int s, int t) {
        return K(qry[s]) < K(qry[t]);
    });

    for (auto qi : s) {
        pair<int, int> q = qry[qi];
        while (L > q.first) add(--L, 0); 
        while (R < q.second) add(++R, 1);
        while (L < q.first) remove(L++, 0);
        while (R > q.second) remove(R--, 1);
        res[qi] = calc();
    }
    for (int i : res) {
        cout << i << endl;
    }
    return 0;
}