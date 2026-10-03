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
        if (r < 0 or c < 0 or r >= n or c >= m or vis[r][c] or g[r][c] == '#') {
            return;
        }
        vis[r][c] = 1;
        dfs(r + 1, c);
        dfs(r, c + 1);
        dfs(r - 1, c);
        dfs(r, c - 1);
    };

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (vis[i][j] == 0 and g[i][j] == '.') { // Count Component at each time call 
                ans++;
                dfs(i, j);
            }
        }
    }
    cout << ans << endl;
    return 0;
}