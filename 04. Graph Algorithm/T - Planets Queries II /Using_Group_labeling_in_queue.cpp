#include <bits/stdc++.h>
using namespace std;

#define N 200200
struct node
{
    int id = 0;
    node *next = 0;
    node() = default;
    node(int a) : id(a) {}
};
node *add(node *n, int i)
{
    node *t = new node(i);
    t->next = n;
    return t;
}
node *from[N] = {};
int timer, indeg[N], ringsize[N], to[N], dist[N], head[N], Set[N], ring[N], tin[N], tout[N];
#define isanc(a, b) (tin[a] <= tin[b] && tout[a] >= tout[b])

void dfs(int i)
{
    tin[i] = ++timer;
    for (node *t = from[i]; t != nullptr; t = t->next)
        if (head[t->id] == 0)
        {
            head[t->id] = head[i];
            Set[t->id] = Set[i];
            dist[t->id] = dist[i] + 1;
            dfs(t->id);
        }
    tout[i] = ++timer;
}

int main()
{
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
    {
        cin >> to[i];
        from[to[i]] = add(from[to[i]], i);
        indeg[to[i]]++;
    }
    queue<int> leafs;
    for (int i = 1; i <= n; ++i)
        if (!indeg[i])
            leafs.push(i);
    while (!leafs.empty())
    {
        int i = leafs.front();
        ring[i] = -1;
        indeg[to[i]]--;
        leafs.pop();
        if (indeg[to[i]] == 0)
            leafs.push(to[i]);
    }
    for (int i = 1, Set_n = 1; i <= n; ++i)
    {
        if (ring[i] != 0)
            continue;
        int st = i, number = 0;
        while (true)
        {
            head[st] = st;
            Set[st] = Set_n;
            ring[st] = number++;
            if (to[st] == i)
            {
                ringsize[Set_n] = ring[st] + 1;
                break;
            }
            st = to[st];
        }
        Set_n++;
    }
    for (int i = 1; i <= n; ++i)
        if (ring[i] >= 0)
            timer = 0, dfs(i);
    while (q--)
    {
        int x, y;
        cin >> x >> y;
        if ((Set[x] != Set[y]) || (ring[x] >= 0 && ring[y] < 0))
        {
            cout << "-1\n";
            continue;
        }
        int out;
        if (ring[x] >= 0 && ring[y] >= 0)
        {
            out = ring[y] - ring[x];
            if (out < 0)
                out += ringsize[Set[x]];
        }
        else if (ring[y] >= 0)
        {
            out = ring[y] - ring[head[x]];
            if (out < 0)
                out += ringsize[Set[y]];
            out += dist[x];
        }
        else
        {
            if (head[x] == head[y] && isanc(y, x))
                out = dist[x] - dist[y];
            else
                out = -1;
        }
        cout << out << '\n';
    }
}