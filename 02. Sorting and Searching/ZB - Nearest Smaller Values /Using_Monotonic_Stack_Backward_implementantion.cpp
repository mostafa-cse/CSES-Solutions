#include <bits/stdc++.h>
#define int long long
using namespace std;
#define endl "\n"
#define all(x) x.begin(), x.end()
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    stack<int> val;
    vector<int> ans(n + 1, 0);
    for (int i = n; i >= 1; i--) {
        while (!val.empty() and a[val.top()] > a[i]) {
            ans[val.top()] = i;
            val.pop();
        }
        val.push(i);
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }
    return 0;
}
