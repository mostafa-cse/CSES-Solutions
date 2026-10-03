#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<ll> a(n + 2);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    a[n + 1] = 1e18; // sentinel

    // Prefix sums
    vector<ll> ps(n + 2);
    for (int i = 1; i <= n; i++) {
        ps[i] = ps[i - 1] + a[i];
    }

    // Next greater element using monotonic stack
    vector<int> rmax(n + 2, n + 1);
    stack<int> st;
    for (int i = 1; i <= n + 1; i++) {
        while (!st.empty() && a[i] > a[st.top()]) {
            rmax[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }

    const int LOG = 20;
    vector<vector<int>> nxt(n + 2, vector<int>(LOG));
    vector<vector<ll>> cost(n + 2, vector<ll>(LOG));

    // Base case
    for (int i = 1; i <= n + 1; i++) {
        nxt[i][0] = rmax[i];
        if (rmax[i] - i - 1 > 0) {
            ll cnt = rmax[i] - i - 1;
            ll sum = ps[rmax[i] - 1] - ps[i];
            cost[i][0] = a[i] * cnt - sum;
        } else {
            cost[i][0] = 0;
        }
    }

    // Binary lifting
    for (int e = 1; e < LOG; e++) {
        for (int i = 1; i <= n + 1; i++) {
            int mid = nxt[i][e - 1];
            nxt[i][e] = nxt[mid][e - 1];
            cost[i][e] = cost[i][e - 1] + cost[mid][e - 1];
        }
    }

    while (q--) {
        int l, r;
        cin >> l >> r;

        int cur = l;
        ll ans = 0;

        // Binary lifting to jump blocks
        for (int e = LOG - 1; e >= 0; e--) {
            if (nxt[cur][e] <= r) {
                ans += cost[cur][e];
                cur = nxt[cur][e];
            }
        }

        // Handle remaining tail
        if (cur < r) {
            ans += a[cur] * (ll)(r - cur) - (ps[r] - ps[cur]);
        }

        cout << ans << '\n';
    }

    return 0;
}
