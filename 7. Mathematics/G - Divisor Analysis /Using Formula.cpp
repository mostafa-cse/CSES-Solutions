#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 1e9 + 7;
int modexpo(int a, int p) {
    int res = 1;
    while (p) {
        if(p & 1) {
            res = (a * res) % Mod;
        }
        p >>= 1;
        a = (a * a) % Mod;
    }
    return res;
}
int inv(int x) {
    return modexpo(x, Mod - 2);
}
signed main() {
    int n;
    cin >> n;

    vector<int> p(n), c(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i] >> c[i];
    }

    int cntDivisor = 1;
    for (int i = 0; i < n; i++) {
        cntDivisor *= (c[i] + 1);
        cntDivisor %= Mod;
    }

    int sum = 1;
    for (int i = 0; i < n; i++) {
        sum *= modexpo(p[i], c[i] + 1) - 1;
        sum = (sum + Mod) % Mod;

        sum *= inv(p[i] - 1);
        sum %= Mod;
    }

    int count2 = 1; // count divisor
    bool isPerfectSqure = true;
    for (int i = 0; i < n; i++) {
        if (isPerfectSqure and (c[i] & 1)) {
            count2 = count2 * ((c[i] + 1) / 2);
            isPerfectSqure = false;
        } else {
            count2 *= (c[i] + 1);
        }
        count2 %= (Mod - 1);
    }

    int prod = 1;
    for (int i = 0; i < n; i++) {
        if (isPerfectSqure) c[i] /= 2;
        prod *= modexpo(modexpo(p[i], c[i]), count2);
        prod %= Mod;
    }
    cout << cntDivisor << " " << sum << " " << prod << endl;
    return 0;
}
