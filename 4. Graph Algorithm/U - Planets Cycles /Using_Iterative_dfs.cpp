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
    vector<int> vis(n + 1, 0), jmp(n + 1, -1), ans(n + 1, 0);
    stack<int> st;
    function<void(int)> dfs = [&](int u) -> void {
        int jump = 0, j = 0;
        stack<int> st;

        while (true) {
            if (vis[u]) {
                if (jmp[u] >= 0) {
                    j = jump - jmp[u];
                } else {
                    j = ans[u];
                    st.push(n + 1);
                    u = n + 1;
                }
                break;
            } else {
                jmp[u] = jump;
                st.push(u);
                vis[u] = 1;
                jump++;

                u = a[u];
            }
        }

        bool ok = false;
        while (!st.empty()) {
            int v = st.top();
            jmp[v] = -1;
            st.pop();


            if (ok) {
                ans[v] = ++j;
            } else {
                ans[v] = j;
                if (v == u) {
                    ok = true;
                }
            }
        }
    };

    for (int i = 1; i <= n; i++) {
        if (vis[i] == 0) {
            dfs(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}