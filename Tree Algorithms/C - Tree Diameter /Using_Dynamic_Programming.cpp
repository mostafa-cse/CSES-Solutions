#include <bits/stdc++.h>
#define int long long
using namespace std;
int ans = 0;
void dfs(int u, int par, vector<vector<int>> &a, vector<int> &dp) {
    int mxDis = 0;
    for (int v : a[u]) {
        if (v != par) {
            dfs(v, u, a, dp);
            ans = max(ans, mxDis + dp[v] + 1);
            mxDis = max(mxDis, dp[v] + 1);
        }
    }
    dp[u] = mxDis;
}
signed main() {
    int n;
    cin >> n;

    vector<vector<int>> a(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    vector<int> dp(n + 1, 0);
    dfs(1, -1, a, dp);
    cout << ans << endl;
    return 0;
}
