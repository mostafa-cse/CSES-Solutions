#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, mod = 1e9 + 7;
void tabu(vector<int>&a) {
    vector<vector<int>> dp(n, vector<int>(m + 1, 0));
    if(a[0] == 0) {
        for (int i = 1; i<= m; i++) {
            dp[0][i] = 1;
        }
    }else {
        dp[0][a[0]] = 1;
    }
 
    for (int i = 1; i < n; i++) {
        if (a[i] == 0) {
            for (int j = 1; j<= m; j ++) {
                dp[i][j] += dp[i-1][j];
                if(j -1 >= 1) {
                    dp[i][j] += dp[i-1][j -1];
                }
                if(j + 1<= m) {
                    dp[i][j] += dp[i-1][j+1];
                }
                dp[i][j] %= mod;
            }
        } else {
            dp[i][a[i]] += dp[i - 1][a[i]];
            if(a[i] - 1 >= 1) {
                dp[i][a[i]] += dp[i - 1][a[i] - 1];
            }
            if (a[i] + 1 <= m){
                dp[i][a[i]] += dp[i - 1][a[i] + 1];
            }
            dp[i][a[i]] %= mod;
        }
    }
    int ans = 0;
    for(int i = 1; i <= m; i++) {
        ans = (ans + dp[n-1][i]) % mod;
    }
    cout << ans << endl;
}
int32_t main() {
    cin >> n >> m;
    vector<int>a(n + 1);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    tabu(a);
    return 0;
}