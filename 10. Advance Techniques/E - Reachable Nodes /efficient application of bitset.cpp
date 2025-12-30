#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
const int M = 5e4 + 7;
bitset<M> dp[M];
vector<int> vis(M, 0);
vector<int> g[M];
void dfs(int from) {
    vis[from] = 1;
    dp[from].set(from);
    for (int to : g[from]) {
        if (vis[to] == 0) {
            dfs(to);
        }
        dp[from] |= dp[to];
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) {
            dfs(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << dp[i].count() << " ";
    }
    return 0;
}
