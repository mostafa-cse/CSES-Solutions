#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define all(x) x.begin(), x.end()
const int M = 1e9 + 7;
int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(all(a));

    int ans = 1, i = 0;
    while (i < n)
    {
        int j = i + 1;
        while (j < n and a[j] == a[i])
            j++;
        ans = (1LL * ans * (j - i + 1)) % M;
        i = j;
    }
    cout << ans - 1 << endl;
    return 0;
}
