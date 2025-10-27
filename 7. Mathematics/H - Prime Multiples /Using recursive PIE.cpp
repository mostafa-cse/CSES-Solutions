#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;

    vector<int> a(k);
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }

    function<int(int, int)> dfs = [&](int N, int i) -> int {
        if (i == k) return 0;
        int ans = N / a[i];
        ans -= dfs(N / a[i], i + 1); // take this
        ans += dfs(N, i + 1); // not take this
        return ans;
    };
    cout << dfs(n, 0) << endl;
    return 0;
}
