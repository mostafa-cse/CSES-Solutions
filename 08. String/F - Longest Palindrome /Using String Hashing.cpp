#include <bits/stdc++.h>
using namespace std;
using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const ll M = 991831889;
const ll C = 239;

struct HashString {
    int n;
    vector<ll> pows, sums;

    HashString(const string &s) : n((int)s.size()), pows(n + 1, 1), sums(n + 1) {
        for (int i = 1; i <= n; i++) {
            pows[i] = pows[i - 1] * C % M;
            sums[i] = (sums[i - 1] * C + s[i - 1]) % M;
        }
    }

    ll hash(int l, int r) const {
        ll h = sums[r] - sums[l] * pows[r - l] % M;
        if (h < 0) h += M;
        return h;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;

    int n = (int)s.size();
    string t = s;
    HashString front(s);

    reverse(t.begin(), t.end());
    HashString back(t);

    auto is_pal_len = [&](int len) -> bool {
        if (len < 0 || len > n) return false;
        for (int i = 0; i + len <= n; i++) {
            int l = i;
            int r = i + len;
            int rl = n - r;
            int rr = n - l;
            if (front.hash(l, r) == back.hash(rl, rr)) {
                return true;
            }
        }
        return false;
    };

    int ans = 1;
    int l = 0, r = n / 2;
    while (l <= r) {
        int mid = (l + r) >> 1;
        int len = mid * 2;
        if (is_pal_len(len)) {
            ans = len;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    l = 0;
    r = (n - 1) / 2;
    while (l <= r) {
        int mid = (l + r) >> 1;
        int len = mid * 2 + 1;
        if (is_pal_len(len)) {
            ans = max(ans, len);
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    for (int i = 0; i + ans <= n; i++) {
        int l0 = i;
        int r0 = i + ans;
        int rl = n - r0;
        int rr = n - l0;
        if (front.hash(l0, r0) == back.hash(rl, rr)) {
            cout << s.substr(i, ans) << '\n';
            return 0;
        }
    }
    return 0;
}
