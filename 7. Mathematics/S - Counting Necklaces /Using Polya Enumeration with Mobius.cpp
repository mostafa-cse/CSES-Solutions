#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;

long long binpow(long long a, long long b, long long m=MOD) {
    long long res = 1 % m;
    a %= m;
    while (b > 0) {
        if (b & 1) res = (res * a) % m;
        a = (a * a) % m;
        b >>=1;
    }
    return res;
}

long long modInverse(long long a, long long m=MOD) {
    return binpow(a, m-2, m);
}

vector<long long> getDivisors(long long x) {
    vector<long long> divs;
    for (long long i = 1; i * i <= x; i++) {
        if (x % i == 0) {
            divs.push_back(i);
            if (i != x / i) {
                divs.push_back(x / i);
            }
        }
    }
    sort(divs.begin(), divs.end());
    return divs;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m;
    cin >> n >> m;

    auto divisors = getDivisors(n);
    std::vector<long long> dp(divisors.size());

    for (size_t i=0; i<divisors.size(); i++) {
        dp[i] = binpow(m, divisors[i]);
    }

    for (size_t i=0; i<divisors.size(); i++) {
        for (size_t j=0; j<i; j++) {
            if (divisors[i] % divisors[j] == 0) {
                dp[i] = (dp[i] - dp[j] + MOD) % MOD;
            }
        }
    }

    long long answer = 0;
    for (size_t i=0; i<divisors.size(); i++) {
        long long inv_div = modInverse(divisors[i]);
        answer = (answer + dp[i] * inv_div) % MOD;
    }
    cout << answer << "\n";
    return 0;
}
