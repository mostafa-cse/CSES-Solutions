#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> a(n);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i - 1].first;
        a[i - 1].second = i;
    }
    sort(a.begin(), a.end());

    for (int i = 0; i < n; i++)
    {
        int target = k - a[i].first;
        auto it = lower_bound(a.begin() + i + 1, a.end(), make_pair(target, 0), [&](pair<int, int> x, pair<int, int> y){
            return x.first < y.first;
        });
        if (it != a.end() && it->first == target)
        {
            cout << a[i].second << " " << it->second << endl;
            return 0;
        }
    }
    cout << "IMPOSSIBLE";
    return 0;
}