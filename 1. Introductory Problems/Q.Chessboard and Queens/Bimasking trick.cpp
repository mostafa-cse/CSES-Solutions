#include <bits/stdc++.h>
#define int long long
using namespace std;
vector<int> g(8);
int row, col, left_corner, right_corner;
signed main() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            char c;
            cin >> c;
            g[i] |= ((c == '*') << j);
        }
    }
    function<int(int)> fun = [&](int c) -> int {
        if (c == 8) return 1;
        int ans = 0;
        for (int r = 0; r < 8; r++) {
            if ((g[r] >> c & 1) or (row >> r & 1) or (col >> c & 1) or (left_corner >> (8 + r - c) & 1) or (right_corner >> (r + c) & 1)) {
                continue;
            }
            row |= (1 << r), col |= (1 << c), left_corner |= (1 << (8 + r - c)), right_corner |= (1 << (r + c));
            ans += fun(c + 1);
            row ^= (1 << r), col ^= (1 << c), left_corner ^= (1 << (8 + r - c)), right_corner ^= (1 << (r + c));
        }
        return ans;
    };
    cout << fun(0);
    return 0;
}