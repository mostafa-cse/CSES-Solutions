#include <bits/stdc++.h>
#define int long long
using namespace std;
bool dfs(int u, int dest, vector<vector<int>> &adj, vector<int> &path, int threshhold, vector<int> &vis, int n)
{
    vis[u] = 1;
    if (u == dest)
    {
        path.push_back(u);
        return true;
    }
    for (int v = 1; v <= n; v++)
    {
        if (vis[v] == 0 and adj[u][v] >= threshhold)
        {
            if (dfs(v, dest, adj, path, threshhold, vis, n))
            {
                path.push_back(u);
                return true;
            }
        }
    }
    return false;
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    int src = 1, dest = n, N = n + 1;

    vector<vector<int>> adj(N, vector<int>(N, -1));
    vector<vector<int>> ase(N, vector<int>(N, 0));
    int sum = 0;
    for (int i = 0; i < k; i++)
    {
        int x, y;
        const int w = 1;
        cin >> x >> y;

        ase[x][y] = w;
        if (adj[x][y] == -1)
        {
            adj[x][y] = 0;
            adj[y][x] = 0;
        }
        adj[x][y] += w;
        sum = max(sum, max(adj[x][y], adj[y][x]));
    }
    int mx = 1;
    while (sum >= mx)
    {
        mx <<= 1;
    }
    sum = mx;
    int ans = 0;
    while (sum > 0)
    {
        vector<int> path;
        vector<int> vis(N, 0);

        bool f = dfs(src, dest, adj, path, sum, vis, dest);

        if (f == true)
        {
            reverse(path.begin(), path.end());
            int k = path.size();
            int minedgewt = INT_MAX;
            for (int i = 0; i < k - 1; i++)
            {
                minedgewt = min(minedgewt, adj[path[i]][path[i + 1]]);
            }
            ans += minedgewt;
            for (int i = 0; i < k - 1; i++)
            {
                adj[path[i]][path[i + 1]] -= minedgewt;
                adj[path[i + 1]][path[i]] += minedgewt;
            }
        }
        else
        {
            sum /= 2;
        }
    }
    cout << ans << "\n";
    for (int i = 1; i <= ans; ++i)
    {
        vector<int> path = {1};
        int u = 1;
        while (u != n)
        {
            for (int v = 1; v <= n; v++)
            {
                if (adj[u][v] == 0 and ase[u][v] == 1)
                {
                    path.push_back(v);
                    ase[u][v] = 0;
                    u = v;
                    break;
                }
            }
        }
        cout << path.size() << endl;
        for (int x : path)
        {
            cout << x << " ";
        }
        cout << endl;
    }

    return 0;
}