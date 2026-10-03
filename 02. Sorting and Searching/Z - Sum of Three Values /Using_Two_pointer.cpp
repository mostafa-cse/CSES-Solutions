#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, S;
    cin >> n >> S;

    vector<pair<int, int>> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a.begin() + 1, a.end());

    for (int i = 1; i + 2 <= n; i++) {
        int l = i + 1, r = n;
        while (l < r) {
            int curSum = a[i].first + a[l].first + a[r].first;
            if (curSum == S) {
                return cout << a[i].second << " " << a[l].second << " " << a[r].second, 0;
            } else if (curSum < S) {
                l++;
            } else {
                r--;
            }
        }
    }
    cout << "IMPOSSIBLE";
    return 0;
}