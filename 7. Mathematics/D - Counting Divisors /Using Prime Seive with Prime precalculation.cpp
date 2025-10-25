#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e6 + 123;
bool is_prime[MAXN];
vector<int> p;
auto prime_sieve = []() {
    for (int i = 3; i < MAXN; i += 2) {
        is_prime[i] = true;
    }
    is_prime[2] = true;
    for (int i = 3; i * i <= MAXN; i += 2) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAXN; j += i) {
                is_prime[j] = false;
            }
        }
    }
    for (int i = 2; i < MAXN; i++) {
        if (is_prime[i]) {
            p.push_back(i);
        }
    }
    return 0;
}();
void solve() {
    int x;
    cin >> x;

    if (is_prime[x]) {
        cout << 2 << endl;
    } else {
        int ans = 1;
        for (auto el : p) {
            if (el * el > x) break;
            int cnt = 0;
            while (x % el == 0) {
                cnt++;
                x /= el;
            }
            ans *= (cnt + 1);
        }

        if (x > 1) {
            ans *= 2;
        }
        cout << ans << endl;
    }
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
