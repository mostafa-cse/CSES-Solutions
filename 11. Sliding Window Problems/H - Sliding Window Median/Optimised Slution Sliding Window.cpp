#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    multiset<int> left, right;
    int need = (k + 1) / 2;
    for (int i = 0; i < n; ++i) {
        left.insert(a[i]);

        if (left.size() > need) {
            auto it = prev(left.end());
            right.insert(*it);
            left.erase(it);
        }

        if (i >= k - 1) {
            cout << *left.rbegin() << ' ';
            int x = a[i - k + 1];
            auto it = right.find(x);
            
            if (it != right.end()) {
                right.erase(it);
            } else {
                left.erase(left.find(x));
                if (!right.empty()) {
                    it = right.begin();
                    left.insert(*it);
                    right.erase(it);
                }
            }
        }
    }
    return 0;
}
