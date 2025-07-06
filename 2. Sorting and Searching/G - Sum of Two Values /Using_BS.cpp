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

    for (int i = 0; i < n; i++) {
        int target = k - a[i].first;
        int l = i + 1, r = n - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (a[mid].first == target) {
                cout << a[i].second << " " << a[mid].second << endl;
                return 0;
            } else if (a[mid].first < target) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }
    cout << "IMPOSSIBLE";
    return 0;
}
