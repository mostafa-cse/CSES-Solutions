#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,a[101];
bool dp[101][100005];
vector<int> tabu() {
    memset(dp, 0, sizeof(dp));
    for(int i = 0; i <= 100; i++) {
        dp[i][0] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= 100000; j++) {
            dp[i][j] |= dp[i - 1][j];
            if(j - a[i] >= 0) {
                dp[i][j] |= dp[i - 1][j - a[i]];
            }
        }
    }
    int ans = 0;
    vector<int> sums;
    for (int i = 1; i <= 100000; i++) {
        if(dp[n][i]) {
            sums.push_back(i);
        }
    }
    return sums;
}
int32_t main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);  cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    set <int> s;
    vector<int> ans = tabu();
    cout << ans.size() << '\n';
    for (auto ele : ans) {
        cout << ele << " ";
    }
    return 0;
}