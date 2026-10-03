#include <bits/stdc++.h>
using namespace std;
using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const ll M = 991831889;
const ll C = uniform_int_distribution<ll>(0.1 * M, 0.9 * M)(rng);

struct HashString {
    int n;
    vector<ll> pows, sums;

    HashString(string s) : n(s.size()), pows(n + 1, 1), sums(n + 1) {
        for (int i = 1; i <= n; i++) {
            pows[i] = pows[i - 1] * C % M;
            sums[i] = (sums[i - 1] * C + s[i - 1]) % M;
        }
    }

    // Returns the hash of the substring [l, r)
    ll hash(int l, int r) {
        ll h = sums[r] - sums[l] * pows[r - l];
        return (h % M + M) % M;
    }
};

int main() {
    string s;
    cin >> s;
    int n = s.size();
    s = s + s;

    HashString h(s);

    auto cmp = [&](int a, int b) {
        int len = 0;
        for (int add = n; add >= 1; add /= 2) {
            while (len + add < n) {
                ll hash1 = h.hash(a, a + len + add);
                ll hash2 = h.hash(b, b + len + add);
                if (hash1 != hash2) break;
                len += add;
            }
        }
        return s[a + len] > s[b + len];
    };

    int pos = 0;
    for (int i = 1; i < n; i++) {
        if (cmp(pos, i)) pos = i;
    }
    cout << s.substr(pos, n) << "\n";
}
