#include <bits/stdc++.h>
#define int long long
using namespace std;
const int M = 1e6 + 1;
int derangement[M];
const int Mod = 1e9 + 7;
signed main() {
    int n;
    cin >> n;

    derangement[1] = derangement[0] = 0;
    derangement[2] = 1;
    for (int i = 3; i <= n; i++) {
        derangement[i] = (i - 1) * (derangement[i - 1] + derangement[i - 2]);
        derangement[i] %= Mod;
    }
    cout << derangement[n];
    return 0;
}
