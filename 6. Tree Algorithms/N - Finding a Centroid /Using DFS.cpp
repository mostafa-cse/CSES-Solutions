#include <bits/stdc++.h>
#define int long long
using namespace std;
const int M = 3e5;
vector<vector<int>> adj(M);
vector<int> subTree(M, 0), parent(M, 0);
signed main() {
    int n;
    cin >> n;

    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    function<void(int, int)> dfsSz = [&](int u, int p) -> void {
        subTree[u] = 1;
        for (int v : adj[u]) {
            if (v != p) {
                parent[v] = u;
                dfsSz(v, u);
                subTree[u] += subTree[v];
            }
        }
    };
    dfsSz(1, 0);

    for (int i = 1; i <= n; i++) {
        int letRoot = i;
        bool ok = true;
        int store = 1;
        for (int child : adj[letRoot]) {
            if (parent[letRoot] != child) {
                ok &= (subTree[child] <= (n >> 1));
                store += subTree[child];
            }
        }
        store = n - store;
        ok &= (store <= (n >> 1));
        if (ok) {
            return cout << letRoot << endl, 0;
        }
    }
    return 0;
}
