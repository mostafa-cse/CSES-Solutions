#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, k;
    cin >> n >> k;

    vector<int> num(n);
    for (int &i : num) {
        string s;
        cin >> s;
        i = stol(s, 0, 2);
    }

    int32_t ans = 30;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dis = num[i] ^ num[j];
            ans = min(ans, __builtin_popcount(dis));
        }
    }
    cout << ans << endl;
    return 0;
}
