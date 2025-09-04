#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    vector<int> p(n + 1, 0), deg(n + 1, 0);
    for (int i = 2; i <= n; i++) {
        cin >> p[i];
        deg[p[i]]++;
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }

    vector<int> ans(n + 1, 0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        deg[p[u]]--;
        if (deg[p[u]] == 0) q.push(p[u]);
        ans[p[u]] += ans[u] + 1;
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
// another way to reverse this graph and use Topsort snippet
