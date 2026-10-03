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
    function<void(int, int)> bfs = [&](int r, int c) -> void {
        queue<pair<int, int>> q;
        q.push({r, c});
        vis[r][c] = true;
        while (!q.empty()) { // while(q.size())
            const auto &[pi, pj] = q.front();
            q.pop();

            for (int d = 0; d < 4; d++) {
                int ni = pi + dx[d];
                int nj = pj + dy[d];
                
                /*
                    You can use additional function for check for valid index of [i,j] such as :
                     
                    function<bool(int, int)> check = [](int i, int j) -> bool {
                        return i >= 0 and j >= 0 and i < n and j < m and vis[i][j] == 0 and g[i][j] == '.';
                    };
                */
                if (ni >= 0 and nj >= 0 and ni < n and nj < m and !vis[ni][nj] and g[ni][nj] == '.') {
                    vis[ni][nj] = true;
                    q.push({ni, nj});
                }
            }
        }
    };

    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (vis[i][j] == 0 and g[i][j] == '.') {
                ans++;
                bfs(i, j);
            }
        }
    }
    cout << ans << endl;
    return 0;
}