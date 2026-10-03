#include <bits/stdc++.h>
#define int long long
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
const int LOGN = 21;
vector<vector<int>> adj;
vector<vector<int>> up;
vector<int> lvl;
void dfs(int u, int p, int l) {
    lvl[u] = l;
    up[u][0] = p;
    for (int i = 1; i < LOGN; ++i) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, l + 1);
        }
    }
}
int getLCA(int u, int v) {
    if (lvl[u] < lvl[v]) {
        swap(u, v);
    }
    for (int i = LOGN - 1; i >= 0; --i) {
        if (lvl[u] - (1 << i) >= lvl[v]) {
            u = up[u][i];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = LOGN - 1; i >= 0; --i) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    adj.resize(n + 1);
    up.assign(n + 1, vector<int>(LOGN, 0));
    lvl.resize(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 1, 0);
    while (q--) {
        int u, v;
        cin >> u >> v;
        int lca = getLCA(u, v);
        cout << lvl[u] + lvl[v] - 2 * lvl[lca] << '\n';
    }
    return 0;
}
