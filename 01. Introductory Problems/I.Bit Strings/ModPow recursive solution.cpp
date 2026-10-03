#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    function<int(int, int, int)> rec = [&](int a, int n, int Mod) -> int {
        if (n == 0) {
            return 1;
        } else if (n & 1) {
            return (a * rec((a * a) % Mod, n - 1 >> 1, Mod)) % Mod;
        } else {
            return rec((a * a) % Mod, n >> 1, Mod);
        }
    };
    cout << rec(2, n, 1e9 + 7);
    return 0;
}