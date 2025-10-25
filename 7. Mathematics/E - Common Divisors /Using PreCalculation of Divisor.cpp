#include <bits/stdc++.h>
using namespace std;
int const M = 1e6 + 5;
int cnt[M];
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        int a = sqrt(x);
        for (int d = 1; d <= a; d++) {
            if (x % d == 0) {
                cnt[d]++;
                if (d * d != x) {
                    cnt[x / d]++;
                }
            }
        }
    }
    for (int i = M - 1; i >= 1; i--) {
        if (cnt[i] >= 2) {
            return cout << i, 0;
        }
    }
    return 0;
}
