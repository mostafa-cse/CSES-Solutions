#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
vector<int> adj[N + 1];
vector<int> c(N), freq(N), res(N);
int IN[N], OUT[N], sz[N], bg[N];
int timer = 0, ans = 0;
vector<int> euler;
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
void dfs0(int u, int p) {
    euler.emplace_back(u);
    IN[u] = timer++;
    sz[u] = 1;
    for (auto v : adj[u]) {
        if (v == p) continue;
        dfs0(v, u);
        sz[u] += sz[v];
        if (bg[u] == -1 || sz[v] > sz[bg[u]]) {
            bg[u] = v;
        }
    }
    OUT[u] = timer - 1;
}
void dfs(int u, int p, bool keep) {
    for (auto v : adj[u]) {
        if (v == p || v == bg[u]) continue;
        dfs(v, u, false);
    }
    if (bg[u] != -1) dfs(bg[u], u, true);
    for (auto x : adj[u]) {
        if (x != p && x != bg[u]) {
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
void solve() {
}
signed main() {
    int n; cin >> n;
    memset(bg, -1, sizeof bg);
    vector<pair<int, int>> comp(n);
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        comp[i - 1] = {c[i], i};
    }
    sort(comp.begin(), comp.end());
    int x = 0;
    c[comp[0].second] = x;
    for (int i = 1; i < n; i++) {
        if (comp[i].first != comp[i - 1].first) x++;
        c[comp[i].second] = x;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    timer = 0;
    dfs0(1, -1);
    dfs(1, -1, false);
    for (int i = 1; i <= n; i++) cout << res[i] << ' ';
    cout << '\n';
    return 0;
}
