#include <bits/stdc++.h>
#define int long long
using namespace std;
const int M = 1e6 + 6;
int dp[M];
int rec(int num) {
    if (num <= 0) {
        return num == 0 ? 0 : 1e18;
    }
    if (dp[num] != -1) return dp[num];
    int ans = 1e18;
    int tem = num;
    while (tem > 0) {
        int last = tem % 10;
        tem /= 10;
        if (last) ans = min(ans, 1 + rec(num - last));
    }
    return dp[num] = ans;
}
signed main() {
    int n;
    cin >> n;

    memset(dp, -1, sizeof dp);
    cout << rec(n);
    return 0;
}