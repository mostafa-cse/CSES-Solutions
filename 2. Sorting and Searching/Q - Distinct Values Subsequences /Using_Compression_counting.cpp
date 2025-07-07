#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 2e5 + 5, mod = 1e9 + 7;
int n, a[N], b[N], p[N], ans = 1;
signed main()
{
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }

    sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; i++)
    {
        a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b; // just compression to 1e9 to index
        p[a[i]]++;
    }
    for (int i = 1; i <= n; i++)
        ans = ans * (p[i] + 1) % mod;
    cout << ((ans + mod - 1) % mod);
    return 0;
}
