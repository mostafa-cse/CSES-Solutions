#include <bits/stdc++.h>
using namespace std;
#define int long long

bool dfs(int u, int dest, vector<vector<int>> &adj, vector<int> &path, int threshhold, vector<int> &vis, int n) {
    vis[u] = 1;
    if (u == dest) {
        path.push_back(u);
        return true;
    }
    for (int v = 1; v <= n; v++) {
        if (vis[v] == 0 and adj[u][v] >= threshhold) {
            if (dfs(v, dest, adj, path, threshhold, vis, n)) {
                path.push_back(u);
                return true;
            }
        }
    }
    return false;
}
void dfs2(int u, vector<vector<int>> &adj, vector<int> &left, vector<int> &visited, int n) {
    visited[u] = 1;
    left.push_back(u);
    for (int v = 1; v <= n; v++) {
        if (visited[v] == 0 and adj[u][v] >= 1) {
            dfs2(v, adj, left, visited, n);
        }
    }
}
int32_t main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1, vector<int>(n + 1, -1));
    vector<vector<int>> og(n + 1, vector<int>(n + 1, -1));
    int sum = 0;
    for (int i = 0; i < m; i++) {
        int x, y;
        const int w = 1;
        cin >> x >> y;
        og[x][y] = w;
        og[y][x] = w;
        if (adj[x][y] == -1) {
            adj[x][y] = 0;
            adj[y][x] = 0;
        }
        adj[x][y] += w;
        adj[y][x] += w;
        sum += w;
    }

    int ans = 0;
    while (sum > 0) {
        vector<int> path;
        vector<int> vis(n + 1, 0);

        bool f = dfs(1, n, adj, path, sum, vis, n);
        
        if (f == true) {
            reverse(path.begin(), path.end());
            int k = path.size();
            int minedgewt = INT_MAX;
            for (int i = 0; i < k - 1; i++) {
                minedgewt = min(minedgewt, adj[path[i]][path[i + 1]]);
            }
            ans += minedgewt;
            for (int i = 0; i < k - 1; i++) {
                adj[path[i]][path[i + 1]] -= minedgewt;
                adj[path[i + 1]][path[i]] += minedgewt;
            }
        } else {
            sum /= 2;
        }
    }
    cout << ans << "\n";

    // Minimum Vertex Cover	When you need the minimum cut/vertex cover edges
    vector<int> left;
    vector<int> visited(n + 1, 0);
    dfs2(1, adj, left, visited, n);

    unordered_set<int> st;
    
    for (auto &i : left) {
        st.insert(i);
    }
    for (auto &i : left) {
        for (int j = 1; j <= n; j++) {
            if (((og[i][j] == 1) && (adj[i][j] == 0)) && (st.find(j) == st.end())) {
                cout << i << " " << j << "\n";
            }
        }
    }
    return 0;
}