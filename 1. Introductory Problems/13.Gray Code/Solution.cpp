#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;
    
    for (int mask = 0; mask < (1 << n); mask++) {
        int gray = (mask ^ (mask >> 1));
        for (int b = n - 1; b >= 0; b--) {
            cout << (gray >> b & 1);
        }
        cout << endl;
    }
    return 0;
}