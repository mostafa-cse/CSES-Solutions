#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
const int Mod = 1e9 + 7;
struct DSU {
    vector<int> parent;
    vector<int> sz;
    int num_components;

    DSU(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
        sz.assign(n + 1, 1);
        num_components = n;
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i != root_j) {
            if (sz[root_i] < sz[root_j])
                swap(root_i, root_j);

            parent[root_j] = root_i;
            sz[root_i] += sz[root_j];
            num_components--;
            return true;
        }
        return false;
    }

    bool same(int i, int j) {
        return find(i) == find(j);
    }

    int size(int i) {
        return sz[find(i)];
    }
};
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, m;
    cin >> n >> m;

    int ans = 1;
    DSU ds(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        if (ds.unite(u, v)) {
            continue;
        }
        ans = ans * 2 % Mod;
    }
    cout << ans << endl;
    return 0;
}

