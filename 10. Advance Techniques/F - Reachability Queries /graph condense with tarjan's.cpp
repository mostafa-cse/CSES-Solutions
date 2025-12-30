#include <bits/stdc++.h>
#define int long long
using namespace std;
const int M = 5e4 + 5;
bitset<M> res[M];
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, m, q;
    cin >> n >> m >> q;

    vector<int> g[n + 1];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }

    vector<int> low(n + 1, 0), num(n + 1, 0);
    vector<int> vt;
    int cnt = 0;
    int discover = 0;
    vector<int> com(M, 0);
    function<void(int)> dfs = [&](int from) -> void{
        low[from] = num[from] = ++discover;
        vt.push_back(from);

        for (int to : g[from]) {
            if (num[to]) {
                low[from] = min(low[from], num[to]);
            } else {
                dfs(to);
                low[from] = min(low[from], low[to]);
            }
        }

        if (low[from] == num[from]) {
            cnt++;
            int to;

            do {
                to = vt.back();
                vt.pop_back();
                com[to] = cnt;
                low[to] = num[to] = 1e9;
            } while (to != from);
        }
    };
    vector<int> id(n + 1, 0);
    for (int  i = 1; i <= n; i++) {
        id[i] = i;
        res[i][i] = 1;
        if (num[i] == 0) {
            dfs(i);
        }
    }
    sort(id.begin() + 1, id.end(), [&](int x, int y) {
        return com[x] > com[y];
    });

    for (int i = 1; i <= n; i++) {
        int u = id[i];
        for (int v : g[u]) {
            res[com[v]] |= res[com[u]];
        }
    }

    while (q--) {
        int u, v;
        cin >> u >> v;

        if (res[com[v]][com[u]]) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}

