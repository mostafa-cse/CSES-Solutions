#include <bits/stdc++.h>
using namespace std;

#define int long long

// Graph and SCC variables
vector<vector<int>> adj, condensed_adj;
vector<int> coins, scc_id;
vector<int> scc_coins, dp;
vector<bool> visited, on_stack;
stack<int> st;
vector<int> low, disc;
int timer_val = 0, scc_count = 0;

// Tarjan's algorithm to find SCCs
void tarjan(int u) {
    disc[u] = low[u] = ++timer_val;
    visited[u] = true;
    st.push(u);
    on_stack[u] = true;

    for (int v : adj[u]) {
        if (!visited[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (on_stack[v]) {
            low[u] = min(low[u], disc[v]);
        }
    }

    if (low[u] == disc[u]) {
        int total = 0;
        int node;
        do {
            node = st.top(); st.pop();
            on_stack[node] = false;
            scc_id[node] = scc_count;
            total += coins[node];
        } while (node != u);
        scc_coins.push_back(total);
        scc_count++;
    }
}

// DP on condensed graph
int dfs(int u) {
    if (dp[u] != -1) return dp[u];
    int best = 0;
    for (int v : condensed_adj[u]) {
        best = max(best, dfs(v));
    }
    return dp[u] = scc_coins[u] + best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    adj.resize(n);
    coins.resize(n);
    for (int i = 0; i < n; ++i) cin >> coins[i];
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
    }

    // Tarjan's SCC
    scc_id.resize(n);
    visited.assign(n, false);
    on_stack.assign(n, false);
    low.resize(n);
    disc.resize(n);
    scc_coins.clear();
    scc_count = 0;
    timer_val = 0;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) tarjan(i);
    }

    // Build condensed graph
    condensed_adj.resize(scc_count);
    vector<vector<bool>> has_edge(scc_count, vector<bool>(scc_count, false));
    for (int u = 0; u < n; ++u) {
        for (int v : adj[u]) {
            int su = scc_id[u], sv = scc_id[v];
            if (su != sv && !has_edge[su][sv]) {
                condensed_adj[su].push_back(sv);
                has_edge[su][sv] = true;
            }
        }
    }

    // DP to find max coins
    dp.assign(scc_count, -1);
    int ans = 0;
    for (int i = 0; i < scc_count; ++i) {
        ans = max(ans, dfs(i));
    }
    cout << ans << '\n';
    return 0;
}
