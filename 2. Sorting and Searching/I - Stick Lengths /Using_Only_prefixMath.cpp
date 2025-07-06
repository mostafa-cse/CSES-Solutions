#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    int n;
    cin >> n;
    vector<int> v(n);
    vector<int> ps(n + 1, 0);
    for (int i = 0; i < n; i++)
        cin >> v[i];
    sort(v.begin(), v.end());
    for (int i = 1; i < n + 1; i++)
        ps[i] = ps[i - 1] + v[i - 1];

    int ans = (1ll << 62);
    for (int i = 0; i < n; i++) {
        int sum = (ps[n] - ps[i]) - v[i] * 1ll * (n - i);
        sum += v[i] * 1ll * (i + 1) - ps[i + 1];
        ans = min(ans, sum);
    }
    cout << ans << endl;
    return 0;
}