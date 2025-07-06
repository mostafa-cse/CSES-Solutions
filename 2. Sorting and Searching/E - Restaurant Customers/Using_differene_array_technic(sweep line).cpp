#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);  cout.tie(0);
    int n;
    cin >> n;
    vector<pair<int, int>> a;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        a.push_back({x, 1});   // arrival: +1
        a.push_back({y, -1});  // departure: -1
    }
    sort(all(a));
    int ans = 0, sum = 0;
    for (auto &[time, delta] : a) {
        sum += delta;
        ans = max(ans, sum);
    }
    cout << ans << '\n';
    return 0;
}
