#include <bits/stdc++.h>
#define int long long
using namespace std;
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
signed main() {
    int n, m;
    cin >> n >> m;

    vector<vector<char>> g(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];
        }
    }

    vector<vector<bool>> vis(n, vector<bool>(m, false));
    function<void(int, int)> dfs = [&](int r, int c) -> void {
        vis[r][c] = 1;
        for (int d = 0; d < 4; d++) {
            int ni = r + dx[d];
            int nj = c + dy[d];

            if (ni >= 0 and nj >= 0 and ni < n and nj < m and !vis[ni][nj] and g[ni][nj] == '.') {
                dfs(ni, nj);
            }
        }
    };
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (vis[i][j] == 0 and g[i][j] == '.') { // Same as before just change of using 4-direction
                ans++;
                dfs(i, j);
            }
        }
    }
    cout << ans << endl;
    return 0;
}