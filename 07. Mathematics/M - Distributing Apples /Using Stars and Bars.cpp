#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e6 + 123;
int fact[MAXN];
const int mod = 1e9 + 7;
auto factorial = []() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
    return 0;
}();
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
int nCr(int n, int r) {
    if (n < r)
        return 0;
    return (((fact[n] * inverse(fact[r])) % mod) * inverse(fact[n - r])) % mod;
}
signed main() {
    int n, k;
    cin >> k >> n;

    int N = n + k - 1;
    int R = k - 1;
    if (R == 0) {
        cout << 1 << endl;
        return 0;
    }
    cout << nCr(N, R);
    return 0;
}
