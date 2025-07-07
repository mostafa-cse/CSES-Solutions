#include <bits/stdc++.h>
using namespace std;

const int N = 5005;
long long dp[N][N];
long long prefix[N];

long long solve(vector<int>& x, int n) {
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] + x[i - 1];
    }
    
    for (int len = 1; len <= n; len++) {
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            if (l == r) {
                dp[l][r] = x[l];
            } else {
                dp[l][r] = max(x[l] + (prefix[r + 1] - prefix[l + 1]) - dp[l + 1][r], x[r] + (prefix[r] - prefix[l]) - dp[l][r - 1]);
            }
        }
    }
    return dp[0][n - 1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    
    cout << solve(x, n) << "\n";
    return 0;
}
