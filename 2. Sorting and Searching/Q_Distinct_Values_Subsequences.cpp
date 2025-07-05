#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 1e9 + 7;
signed main()
{
    int n;
    cin >> n;

    map<int, int> cnt;
    for (int i = 0; i < n; i++)
    {
        int x; cin >> x;
        cnt[x]++;
    }

    int ans = 1;
    for (auto [f, s] : cnt)
    {
        ans = (ans * (s + 1)) % Mod;
    }
    cout << (ans - 1 + Mod) % Mod << endl;
    return 0;
}