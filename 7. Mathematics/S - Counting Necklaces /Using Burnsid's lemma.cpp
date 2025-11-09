#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 1e9 + 7;
int modexpo(int a, int p,int mod) {
    int res = 1;
    while (p) {
        if(p & 1) {
            res = (a * res) % mod;
        }
        p >>= 1;
        a = (a * a) % mod;
    }
    return res;
}
signed main() {
    int n, k;
    cin >> n >> k;

    int ans = 0;
    for (int i = 0; i < n; i++) {
        int g = __gcd(i, n);
        ans += modexpo(k, g, Mod);
        ans %= Mod;
    }
    ans = (ans * modexpo(n, Mod - 2, Mod)) % Mod;
    cout << ans << endl;
    return 0;
}
