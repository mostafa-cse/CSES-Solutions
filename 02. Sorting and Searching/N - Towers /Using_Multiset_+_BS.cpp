#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    multiset<int> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        auto it = a.upper_bound(x);
        if (it == a.end()) a.insert(x);
        else {
            a.erase(it);
            a.insert(x);
        }
    }
    cout << a.size();
    return 0;
}