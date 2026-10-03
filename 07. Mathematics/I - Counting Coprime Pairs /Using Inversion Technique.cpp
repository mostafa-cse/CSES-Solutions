#include <bits/stdc++.h>
// #define int long long
using namespace std;

signed main() {
    int n;
    cin >> n;

    long long pairGcd = 0; // count which gcd > 1
    unordered_map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        vector<int> factorial;
        for (int j = 2; j * j <= x; j++) {
            if (x % j == 0) {
                factorial.push_back(j);
                while (x % j == 0) {
                    x /= j;
                }
            }
        }
        if (x > 1) {
            factorial.push_back(x);
        }
        sort(factorial.begin(), factorial.end());
        factorial.resize(unique(factorial.begin(), factorial.end()) - factorial.begin());

        for (int mask = 1; mask < (1 << factorial.size()); mask++) {
            int mul = 1, bcnt = 0;
            for (int b = 0; b < factorial.size(); b++) {
                if (mask >> b & 1) {
                    mul *= factorial[b];
                    bcnt++;
                }
            }

            int val = cnt[mul];
            if (bcnt % 2 == 0) {
                val *= -1;
            }
            pairGcd += val;
            cnt[mul]++;
        }
    }
    cout << ((long long)n * (n - 1) / 2) - pairGcd << endl;
    return 0;
}
