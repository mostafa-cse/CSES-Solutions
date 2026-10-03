#include <bits/stdc++.h>
#define int long long
using namespace std;
const int M = 2e5 + 1;
int dp[M][2];
vector<int> adj[M];
void modify(int node, int offer) {
    if (dp[node][0] < offer) {
        dp[node][1] = dp[node][0];
        dp[node][0] = offer;
    } else if (dp[node][1] < offer) {
        dp[node][1] = offer;
    }
}
void dfs1(int node, int parent) {
    for (int child : adj[node]) {
        if (child == parent) continue;
        dfs1(child, node);
        modify(node, dp[child][0] + 1);
    }
}
void dfs2(int node, int parent) {
    for (int child : adj[node]) {
        if (child == parent) continue;
        if (dp[node][0] == dp[child][0] + 1) {
            modify(child, dp[node][1] + 1);
        } else {
            modify(child, dp[node][0] + 1);
        }
        dfs2(child, node);
    }
}
signed main() {
    int n;
    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs1(1, 1);
    dfs2(1, 1);
    for (int i = 1; i <= n; i++) {
        cout << dp[i][0] << " ";
    }
    return 0;
}
