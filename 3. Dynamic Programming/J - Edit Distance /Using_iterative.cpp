#include<bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    string a, b;
    cin >> a >> b;
    int m = a.size();
    int n = b.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1,0));
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }
 
    for (int i = 0; i <= n; i++) {
        dp[0][i] = i;
    }
 
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if(a[i-1] == b[j-1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }else{
                dp[i][j] = min({dp[i - 1][j - 1], dp[i][j - 1], dp[i - 1][j]}) + 1;
            }
        }
    }
    cout << dp[m][n];
    return 0;
}