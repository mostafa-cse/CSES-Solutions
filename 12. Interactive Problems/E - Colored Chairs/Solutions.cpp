#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
char ask(int m) {
    cout << "? " << m << endl;
    char c;
    cin >> c;
    return c;
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n;
    cin >> n;
    char inital = ask(1);
    int l = 2, r = n, ans = n;
    while (l <= r) {
        int mid = (l + r) >> 1;

        if ((ask(mid) != inital) ^ (mid & 1) ^ 1) {
            ans = mid - 1;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << "! " << ans << endl;
    return 0;
}

