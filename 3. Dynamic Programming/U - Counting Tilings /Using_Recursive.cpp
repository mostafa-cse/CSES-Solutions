#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
const int MAXN = 10;
const int MAXM = 1000;

int sum(int a, int b)
{
    return a + b >= MOD ? a + b - MOD : a + b;
}

int n, m;
int mxBit;
int dp[MAXN][MAXM][1 << MAXN];
int solve(int i, int j, int msk)
{
    if (i == n)
        return solve(0, j + 1, msk);
    if (j == m)
        return msk == 0;
    if (dp[i][j][msk] != -1)
        return dp[i][j][msk];

    int ans = 0;
    if ((msk & 1) == 0)
    {
        ans = sum(ans, solve(i + 1, j, (msk >> 1) | mxBit));
        if (i > 0 && (msk & mxBit) > 0)
        {
            ans = sum(ans, solve(i + 1, j, (msk ^ mxBit) >> 1));
        }
    }
    else
    {
        ans = sum(ans, solve(i + 1, j, msk >> 1));
    }

    return dp[i][j][msk] = ans;
}

int main()
{
    cin >> n >> m;
    mxBit = 1 << (n - 1);

    memset(dp, -1, sizeof dp);
    cout << solve(0, 0, 0) << "\n";
    return 0;
}