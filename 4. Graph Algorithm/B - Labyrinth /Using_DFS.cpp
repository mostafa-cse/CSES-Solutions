// DFS Solution will not to be efficient : TLE Solution
#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<char>> g(n, vector<char>(m));
    int x_i, y_i, x_j, y_j;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> g[i][j];
            if (g[i][j] == 'A')
            {
                x_i = i, y_i = j;
            }
            else if (g[i][j] == 'B')
            {
                x_j = i, y_j = j;
            }
        }
    }
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<pair<int, int>> dir = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    vector<vector<pair<int, int>>> par(n, vector<pair<int, int>>(m, {-1, -1}));
    vector<vector<int>> parent_dir(n, vector<int>(m, -1));
    string direction = "RLDU";
    bool found = false;
    function<void(int, int)> dfs = [&](int i, int j) -> void
    {
        if (found || (i == x_j and j == y_j))
        {
            found = true;
            return;
        }
        visited[i][j] = true;
        for (int d = 0; d < 4; d++)
        {
            int ni = i + dir[d].first;
            int nj = j + dir[d].second;
            if (ni >= 0 and nj >= 0 and ni < n and nj < m and g[ni][nj] != '#' and !visited[ni][nj])
            {
                par[ni][nj] = {i, j};
                parent_dir[ni][nj] = d;
                dfs(ni, nj);
                if (found)
                    return;
            }
        }
    };
    dfs(x_i, y_i);

    if (!found)
    {
        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;

    string path = "";
    int curr_x = x_j, curr_y = y_j;

    while (par[curr_x][curr_y].first != -1)
    {
        path += direction[parent_dir[curr_x][curr_y]];
        int temp_x = par[curr_x][curr_y].first;
        int temp_y = par[curr_x][curr_y].second;
        curr_x = temp_x;
        curr_y = temp_y;
    }

    reverse(path.begin(), path.end());
    cout << path.length() << endl;
    cout << path << endl;
    return 0;
}