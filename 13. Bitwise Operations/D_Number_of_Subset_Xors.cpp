#include <bits/stdc++.h>
#define int long long
using namespace std;
struct XorBasis {
    vector<int> basis;
    int N=0, tmp=0;

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
    int n;
    cin >> n;

    vector<int> a(n);
    XorBasis xb;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        xb.add(a[i]);
    }
    cout << (1LL << xb.size()) << endl;
    return 0;
}

