#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
int n;
int query(int flag, int x) {
    if (x > n) return 0;
    if (x == 0) return 2e9;
    cout << (flag == 1 ? "F " : "S ") << x << endl;

    int s;
    cin >> s;

    return s;
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int k;
    cin >> n >> k;

    int l = 0, r = min(k, n);
    int ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;

        int a = query(1, mid);
        int b = query(2, k - mid + 1);

        if (a < b) {
            r = mid - 1;
        } else {
            ans = min(a, query(2, k - mid));
            l = mid + 1;
        }
    }
    cout << "! " << ans << endl;
    return 0;
}

