#include <bits/stdc++.h>
#define int long long
using namespace std;
class DSU {
    vector<int> parent, rank;

public:
    DSU(int n) : parent(n + 1), rank(n + 1, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool unite(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if (ra == rb) return false;
        if (rank[ra] < rank[rb]) swap(ra, rb);

        parent[rb] = ra;
        if (rank[ra] == rank[rb]) {
            ++rank[ra];
        }
        return true;
    }
    bool connected(int a, int b) {
        return find(a) == find(b);
    }
};

signed main() {
    int n, m;
    cin >> n >> m;

    vector<array<int, 3>> edges(m);
    for (auto &[w, u, v] : edges) {
        cin >> u >> v >> w;
    }
    sort(edges.begin(), edges.end());

    DSU ds(n);
    int ans = 0;    
    for (auto &[w, u, v] : edges) {
        if (ds.unite(u, v)) {
            ans += w;
        }
    }
    
    set<int> cities;
    for (int i = 1; i <= n; i++) {
        cities.insert(ds.find(i));
        if (cities.size() == 2) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }
    cout << ans;
    return 0;
}