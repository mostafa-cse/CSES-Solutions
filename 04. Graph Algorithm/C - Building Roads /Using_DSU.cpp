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

    DSU ds(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        ds.unite(u, v);
    }

    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        ans.push_back(ds.find(i));
    }
    sort(ans.begin(), ans.end());
    ans.resize(unique(ans.begin(), ans.end()) - ans.begin());

    cout << ans.size() - 1 << endl;
    for (int i = 1; i < ans.size(); i++) {
        cout << ans[i - 1] << " " << ans[i] << endl;
    }
    return 0;
}