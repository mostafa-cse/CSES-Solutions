#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n;
    cin >> n;

    int mnSum = 1e18, mxSum = -1e18;
    int mnSub = 1e18, mxSub = -1e18;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;

        int sum = x + y;
        int sub = x - y;

        mnSub = min(mnSub, sub);
        mxSub = max(mxSub, sub);

        mnSum = min(mnSum, sum);
        mxSum = max(mxSum, sum);

        cout << max(mxSum - mnSum, mxSub - mnSub) << endl;
    }
    return 0;
}

