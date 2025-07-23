#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;

    vector<int> coin(n);
    for (int &i : coin) {
        cin >> i;
    }

    vector<int> adj[n];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u -= 1, v -= 1;
        adj[u].push_back(v);
    }

    vector<int> disc(n, 0), low(n, 0);
    vector<bool> vis(n, false), onstack(n, false);
    vector<int> SCC(n), scc_coins;
    stack<int> st;
    int timer = 0, id = 0;
    function<void(int)> tarjans = [&](int u) -> void {
        disc[u] = low[u] = ++timer;
        vis[u] = 1;
        st.push(u);
        onstack[u] = 1;
        for (int v : adj[u]) {
            if (vis[v] == 0) {
                tarjans(v);
                low[u] = min(low[u], low[v]);
            } else if (onstack[v] == 1) {
                low[u] = min(low[u], disc[v]);
            }
        }

        if (disc[u] == low[u]) {
            int total = 0;
            int node;
            do {    
                node = st.top();
                st.pop();
                onstack[node] = false;
                SCC[node] = id;
                total += coin[node];
            } while (node != u);
            
            scc_coins.push_back(total);
            id++;
        }
    };

    for (int i = 0; i < n; ++i) {
        if (vis[i] == 0)  {
            tarjans(i);
        }
    }

    set<int> condence_adj[id];
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            int id_u = SCC[u];
            int id_v = SCC[v];
            
            if (id_u != id_v) {
                condence_adj[id_u].insert(id_v);
            }
        }
    }
    
    recursive_sol:
    {
        vector<int> dp(id, -1);
        function<int(int)> dfs = [&](int u) -> int {
            if (dp[u] != -1) {
                return dp[u];
            }

            int mx = 0;
            dp[u] = scc_coins[u];
            for (int v : condence_adj[u]) {
                mx = max(mx, dfs(v));
            }
            dp[u] += mx;
            return dp[u];
        };
        
        int ans = 0;
        for (int i = 0; i < id; ++i) {
            ans = max(ans, dfs(i));
        }
        cout << ans << endl;
    }    

    iterative_sol :{ // Not Working
                vector<int> dp(id, 0);
        vector<int> indegree(id, 0);
        queue<int> q;

        // Calculate indegree for each SCC
        for (int u = 0; u < id; ++u) {
            for (int v : condence_adj[u]) {
                indegree[v]++;
            }
        }

        // Push all SCCs with indegree 0 into the queue
        for (int u = 0; u < id; ++u) {
            if (indegree[u] == 0) {
                q.push(u);
                dp[u] = scc_coins[u];
            }
        }

        int ans = 0;

        // Perform topological sort and calculate maximum coins
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            ans = max(ans, dp[u]);

            for (int v : condence_adj[u]) {
                dp[v] = max(dp[v], dp[u] + scc_coins[v]);
                indegree[v]--;
                if (indegree[v] == 0) {
                    q.push(v);
                }
            }
        }

        cout << ans << endl;
    }
    return 0;
}