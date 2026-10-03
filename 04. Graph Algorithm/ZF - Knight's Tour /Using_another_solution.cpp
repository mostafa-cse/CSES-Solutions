#include <bits/stdc++.h>
using namespace std;

const vector<pair<int, int>> moves = {{2, 1}, {2, -1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {1, -2}, {-1, -2}};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int sx, sy;
    cin >> sy >> sx;
    sx--;
    sy--;
    vector<vector<int>> ans(8, vector<int>(8, 0));
    vector<vector<int>> pos(8, vector<int>(8, 0));
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            for (auto [dx, dy] : moves)
            {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && ny >= 0 && nx < 8 && ny < 8)
                    pos[x][y]++;
            }
        }
    }
    auto decr_pos = [&](int cx, int cy)
    {
        for (auto [dx, dy] : moves)
        {
            int nx = cx + dx, ny = cy + dy;
            if (nx < 0 || ny < 0 || nx >= 8 || ny >= 8)
                continue;
            pos[nx][ny]--;
        }
    };
    int x = sx, y = sy;
    ans[x][y] = 1;
    decr_pos(x, y);
    while (ans[x][y] != 64)
    {
        int next_x, next_y;
        int lowest = 1000;
        for (auto [dx, dy] : moves)
        {
            int nx = x + dx, ny = y + dy;
            if (nx < 0 || ny < 0 || nx >= 8 || ny >= 8 || ans[nx][ny] != 0)
                continue;
            if (pos[nx][ny] < lowest)
            {
                lowest = pos[nx][ny];
                next_x = nx, next_y = ny;
            }
        }
        ans[next_x][next_y] = ans[x][y] + 1;
        x = next_x, y = next_y;
        decr_pos(x, y);
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}