#include <bits/stdc++.h>
#define int long long
using namespace std;
vector<vector<char>> g(9, vector<char>(9));
vector<int> row(9, 0), col(9, 0), left_corner(16, 0), right_corner(17, 0);
signed main() {
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            cin >> g[i][j];
        }
    }

    function<int(int)> rec = [&](int r) -> int {
        if (r == 9) return 1;
        int ans = 0;
        for (int c = 1; c <= 8; c++) {
            if (g[r][c] == '*' or row[r] or col[c] or left_corner[8 + r - c] or right_corner[r + c]) {
                continue;
            }
            row[r] = col[c] = left_corner[8 + r - c] = right_corner[r + c] = 1;
            ans += rec(r + 1);
            row[r] = col[c] = left_corner[8 + r - c] = right_corner[r + c] = 0;
        }
        return ans;
    };
    cout << rec(1) << endl;
    return 0;
}