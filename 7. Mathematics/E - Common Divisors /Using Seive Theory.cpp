#include <bits/stdc++.h>
#define int long long
using namespace std;
const int M = 1e6 + 6;
int cnt[M];

signed main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    int mxGCD = 1;
    for (int i = 2; i < M; i++) {
        int curr = 0;
        for (int j = i; j < M; j += i) {
            if (cnt[j]) {
                curr += cnt[j];
            }
        }
        if (curr >= 2) {
            mxGCD = i;
        }
    }
    cout << mxGCD;
    return 0;
}
