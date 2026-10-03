#include <bits/stdc++.h>
#define int long long
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
signed main() {
    int n;
    cin >> n;

    vector<int>adj[n + 1];
    for (int i = 0; i < n - 1; i ++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    function<vector<int>(int)> bfs = [&](int src) -> vector<int> {
        queue<int> q;
        vector<int> dis(n + 1, -1e12);

        q.push(src);
        dis[src] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (dis[v] < 0) {
                    dis[v] = dis[u] + 1;
                    q.push(v);
                }
            }
        }
        return dis;
    };

    vector<int> dis = bfs(1);

    int node = -1, d = -1;
    for (int i = 1; i <= n; i++) {
        if (dis[i] > d) {
            d = dis[i];
            node = i;
        }
    }
    vector<int> ans = bfs(node);
    cout << *max_element(ans.begin(), ans.end()) << endl;
    return 0;
}
