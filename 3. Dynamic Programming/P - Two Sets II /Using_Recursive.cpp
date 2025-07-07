#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9 + 7;
int memoi(int n, int sum, vector<int> &a, vector<vector<int> > &dp) {
    if(sum < 0 or n < 0) {
        return (sum == 0) * 1ll;
    }
    if(dp[n][sum] != -1) {
        return dp[n][sum];
    }
    int total = 0;
    total = (total + (memoi(n - 1, sum - a[n], a, dp)));
    total = (total + (memoi(n - 1, sum, a, dp))) % mod;
    return dp[n][sum] =  total;
}
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
        vector<vector<int>> dp(n + 1, vector<int>((sum >> 1) + 1ll, -1));
        cout << (memoi(n - 1, (sum >> 1), a, dp) * modexpo(2, mod - 2, mod)) % mod << '\n';
    }
    return 0;
}