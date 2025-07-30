#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MOD 1000000007
ll dp[1 << 21][22];
vector<int> adj[22];
int n;
ll dfs(int mask, int node) {
    mask = mask ^ (1 << (node));
    if ((mask == 0) or (node == (n - 1)))  return mask == 0 and node == n - 1;
    if (dp[mask][node] != -1)  return dp[mask][node];
    int res = 0;
    for (auto &i : adj[node]) {
        if ((1ll << (i)) & mask) {
            res += dfs(mask, i);
            if (res >= MOD) {
                res %= MOD;
            }
        }
    }
    return (dp[mask][node] = res);
}
int main() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        adj[x].push_back(y);
    }
    memset(dp, -1, sizeof(dp));
    cout << dfs((1 << n) - 1, 0);
    return 0;
}