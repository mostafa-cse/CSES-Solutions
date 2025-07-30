#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1e9 + 7;
int dp[20][1 << 20];
signed main() {
    int n, m;
    cin >> n >> m;


    vector<int> adj[n];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
    }

    memset(dp, -1, sizeof dp);
    function<int(int, int)> rec = [&](int u, int mask) -> int {
        if (mask == (1 << n) - 1) {
            return u == n - 1; // use full path and reach to destination
        }
        if (u == n - 1)  return 0; // You reached this destination, So you don't Use full path
        if (dp[u][mask] != -1) return dp[u][mask];
        int ans = 0;
        for (int v : adj[u]) {
            if (mask >> v & 1) continue;
            ans += rec(v, mask | (1 << v));
            if (ans > mod) ans %= mod;
        }
        return dp[u][mask] = ans;
    };
    cout << rec(0, 1) << endl;
    return 0;
}