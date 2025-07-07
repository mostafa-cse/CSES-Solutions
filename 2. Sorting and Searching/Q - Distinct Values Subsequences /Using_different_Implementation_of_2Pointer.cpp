#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MOD 1000000007

signed main()
{
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a.begin(), a.end());

    int ans = 1, cnt = 1;
    for (int i = 1; i < n; i++)
    {
        if (a[i] == a[i - 1])
            cnt++;
        else
        {
            ans = (ans * (cnt + 1)) % MOD;
            cnt = 1;
        }
    }
    ans = (ans * (cnt + 1)) % MOD;
    cout << ans - 1 << endl;
    return 0;
}
