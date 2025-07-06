#include <bits/stdc++.h>
using namespace std;
#define int long long
int32_t main() {
    int n;
    cin >> n;
    vector<int> v(n);
    vector<int> prefixSum(n + 1, 0), suffixSum(n + 1, 0);

    for (int i = 0; i < n; i++)
        cin >> v[i];
    sort(v.begin(), v.end());

    for (int i = 1; i <= n; i++)
        prefixSum[i] = prefixSum[i - 1] + v[i - 1];

    for (int i = n - 1; i >= 0; i--)
        suffixSum[i] = suffixSum[i + 1] + v[i];

    int ans = (1ll << 62);
    for (int i = 0; i < n; i++) {
        int leftCost = v[i] * i - prefixSum[i];
        int rightCost = suffixSum[i + 1] - v[i] * (n - i - 1);
        ans = min(ans, leftCost + rightCost);
    }

    cout << ans << endl;
    return 0;
}