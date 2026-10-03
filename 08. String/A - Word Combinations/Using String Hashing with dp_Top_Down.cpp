/*
Author : M0stafa
Topic : String Algorithm
Algorithm : String Hashing with DP
DP trick : Top-Down approach
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
const int Mod = 1e9 + 7;
const int Z = 1111111111111111111;  // Z is a prime.
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int C = uniform_int_distribution<int>(Z / 10, Z / 10 * 9)(rng);
struct HashString {
    int n;
    vector<int> pows, sums;

    int mul(int a, int b) {
        return __int128(a) * b % Z;
    }
    HashString(string s) : n(s.size()), pows(n + 1, 1), sums(n + 1) {
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
const int M = 1e6 + 1;
int len[M];
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    string s;
    cin >> s;
    HashString hs(s);

    int n = s.size();

    int q;
    cin >> q;

    unordered_set<int> mset;
    for (int i = 0; i < q; i++) {
        string t;
        cin >> t;
        len[t.size()] = 1;
        HashString ht(t);
        mset.insert(ht.hash(1, t.size()));
    }

    vector<int> dp(n + 2, 0);
    dp[1] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            if (len[j - i + 1] and mset.count(hs.hash(i, j))) {
                dp[j + 1] = (dp[j + 1] + dp[i]) % Mod;
            }
        }
    }
    cout << dp[n + 1];
    return 0;
}

