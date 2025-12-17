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

signed main() {
    string s;
    cin >> s;

    string sr = s;
    reverse(sr.begin(), sr.end());

    HashString hs(s), rhs(sr);

    int n = s.size();
    vector<int> ans(n, 0);

    for (int i = 0; i < n; i++) {

        // for odd length
        int l = 0, r = min(i, n - i);
        while (l <= r) {
            int mid = (l + r) >> 1;
            // for default string
            int L = i - mid;
            int R = i + mid;

            // for reverse string
            int rL = n - R - 1;
            int rR = n - L - 1;

            if (hs.hash(L + 1, R + 1) == rhs.hash(rL + 1, rR + 1)) {
                l = mid + 1;
                ans[i + mid] = max(ans[i + mid], 2 * mid + 1);
            } else {
                r = mid - 1;
            }
        }
        // for even length
        l = 1, r = min(i + 1, n - i - 1);
        while (l <= r) {
            int mid = (l + r) >> 1;
            // for default string
            int L = i - mid + 1;
            int R = i + mid;
            // for reverse string
            int rL = n - R - 1;
            int rR = n - L - 1;

            if (hs.hash(L + 1, R + 1) == rhs.hash(rL + 1, rR + 1)) {
                l = mid + 1;
                ans[i + mid] = max(ans[i + mid], 2 * mid);
            } else {
                r = mid - 1;
            }
        }

    }
    for (int i = n - 1; i > 0; i--) {
        ans[i - 1] = max(ans[i - 1], ans[i] - 2);
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
