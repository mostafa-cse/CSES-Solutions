#include <bits/stdc++.h>
#define int long long
using namespace std;
template<int MOD, int RT> struct mint {
	static const int mod = MOD;
	static constexpr mint rt() { return RT; } // primitive root for FFT
	int v; explicit operator int() const { return v; } // explicit -> don't silently convert to int
	mint():v(0) {}
	mint(int _v) { v = (-MOD < _v && _v < MOD) ? _v : _v % MOD; if (v < 0) v += MOD; }
	bool operator==(const mint& o) const { return v == o.v; }
	friend bool operator!=(const mint& a, const mint& b) { return !(a == b); }
	friend bool operator<(const mint& a, const mint& b) { return a.v < b.v; }
	mint& operator+=(const mint& o) { if ((v += o.v) >= MOD) v -= MOD; return *this; }
	mint& operator-=(const mint& o) { if ((v -= o.v) < 0) v += MOD; return *this; }
	mint& operator*=(const mint& o) { v = (v * o.v % MOD); return *this; }
    mint& operator/=(const mint& o) { return (*this) *= inv(o); }
	friend mint pow(mint a, int p) { mint ans = 1; for (; p; p /= 2, a *= a) if (p&1) ans *= a; return ans; }
    friend mint inv(const mint &a) { return pow(a, MOD - 2);}
    mint operator-() const { return mint(-v); }
	mint& operator++() { return *this += 1; }
	mint& operator--() { return *this -= 1; }
	friend mint operator+(mint a, const mint& b) { return a += b; }
	friend mint operator-(mint a, const mint& b) { return a -= b; }
	friend mint operator*(mint a, const mint& b) { return a *= b; }
	friend mint operator/(mint a, const mint& b) { return a /= b; }
};
using Mint = mint<(int)1e9+7, 5>;
signed main() {
    int n;
    cin >> n;

    Mint ans = 0;
    for (int i = 1; i * i <= n; i++) {
        Mint l = i;
        Mint r = n / i;
        Mint len = r - l + 1;
        const int K = i;

        // a divisor compose according to n = i * (n / i)

        // add len times appear of K between [1, N]
        Mint proper = len * K;

        // add another that [n / i], 'l' has counted at 'proper' as before
        l += 1;
        Mint range = (l + r) * (r - l + 1) / 2;

        ans = ans + proper + range;
    }

    cout << ans.v << endl;
    return 0;
}
