#include <bits/stdc++.h>
#define int long long
using namespace std;
const int M = 1e7 + 1;
pair<int, int> sum[2 * M];
void solve() {
    int x;
    cin >> x;
    for (int i = 0; i + i <= x; i++) {
        if (sum[i].first == -1 or sum[x - i].first == -1) continue;
        cout << sum[i].first << " " << sum[i].second << " " << sum[x - i].first << " " << sum[x - i].second << endl;
        return;
    }
}
signed main() {
    memset(sum, -1, sizeof sum);
    for (int i = 0; i * i < M; i++) {
        for (int j = 0; j * j < M; j++) {
            sum[i * i + j * j] = {i, j};
        }
    }
    int tc;
    cin >> tc;

    for (int t = 1; t <= tc; t++) {
        // cout << "Case " << t << ": ";
        solve();
    }
    return 0;
}
