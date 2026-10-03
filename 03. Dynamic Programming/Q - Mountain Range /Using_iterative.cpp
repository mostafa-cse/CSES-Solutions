#include <bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
    int N;
    cin >> N;

    vector<int> h(N);
    for (int i = 0; i < N; i++) {
        cin >> h[i];
    }
    h.insert(begin(h), 2e18);

    vector<int> dp(N + 1), l(N + 1, -1), r(N + 1, -1);
    vector<int> s(1, 0);
    for (int i = 1; i <= N; i++) {
        while (h[s.back()] <= h[i]) {
            int p = end(s)[-2], j = end(s)[-1];
            r[p] = -1;
            r[j] = l[i];
            l[i] = j;
            s.pop_back();
        }
        r[s.back()] = i;
        s.emplace_back(i);
    }
    auto dfs = [&](auto&& dfs, int x) -> void {
        if (l[x] != -1) {
            dp[l[x]] = dp[x] + (h[l[x]] != h[x]);
            dfs(dfs, l[x]);
        }
        if (r[x] != -1) {
            dp[r[x]] = dp[x] + (h[r[x]] != h[x]);
            dfs(dfs, r[x]);
        }
    };
    dfs(dfs, 0);
    cout << *max_element(begin(dp), end(dp)) << '\n';
    return 0;
}
