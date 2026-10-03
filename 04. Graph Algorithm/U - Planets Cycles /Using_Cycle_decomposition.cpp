#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5 + 1;
vector<int> v(N);
vector<bool> vis(N);
vector<bool> cyc(N);
vector<int> ans(N);
vector<int> p;
void dfs(int k)
{
    vis[k] = true;
    p.push_back(k);

    if (!vis[v[k]])
    {
        dfs(v[k]);
    }
    else
    {
        p.erase(p.begin(), find(p.begin(), p.end(), v[k]));
        for (auto i : p)
        {
            cyc[i] = 1;
            ans[i] = p.size();
        }
    }
}

void dfs2(int k)
{
    vis[k] = 1;
    if (!vis[v[k]] && !cyc[v[k]])
        dfs2(v[k]);
    ans[k] = ans[v[k]] + 1;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        v[i] = a;
    }
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            dfs(i);
            p.clear();
        }
    }
    fill(vis.begin(), vis.end(), 0);
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i] && !cyc[i])
            dfs2(i);
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
