/*
SACK
This is Also Tree re-rooting problem.
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int M = 2e5 + 5;
vector<int> adj[M];
int ans = 0, n, k;
map<int ,int> dfs (int u, int p, int d) {
    map<int, int> parentList;
    parentList[d] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            map<int, int> childList = dfs(v, u, d + 1);
            if (childList.size() > parentList.size()) {
                swap(childList, parentList);
            }
            for (auto &[depth, cnt] : childList) {
                ans += parentList[k - depth + 2 * d] * cnt;;
            }
            for (auto &[f, s] : childList) {
                parentList[f] += s;
            }
        }
    }
    return parentList;
}
signed main() {
    cin >> n >> k;

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0, 0);
    cout << ans << endl;
    return 0;
}
