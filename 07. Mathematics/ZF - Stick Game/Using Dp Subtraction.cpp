#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int p, n;
    cin >> p >> n;

    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }

    vector<int> dp(p + 1, 0);
    for (int i = 1; i <= p; i++) {
        for (int j = 0; j < n; j++) {
            if (i - a[j] >= 0) {
                if (!dp[i - a[j]]) { // ager kono move a jdi Loss hoi taile oi move akn win hobe
                    dp[i] = 1;
                    break;
                }
            }
        }
    }
    string str = "LW";
    for (int i = 1; i <= p; i++) {
        cout << str[dp[i]];
    }
    return 0;
}
