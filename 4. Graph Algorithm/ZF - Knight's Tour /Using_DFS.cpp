#include <bits/stdc++.h>
#define int long long
using namespace std;
int dx[] = {1, -1, 1, -1, 2, -2, 2, -2};
int dy[] = {2, 2, -2, -2, 1, 1, -1, -1};
signed main() {
    int x, y;
    cin >> x >> y;

    vector<vector<int>> path(8, vector<int>(8, 0));

    function<int(int, int)> check = [&](int i, int j) -> int {
        int c = 0;
        for (int d = 0; d < 8; d++) {
            int x = i + dx[d];
            int y = j + dy[d];
            c += (x >= 0 and y >= 0 and x < 8 and y < 8 and !path[x][y]);
        }
        return c;
    };
    function<bool(int, int, int)> dfs = [&](int i, int j, int moves) -> bool {
        path[i][j] = moves;
        if (moves == 64) {
            return true;
        }
        vector<array<int, 3>> val;
        for (int d = 0; d < 8; ++d) {
            int x = i + dx[d];
            int y = j + dy[d];
            if (x >= 0 and y >= 0 and x < 8 and y < 8 and path[x][y] == 0) {
                val.push_back({check(x, y), x, y});
            }
        }
        sort(val.begin(), val.end());
        for (auto [d, x, y] : val) {
            if (dfs(x, y, moves + 1)) {
                return true;
            }
        }
        path[i][j] = 0;
        return false;
    };
    dfs(y - 1, x - 1, 1);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; j++) {
            cout << path[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}