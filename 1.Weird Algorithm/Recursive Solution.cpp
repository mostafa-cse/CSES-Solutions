#include <bits/stdc++.h>
#define int long long
using namespace std;
 
signed main() {
    int n;
    cin >> n;
 
    function<void(int)> rec = [&](int n) -> void {
        if (n == 1) {
            return cout << n, void();
        }
        cout << n << " ";
        if (n % 2 == 0) {
            rec(n / 2);
        } else {
            rec(3 * n + 1);
        }
    };
    rec(n);
    return 0;
}
