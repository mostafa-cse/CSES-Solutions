#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n;
    scanf("%lld", &n);

    vector<int> r(n);
    for (int  &i : r) {
        scanf("%lld", &i);
    }

    double ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double val = 0;
            double total = r[i] * r[j];
            for (int p = 1; p <= r[i]; p++) {
                double cur = min(p - 1, r[j]);
                if (cur > 0) {
                    val += cur;
                }
            }
            ans += (val / total);
        }
    }
    double sum = 0;
    while (ans)
    printf("%0.6lf\n", ans);
    return 0;
}
