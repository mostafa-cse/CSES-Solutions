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

    int cnt = 0;
    queue<int> q;
    vector<int> vis(n + 1, 0), len(n + 1, 0);
    function<void(int)> dfs = [&](int u) -> void {
        q.push(u);
        if (vis[u] == 1) {
            cnt += len[u];
            return;
        }
        vis[u] = 1;
        cnt++;
        dfs(a[u]);
    };
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            cnt = 0;
            dfs(i);
            int cnt2 = 1;
            while (!q.empty()) {
                if (q.front() == q.back()) {
                    cnt2 = 0;
                }
                len[q.front()] = cnt;
                cnt -= cnt2;
                q.pop();
            }
        }
    }    
    for (int i = 1; i <= n; i++) {
        cout << len[i] << " ";
    }
    return 0;
}