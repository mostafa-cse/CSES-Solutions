#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> g1[2 * m + 1], g2[2 * m + 1];
    for (int i = 0; i < n; i++)
    {
        char x, y;
        int a, b;
        cin >> x >> a >> y >> b;

        if (x == '-')
            a = 2 * m - a + 1;
        if (y == '-')
            b = 2 * m - b + 1;

        g1[2 * m - a + 1].push_back(b);
        g1[2 * m - b + 1].push_back(a);

        g2[a].push_back(2 * m - b + 1);
        g2[b].push_back(2 * m - a + 1);
    }

    stack<int> order;
    vector<int> vis(2 * n + 1, 0);
    function<void(int)> dfs = [&](int u) -> void
    {
        vis[u] = 1;
        for (int v : g1[u])
        {
            if (vis[v] == 0)
            {
                dfs(v);
            }
        }
        order.push(u);
    };
    for (int i = 1; i <= 2 * m; ++i)
    {
        if (vis[i] == 0)
        {
            dfs(i);
        }
    }

    fill(vis.begin(), vis.end(), 0);
    function<void(int, int)> dfs2 = [&](int u, int clr) -> void
    {
        vis[u] = clr;
        for (int v : g2[u])
        {
            if (vis[v] == 0)
            {
                dfs2(v, clr);
            }
        }
    };

    int k = 0;
    while (!order.empty())
    {
        int x = order.top();
        if (!vis[x])
        {
            ++k;
            dfs2(x, k);
        }
        order.pop();
    }

    vector<char> ans(n + 1, ' ');
    for (int i = 1; i <= m; i++)
    {
        if (vis[i] == vis[2 * m - i + 1])
        {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
        ans[i] = (vis[i] > vis[2 * m - i + 1]);
    }
    for (int i = 1; i <= m; i++)
    {
        cout << ((ans[i]) ? '+' : '-') << " ";
    }
    return 0;
}
