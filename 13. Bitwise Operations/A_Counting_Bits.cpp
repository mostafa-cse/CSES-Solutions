#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
vector<int> p2(61);
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    p2[0] = 1;
    for (int i = 1; i <= 60; i++) {
        p2[i] = p2[i - 1] * 2;
    }

    int n;
    cin >> n;

    int ans = 0;
    for (int i = 0; p2[i] <= n; i++) {
        int first = p2[i] * ((n - p2[i] + 1) / p2[i + 1]);
        int second = min((n - p2[i] + 1) % p2[i + 1], p2[i]);
        ans += first + second;
    }
    cout << ans << endl;
    return 0;
}
