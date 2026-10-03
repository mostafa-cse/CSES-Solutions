#include <bits/stdc++.h>
#define int long long
using namespace std;
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

    vector<int> order(n + 2, 0);
    for (int i = 1; i <= n; i++) {
        order[a[i]] = i;
    }

    string ans = "";
    for (int i = 0; i <= n; i++) {
        ans += 'a';
    }

    char cur = 'a';
    for (int i = 1; i < n; i++) {
        int x = a[i], y = a[i + 1];
        if (order[x + 1] > order[y + 1]) {
            cur++;
        }
        if (cur > 'z') {
            return cout << -1 << endl, 0;
        }
        ans[y] = cur;
    }
    cout << ans.substr(1, n) << endl;
    return 0;
}
