#include <bits/stdc++.h>
#define int long long
using namespace std;
const int M = 1e6 + 5;
int lpf[M];
void leastPrimeFactor() {
    for (int i = 0; i < M; i++) {
        lpf[i] = i;
    }
    for (int i = 2; i * i <= M; i++) {
        for (int j = i * i; j < M and lpf[i] == i; j += i) {
            if (lpf[j] == j) lpf[j] = i;
        }
    }
}
int mobius[M];
void Mobius() {
    leastPrimeFactor();
    for (int i = 1; i < M; i++) {
        if (i == 1) {
            mobius[i] = 1;
        } else {
            if (lpf[i / lpf[i]] == lpf[i]) {
                mobius[i] = 0;
            } else {
                mobius[i] = -1 * mobius[i / lpf[i]];
            }
        }
    }
}
int cnt[M];
signed main() {
    Mobius();
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    int ans = 0;
    for (int i = 1; i < M; i++) {
        int d = 0;
        for (int j = i; j < M; j += i) {
            d += cnt[j];
        }
        ans += (d * (d - 1) / 2) * mobius[i];
    }
    cout << ans;
    return 0;
}
