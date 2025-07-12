#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

int Color[200000];
vector<int> Next[200000];
int K[200000];
int LinkUp[200000];
int LinkDown[200000];
int Leaf[200000];
int Adj[200000] = {};
int CircleColor[200000];
bool IsCircle[200000];


void cal(int node, int prev, int step, int c)
{
    if (Color[node] == -1)
    {
        Color[node] = c;
        Next[LinkUp[prev]].push_back(node);
        LinkUp[node] = LinkUp[prev];
        K[node] = step + K[LinkUp[prev]];
        cal(Adj[node], node, step + 1, c);
        return;
    }
    if (Color[node] != c)
    {
        LinkDown[LinkUp[prev]] = node;
        return;
    }

    return;
}

int Kfind(int node, int &k)
{
    int parent = LinkUp[node];
    int newK = k + K[node];
    while (LinkDown[parent] != -1 && newK >= Next[parent].size())
    {                                // or >
        newK -= Next[parent].size(); //+-1 ?
        parent = LinkDown[parent];
        newK += K[parent];
        parent = LinkUp[parent];
    }
    // mb right?
    // cerr << "value = " << newK % Next[parent].size() << endl;
    return Next[parent][newK % Next[parent].size()];
}

void dfs(int node, int &c)
{
    if (CircleColor[node] == -1)
    {
        CircleColor[node] = c;
    }
    else
    {
        IsCircle[node] = 1;
    }
    if (CircleColor[Adj[node]] == -1)
    {
        dfs(Adj[node], c);
    }
    else if (CircleColor[Adj[node]] == c && IsCircle[Adj[node]] == 0)
    {
        dfs(Adj[node], c);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < (n); ++i)
    {
        LinkDown[i] = -1;
        Leaf[i] = 1;
        CircleColor[i] = -1;
        Color[i] = -1;
        LinkUp[i] = i;
    }
    for (int i = 0; i < (n); ++i)
    {
        cin >> Adj[i];
        --Adj[i];
        Leaf[Adj[i]] = 0;
    }
    for (int i = 0; i < (n); ++i)
    {
        if (CircleColor[i] == -1)
        {
            dfs(i, i);
        }
    }
    for (int i = 0; i < (n); ++i)
    {
        if (Color[i] == -1 && IsCircle[i] == 1)
        {
            cal(i, i, 0, i);
        }
    }
    for (int i = 0; i < (n); ++i)
    {
        if (Leaf[i] == 1)
        {
            cal(i, i, 0, i + n);
        }
    }

    while (q--)
    {
        int x, k;
        cin >> x >> k;
        cout << Kfind(x - 1, k) + 1 << endl;
    }
    return 0;
}