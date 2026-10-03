#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, k, price[1001],page[1001], dp[1001][100001];
int tabuOpt() {
    vector<int>dp(k + 1,0), tem(k + 1,0);
    for (int i = 1; i <= n; i++) {
        vector<int> tem(k + 1,0);
        for (int j = 1; j <= k; j++) {
            int ans = dp[j];
            if(j - price[i] >= 0) {
                ans = max(ans, page[i] + dp[j - price[i]]);
            }
            tem[j] = ans;
        }
        dp = tem;
    }
    return dp[k];
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> price[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> page[i];
    }
    cout << tabuOpt() << '\n';
    return 0;
}