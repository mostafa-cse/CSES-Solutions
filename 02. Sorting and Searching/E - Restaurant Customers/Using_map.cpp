#include <bits/stdc++.h>
using namespace std;

bool sortbyCond2(const pair<int, int> &A, const pair<int, int> &B)
{
    return (A.second > B.second); // decreasing second value
}

bool sortbyCond1(const pair<int, int> &A, const pair<int, int> &B)
{
    if (A.first != B.first)
        return (A.first < B.first); // increasing first value
}

int main()
{

    long long int l, r = 0, n, m = 0, sum = 0, ans = 0;
    map<long long int, long long int> mp;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> l >> r;
        mp[l]++;
        mp[r]--;
    }
    
    for (const auto &p : mp)
    {
        sum += p.second;
        ans = max(ans, sum);
    }
    cout << ans;
    return 0;
}