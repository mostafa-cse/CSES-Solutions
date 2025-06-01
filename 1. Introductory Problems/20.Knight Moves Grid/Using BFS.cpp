#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    vector<vector<int>> grid(n + 1, vector<int>(n + 1, -1));
    queue<array<int, 3>> q;

    #define x a[0]
    #define y a[1]
    #define p a[2]
    int X[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int Y[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    q.push({1, 1, 0});
    grid[1][1] = 0;
    while (!q.empty()) {
        array<int, 3> a = q.front();
        q.pop();

        for (int d = 0; d < 8; d++) {
            int nx = x + X[d];
            int ny = y + Y[d];
            if (nx <= n and ny <= n and nx >= 1 and ny >= 1 and grid[nx][ny] == -1) {
                grid[nx][ny] = p + 1;
                q.push({nx, ny, p + 1});
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}