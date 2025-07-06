#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int& i : a) {
        cin >> i;
    }
    sort(a.begin(), a.end());

    int sum = 1;
    for (int i = 0; i < n; i++) {
        if (sum < a[i]) {
            cout << sum << endl;
            return 0;
        }
        sum += a[i];
    }

    cout << sum << endl;
    return 0;
}
