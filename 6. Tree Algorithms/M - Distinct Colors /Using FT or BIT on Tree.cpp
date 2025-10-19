#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5+4;
int n, a[maxn], tin[maxn], tout[maxn], last[maxn], nit[maxn], ans[maxn];
vector<int> adj[maxn];

int bit[maxn];
void update(int i, int v) {
    for (; i <= n; i += i & -i) {
        bit[i] += v;
    }
}
int get(int i) {
    int res = 0;
    for (; i > 0; i -= i & -i) {
        res += bit[i];
    }
    return res;
}
int query(int l, int r) {
    return get(r) - get(l-1);
}

int t = 0;
void dfs(int u = 1, int p = 0) {
    tin[u] = ++t;
    nit[tin[u]] = u;

    for (int v: adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    tout[u] = t;
}

vector<int> idx[maxn];

int32_t main (){
    ios_base::sync_with_stdio (false);
    cin.tie (nullptr);

    cin >> n;
    vector<int> V;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        V.push_back(a[i]);
    }
    sort(V.begin(), V.end());
    for (int i = 1; i <= n; i++) {
        a[i] = lower_bound(V.begin(), V.end(), a[i]) - V.begin() + 1;
    }

    for (int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs();

    for (int i = 1; i <= n; i++) {
        idx[tout[i]].push_back(i);
    }

    for (int r = 1; r <= n; r++) {
        update(r, 1);
        int u = nit[r];
        if (last[a[u]] > 0) {
            update(last[a[u]], -1);
        }
        last[a[u]] = r;

        for (int i: idx[r]) {
            int l = tin[i];
            ans[i] = query(l, r);
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}
