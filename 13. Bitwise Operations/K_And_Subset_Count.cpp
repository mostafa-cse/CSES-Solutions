#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
const int M = 18;
vector<int> p2((1 << M) + 5), a((1 << M) + 5);
const int Mod = 1e9 + 7;
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    p2[0] = 1;
    for (int i = 1; i <= (1 << M); i++) {
        p2[i] = (p2[i - 1] * 2) % Mod;

    }

    int n;
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        a[c]++;
    }

    for (int i = 0; i < M; i++) {
        for (int mask = 0; mask < (1 << M); mask++) {
            if (!(mask >> i & 1)) {
                a[mask] += a[mask ^(1 << i)];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        a[i] = (p2[a[i]] - 1 + Mod) % Mod;
    }

    for (int i = 0; i < M; i++) {
        for (int mask = 0; mask < (1 << M); mask++) {
            if (!(mask >> i & 1)) {
                a[mask] -= a[mask ^ (1 << i)];
                a[mask] = (a[mask] + Mod) % Mod;
            }
        }
    }

    for (int i = 0; i <= n; i++) {
        cout << a[i] << " ";
    }
    return 0;
}

