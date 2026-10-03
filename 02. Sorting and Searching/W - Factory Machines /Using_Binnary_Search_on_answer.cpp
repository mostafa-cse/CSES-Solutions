#include<bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()

int32_t main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);  cout.tie(0);
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }

    int l = 0, r = 1e18, ans = -1;
    while (l <= r) {
        __int128_t mid = (l + r) / 2;

        __int128_t tot = 0;
        for (int p : a) {
            tot += (int)mid / p;
        }

        if (tot >= k) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans;
    return 0;
}
