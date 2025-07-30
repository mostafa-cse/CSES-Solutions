#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    for (int i = 0; i < (1 << n); i++) {
        int gray = (i ^ (i >> 1));
        bitset<16> b(gray);
        cout << b.to_string().substr(16 - n) << endl;
    }
    return 0;
}