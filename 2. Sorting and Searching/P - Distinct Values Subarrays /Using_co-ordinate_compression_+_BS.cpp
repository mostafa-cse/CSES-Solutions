#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 200005;
int a[MAX_N], b[MAX_N], c[MAX_N], n;
int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        b[i] = a[i];
    }

    sort(b + 1, b + n + 1);
    int tot = unique(b + 1, b + n + 1) - b;

    long long result = 0;
    int r = 0;
    for (int i = 1; i <= n; ++i) {
        int t = lower_bound(b + 1, b + tot + 1, a[i]) - b;
        r = min(r + 1, i - c[t]);
        c[t] = i;
        result += r;
    }
    cout << result << endl;
    return 0;
}