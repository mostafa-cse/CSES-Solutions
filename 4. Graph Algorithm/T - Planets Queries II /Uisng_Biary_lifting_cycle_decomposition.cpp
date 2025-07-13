#include <bits/stdc++.h>
using namespace std;
#define N 200001
#define J 18

// Directed graph with outdegree 1 for every node
// Every node belongs to a tree or cycle. Every tree is rooted in a cycle

int main()
{
    static int t[J][N], d[N], o[N];              // d = indegree
    static int l[N], cs[N], ci[N], cl[N], ce[N]; // level, cycle start node, index in cycle, cycle length, cycle entry point

    for (int i = 0; i < N; i++)
    {
        d[i] = o[i] = l[i] = cs[i] = ci[i] = cl[i] = ce[i] = 0;
    }

    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++)
    {
        // i -> x
        int x;
        cin >> x;
        t[0][i] = x;
        d[x]++;
    }

    // 2^j teleportation lookup using binary lifting
    for (int j = 1; j < J; j++)
    {
        for (int i = 1; i <= n; i++)
        {
            t[j][i] = t[j - 1][t[j - 1][i]];
        }
    }

    // Process all non-cycle nodes in forwards direction, recording traversal order
    int j = 1;
    for (int i = 1; i <= n; i++)
    {
        int e = i;
        while (d[e] == 0)
        {
            d[e]--;
            o[j++] = e;
            e = t[0][e];
            d[e]--;
        }
    }

    // Process cycle nodes
    for (int i = 1; i <= n; i++)
    {
        if (d[i] == 1)
        {
            int e = i;
            int k = 0;
            while (d[e] == 1)
            {
                ce[e] = e;
                cs[e] = i;
                ci[e] = k++;
                d[e]--;
                e = t[0][e];
            }
            cl[i] = k;
            ce[i] = i;
        }
    }

    // Reverse over all non-cycle nodes, recording level and cycle start node
    while (--j)
    {
        int e = o[j];
        int te = t[0][e];
        l[e] = l[te] + 1;
        cs[e] = cs[te];
        ce[e] = ce[te];
    }

    while (q--)
    {
        int a, b;
        cin >> a >> b;
        int r;

        if (cs[a] != cs[b] || l[a] < l[b])
        {
            r = -1;
        }
        else if (l[a] > 0 && l[b] > 0)
        {
            // a and b are both in same tree. Fast-forward a to b's level and see if they match
            int p = l[a] - l[b];
            int ps = p;
            j = 0;
            while (p)
            {
                if (p & 1)
                {
                    a = t[j][a];
                }
                j++;
                p >>= 1;
            }
            if (a == b)
            {
                r = ps;
            }
            else
            {
                r = -1;
            }
        }
        else
        {
            // Get a into cycle
            if (l[a] > 0)
            {
                r = l[a];
                a = ce[a];
            }
            else
            {
                r = 0;
            }
            int cla = cl[cs[a]];

            r += ((cla + ci[b] - ci[a]) % cla);
        }

        cout << r << endl;
    }
}