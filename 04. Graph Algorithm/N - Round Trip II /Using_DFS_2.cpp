#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> color;
vector<int> parent;
int cycle_start = -1, cycle_end = -1;

bool dfs(int v) {
    color[v] = 1;
    for (int u : adj[v]) {
        if (color[u] == 0) {
            parent[u] = v;
            if (dfs(u)) return true;
        } else if (color[u] == 1) {
            cycle_end = v;
            cycle_start = u;
            return true;
        }
    }
    color[v] = 2;
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    adj.assign(n, vector<int>());
    color.assign(n, 0);
    parent.assign(n, -1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    for (int v = 0; v < n; ++v) {
        if (color[v] == 0 && dfs(v)) break;
    }

    if (cycle_start == -1) {
        cout << "IMPOSSIBLE\n";
    } else {
        vector<int> cycle;
        cycle.push_back(cycle_start);
        do {
            cycle.push_back(cycle_end);
            cycle_end = parent[cycle_end];
        } while (cycle_end != cycle_start);
        cycle.push_back(cycle_start);
        reverse(cycle.begin(), cycle.end());
        cout << cycle.size() << endl;
        for (size_t i = 0; i < cycle.size(); ++i)
            cout << cycle[i] << (i + 1 < cycle.size() ? " " : "\n");
    }
    return 0;
}
