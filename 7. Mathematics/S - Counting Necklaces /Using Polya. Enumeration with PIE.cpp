#include<bits/stdc++.h>
#define int long long
using namespace std;

const int MOD = 1e9 + 7;

int modPow (int a, int b) {
    int prod = 1 ;
    while (b > 0) {
        if (b & 1) prod = (prod * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return prod ;
}

int modInv (int a) {
    return modPow (a, MOD - 2) ;
}

int main () {
    int n, m ;
    cin >> n >> m ;

    vector<int> divisors;
    for (int i = 1 ; i * i <= n ; i++) {
        if (n % i == 0) {
            divisors.push_back(i) ;
            if (i * i != n) divisors.push_back(n / i) ;
        }
    }

    int divCnt = divisors.size() ;
    sort(divisors.begin(), divisors.end()) ;
    int res[divCnt] ;
    for (int i = 0 ; i < divCnt ; i++) {
        res[i] = modPow(m, divisors[i]) ;
    }

    int ans = 0;
    for (int i = 0 ; i < divCnt ; i++) {
        for (int j = i + 1 ; j < divCnt ; j ++) {
            if (divisors[j] % divisors[i] == 0) {
                res[j] = (res[j] - res[i] + MOD) % MOD ;
            }
        }
        ans = (ans + res[i] * modInv(divisors[i]) % MOD) % MOD ;
    }
    cout << ans << "\n" ;
    return 0;
}
