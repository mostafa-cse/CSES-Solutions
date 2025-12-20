#include<bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 1e9+7;

int32_t main() {
    string s;
    cin >> s;
    s = s;

    int n = s.size();
    vector<int> dp(n + 1, 0), prev(26, -1);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        dp[i + 1] = dp[i] * 2;
        if (prev[s[i] - 'a'] != -1) {
            dp[i + 1] = dp[i + 1] - dp[prev[s[i]-'a']] ;
            // dp_i = dp_(i-1) * 2 - dp[pre[s[i]] - 1];
        }
        dp[i + 1] %= Mod;
        prev[s[i] - 'a'] = i;
    }
    cout << (dp[n] - 1 + Mod) % Mod << endl;
    return 0;
}
