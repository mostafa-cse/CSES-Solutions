#include <bits/stdc++.h>
#define int long long
using namespace std;

int n, la, A[26 + 10];
string s, ans;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    cin >> s;
    n = s.size();
    s = "0" + s;

    for (int i = 1; i <= n; i++)
        A[s[i] - 'A' + 1]++;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= 26; j++)
        {
            if (!A[j] || j == la)
                continue;

            A[j]--;
            int maxn = 0;
            for (int k = 1; k <= 26; k++)
                maxn = max(maxn, A[k]);

            if (maxn * 2 > n - i + 1)
            {
                A[j]++;
                continue;
            }

            ans += char(j + 'A' - 1);
            la = j;
            break;
        }

        if (ans.size() != i) {
            return cout << "-1\n", 0;
        }
    }
    cout << ans << "\n";
    return 0;
}