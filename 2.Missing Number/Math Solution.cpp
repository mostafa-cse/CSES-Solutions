#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    int sum = n * (n + 1) >> 1;
    for (int i = 1; i < n; i++) {
        int x;
        cin >> x;
        sum -= x;
    }
    cout << sum << endl;
    return 0;
}
