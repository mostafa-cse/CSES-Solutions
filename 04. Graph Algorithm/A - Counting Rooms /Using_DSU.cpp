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
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
signed main() {
    int n, m;
    cin >> n >> m;

    vector<vector<char>> g(n, vector<char>(m));
    for (auto &sub : g) {
        for (char &c : sub) {
            cin >> c;
        }
    }
    DSU ds(n * m);
    function<int(int, int)> get_num = [&](int ri, int ci) -> int {
        return ri * m + ci;
    };

    vector<int> wallPoint;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == '.') {
                wallPoint.push_back(get_num(i, j));
            }
            for (int d = 0; d < 4 and g[i][j] == '.'; d++) {
                int ni = i + dx[d];
                int nj = j + dy[d];

                if (ni >= 0 and nj >= 0 and ni < n and nj < m and g[ni][nj] == '.') {
                    int p1 = get_num(i, j);
                    int p2 = get_num(ni, nj);
                    ds.unite(p1, p2);
                }
            }
        }
    }

    set<int> par;
    for (int i : wallPoint) {
        par.insert(ds.find(i));
    }
    cout << par.size();
    return 0;
}