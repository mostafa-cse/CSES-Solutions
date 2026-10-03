#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    vector<pair<int, int>> a(n);
    for (auto &[f, s] : a) {
        cin >> f >> s;
    }
    sort(a.begin(), a.end(), [&](pair<int, int>&x, pair<int, int>&y){
        if (x.second == y.second) return x.first < y.first;
        return x.second < y.second;
    });

    int ans = 0, curr = 0;
    for (int i = 0; i < n; i++) {
        if (a[i].first >= curr) {
            ans++;
            curr = a[i].second;
        }
    }
    cout << ans;
    return 0;
}