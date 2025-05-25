#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    int Xor = n;
    for (int i = 1; i < n; i++) {
        int x;
        cin >> x;
        Xor ^= x;
        Xor ^= i;
    }
    cout << Xor << endl;
    return 0;
}
