#include <bits/stdc++.h>
using namespace std;
const int N = 2e5;
int n, tot, to[N + 5], in[N + 5], val[N + 5], circleid[N + 5], circlesize[N + 5];
void topo()
{
    queue<int> q;
    for (int i = 1; i <= n; i++)
        in[to[i]]++;
        
    for (int i = 1; i <= n; i++)
        if (!in[i])
            q.push(i);
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        in[to[now]]--;
        if (!in[to[now]])
            q.push(to[now]);
    }
    for (int i = 1; i <= n; i++)
    {
        if (in[i] || circleid[i])
            continue;
        int cur = i;
        tot++;
        while (!circleid[cur])
            circleid[cur] = tot, circlesize[tot]++, cur = to[cur];
    }
    for (int i = 1; i <= n; i++)
        val[i] = circlesize[circleid[i]];
}
int dfs(int now)
{
    if (val[now])
        return val[now];
    val[now] = dfs(to[now]) + 1;
    return val[now];
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> to[i];
    topo();
    for (int i = 1; i <= n; i++)
        if (!val[i])
            dfs(i);
    for (int i = 1; i <= n; i++)
        cout << val[i] << " ";
    return 0;
}
