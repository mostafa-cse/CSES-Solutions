#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<pair<int, int>> a(n);
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i].first >> a[i].second;
    }

    sort(a.begin(), a.end());
    int ans = 0;
    for (auto b : a)
    {
        while (!q.empty() && q.top() < b.first)
        {
            q.pop();
        }
        q.push(b.second);
        ans = max(ans, (int)q.size());
    }

    cout << ans << endl;
    return 0;
}