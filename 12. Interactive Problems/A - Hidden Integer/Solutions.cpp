#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
string query(int val) {
    cout << "? " << val << endl;
    string s;
    cin >> s;

    return s;
}
signed main() {
    int n;

    int l = 1, r = 1e9;
    while (l <= r) {
        int mid = l + r >> 1;

        if (l == r) {
            cout << "! " << l << endl;
            break;
        }
        if (query(mid) == "YES") {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    return 0;
}

