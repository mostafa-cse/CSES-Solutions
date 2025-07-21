#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

using ll = long long;

// Kosaraju's algorithm for SCCs
void dfs1(int u, const vector<vector<int>> &rev_adj, vector<bool> &visited, vector<int> &order)
{
    visited[u] = true;
    for (int v : rev_adj[u])
    {
        if (!visited[v])
            dfs1(v, rev_adj, visited, order);
    }
    order.push_back(u);
}

void dfs2(int u, const vector<vector<int>> &adj, vector<int> &scc_id, int id, vector<vector<int>> &sccs)
{
    scc_id[u] = id;
    sccs[id].push_back(u);
    for (int v : adj[u])
    {
        if (scc_id[v] == -1)
            dfs2(v, adj, scc_id, id, sccs);
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<ll> coins(n);
    for (int i = 0; i < n; ++i)
        cin >> coins[i];

    vector<vector<int>> adj(n), rev_adj(n);
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        adj[a].push_back(b);
        rev_adj[b].push_back(a);
    }

    // 1st pass: order vertices by finish time in reverse graph
    vector<bool> visited(n, false);
    vector<int> order;
    for (int i = 0; i < n; ++i)
    {
        if (!visited[i])
            dfs1(i, rev_adj, visited, order);
    }

    // 2nd pass: assign SCC ids
    vector<int> scc_id(n, -1);
    vector<vector<int>> sccs;
    int scc_count = 0;
    for (int i = n - 1; i >= 0; --i)
    {
        int u = order[i];
        if (scc_id[u] == -1)
        {
            sccs.push_back({});
            dfs2(u, adj, scc_id, scc_count++, sccs);
        }
    }

    // Build condensed graph (DAG of SCCs)
    vector<ll> scc_coins(scc_count, 0);
    vector<set<int>> dag(scc_count);
    for (int i = 0; i < scc_count; ++i)
    {
        for (int u : sccs[i])
        {
            scc_coins[i] += coins[u];
            for (int v : adj[u])
            {
                if (scc_id[u] != scc_id[v])
                    dag[scc_id[u]].insert(scc_id[v]);
            }
        }
    }

    // DP on DAG to find max coins
    vector<ll> dp(scc_count, 0);
    ll ans = 0;
    for (int i = scc_count - 1; i >= 0; --i)
    {
        dp[i] = scc_coins[i];
        for (int v : dag[i])
        {
            dp[i] = max(dp[i], scc_coins[i] + dp[v]);
        }
        ans = max(ans, dp[i]);
    }

    cout << ans << '\n';
    return 0;
}
