#include <bits/stdc++.h>
#define int long long
using namespace std;

struct Tree {
    int node;
    vector<vector<int>> adj;

    Tree(int n) : node(n + 1), adj(n + 1) {}

    pair<int, vector<int>> BFS(int src) {
        vector<int> dis(node + 1, -1);
        queue<int> q;
        int mx = 0, TargetNode = src;
        q.push(src);
        dis[src] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                if (dis[v] < 0) {
                    dis[v] = dis[u] + 1;
                    q.push(v);
                    if (dis[v] > mx) {
                        mx = dis[v];
                        TargetNode = v;
                    }
                }
            }
        }
        // Node, level vector
        return {TargetNode, dis};
    }
};
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    Tree a(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        a.adj[u].push_back(v);
        a.adj[v].push_back(u);
    }
    pair<int, vector<int>> determine_node = a.BFS(1);
    pair<int, vector<int>> start = a.BFS(determine_node.first);
    pair<int, vector<int>> end = a.BFS(start.first);
    for (int i = 1; i <= n; i++) {
        cout << max(start.second[i], end.second[i]) << " ";
    }
    return 0;
}
