#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e6 + 123;
int fact[MAXN];
int inv[MAXN];
const int mod = 1e9 + 7;
int modexpo(int a, int p, int mod) {
    int res = 1;
    while (p) {
        if (p & 1) {
            res = (a * res) % mod;
        }
        p >>= 1;
        a = (a * a) % mod;
    }
    return res;
}
int inverse(int n) { return modexpo(n, mod - 2, mod); }
auto factorial = []() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
    inv[MAXN - 1] = inverse(fact[MAXN - 1]);
    for (int i = MAXN - 1; i >= 1; i--) {
        inv[i - 1] = (inv[i] * i) % mod;
    }
    return 0;
}();
int nCr(int n, int r) {
    if (n < r)
        return 0LL;
    return (((fact[n] * inv[r]) % mod * inv[n - r])) % mod;
}
signed main() {
    int n;
    cin >> n;


    if (n & 1) {
        cout << 0 << endl;
    } else {
        // int ans = (((nCr(n, n >> 1) * inverse(n + 2)) % mod) * 2) % mod; // this is also catalan number formula
        int ans = ((nCr(n, n >> 1) * inverse(n / 2 + 1)) % mod); // this is also catalan number formula
        cout << ans << endl;
    }
    return 0;
}
