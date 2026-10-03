#include <bits/stdc++.h>
using namespace std;
#define int long long

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
void dfs2(int u, vector<vector<int>> &adj, vector<int> &left, vector<int> &visited, int n)
{
    visited[u] = 1;
    left.push_back(u);
    for (int v = 1; v <= n; v++)
    {
        if (visited[v] == 0 and adj[u][v] >= 1)
        {
            dfs2(v, adj, left, visited, n);
        }
    }
}
int32_t main()
{
    int n, m, k;
    cin >> n >> m >> k;
    int src = 0, dest = n + m + 1, N = dest + 1;

    vector<vector<int>> adj(N, vector<int>(N, -1));
    vector<vector<int>> ase(N, vector<int>(N, -1));
    int sum = 0;
    for (int i = 0; i < k; i++)
    {
        int x, y;
        const int w = 1;
        cin >> x >> y;
        y = y + n;
        ase[x][y] = w;
        ase[y][x] = w;

        if (adj[x][y] == -1)
        {
            adj[x][y] = 0;
            adj[y][x] = 0;
        }
        adj[0][x] = 1;
        adj[x][y] += w;
        adj[y][x] += w;
        adj[y][n + m + 1] = 1;
        sum += w;
    }

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

    for (int boys = 1; boys <= n; boys++)
    {
        for (int girls = n + 1; girls <= n + m; girls++)
        {
            if (ase[boys][girls] == 1 && adj[boys][girls] == 0 && adj[girls][boys] >= 1)
            {
                cout << boys << " " << (girls - n) << endl;
                break; 
            }
        }
    }
    return 0;
}