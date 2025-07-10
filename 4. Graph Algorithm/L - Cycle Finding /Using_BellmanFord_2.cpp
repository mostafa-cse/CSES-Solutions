#include <bits/stdc++.h>
#define int long long
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n + 1);
    vector<vector<int>> edges;
    for (int i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;
        adj[x].push_back({y, w});
        edges.push_back({x, y, w});
    }
    vector<int> dist(n + 1, 3);
    dist[1] = 0;
    for (int i = 0; i < n; i++)
    {
        for (auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            dist[v] = min(dist[v], dist[u] + w);
        }
    }
    bool f = true;
    vector<int> par(n + 1, -1);
    for (int i = 0; i < n; i++)
    {
        for (auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];

            int z = dist[v];
            dist[v] = min(dist[v], dist[u] + w);
            if (dist[v] != z)
            {
                f = false;
                par[v] = u;
            }
        }
    }
    if (f)
    {
        cout << "NO\n";
    }
    else
    {
        int x = 0;
        for (int i = 1; i <= n; i++)
        {
            if (par[i] != -1)
            {
                x = i;
                break;
            }
        }
        
        vector<int> cycle;
        unordered_set<int> st;
        while (st.find(x) == st.end())
        {
            cycle.push_back(x);
            st.insert(x);
            x = par[x];
        }
        cycle.push_back(x);
        reverse(cycle.begin(), cycle.end());
        cout << "YES\n";
        unordered_set<int> final;
        for (auto &i : cycle)
        {
            cout << i << " ";
            if (final.find(i) != final.end())
            {
                break;
            }
            final.insert(i);
        }
    }
    return 0;
}