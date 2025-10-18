#include <bits/stdc++.h>
#define int long long
using namespace std;
const int M = 2e5 + 5;
vector<int> pre(1), adj[M];
int depth[M], Size[M], parent[M], son[M], tp[M], ans[M];
void dfs1(int u, int p) {
    pre.push_back(u);
    depth[u] = depth[p] + 1;
    Size[u] = 1;
    parent[u] = p;
    for (int v : adj[u]) {
        if (p != v) {
            dfs1(v, u);
            Size[u] += Size[v];
            if (Size[v] > Size[son[u]]) {
                son[u] = v;
            }
        }
    }
}
void dfs2(int u, int tope) {
    tp[u] = tope;
    if (son[u] == 0) {
        return;
    }
    dfs2(son[u], tope);
    for (int v : adj[u]) {
        if (v == parent[u] or v == son[u]) {
            continue;
        }
        dfs2(v, v);
    }
}
int lca(int a, int b) {
    while (tp[a] != tp[b]) {
        if (depth[tp[a]] < depth[tp[b]]) {
            swap(a, b);
        }
        a = parent[tp[a]];
    }

    int res;
    if (depth[a] < depth[b]) {
        res = a;
    } else {
        res = b;
    }
    return res;
}
int dfs3 (int u, int p) {
    int sum = 0;
    for (int v : adj[u]) {
        if (v != p) {
            dfs3(v, u);
            ans[u] += ans[v];
        }
    }
    return ans[u];
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, q;
    cin >> n >> q;

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    adj[0].push_back(1);
    dfs1(1, 0);
    dfs2(1, 0);

    while (q--) {
        int a, b;
        cin >> a >> b;

        ans[a]++;
        ans[b]++;

        int lcaVal = lca(a, b);
        ans[lcaVal]--;
        ans[parent[lcaVal]]--;
    }
    dfs3(1, 0);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
