// Runtime Error Solution 
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, k, price[1001], page[1001], dp[1001][100001];
int memoi(int N, int k) {
    if (k < 0) return LLONG_MIN;
    if (N == 0) return 0;
    int &res = dp[N][k];
    if (res != -1) return res;
    res = memoi(N - 1, k);
    if (k >= price[N - 1]) {
        res = max(res, page[N - 1] + memoi(N - 1, k - price[N - 1]));
    }
    return res;
}
int32_t main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> price[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> page[i];
    }
    memset(dp, -1, sizeof dp);
    cout << memoi(n, k) << '\n';
    return 0;
}