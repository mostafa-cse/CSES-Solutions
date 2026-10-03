#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> a(n + 2);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    stack<int> s;
    vector<vector<int>> nextGreater(n + 2, vector<int>(20, 0)); 
    for (int i = 1; i <= n; ++i) {
        while (!s.empty() && a[i] > a[s.top()]) {
            nextGreater[s.top()][0] = i;
            s.pop();
        }
        s.push(i);
    }
    while (!s.empty()) {
        nextGreater[s.top()][0] = n + 1;
        s.pop();
    }
    nextGreater[n + 1][0] = n + 1;

    for (int k = 1; k <= 19; ++k)
        for (int j = 1; j <= n + 1; ++j)
            nextGreater[j][k] = nextGreater[nextGreater[j][k - 1]][k - 1];

    while (q--) {
        int l, r;
        cin >> l >> r;
        int ans = 1;
        for (int k = 19; k >= 0; --k) {
            if (nextGreater[l][k] <= r) {
                l = nextGreater[l][k];
                ans += (1LL << k);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
