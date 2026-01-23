#include <bits/stdc++.h>
// #define int long long
using namespace std;
#define all(x) x.begin(), x.end()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, k;
    cin >> n >> k;

    int x, a, b, c;
    cin >> x >> a >> b >> c;

    vector<int> ar;
    ar.emplace_back(x);
    for (int i = 1; i < n; i++) {
        long long cur = ar[i - 1] * 1LL * a + 1LL * b;
        while (cur >= c) cur -= c;
        ar.emplace_back(cur);
    }

    long long ans = 0;
    priority_queue<pair<int, int>> pq;
    for (int i = 0; i < n; i++) {
        while (!pq.empty() and (i - pq.top().second) >= k) {
            pq.pop();
        }
        pq.push({-ar[i], i});
        if (i + 1 >= k) {
            ans ^= -pq.top().first;
        }
    }
    cout << ans << endl;
    return 0;
}

