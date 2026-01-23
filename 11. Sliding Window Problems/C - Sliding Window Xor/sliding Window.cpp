#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, k;
    cin >> n >> k;

    int x, a, b, c;
    cin >> x >> a >> b >> c;

    vector<int> ar = {x};
    for (int i = 1; i < n; i++) {
        int cur = (ar[i - 1] * a + b) % c;
        ar.push_back(cur);
    }
    int sum = 0;
    for (int i = 0, curSum = 0; i < n; i++) {
        curSum ^= ar[i];
        if (i + 1 >= k) {
            sum ^= curSum;
            curSum ^= ar[i - k + 1];
        }
    }
    cout << sum << endl;
    return 0;
}

