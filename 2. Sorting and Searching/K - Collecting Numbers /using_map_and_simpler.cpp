#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    int n;
    cin >> n;

    vector<int> x(n);
    map<int, int> pos;

    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
        pos[x[i]] = i;
    }

    int ans = 1;
    for (int i = 1; i < n; i++)
    {
        if (pos[i] > pos[i + 1])
        {
            ans++;
        }
    }

    cout << ans << endl;
    return 0;
}