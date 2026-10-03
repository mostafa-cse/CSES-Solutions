#include <bits/stdc++.h>
#define int long long
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
const int M = 21;
vector<int> fact(M);
signed main() {
    fact[0] = 1;
    for (int i = 1; i <= 20; i++) {
        fact[i] = fact[i - 1] * i;
    }

    int test = 0;
    cin >> test;
    while (test--) {
        int op;
        cin >> op;

        if (op == 1) {
            int n, k;
            cin >> n >> k;

            vector<bool> flag(n + 1, false);
            for (int i = 1; i <= n; i++) flag[i] = false;

            for (int i = 1; i <= n; i++) {
                int t = (k - 1) / fact[n - i];
                int q = 0;
                for (int j = 1; j <= n; j++) {
                    if (flag[j] == false) q++;
                    if (q == t + 1) {
                        q = j;
                        break;
                    }
                }
                cout << q << " ";
                flag[q] = true;
                k -= t * fact[n - i];
            }
            cout << endl;
        } else {
            int n;
            cin >> n;
            vector<int> flag(n + 1, false), a(n + 1);
            int k = 0;
            for (int i = 1; i <= n; i++) {
                cin >> a[i];

                int rnk = 0;
                for (int j = 1; j <= a[i]; j++) {
                    if (flag[j] == false) {
                        rnk++;
                    }
                }
                flag[a[i]] = true;
                k += ((rnk - 1) * fact[n - i]);
            }
            cout << k + 1 << endl;
        }
    }
    return 0;
}
