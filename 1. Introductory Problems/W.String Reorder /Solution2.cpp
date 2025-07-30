#include <bits/stdc++.h>
using namespace std;

string ans;
int co[26];

bool ok()
{
    int sum = 0, mx = 0;
    for (int i = 0; i < (26); i++)
    {
        if (co[i] > co[mx])
            mx = i;
        sum += co[i];
    }
    if (2 * co[mx] <= sum)
        return 1;
    if (2 * co[mx] - 1 == sum && !((int)ans.size() && (ans.back() - 'A') == mx))
        return 1;
    return 0;
}

int main()
{
    string s;
    cin >> s;

    for (auto &t : s)
    {
        co[t - 'A']++;
    }

    if (!ok())
    {
        cout << -1;
        exit(0);
    }
    while ((int)ans.size() < (int)s.size())
    {
        for (int i = 0; i < (26); i++)
            if (co[i])
            {
                if ((int)ans.size() && ans.back() - 'A' == i)
                    continue;
                ans += char('A' + i);
                co[i]--;
                if (ok())
                    break;
                ans.pop_back();
                co[i]++;
            }
    }
    cout << ans;
    return 0;
}