#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 1e9 + 7;

signed main() {
    int n;
    cin >> n;

    int ans = 0;
    int l = 1;
    function<int(int)> Sum = [](int x) -> int {
        return (x * (x + 1) % Mod) % Mod;
    };
    while (l <= n) {
        int k = n / l;
        int r = n / k;
        ans += ((Sum(r) - Sum(l - 1) + Mod) % Mod * k) % Mod;
        ans %= Mod;
        l = r + 1;
    }
    cout << (ans * (Mod + 1) / 2) % Mod << endl;
    return 0;
}
