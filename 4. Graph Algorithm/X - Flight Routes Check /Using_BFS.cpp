#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int N = 100001;

void bfs(const vector<vector<int>>& adj, vector<bool>& visited, int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1), rev_adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        rev_adj[b].push_back(a);
    }

    vector<bool> visited(n + 1, false);
    bfs(adj, visited, 1);
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            cout << "NO\n1 " << i << '\n';
            return 0;
        }
    }

    fill(visited.begin(), visited.end(), false);
    bfs(rev_adj, visited, 1);
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            cout << "NO\n" << i << " 1\n";
            return 0;
        }
    }

    cout << "YES\n";
    return 0;
}
