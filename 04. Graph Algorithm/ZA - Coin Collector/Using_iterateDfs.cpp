#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // weights[i] = weight of node i
    vector<int> weights(n);
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }

    // adj[i] = nodes reachable from i
    // revAdj[i] = nodes that can reach i
    vector<vector<int>> adj(n), revAdj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        revAdj[v].push_back(u);
    }

    // 1) First DFS pass: build finish order
    vector<char> visited1(n, 0);
    vector<int> finishOrder;
    stack<int> dfsStack;

    for (int i = 0; i < n; i++) {
        if (!visited1[i]) {
            dfsStack.push(i);
            while (!dfsStack.empty()) {
                int u = dfsStack.top();
                if (!visited1[u]) {
                    visited1[u] = 1;                     // mark “in progress”
                    for (int v : adj[u]) {
                        if (!visited1[v]) dfsStack.push(v);
                    }
                } else {
                    dfsStack.pop();
                    if (visited1[u] == 1) {
                        visited1[u] = 2;                  // mark “finished”
                        finishOrder.push_back(u);
                    }
                }
            }
        }
    }

    // 2) Second DFS pass on reversed graph: assign components
    vector<int> compId(n, -1);
    int numComps = 0;
    for (int idx = n - 1; idx >= 0; idx--) {
        int node = finishOrder[idx];
        if (compId[node] == -1) {
            dfsStack.push(node);
            while (!dfsStack.empty()) {
                int u = dfsStack.top();
                dfsStack.pop();
                if (compId[u] == -1) {
                    compId[u] = numComps;
                    for (int v : revAdj[u]) {
                        if (compId[v] == -1) dfsStack.push(v);
                    }
                }
            }
            numComps++;
        }
    }

    // 3) Compute total weight of each component
    vector<long long> compWeight(numComps, 0);
    for (int i = 0; i < n; i++) {
        compWeight[compId[i]] += weights[i];
    }

    // 4) Build component graph (DAG)
    vector<set<int>> compGraph(numComps);
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            int cu = compId[u], cv = compId[v];
            if (cu != cv) compGraph[cu].insert(cv);
        }
    }

    // 5) DP on DAG to find max path-sum from each component
    vector<long long> dp(numComps, 0);
    for (int c = numComps - 1; c >= 0; c--) {
        long long bestNext = 0;
        for (int nxt : compGraph[c]) {
            bestNext = max(bestNext, dp[nxt]);
        }
        dp[c] = compWeight[c] + bestNext;
    }

    // 6) Answer = highest dp value
    long long answer = 0;
    for (long long x : dp) {
        answer = max(answer, x);
    }

    cout << answer << "\n";
    return 0;
}
