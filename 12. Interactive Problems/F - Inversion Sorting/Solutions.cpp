#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
int ask(int l, int r) {
    cout << l << " " << r << endl;
    int inv;
    cin >> inv;
    if(inv == 0) exit(0);
    return inv;
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n;
    cin >> n;

    int inv = ask(1, n);
    for (int i = 2; i <= n; i++) {
        int new_inv = ask(1, i);
        int rank = (inv - new_inv + (i - 2) * (i - 1) / 2 + i - 1) / 2;
        ask(1, i);
        if (i - rank < i) {
            ask(i - rank, i - 1);
        }
        inv = ask(i - rank, i);
    }
    return 0;
}

