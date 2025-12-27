#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()

// Helper function to print __int128_t
void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n;
    cin >> n;

    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    sort(all(x));
    sort(all(y));

    __int128_t ans = 0;
    int sumX = x[0];
    int sumY = y[0];

    for (int i = 1; i < n; i++) {
        ans += (__int128_t)x[i] * i - sumX;
        sumX += x[i];

        ans += (__int128_t)y[i] * i - sumY;
        sumY += y[i];
    }

    print(ans);
    cout << endl;

    return 0;
}
