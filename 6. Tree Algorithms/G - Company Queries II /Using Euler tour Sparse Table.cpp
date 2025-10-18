#include <bits/stdc++.h>
// #define int long long
using namespace std;
const int M = 4e5;
vector<int> adj[M + 1];
vector<pair<int, int>> tour;
int depth[M + 1];
int pos[M + 1];
int st[M + 1][25];
void dfs(int u) {
    tour.emplace_back(depth[u], u);
    for (int v : adj[u]) {
        depth[v] = depth[u] + 1;
        dfs(v);
        tour.emplace_back(depth[u], u);
    }
}
template<class T> struct RMQ {
    vector<vector<T>> jump;
    RMQ(const vector<T> &V) : jump(1, V) {
        for (int pw = 1, k = 1; (1 << k) <= V.size(); ++k) {
            jump.emplace_back(V.size() - (1 << k) + 1);
            for (int j = 0; j + (1 << k) <= V.size(); ++j) {
                jump[k][j] = min(jump[k - 1][j], jump[k - 1][j + (1 << (k - 1))]);
            }
        }
    }
    T query(int a, int b) {
        if (a > b) swap(a, b);
        int dep = 31 - __builtin_clz(b - a + 1);
        return min(jump[dep][a], jump[dep][b - (1 << dep) + 1]);
    }
};
signed main() {
    int n, q;
    cin >> n >> q;

    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        adj[p].push_back(i);
    }

    // flatten this tree
    tour.emplace_back(0, 1);
    dfs(1);
    memset(pos, -1, sizeof pos);

    for (int i = 1; i < tour.size(); i++) {
        int node = tour[i].second;
        if (pos[node] == -1) {
            pos[node] = i;
        }
    }

    RMQ<pair<int, int>> st(tour);
    while (q--) {
        int a, b;
        cin >> a >> b;

        a = pos[a];
        b = pos[b];

        cout << st.query(a, b).second << endl;
    }
    return 0;
}
