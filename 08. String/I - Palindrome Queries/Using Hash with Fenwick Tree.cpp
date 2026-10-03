#include <bits/stdc++.h>
#define ll long long
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);cin.tie(NULL)
using namespace std;

ll mod = 1e9 + 7;
struct FenwickTree {
    ll n;
    vector<ll> bit; // binary indexed tree

    FenwickTree(ll n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<ll> const &a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++) {
            add(i, a[i]);
        }
    }

    ll sum(ll r) {
        ll ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret % mod;
    }

    ll sum(ll l, ll r) {
        return sum(r) - sum(l) + mod;
    }

    void add(ll idx, ll delta) {
        delta %= mod;
        if (delta < 0) delta += mod;
        for (; idx < n; idx = idx | (idx + 1)) {
            bit[idx] += delta;
            bit[idx] %= mod;
        }
    }
};

signed main() {
    int n, q;
    cin >> n >> q;

    string s;
    cin >> s;

    FenwickTree forward(n + 3), backward(n + 3);

    ll base = 31;
    vector<ll> p(n + 2, 1);

    for (ll i = 0; i < n + 2; ++i) {
        p[i + 1] = p[i] * base;
        p[i + 1] %= mod;
    }

    for (ll i = 0; i < n; ++i) {
        forward.add(i + 1, (s[i] - 'a' + 1)*p[i]);
        backward.add(i + 1, (s[i] - 'a' + 1) * p[n - i - 1]);
    }

    ll l, r;
    ll type;
    while (q--) {
        cin >> type;

        if (type == 1) {
            ll pos;
            char c;
            cin >> pos >> c;
            pos--;

            forward.add(pos + 1, -((s[pos] - 'a' + 1) * p[pos])); // exclude previous
            forward.add(pos + 1, ((c - 'a' + 1)*p[pos])); // include current

            backward.add(pos + 1, -((s[pos] - 'a' + 1) * p[n - pos - 1])); // exclude previous
            backward.add(pos + 1, ((c - 'a' + 1)*p[n - pos - 1])); // include current

            s[pos] = c;

        } else {
            cin >> l >> r;
            ll front = (forward.sum(l - 1, (l + r) / 2) + mod) % mod;
            front = (front * p[n - r]) % mod;
            
            ll back = backward.sum((l + r - 1) / 2, r) + mod;
            back = (back * p[l - 1]) % mod;

            if (front == back) {
                cout << "YES";
            } else {
                cout << "NO";
            }
            cout << "\n";
        }
    }
}
