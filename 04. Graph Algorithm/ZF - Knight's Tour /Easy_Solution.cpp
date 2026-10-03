#include <bits/stdc++.h>
using namespace std;
int x, y, f[10][10], g[10];
bool kt(int u, int v)
{
    return (!f[u][v] && u >= 1 && u <= 8 && v >= 1 && v <= 8);
}
int l[] = {2, 2, 1, 1, -2, -2, -1, -1};
int r[] = {1, -1, 2, -2, 1, -1, 2, -2};
int mnin() {
    cin >> x >> y;
    swap(x, y);

    int dem = 0;
    f[x][y] = ++dem;
    while (dem < 64)
    {
        int mn = 9, j;
        for (int i = 0; i < 8; i++)
        {
            int u = x + l[i], v = y + r[i];
            for (int j = 0; j < 10; j++)
                g[j] = 0;
            if (kt(u, v))
            {
                for (int k = 0; k < 8; k++)
                {
                    if (kt(u + l[k], v + r[k]))
                        g[i]++;
                }
                if (mn >= g[i])
                    mn = g[i], j = i;
            }
        }
        x += l[j], y += r[j];
        f[x][y] = ++dem;
    }
    for (int i = 1; i <= 8; i++)
    {
        for (int j = 1; j <= 8; j++)
            cout << f[i][j] << ' ';
        cout << endl;
    }
}
