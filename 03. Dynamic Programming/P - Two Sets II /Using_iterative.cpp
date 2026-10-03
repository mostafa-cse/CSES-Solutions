#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9 + 7;
int modexpo(int a, int p,int mod){
    int res = 1;
    while(p){
        if(p&1){
            res = (a * res) % mod;
        }
        p >>= 1;
        a = (a * a) % mod;
    }
    return res;
}
int tabu(int n,int sum) {
    vector<vector<int> > dp(n + 1, vector<int>(sum + 1, 0));
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            int ans = dp[i - 1][j] % mod;
            if(j - i >= 0) {
                ans = (ans + dp[i - 1][j - i]) % mod;
            }
            dp[i][j] = ans;
        }
    }
    return (dp[n][sum] * modexpo(2, mod - 2, mod)) % mod;
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    int sum = n * (n + 1) / 2;
    if (sum & 1) {
        cout << 0 << '\n';
    } else {
        vector<int> a;
        for(int i = 1; i<= n; i++) {
            a.push_back(i);
        }
        cout << tabu(n, sum / 2) << '\n';
    }
    return 0;
}