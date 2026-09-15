#include <bits/stdc++.h>
#define int long long
using namespace std;
#define endl "\n"
#define all(x) x.begin(), x.end()
struct SlidingWindowMex {
    set<int> missing;
    map<int, int> cnt;
    SlidingWindowMex(int k) {
        for (int i = 0; i <= k; i++) {
            missing.insert(i);
        }
    }
    void add (int x) {
        if (cnt[x] == 0) {
            missing.erase(x);
        }
        cnt[x]++;
    };
    void remove (int x) {
        cnt[x]--;
        if (cnt[x] == 0) {
            missing.insert(x);
        }
    };
    int MEX () {
        return *missing.begin();
    };
};
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int &i : a) cin >> i;

    SlidingWindowMex mex(k);
    for (int i = 0; i < n; ++i) {
        mex.add(a[i]);
        if (i + 1 >= k) {
            cout << mex.MEX() << " ";
            mex.remove(a[i - k + 1]);
        }
    }
    return 0;
}
