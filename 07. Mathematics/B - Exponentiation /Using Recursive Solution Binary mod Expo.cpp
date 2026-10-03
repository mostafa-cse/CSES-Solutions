#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 1e9 + 7;
int modexpo(int a, int p) {
    if (p == 0) return 1;
    if (p & 1) return (a * modexpo((a * a) % Mod, p >> 1)) % Mod;
    return modexpo((a * a) % Mod, p >> 1);
}
void solve() {
    int n, p;
    cin >> n >> p;
    cout << modexpo(n, p) << endl;
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
