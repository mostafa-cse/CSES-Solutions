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

    auto f = [&](int target) -> int{
        int cnt = 1;
        for (int i = 0, sum = 0; i < n; i++) {
            sum += a[i];
            if (sum > target) {
                cnt++;
                sum = a[i];
            }
        }
        return cnt;
    };

    int l = *max_element(all(a)), r = accumulate(all(a), 0ll), ans = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;

        if (f(mid) <= k) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans;
    return 0;
}
