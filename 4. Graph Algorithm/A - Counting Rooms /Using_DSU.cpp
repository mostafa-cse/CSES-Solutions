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
    
    vector<vector<char>> g(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];
        }
    }
    
    DSU dsu(n * m);
    const int dx[] = {0, 0, 1, -1};
    const int dy[] = {1, -1, 0, 0};
    
    // Convert 2D position to 1D index
    auto getId = [&](int x, int y) -> int {
        return x * m + y;
    };
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == '.') {
                for (int d = 0; d < 4; d++) {
                    int ni = i + dx[d];
                    int nj = j + dy[d];
                    
                    if (ni >= 0 && nj >= 0 && ni < n && nj < m && g[ni][nj] == '.') {
                        dsu.unite(getId(i, j), getId(ni, nj));
                    }
                }
            }
        }
    }
    
    set<int> rooms;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == '.') {
                rooms.insert(dsu.find(getId(i, j)));
            }
        }
    }
    
    cout << rooms.size() << endl;
    return 0;
}