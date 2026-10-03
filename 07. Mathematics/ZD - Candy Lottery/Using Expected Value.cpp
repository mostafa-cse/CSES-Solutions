#include <bits/stdc++.h>
#define int long long
using namespace std;
double expo (double a, int p){
    double res = 1;
    while (p) {
        if(p & 1) {
            res = (a * res);
        }
        p >>= 1;
        a = (a * a);
    }
    return res;
}
signed main() {
    int n, k;
    cin >> n >> k;

    double ans = 0;
    for (int i = 1; i <= k; i++) {
        double curProb = expo(i * 1.00 / k, n);
        double preProb = expo((i - 1) * 1.00 / k, n);

        double prob = curProb - preProb;
        ans += (i * prob);
    }
    cout << fixed << setprecision(6) << ans;
    return 0;
}
