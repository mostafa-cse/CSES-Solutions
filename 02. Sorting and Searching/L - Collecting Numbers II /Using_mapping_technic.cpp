#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, q;
    cin >> n >> q;

    vector<int> a(n), pos(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = x - 1;
        pos[x - 1] = i;
    }

    int ans = 1;
    for (int i = 0; i + 1 < n; i++) {
        ans += (pos[i] > pos[i + 1]);
    }

    while (q--) {
        int u, v;
        cin >> u >> v;
        u -= 1, v -= 1;

        set<pair<int, int>> st;
        if (a[u] - 1 >= 0) st.insert({a[u] - 1, a[u]});
        if (a[u] + 1 < n) st.insert({a[u], a[u] + 1});
        if (a[v] - 1 >= 0) st.insert({a[v] - 1, a[v]});
        if (a[v] + 1 < n) st.insert({a[v], a[v] + 1});
        
        function<int()> countInversion = [&]() -> int {
            int cnt = 0;
            for (auto [x, y] : st) {
                cnt += pos[x] > pos[y];
            }
            return cnt;
        };
        int init = countInversion();
        swap(a[u], a[v]);
        pos[a[u]] = u;
        pos[a[v]] = v;
        int curr = countInversion();

        ans += curr - init;
        cout << ans << endl;
    }
    return 0; 
}