#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n), b(m);
    for (int &i : a) {
        cin >> i;
    }

    for (int &i : b) {
        cin >> i;
    }

    vector<vector<int>> dp(n, vector<int>(m, -1));
    function<int(int, int)> rec = [&](int i, int j) -> int {
        if (i >= n or j >= m) return 0;
        if (dp[i][j] != -1) return dp[i][j];
        int ans = 0;
        if (a[i] == b[j]) ans = max(ans, 1 + rec(i + 1, j + 1));
        ans = max(ans, rec(i + 1, j));
        ans = max(ans, rec(i, j + 1));
        return dp[i][j] = ans;
    };
    cout << rec(0, 0) << endl;

    // function<void(int, int)> Print = [&](int i, int j) -> void {
    //     if (i >= n or j >= m) return;
    //     if (a[i] == b[j] && dp[i][j] == 1 + (i + 1 < n && j + 1 < m ? dp[i + 1][j + 1] : 0)) {
    //         cout << a[i] << " ";
    //         Print(i + 1, j + 1);
    //     } else if (i + 1 < n && dp[i][j] == dp[i + 1][j]) {
    //         Print(i + 1, j);
    //     } else if (j + 1 < m && dp[i][j] == dp[i][j + 1]) {
    //         Print(i, j + 1);
    //     }
    // };
    // Print(0, 0);

    int i = 0, j = 0;
    vector<int> lcs;
    while (i < n && j < m) {
        if (a[i] == b[j]) {
            lcs.push_back(a[i]);
            i++;
            j++;
        } else if (i + 1 < n && dp[i][j] == dp[i + 1][j]) {
            i++;
        } else if (j + 1 < m && dp[i][j] == dp[i][j + 1]) {
            j++;
        } else {
            break;
        }
    }
    for (int x : lcs) cout << x << " ";
    cout << endl;
    return 0;
}