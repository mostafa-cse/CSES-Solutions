#include <bits/stdc++.h>
#define int long long
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
void solve() {
    int n;
    cin >> n;

    set<int> s;
    for (int i= 0 ; i < n; i++) {
        int x;
        cin >> x;
        s.insert(x);
    }
    dout(s);
    if (s.count(s.size())) {
        cout << s.size() << endl;
    } else {
        int size = s.size();
        int up = *s.upper_bound(size);

        int add = up - size;

        cout << add + size << endl;
    }
}
signed main() {
    int tc;
    cin >> tc;

    for (int t = 1; t <= tc; t++) {
        // cout << "Case " << t << ": ";
        solve();
    }
    return 0;
}
