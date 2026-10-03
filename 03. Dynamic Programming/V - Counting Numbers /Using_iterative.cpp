#include <bits/stdc++.h>
#define int long long
using namespace std;

int count(string num) {
    int n = num.size();
    int dp[20][2][11][2] = {};
    dp[0][1][10][0] = 1;
    for (int pos = 0; pos < n; pos++) {
        for (int tight = 0; tight <= 1; tight++) {
            for (int prev = 0; prev <= 10; prev++) {
                for (int started = 0; started <= 1; started++) {
                    int ways = dp[pos][tight][prev][started];
                    if (!ways)
                        continue;
                    int ub = tight ? (num[pos] - '0') : 9;
                    for (int d = 0; d <= ub; d++) {
                        if (started && d == prev)
                            continue;
                        int nstarted = started || d != 0;
                        int nprev = nstarted ? d : 10;
                        int ntight = tight && (d == ub);
                        dp[pos + 1][ntight][nprev][nstarted] += ways;
                    }
                }
            }
        }
    }
    int res = 0;
    for (int tight = 0; tight <= 1; tight++)
        for (int prev = 0; prev <= 10; prev++)
            res += dp[n][tight][prev][1];
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int x, y;
    cin >> x >> y;
    string b = to_string(y);
    if (x == 0) {
        cout << count(b) + 1;
    } else {
        string x_minus_1 = to_string(x - 1);
        while (x_minus_1.size() < b.size())
            x_minus_1 = '0' + x_minus_1;
        cout << count(b) - count(x_minus_1);
    }
    return 0;
}
