#include <bits/stdc++.h>
#define int long long
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
const int M = 1e6 + 1;
int grundy[M];
void solve() {
    int n;
    cin >> n;
    if (n >= 2000) cout << "first" <<endl;
    else cout << (grundy[n] ? "first" : "second") << endl;
}
signed main() {
    for (int pile = 3; pile <= 2000; pile++) {
        map<int, int> seen;
        for (int a = 1; a * 2 < pile; a++) {
            int b = pile - a;
            int mexVal = grundy[a] ^ grundy[b];
            seen[mexVal] = 1;
        }
        int mex = 0;
        while (seen.count(mex)) {
            mex++;
        }
        grundy[pile] = mex;
    }

    int tc;
    cin >> tc;

    for (int t = 1; t <= tc; t++) {
        // cout << "Case " << t << ": ";
        solve();
    }
    return 0;
}
