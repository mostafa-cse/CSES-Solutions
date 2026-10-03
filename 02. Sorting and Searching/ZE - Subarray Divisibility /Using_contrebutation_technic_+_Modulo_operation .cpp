#include<bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
    ios_base::sync_with_stdio(0); 
    cin.tie(0);  cout.tie(0);
    int ans = 0, n;
    cin >> n;

    map<int, int> mark;
    mark[0] = 1;
    for (int i = 0, x, sum = 0; i < n; ++i) {
        cin >> x;
        sum = ((sum + x) % n + n) % n;
        ans += mark[sum];
        mark[sum]++;
    }
    cout << ans;
    return 0;
}
