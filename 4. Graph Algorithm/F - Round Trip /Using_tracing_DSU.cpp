#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod = 1e9 + 7;
const int maxn = 1e5 + 1;
int n, m, a, b, par[maxn], lap[maxn];
vector<int> adj[maxn], ans;
int trace(int u)
{
    return (lap[u] < 0 ? u : lap[u] = trace(lap[u]));
}
bool syncretize(int u, int v)
{
    u = trace(u), v = trace(v);
    if (u == v)
        return 0;
    if (lap[u] < lap[v])
        swap(u, v);
    lap[v] += lap[u], lap[u] = v;
    return 1;
}
void dfs(int cur)
{
    for (auto next : adj[cur])
        if (next != par[cur])
            par[next] = cur, dfs(next);
}
int main()
{
    cin >> n >> m;
    fill(lap + 1, lap + n + 1, -1);
    while (m--)
    {
        cin >> a >> b;
        if (!syncretize(a, b))
        {
            dfs(a);
            int temp = b;
            while (temp != 0)
                ans.push_back(temp), temp = par[temp];
            cout << ans.size() + 1 << endl;
            for (auto x : ans)
                cout << x << " ";
            cout << b;
            exit(0);
        }
        adj[a].push_back(b), adj[b].push_back(a);
    }
    cout << "IMPOSSIBLE";
    return 0;
}
