#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n;
    cin >> n;

    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    x.push_back(x[0]);
    y.push_back(y[0]);


    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += x[i] * y[i + 1];
        ans -= y[i] * x[i + 1];
    }
    cout << abs(ans) << endl;
    return 0;
}

