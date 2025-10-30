#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1000005;
int a[N], prime_count[N], mobius[N];
auto cal_mobius = []() {
    for (int i = 1; i < N; i++) {
        a[i] = 1;
    }
    for (int i = 2; i < N; i++) {
        if (prime_count[i])
            continue;
        for (int j = i; j < N; j += i) {
            prime_count[j]++;
            a[j] *= i;
        }
    }
    for (int i = 1; i < N; i++) {
        if (a[i] == i) {
            if (prime_count[i] % 2 == 1) {
                mobius[i] = -1;
            } else {
                mobius[i] = 1;
            }
        } else {
            mobius[i] = 0;
        }
    }
    return 0;
}();
signed main() {
    int n;
    cin >> n;

    unordered_map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    int ans = 0;
    for (int i = 1; i < N; i++) {
        int d = 0;
        for (int j = i; j < N; j += i) {
            d += cnt[j];
        }
        ans += (d * (d - 1) / 2) * mobius[i];
    }
    cout << ans;
    return 0;
}
