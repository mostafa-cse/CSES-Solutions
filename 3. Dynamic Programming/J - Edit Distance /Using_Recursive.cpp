#include<bits/stdc++.h>
#define int long long
using namespace std;

vector<vector<int>> dp(5005, vector<int>(5005, -1));
int Memoiation (string &a, int i, int j, string &b) {
    if (i < 0 or j < 0) {
        if (i < 0) return j + 1;
        else return i + 1;
    } else if(dp[i][j] != -1) {
        return dp[i][j];
    } else if (a[i] == b[j]) {
        return dp[i][j] = Memoiation(a, i - 1, j - 1, b);
    } else {
        int insert = 1 + Memoiation(a, i - 1, j, b);
        int del = 1 + Memoiation(a, i, j - 1, b);
        int replace = 1 + Memoiation(a, i - 1, j - 1, b);
        return dp[i][j] = min({insert, del, replace});
    }
}
int32_t main() {
    string a, b;
    cin >> a >> b;
    int ans = Memoiation(a, a.size() - 1, b.size() - 1, b);
    cout << ans << endl;
    return 0;
}