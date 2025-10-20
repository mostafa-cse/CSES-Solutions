#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
vector<int> adj[N + 1];
vector<int> c(N), freq(N), res(N);
int IN[N], OUT[N], sz[N], heavy[N];
int timer = 0, ans = 0;
vector<int> euler;
void dfs(int u, int p) {
    euler.emplace_back(u);
    IN[u] = timer++;
    sz[u] = 1;
    for (auto v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
        if (heavy[u] == -1 || sz[v] > sz[heavy[u]]) {
            heavy[u] = v;
        }
    }
    OUT[u] = timer - 1;
}
void add(int u) {
    int col = c[u];
    freq[col]++;
    ans += (freq[col] == 1);
}
void erase(int u) {
    int col = c[u];
    freq[col]--;
    ans -= (freq[col] == 0);
}
void dsu(int u, int p, bool keep) {
    for (auto v : adj[u]) {
        if (v == p || v == heavy[u]) continue;
        dsu(v, u, false);
    }
    if (heavy[u] != -1) dsu(heavy[u], u, true);
    for (auto x : adj[u]) {
        if (x != p && x != heavy[u]) {
            for (int i = IN[x]; i <= OUT[x]; i++) {
                add(euler[i]);
            }
        }
    }
    add(u);
    res[u] = ans;
    if (!keep) {
        for (int i = IN[u]; i <= OUT[u]; i++) {
            erase(euler[i]);
        }
    }
}
signed main() {
    int n;
    cin >> n;

    memset(heavy, -1, sizeof heavy);
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    vector<int> a = c;

    sort(a.begin(), a.end());
    for (int i = 1; i < n; i++) {
        c[i] = lower_bound(a.begin(), a.end(), c[i]) - a.begin();
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    timer = 0;
    dfs(1, -1);
    dsu(1, -1, false);
    for (int i = 1; i <= n; i++) cout << res[i] << ' ';
    cout << '\n';
    return 0;
}
