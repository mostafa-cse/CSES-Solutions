/*
    Author : M0stafa
    Topic : String Algorithm
    Algorithm : String Hashing
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int Z = 1111111111111111111;  // Z is a prime.
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int C = uniform_int_distribution<int>(Z / 10, Z / 10 * 9)(rng);
struct HashString {
    int n;
    vector<int> pows, sums;

    int mul(int a, int b) {
        return __int128(a) * b % Z;
    }
    HashString(string s) : n(s.size()), pows(n + 1, 1), sums(n + 1, 0) {
        for (int i = 1; i <= n; i++) {
            pows[i] = mul(pows[i - 1], C);
            sums[i] = (mul(sums[i - 1], C) + s[i - 1]) % Z;
        }
    }
    // Returns the hash of the substring [l, r) [1-based]
    int hash(int l, int r) {
        int h = sums[r] - mul(sums[l - 1], pows[r - l + 1]);
        return (h % Z + Z) % Z;
    }
};
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    string line, pat;
    cin >> line >> pat;

    HashString patHash(pat), lineHash(line);

    int pattern = patHash.hash(1, pat.size());

    int ans = 0;
    for (int i = 0; i + pat.size() <= line.size(); i += 1) {
        int l = i + 1;
        int r = i + pat.size();
        ans += lineHash.hash(l, r) == pattern;
    }
    cout << ans;
    return 0;
}
