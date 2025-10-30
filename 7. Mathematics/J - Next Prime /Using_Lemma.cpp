#include <bits/stdc++.h>
#define int long long
using namespace std;
const int M = 1e6 + 5;
int mark[M];
vector<int> primes;
void Seive() {
    for (int i = 0; i < M; i++) {
        mark[i] = 1;
    }

    mark[0] = mark[1] = 0;
    for (int i = 2; i * i <= M; i++) {
        if (mark[i]) {
            for (int j = i * i; j < M; j += i) {
                mark[j] = 0;
            }
        }
    }

    for (int i = 2; i < M; i++) {
        if (mark[i]) {
            primes.push_back(i);
        }
    }
}
void solve() {
    int n;
    cin >> n;

    n++;
    while (true) {
        bool ok = true;
        for (int el : primes) {
            if (el * el > n) {
                break;
            }

            if (n % el == 0) {
                ok = false;
                break;
            }
        }

        if (ok) {
            cout << n << endl;
            return;
        }
        n++;
    }
}
signed main() {
    Seive();
    int tc;
    cin >> tc;

    for (int t = 1; t <= tc; t++) {
        // cout << "Case " << t << ": ";
        solve();
    }
    return 0;
}
