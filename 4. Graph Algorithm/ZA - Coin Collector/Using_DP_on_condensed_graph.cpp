#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj, condensed_adj;
vector<int> coins, scc_id, scc_coins;
vector<bool> visited, on_stack;
stack<int> st;
vector<int> low, disc;
int timer_val = 0, scc_count = 0;

// Tarjan's algorithm to find strongly connected components
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
    
    // If u is a root node, pop the stack and create an SCC
    if (low[u] == disc[u]) {
        int total_coins = 0;
        int node;
        do {
            node = st.top();
            st.pop();
            on_stack[node] = false;
            scc_id[node] = scc_count;
            total_coins += coins[node];
        } while (node != u);
        
        scc_coins.push_back(total_coins);
        scc_count++;
    }
}

// DFS with memoization on the condensed graph
vector<int> dp;
vector<bool> computed;

int solve(int u) {
    if (computed[u]) {
        return dp[u];
    }
    
    computed[u] = true;
    dp[u] = scc_coins[u];
    
    int max_from_neighbors = 0;
    for (int v : condensed_adj[u]) {
        max_from_neighbors = max(max_from_neighbors, solve(v));
    }
    
    dp[u] += max_from_neighbors;
    return dp[u];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    // Initialize data structures
    adj.resize(n);
    coins.resize(n);
    scc_id.resize(n);
    visited.resize(n, false);
    on_stack.resize(n, false);
    low.resize(n);
    disc.resize(n);
    
    // Read coin values
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }
    
    // Read edges
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; // Convert to 0-indexed
        adj[u].push_back(v);
    }
    
    // Find strongly connected components using Tarjan's algorithm
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            tarjan(i);
        }
    }
    
    // Build condensed graph (DAG of SCCs)
    condensed_adj.resize(scc_count);
    set<pair<int, int>> edges; // To avoid duplicate edges
    
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            int scc_u = scc_id[u];
            int scc_v = scc_id[v];
            if (scc_u != scc_v && edges.find({scc_u, scc_v}) == edges.end()) {
                condensed_adj[scc_u].push_back(scc_v);
                edges.insert({scc_u, scc_v});
            }
        }
    }
    
    // Solve using DP on the condensed graph
    dp.resize(scc_count);
    computed.resize(scc_count, false);
    
    int max_coins = 0;
    for (int i = 0; i < scc_count; i++) {
        max_coins = max(max_coins, solve(i));
    }
    
    cout << max_coins << '\n';
    
    return 0;
}
