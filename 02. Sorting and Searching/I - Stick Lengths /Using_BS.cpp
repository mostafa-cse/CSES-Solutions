#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    function<int(int)> fun = [&](int len) -> int {
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += abs(a[i] - len);
        }
        return ans;
    };

    int l = 0, r = 1e10, ans = -1;
    while (l <= r) {
        int mid = l + r >> 1;

        int pre_cost = fun(mid - 1);
        int mid_cost = fun(mid);
        int post_cost = fun(mid + 1);
        if (pre_cost >= mid_cost and mid_cost <= post_cost) {
            ans = mid;
            break;
        } else if (pre_cost >= mid_cost and mid_cost >= post_cost) {
            l = mid + 1;
        } else if (pre_cost <= mid_cost and mid_cost <= post_cost) {
            r = mid - 1;
        }
    }
    cout << fun(ans) << endl;
    return 0;
}