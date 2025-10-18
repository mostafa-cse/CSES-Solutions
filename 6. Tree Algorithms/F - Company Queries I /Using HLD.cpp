#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 1;
int depth[MAXN], jump[MAXN], parent[MAXN], jumpSize[MAXN];
vector<int> adj[MAXN];
void dfs(int u) {
    for (int v : adj[u]) {
        depth[v] = depth[u] + 1;
        parent[v] = u;
        jump[v] = u;
        jumpSize[v] = 1;
        if (jump[u] && jump[jump[u]] && jumpSize[u] == jumpSize[jump[u]]) {
            jump[v] = jump[jump[u]];
            jumpSize[v] = jumpSize[u] * 2 + 1;
        }
        dfs(v);
    }
}
int Jump(int node, int j) {
    if (depth[node] < j) {
        return -1;
    }
    while (j > 0) {
        if (jumpSize[node] <= j) {
            j -= jumpSize[node];
            node = jump[node];
        } else {
            j -= 1;
            node= parent[node];
        }
    }
    return node;
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        adj[p].push_back(i);
    }
    dfs(1);
    while (q--) {
        int node, j;
        cin >> node >> j;
        cout << Jump(node, j) << '\n';
    }
    return 0;
}
