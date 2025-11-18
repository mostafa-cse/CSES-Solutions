#include <iostream>
using namespace std;
const int MOD = 1000000007; 

// Fast doubling recursive Fibonacci
pair<long long, long long> fib(long long n) {
    if (n == 0) return {0, 1}; // Base cases
    auto p = fib(n / 2);
    long long a = p.first, b = p.second;
    long long c = (a * ((2 * b % MOD - a + MOD) % MOD)) % MOD; // F(2k)
    long long d = (a * a % MOD + b * b % MOD) % MOD;           // F(2k+1)
    if (n % 2 == 0)
        return {c, d};      // Even case
    else
        return {d, (c + d) % MOD}; // Odd case
}

int main() {
    long long n;
    cin >> n;
    cout << fib(n).first << "\n";
    return 0;
}
