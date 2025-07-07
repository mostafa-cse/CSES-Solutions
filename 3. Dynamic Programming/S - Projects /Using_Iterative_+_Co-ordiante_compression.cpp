#include<bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
 
    map<int, int> compress;
    int a[n], b[n], p[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i] >> p[i];
        b[i]++;
        compress[a[i]], compress[b[i]];
    }
 
    int cord = 0;
    for (auto &[X, idx] : compress) {
        idx = cord++;
    }
 
    vector<vector<pair<int, int>>> project(cord);
    for (int i = 0; i < n; i++) {
        project[compress[b[i]]].emplace_back(compress[a[i]], p[i]);
    }
 
    vector<int> dp(cord, 0);
    for (int i = 0; i < cord; i++) {
        if (i) dp[i] = dp[i - 1];
 
        for (auto &[A, P] : project[i]) {
            dp[i] = max(dp[i], dp[A] + P);
        }
    }
    cout << dp[cord - 1] << endl;
    return 0;
}