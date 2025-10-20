#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    vector<int> adj[n + 1];
    for (int i = 1; i <= n - 1; ++i) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> subSize(n + 1, 0), mxSize(n + 1, 0);
    function<void(int, int)> dfs = [&](int u, int p) -> void {
        subSize[u] = 1;
        for (int v : adj[u]) {
            if (v != p) {
                dfs(v, u);
                subSize[u] += subSize[v];
                mxSize[u] = max(mxSize[u], subSize[v]);
            }
        }
    };
    dfs(1, 0);

    int centriod = 0;
    for (int root = 1; root <= n; root++) {
        if (max(mxSize[root], n - subSize[root]) <= (n >> 1)) {
            centriod = root;
            break;
        }
    }
    cout << centriod << endl;
    return 0;
}
