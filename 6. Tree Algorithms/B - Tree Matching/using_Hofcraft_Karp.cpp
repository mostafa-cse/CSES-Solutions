#include <bits/stdc++.h>
#define int long long
using namespace std;
bool dfs(int v, vector<vector<int>>& g, vector<int>& mt, vector<bool>& used) {
    for (int to : g[v]) {
        if (used[to]) continue;
        used[to] = true;

        if (mt[to] == -1 || dfs(mt[to], g, mt, used)) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

int max_matching(int n, int m, vector<vector<int>>& g) {
    vector<int> mt(m, -1);
    int result = 0;

    for (int v = 0; v < n; ++v) {
        vector<bool> used(m, false);
        if (dfs(v, g, mt, used))
            result++;
    }
    return result;
}

signed main() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u -= 1, v -= 1;
        adj[u].push_back(v);
    }
    int ans = max_matching(n, n, adj);
    cout << ans << endl;
    return 0;
}
