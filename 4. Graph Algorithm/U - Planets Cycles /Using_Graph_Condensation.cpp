#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> vis(n + 1, 0), condense(n + 1, -1), size(n + 1, 0), Final(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = i, cnt = 0;; j = a[j], cnt++) {
            if (!vis[j]) {
                vis[j] = i;
                condense[j] = cnt;
            } else if (vis[j] == i) {
                size[i] = cnt - condense[j];
                Final[i] = condense[j];
                cout << cnt << " ";
                break;
            } else {
                size[i] = size[vis[j]];
                Final[i] = cnt + max(Final[vis[j]] - condense[j], 0ll);
                cout << Final[i] + size[i] << " ";
                break;
            }
        }
    }
    return 0;
}