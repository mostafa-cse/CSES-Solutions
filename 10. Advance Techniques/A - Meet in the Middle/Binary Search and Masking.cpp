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

    vector<int> a, b;
    for (int i = 0; i < n / 2; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }

    for (int i = n / 2; i < n; i++) {
        int y;
        cin >> y;
        b.push_back(y);
    }

    vector<int> aS;
    for (int mask = 0; mask < (1 << a.size()); mask++) {
        int sum = 0;
        for (int i = 0; i < a.size(); i++) {
            if (mask >> i & 1) {
                sum += a[i];
            }
        }
        aS.push_back(sum);
    }

    vector<int> bS;
    for (int mask = 0; mask < (1 << b.size()); mask++) {
        int sum = 0;
        for (int i = 0; i < b.size(); i++) {
            if (mask >> i & 1) {
                sum += b[i];
            }
        }
        bS.push_back(sum);
    }

    sort(all(aS));
    sort(all(bS));

    int ans = 0;
    for (int i = 0; i < aS.size(); i++) {
        int remSum  = k - aS[i];

        int low = lower_bound(all(bS), remSum) - bS.begin();
        int high = upper_bound(all(bS), remSum) - bS.begin();

        ans += (high - low);
    }
    cout << ans << endl;
    return 0;
}
