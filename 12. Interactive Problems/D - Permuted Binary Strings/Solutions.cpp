#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n;
    cin >> n;

    vector<int> ans(n + 1, 0);
    for (int i = 0; i <= 9; i++) {
        cout << "? ";
        for (int j = 1; j <= n; j++) {
            cout << (j >> i & 1);
        }
        cout << endl;

        string s;
        cin >> s;
        s = " " + s;

        for (int j = 1; j <= n; j++) {
            ans[j] |= (int)(s[j] - '0') * (1LL << i);
        }
    }
    cout << "! ";
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
