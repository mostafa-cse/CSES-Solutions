#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, k, price[1001],page[1001], dp[1001][100001];
int tabu() {
    vector<vector<int>>dp(n + 1, vector<int>(k + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
            if (j - price[i] >= 0) {
                dp[i][j] = max(page[i] + dp[i - 1][j - price[i]], dp[i][j]);
            }
        }
    }
    return dp[n][k];
}
int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0);  cout.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> price[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> page[i];
    }
    cout << tabu() << '\n';
    return 0;
}