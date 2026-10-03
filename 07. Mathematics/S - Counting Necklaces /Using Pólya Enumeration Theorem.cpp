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
const int M = 2e6 + 6;
int Phi[M];
void seivePhi() {
    for (int i = 1; i < M; i++) Phi[i] = i;

    for (int i = 2; i < M; i++) {
        if (Phi[i] == i) {
            for (int j = i; j < M; j += i) {
                Phi[j] = Phi[j] * (i - 1) / i;
            }
        }
    }
}
int inverse(int x) {
    return modexpo(x, Mod - 2, Mod);
}
signed main() {
    seivePhi();
    int n, k;
    cin >> n >> k;


    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            ans += Phi[i] * modexpo(k, n / i, Mod);
            ans %= Mod;
        }
    }
    ans = (ans * inverse(n)) % Mod;
    cout << ans << endl;
    return 0;
}
