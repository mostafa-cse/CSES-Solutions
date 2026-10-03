#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<map<int, int>> adj(n + m + 2);
    vector<vector<int>> ase(n + m + 2, vector<int>(n + m + 2, 0));
    for (int i = 0; i < k; i++)
    {
        int u, v, w = 1;
        cin >> u >> v;
        v += n;
        adj[0][u] = 1;         
        adj[u][v] = 1;         
        adj[v][n + m + 1] = 1; 
        ase[u][v] = 1;         
    }

    int Flow = 0;
    while (true)
    {
        vector<int> par(n + m + 2, -1);
        queue<int> q;

        q.push(0);
        par[0] = 0;

        bool colbe = true;
        while (q.size() and colbe)
        {
            int u = q.front();
            q.pop();
            for (auto [v, w] : adj[u])
            {
                if (w > 0 and par[v] == -1)
                {
                    par[v] = u;
                    q.push(v);
                    if (v == n + m + 1)
                    {
                        colbe = false;
                        break;
                    }
                }
            }
        }

        if (par[n + m + 1] == -1)
        {
            break;
        }

        int btlenk = 1e18;
        for (int p = n + m + 1; p != 0; p = par[p])
        {
            int u = par[p];
            int v = p;
            btlenk = min(btlenk, adj[u][v]);
        }
        Flow += btlenk;
        for (int p = n + m + 1; p != 0; p = par[p])
        {
            int u = par[p];
            int v = p;
            adj[u][v] -= btlenk;
            adj[v][u] += btlenk;
        }
    }
    cout << Flow << endl;

    // Output matching pairs
    for (int u = 1; u <= n; u++)
    {
        for (int v = n + 1; v <= n + m; v++)
        {
            if (ase[u][v] && adj[u][v] == 0)
            {
                cout << u << " " << (v - n) << endl;
            }
        }
    }
    return 0;
}