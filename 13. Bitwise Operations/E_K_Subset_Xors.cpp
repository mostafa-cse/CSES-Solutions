#include <bits/stdc++.h>
#define int long long
using namespace std;
struct XorBasis {
    vector<int> basis;
    int N = 0, tmp = 0;

    void add(int x) {
        N++;
        tmp |= x;
        for (auto &i : basis) {
            x = min(x, x ^ i);
        }

        if(!x) return;

        for(auto &i : basis) {
            if ((i ^ x) < i) {
                i ^= x;
            }
        }
        basis.push_back(x);
        sort(basis.begin(), basis.end());
    }

    int size() {
        return (int)basis.size();
    }

    void clear() {
        N = 0;
        tmp = 0;
        basis.clear();
    }

    bool possible(int x) {
        for (auto &i : basis) {
            x = min(x, x ^ i);
        }
        return !x;
    }

    int maxxor(int x=0) {
        for (auto &i : basis) {
            x = max(x, x ^ i);
        }
        return x;
    }

    int minxor(int x = 0) {
        for (auto &i : basis) {
            x = min(x, x ^ i);
        }
        return x;
    }

    int cntxor(int x) {
        if (!possible(x)) {
            return 0ll;
        }
        return (1ll << (N - size()));
    }

    int sumOfAInt() {
        int ans = tmp * (1ll << (N - 1));
        return ans;
    }

    int kth(int k) {
        int sz = size();
        if (k > (1ll << sz)) {
            return -1;
        }
        k--;
        int ans = 0;
        for (int i = 0; i < sz; i++) {
            if ((k >> i) & 1) {
                ans ^= basis[i];
            }
        }
        return ans;
    }
};
signed main() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    XorBasis xb;
    for (int i : a) {
        xb.add(i);
    }

    int basisSz = xb.size();
    int zerodim = n - basisSz;

    int repeat = 0;
    if (zerodim >= 62) {
        repeat = k + 1;
    } else {
        repeat = 1LL << zerodim;
        if (repeat > k) {
            repeat = k + 1;
        }
    }


    vector<int> ans;
    for (int i = 0; i < k; i++) {
        int pos = (i / repeat) + 1;
        ans.push_back(xb.kth(pos));
    }

    for (int i : ans) {
        cout << i << " ";
    }
    return 0;
}
