#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, q;
    cin >> n >> q;

    vector<int> adj(n + 1), inv[n + 1];
    for (int i = 1; i <= n; i++) {
        cin >> adj[i];
        inv[adj[i]].push_back(i);
    }

    vector<int> vis(n + 1, 0), idx(n + 1, -1), ds[n + 1], pos(n + 1, -1); // vis initialized to 0 (unvisited)
    stack<int> s;
    int cnt = 0;
    function<void(int)> dfs = [&](int u) -> void {
        vis[u] = 1;
        s.push(u);
        int v = adj[u];
        if (vis[v]) { // detect cycle
            if (idx[v] == -1) {
                int t = 0;
                ++cnt;
                while (true) {
                    t = s.top();
                    s.pop();
                    idx[t] = cnt;
                    pos[t] = ds[cnt].size();
                    ds[cnt].push_back(t);
                    if (t == v) break;
                }
            } else {
                idx[u] = 0;
            }
        } else {
            dfs(v);
            if (idx[u] < 1) {
                idx[u] = 0;
            }
        }
    };
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i);
        }
    }
    vector<pair<int, int>> dis(n + 1);
    vector<int> st(n + 1, 0), en(n + 1, 0);
    int dfscnt = 0;
    function<void(int)> dfs2 = [&](int u) -> void {
        st[u] = ++dfscnt;
        for (int v : inv[u]) {
            dis[v] = {dis[u].first + 1, dis[u].second};
            dfs2(v);
        }
        en[u] = dfscnt;
    };

    for (int i = 1; i <= cnt ; i++) {
        ++dfscnt;
        for (int x : ds[i]) {
            dis[x] = {0, x};
            st[x] = dfscnt;
        }

        for (int x : ds[i]) {
            for (int y : inv[x]) {
                if (idx[y] == 0) {
                    dis[y] = {1, x};
                    dfs2(y);
                }
            }
        }
        for (int x : ds[i]) {
            en[x] = dfscnt;
        }
    }

    while (q--) {
        int u, v;
        cin >> u >> v;
        function<bool(int, int)> check = [&](int _u, int _v) -> bool {
            return st[_u] <= st[_v] and en[_v] <= en[_u];
        };
        function<int(int,int)> cal = [&](int _u, int _v) -> int {
            int size = ds[idx[_u]].size();
            return (pos[_u] + size - pos[_v]) % size;
        };
        if (u == v) {
            cout << 0 << endl;
        } else if (!check(u, v) and !check(v, u)) {
            cout << -1 << endl;
        } else if (check(u, v) and check(v, u)) {
            cout << (idx[u] == idx[v] ? cal(u, v) : -1) << endl;
        } else if (!check(v, u)) {
            cout << -1 << endl;
        } else {
            if (!check(u, v)) {
                swap(u, v);
            }
            if (dis[u].first == 0) {
                cout << dis[v].first + cal(dis[v].second, u) << endl;
            } else {
                cout << dis[v].first - dis[u].first << endl;
            }
        }
    }
    return 0;
}