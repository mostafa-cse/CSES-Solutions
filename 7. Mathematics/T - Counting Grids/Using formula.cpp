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
int inverse(int x) {
    return modexpo(x, Mod - 2, Mod);
}
signed main() {
    int n;
    cin >> n;

    int ans = 0;

    ans += modexpo(2, n * n / 4 + 1, Mod);
    ans %= Mod;

    ans += modexpo(2, n * n / 2, Mod);
    ans %= Mod;

    ans *= (n % 2 + 1);
    ans %= Mod;

    ans += modexpo(2, n * n, Mod);
    ans %= Mod;

    ans = ans * inverse(4);
    ans %= Mod;

    cout << ans << endl;
    return 0;
}
