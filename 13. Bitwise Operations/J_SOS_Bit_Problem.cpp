#include <bits/stdc++.h>
#define int long long
using namespace std;
const int M = 20;
int AND[1 << M], OR[1 << M], a[1 << M];
signed main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // AND count
    for (int i = 0; i < n; i++) {
        AND[a[i]]++;
    }

    for (int i = 0; i < M; i++) {
        for (int mask = 0; mask < (1 << M); mask++) {
            if (!(mask >> i & 1)) { // super mask
                AND[mask] += AND[mask ^ (1 << i)];
            }
        }
    }

    // OR count
    for (int i = 0; i < n; i++) {
        OR[a[i]]++;
    }
    for (int i = 0; i < M; i++) {
        for (int mask = 0; mask < (1 << M); mask++) {
            if (mask >> i & 1) { // submask
                OR[mask] += OR[mask ^ (1 << i)];
            }
        }
    }

    // NOT ZERO for AND of two number of an array
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = n - OR[a[i] ^ ((1 << M) - 1)];
    }

    for (int i = 0; i < n; i++) {
        cout << OR[a[i]] << " " << AND[a[i]] << " " << ans[i] << endl;
    }
    return 0;
}
