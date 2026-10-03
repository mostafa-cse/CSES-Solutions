#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> adj;
vector<vector<int>> dp;

// dp[u][0] = max matching in subtree of u when u is NOT matched
// dp[u][1] = max matching in subtree of u when u is matched
void dfs(int u, int parent) {
    dp[u][0] = 0; // u is not matched
    dp[u][1] = 0; // u is matched (will be updated)

    int best_gain = 0;

    for (int v : adj[u]) {
        if (v == parent) continue;

        dfs(v, u);

        // If u is not matched, take the best option for each child
        dp[u][0] += max(dp[v][0], dp[v][1]);

        // Calculate gain if we match u with this child v
        int gain = dp[v][0] + 1 - max(dp[v][0], dp[v][1]);
        best_gain = max(best_gain, gain);
    }

    // If u is matched with its best child
    dp[u][1] = dp[u][0] + best_gain;
}
int main() {
    cin >> n;
    adj.resize(n + 1);
    dp.resize(n + 1, vector<int>(2));

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    cout << max(dp[1][0], dp[1][1]) << endl;
    return 0;
}
