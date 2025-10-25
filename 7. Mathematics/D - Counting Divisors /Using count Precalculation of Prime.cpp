#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e6 + 5;
int cnt[MAXN];
auto prime_sieve = []() {
    for (int i = 1; i < MAXN; i += 1) {
        for (int j = i; j < MAXN; j += i) {
            cnt[j] += 1;
        }
    }
    return 0;
}();
void solve() {
    int x;
    cin >> x;
    cout << cnt[x] << endl;
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int tc;
    cin >> tc;

    for (int t = 1; t <= tc; t++) {
        // cout << "Case " << t << ": ";
        solve();
    }
    return 0;
}
