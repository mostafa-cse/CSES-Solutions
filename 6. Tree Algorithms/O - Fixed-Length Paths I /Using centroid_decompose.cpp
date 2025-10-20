#include <bits/stdc++.h>
#define int long long
using namespace std;
const int M = 2e5 + 5;
vector<int> adj[M];
int subSize[M], dist[M];
bool deleted[M];
int ans = 0, k, mxD = 0, n;

void dfs_sizes(int u, int p) {
    subSize[u] = 1;
    for (int v : adj[u]) {
        if (!deleted[v] and v != p) {
            dfs_sizes(v, u);
            subSize[u] += subSize[v];
        }
    }
}
int find_Centroid(int u,int p, int treeSz) {
    for (int v : adj[u]) {
        if (!deleted[v] and p != v and subSize[v] > treeSz) {
            return find_Centroid(v, u, treeSz);
        }
    }
    return u;
}
// calculate = 1 or add = 0
void dfs(int u, int p, int d, bool isCalculate) {
    if (d > k) return;
    if (isCalculate) {
        ans += dist[k - d];
    } else {
        dist[d]++;
    }
    mxD = max(mxD, d);
    for (int v : adj[u]) {
        if (!deleted[v] and v != p) {
            dfs(v, u, d + 1, isCalculate);
        }
    }
}
void centroid_decompose(int root) {
    dfs_sizes(root, -1);
    int centroid = find_Centroid(root, -1, subSize[root] >> 1);
    deleted[centroid] = 1;
    dist[0] = 1;
    mxD = 0; // maximum depth
    for (int child : adj[centroid]) {
        if (!deleted[child]) {
            dfs(child, centroid, 1, true); // calculate
            dfs(child, centroid, 1, false); // add
        }
    }
    fill(dist, dist + mxD + 1, 0);
    for (int child : adj[centroid]) {
        if (!deleted[child]) {
            centroid_decompose(child);
        }
    }
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    cin >> n >> k;

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    centroid_decompose(1);
    cout << ans;
    return 0;
}
