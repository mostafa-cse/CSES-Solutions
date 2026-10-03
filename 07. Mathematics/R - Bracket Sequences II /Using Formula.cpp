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

    string s;
    cin >> s;

    if (n & 1) {
        return cout << 0 << endl, 0;
    }

    int depth = 0;
    for (char c :s) {
        depth += (c == '(' ? 1 : -1);
        if (depth < 0) {
            return cout << 0, 0;
        }
    }

    if (depth > n - s.size()) {
        cout << 0 << endl;
        return 0;
    }

    int k = s.size();
    int left = (n - k - depth) / 2;
    cout << (nCr(n - k, left) - nCr(n - k, left + depth + 1) + mod) % mod << endl;
    return 0;
}
