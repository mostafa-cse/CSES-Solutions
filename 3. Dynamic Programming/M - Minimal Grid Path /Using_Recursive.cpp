#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    int n;
    cin >> n;

    vector<vector<char>> g(n, vector<char>(n));
    for (auto &sub : g)
    {
        for (char i : sub)
        {
            cin >> i;
        }
    }

    function<string(int, int)> rec = [&](int i, int j) -> string {
        if (i >= n or j >= n)
            return "zzzzzzzzzzzzzzz";

        
    };
    cout << rec(0, 0);
    return 0;
}