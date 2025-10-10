#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> subTree(n + 1, 0), sum(n + 1, 0);
    function<int(int, int)> dfs = [&](int u, int p) -> int {
        subTree[u] = 1;
        int subSum = 0;
        for (int v : adj[u]) {
            if (v != p) {
                subSum += dfs(v, u);
                subTree[u] += subTree[v];
            }
        }
        subSum += subTree[u] - 1;
        return subSum;
    };
    vector<int> ans(n + 1, 0);
    ans[1] = dfs(1, 1);
    function<void(int, int)> dfs2 = [&](int u, int p) -> void {
        for (int v : adj[u]) {
            if (v != p) {
                // cout << ans[u] << " " << subTree[v] << " " << n << " " << u << "->" << v << endl;
                ans[v] = ans[u] - subTree[v] + (n - subTree[v]);
                dfs2(v, u);
            }
        }
    };
    dfs2(1, 1);

    for (int i = 1; i <= n; i++) {
        // cout << i << " : " << subTree[i] << " " << ans[i] << "\n";
        cout << ans[i] << " ";
    }
    return 0;
}
