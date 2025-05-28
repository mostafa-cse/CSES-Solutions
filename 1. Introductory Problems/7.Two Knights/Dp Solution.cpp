#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxN = 1e4 + 5;
int n;
int dp[maxN];
int sum(int n){
    return n * (n + 1) / 2;
}
signed main() {
    dp[2] = 6, dp[3] = 28, dp[4] = 96;
    for (int i = 5; i <= n; ++i){
        dp[i] = sum(i * i - 1);
        dp[i] += -4 * (i - 2) * (i - 4);
        dp[i] += -3 * 2 * (i - 2);
        dp[i] += -2 * (i - 2) * 2;
        dp[i] += -i;
        dp[i] += -(i - 4);
    }
    for (int i = 1; i <= n; ++i) {
        cout << dp[i] << '\n';
    }
    return 0;
}