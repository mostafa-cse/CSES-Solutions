#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;

    vector<vector<char>> g(n, vector<char>(m));
    int x_i, y_i, x_j, y_j;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];
            if (g[i][j] == 'A') {
                x_i = i, y_i = j;
            } else if (g[i][j] == 'B') {
                x_j = i, y_j = j;
            }
        }
    }

    struct Node {
        int dis, x, y;
        string dir;
    };

    queue<Node> pq;
    vector<vector<int>> vis(n, vector<int>(m, 1e10));
    pq.push({0, x_i, y_i, ""});
    vis[x_i][y_i] = 0;

    int ans = n * m;
    string dir_ans = "";
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    string dir_char = "UDLR";


    while (!pq.empty()) {
        auto [dis, x, y, dir] = pq.front();
        pq.pop();

        if (x == x_j && y == y_j) {
            if (dis < ans) {
                ans = dis;
                dir_ans = dir;
            }
            continue;
        }

        for (int d = 0; d < 4; ++d) {
            int ni = x + directions[d].first;
            int nj = y + directions[d].second;
            if (ni >= 0 && nj >= 0 && ni < n && nj < m && g[ni][nj] != '#' && vis[ni][nj] > dis + 1) {
                vis[ni][nj] = dis + 1;
                pq.push({dis + 1, ni, nj, dir + dir_char[d]});
            }
        }
    }
    if (ans != n * m) {
        cout << "YES" << endl;
        cout << ans << endl;
        cout << dir_ans << endl;
    } else {
        cout << "NO\n";
    }
    return 0;
}