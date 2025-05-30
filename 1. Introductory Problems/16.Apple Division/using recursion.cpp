#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }

    function<int(int, int)> fun = [&](int i, int sum) -> int {
        if (i == n) {
            return abs(sum);
        }
        int ans = 1e18;
        ans = min(ans, fun(i + 1, sum + a[i]));
        ans = min(ans, fun(i + 1, sum - a[i]));
        return ans;
    };
    cout << fun(0, 0) << endl;
    return 0;
}