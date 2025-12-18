#include <bits/stdc++.h>
#define int long long
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int M = 991831889;
const int C = uniform_int_distribution<int>(0.1 * M, 0.9 * M)(rng);

struct HashTree {
    struct Hash {
        int hash = 0;
        int mul = 1;

        Hash operator+(Hash other) {
            return {(hash * other.mul + other.hash) % M, mul * other.mul % M};
        }
    };

    int n;
    vector<Hash> tree;

    HashTree(string s) {
        n = 1;
        while (n < s.size()) n *= 2;
        tree.resize(2 * n);
        for (int i = 0; i < s.size(); i++) {
            tree[n + i] = {s[i], C};
        }
        for (int i = n - 1; i >= 1; i--) {
            tree[i] = tree[2 * i] + tree[2 * i + 1];
        }
    }

    void set(int k, char x) {
        k += n;
        tree[k] = {x, C};
        for (k /= 2; k >= 1; k /= 2) {
            tree[k] = tree[2 * k] + tree[2 * k + 1];
        }
    }

    int hash(int l, int r) {
        l += n;
        r += n;
        Hash left, right;
        while (l <= r) {
            if (l % 2 == 1) left = left + tree[l++];
            if (r % 2 == 0) right = tree[r--] + right;
            l /= 2;
            r /= 2;
        }
        return (left + right).hash;
    }
};
signed main() {
    int n, m;
    cin >> n >> m;

    string s;
    cin >> s;

    HashTree fwd(s);

    reverse(s.begin(), s.end());
    HashTree bwd(s);

    while (m--) {
        int t;
        cin >> t;

        if (t == 1) {
            int k;
            char x;
            cin >> k >> x;

            fwd.set(k - 1, x);
            bwd.set(n - k, x);
        } else {
            int l, r;
            cin >> l >> r;

            if (fwd.hash(l - 1, r - 1) == bwd.hash(n - r, n - l)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}
