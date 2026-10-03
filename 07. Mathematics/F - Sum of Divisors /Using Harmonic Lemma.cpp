#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 1e9 + 7;

signed main() {
    int n;
    cin >> n;

    int ans = 0;
    function<int(int)> Sum = [](int x) -> int {
        if (x <= 0) return 0;
        x %= Mod;
        return (x * (x + 1) % Mod) % Mod;
    };
    int left = 1;
    while (left <= n) {
        int constVal = n / left;
        int right = n / constVal;
        ans += ((Sum(right) - Sum(left - 1) + Mod) % Mod * constVal) % Mod;
        ans %= Mod;
        left = right + 1;
    }
    cout << (ans * (Mod + 1) / 2) % Mod << endl;
    return 0;
}
