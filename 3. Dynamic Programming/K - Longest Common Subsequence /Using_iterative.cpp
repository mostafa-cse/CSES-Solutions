#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;

    vector<int> a(n), b(m);
    for (int &i : a) {
        cin >> i;
    }

    for (int &i : b) {
        cin >> i;
    }

    vector<vector<int>> dp(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int ans = 0;
            if (a[i] == b[j]) {
                ans = 1;
                if (i and j) ans += dp[i - 1][j - 1];
            }
            if (i) ans = max(ans, dp[i - 1][j]);
            if (j) ans = max(ans, dp[i][ j - 1]);
            dp[i][j] = ans;
        }
    }
    cout << dp[n - 1][m - 1] << endl;

    int i = n - 1, j = m - 1;
    stack<int> lcs;
    while (i >= 0 && j >= 0) {
        if (a[i] == b[j]) {
            lcs.push(a[i]);
            i--;
            j--;
        } else if (i && dp[i][j] == dp[i - 1][j]) {
            i--;
        } else if (j && dp[i][j] == dp[i][j - 1]) {
            j--;
        } else {
            break;
        }
    }
    while (!lcs.empty()) {
        cout << lcs.top() << " ";
        lcs.pop();
    }
    cout << endl;
    return 0;
}