#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, mod = 1e9 + 7;
void space(vector<int>&a){
    vector<int> prev(m + 1, 0);
    if (a[1] == 0)
    {
        fill(prev.begin(), prev.end(), 1);
    }
    else
    {
        prev[a[1]] = 1;
    }
    for (int i = 2; i <= n; i++)
    {
        vector<int> dp(m + 1, 0);
        int st = (a[i] == 0) ? 1 : a[i];
        int end = (a[i] == 0) ? m : a[i];
        for (int j = st; j <= end; j++)
        {
            dp[j] += prev[j];
            if (j + 1 <= m)
            {
                dp[j] = (dp[j] + prev[j + 1]) % mod;
            }
            if (j - 1 >= 1)
            {
                dp[j] = (dp[j] + prev[j - 1]) % mod;
            }
        }
        prev = dp;
    }
 
    int ans = 0;
    for (int i = 1; i <= m; i++)
    {
        ans = (ans + prev[i]) % mod;
    }
    cout << ans << endl;
}
int32_t main() {
    cin >> n >> m;
    vector<int>a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    space(a);
    return 0;
}