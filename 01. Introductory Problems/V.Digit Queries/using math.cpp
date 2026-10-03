#include<bits/stdc++.h>
#define int long long
using namespace std;

long long power(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) {
            res = (res * a);
        }
        a = (a * a);
        b >>= 1;
    }
    return res;
}
void Solve() {
    int n;
    cin >> n;

    int digits = 1;
    int base = 9;
    while (n - base * digits > 0) {
        n -= base * digits;
        base *= 10;
        digits++;
    }

    int dnum = (n - 1) / digits;
    int idx = n % digits;

    int Num = power(10, digits - 1) + dnum;
    if (idx) {
        Num /= power(10, digits - idx);
    }
    cout << Num % 10 << endl;
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);  cout.tie(0);
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        Solve();
    }
    return 0;
}
