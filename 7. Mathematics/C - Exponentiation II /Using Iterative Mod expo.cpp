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
void solve() {
    int a, b, c;
    cin >> a >> b >> c;
    a %= Mod, b %= Mod, c %= Mod;
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
