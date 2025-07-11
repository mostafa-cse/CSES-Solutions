#include <bits/stdc++.h>
#define int long long
using namespace std;
class DSU {
    vector<int> parent, sz;
public:
    DSU(int n) : parent(n + 1), sz(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    int unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return 0;

        if (sz[ra] < sz[rb]) {
            swap(ra, rb);
        }
        parent[rb] = ra;
        sz[ra] += sz[rb];
        return sz[ra];
    }
    bool connected(int a, int b) {
        return find(a) == find(b);
    }
    int size(int x) {
        return sz[find(x)];
    }
};

signed main() {
    int n, m;
    cin >> n >> m;

    int ans = n, mx = 0;
    DSU ds(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (ds.unite(u, v)) {
            ans--;
            mx = max({ds.size(u), ds.size(v), mx});
        }
        cout << ans << " " << mx << endl;
    }
    return 0;
}