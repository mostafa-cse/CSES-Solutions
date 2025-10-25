#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 1e9 + 7;
int modexpo(int a, int p, const int mod) {
    if (p == 0) return 1;
    if (p & 1) return (a * modexpo((a * a) % mod, p >> 1, mod)) % mod;
    return modexpo((a * a) % mod, p >> 1, mod);
}
void solve() {
    int a, b, c;
    cin >> a >> b >> c;
    cout << modexpo(a, modexpo(b, c, Mod - 1), Mod) << endl;
}
signed main() {
    int tc;
    cin >> tc;

    for (int t = 1; t <= tc; t++) {
        // cout << "Case " << t << ": ";
        solve();
    }
    return 0;
}
