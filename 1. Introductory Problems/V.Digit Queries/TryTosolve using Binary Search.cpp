#include <bits/stdc++.h>
#define int long long
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
int expo(int a, int p) {
    int res = 1;
    while (p > 0) {
        if (p & 1) {
            res = res * a;
        }
        a = a * a;
        p >>= 1;
    }
    return res;
}

void solve() {
    int n;
    cin >> n;

    function<int(int)> cnt_digit = [&](int x) -> int {
        int cnt = 0;
        for (int d = 1; d <= 18; d++) {
            int low = expo(10, d - 1);       
            if (low > x)
                break;             
            int high = min(x, expo(10, d) - 1); 
            cnt += (high - low + 1) * (long long)d;
        }
        return cnt;
    };

    int l = 1, r = 1e18, ans = 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (cnt_digit(mid) >= n) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    int pos = cnt_digit(ans) - n;
    string s = to_string(ans);
    cout << s[s.size() - pos - 1] << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc;
    cin >> tc;
    while (tc--) {
        solve();
    }
    return 0;
}
