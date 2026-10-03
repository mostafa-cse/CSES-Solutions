#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> a(n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i - 1].first;
        a[i - 1].second = i;
    }
    sort(a.begin(), a.end());

    int l = 0, r = n - 1;
    while (l < r) {
        int sum = a[l].first + a[r].first;
        if (sum == k) {
            return cout << a[l].second << " " << a[r].second << endl, 0;
        } else if (sum > k) {
            r--;
        } else {
            l++;
        }
    }
    cout << "IMPOSSIBLE";
    return 0;
}