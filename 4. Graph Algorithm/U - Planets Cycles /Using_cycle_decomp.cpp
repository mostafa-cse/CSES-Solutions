#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    int n;
    cin >> n;

    vector<int> child(n + 1, 0);
    for (int u = 1; u <= n; u++)
    {
        int v;
        cin >> v;
        child[u] = v;
    }
    vector<int> vis(n + 1, 0), depth(n + 1, 0), ans(n + 1, 0);
    stack<int> st;
    function<void(int, int)> dfs = [&](int u, int d) -> void
    {
        vis[u] = 1;
        depth[u] = d;
        st.push(u);

        int v = child[u];
        if (!vis[v])
        {
            dfs(v, d + 1);
        }
        else
        {
            if (vis[v] == 2)
            {
                ans[u] = ans[v] + 1;
            }
            else
            {
                int res = depth[u] - depth[v] + 1;
                // Collect cycle nodes until we reach v
                while (!st.empty())
                {
                    int node = st.top();
                    ans[node] = res;
                    st.pop();
                    if (node == v)
                        break;
                }
            }
        }
        vis[u] = 2;
        if (!ans[u])
            ans[u] = ans[v] + 1;
    };
    for (int u = 1; u <= n; u++)
    {
        if (vis[u] == 0)
        {
            dfs(u, 1);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        cout << ans[i] << " ";
    }
    return 0;
}
