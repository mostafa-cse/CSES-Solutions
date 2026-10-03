#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    // using map, set, hashing
    set<int> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        a.insert(x);
    }
    cout << a.size() << endl;
    return 0;
}