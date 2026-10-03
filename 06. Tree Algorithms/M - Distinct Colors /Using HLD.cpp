#include <bits/stdc++.h>
#define SZ(x) static_cast<int>((x).size())
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> color(n);
    for (int &c : color) {
        cin >> c;
    }

    vector<int> sortedColors = color;
    sort(sortedColors.begin(), sortedColors.end());
    sortedColors.erase(unique(sortedColors.begin(), sortedColors.end()), sortedColors.end());

    for (int &c : color) {
        c = lower_bound(sortedColors.begin(), sortedColors.end(), c) - sortedColors.begin();
    }
    const int maxColor = SZ(sortedColors);

    vector<vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> tin(n), tout(n);
    vector<int> flatColor(n);
    vector<int> heavyParent(n, -1);

    int timer = 0;
    function<void(int, int)> dfs = [&](int u, int p) -> void {
        tin[u] = timer;
        flatColor[timer] = color[u];
        ++timer;

        int heavySize = 0, heavyChild = -1;
        for (int v : adj[u]) if (v != p) {
            int before = timer;
            dfs(v, u);
            int subSize = timer - before;
            if (subSize > heavySize) {
                heavySize = subSize;
                heavyChild = v;
            }
        }
        if (heavyChild != -1) {
            heavyParent[heavyChild] = u;
        }
        tout[u] = timer;
    };
    dfs(0, -1);

    vector<int> answer(n, 0);
    vector<char> seen(maxColor, 0);
    int distinctCnt = 0;

    auto addColor = [&](int c) {
        if (!seen[c]) { seen[c] = 1; ++distinctCnt; }
    };

    for (int leaf = 0; leaf < n; ++leaf) {
        if (tin[leaf] + 1 < tout[leaf]) {
            continue;
        }

        int u = leaf;
        distinctCnt = 0;
        addColor(color[u]);
        answer[u] = distinctCnt;

        while (heavyParent[u] != -1) {
            int p = heavyParent[u];
            for (int i = tin[p]; i < tin[u]; ++i) {
                addColor(flatColor[i]);
            }
            for (int i = tout[u]; i < tout[p]; ++i) {
                addColor(flatColor[i]);
            }
            u = p;
            answer[u] = distinctCnt;
        }
        for (int i = tin[u]; i < tout[u]; ++i) {
            seen[flatColor[i]] = 0;
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << answer[i] << (i + 1 == n ? '\n' : ' ');
    }
    return 0;
}
