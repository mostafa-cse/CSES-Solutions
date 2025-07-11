#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n + 1);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    vector<bool> vis(n + 1, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 1});
    int ans = 0, cnt = 0;
    while (!pq.empty())
    {
        auto [w, u] = pq.top();
        pq.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        ans += w;
        cnt++;
        for (auto [v, cost] : g[u])
        {
            if (!vis[v])
                pq.push({cost, v});
        }
    }
    if (cnt != n)
        cout << "IMPOSSIBLE\n";
    else
        cout << ans << '\n';
    return 0;
}