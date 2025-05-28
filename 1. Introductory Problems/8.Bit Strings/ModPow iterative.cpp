#include <bits/stdc++.h>
#define int long long
using namespace std;
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
signed main() {
    const int Mod = 1e9 + 7;
    int n;
    cin >> n;
    cout << modexpo(2, n, Mod);
    return 0;
}