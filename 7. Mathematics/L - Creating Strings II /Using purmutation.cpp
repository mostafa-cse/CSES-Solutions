#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e6 + 123;
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
int inverse(int n) {
    if (n <= 1)
        return 1;
    return modexpo(n, mod - 2, mod);
}
signed main() {
    string s;
    cin >> s;

    int ans = fact[s.size()];

    vector<int> cnt(27, 0);
    for (char c : s) {
        cnt[c - 'a']++;
    }

    for (int i = 0; i < 27; i++) {
        ans *= inverse(fact[cnt[i]]);
        ans %= mod;
    }
    cout << ans;
    return 0;
}
