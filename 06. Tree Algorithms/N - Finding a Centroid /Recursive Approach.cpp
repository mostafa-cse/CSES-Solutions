#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
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

    function<int(int, int, int)> centriod = [&](int u, int p, int above) ->int {
        if (max(above, mxSize[u]) <= n / 2) {
            return u;
        }
        for (int v : adj[u]) {
            if (v != p) {
                int res = centriod(v, u, above + subSize[u] - subSize[v]);
                if (res) {
                    return res;
                }
            }
        }
        return 0;
    };
    cout << centriod(1, 0, 0) << endl;
    return 0;
}
