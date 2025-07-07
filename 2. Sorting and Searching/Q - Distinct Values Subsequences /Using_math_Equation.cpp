#include <bits/stdc++.h>
using namespace std;
#define int long long
const int T = 2e5 + 10, mod = 1e9 + 7;
int n, a[T];
map<int, int> cnt;
int modexpo(int a, int p, int mod)
{
    int res = 1;
    while (p)
    {
        if (p & 1)
        {
            res = (a * res) % mod;
        }
        p >>= 1;
        a = (a * a) % mod;
    }
    return res;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    
    int ans = 1;
    for (int i = 1; i <= n; i++)
    {
        cnt[a[i]]++;
        ans = ans * modexpo(cnt[a[i]], mod - 2, mod) % mod * (cnt[a[i]] + 1) % mod;
    }
    ans = (ans - 1 + mod) % mod;
    cout << ans;

    return 0;
}