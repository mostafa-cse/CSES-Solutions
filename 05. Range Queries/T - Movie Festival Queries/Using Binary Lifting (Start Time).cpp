#include <bits/stdc++.h>
#define int long long
using namespace std;

const int MX = 1000005;
int nex[MX][20];

int32_t main() {
    cin.tie(NULL)->sync_with_stdio(NULL);
    int n, q;
    cin >> n >> q;

    for (int i = 0; i < (MX); i++) {
        nex[i][0] = MX - 1;
    }

    for (int i = 0; i < (n); i++) {
        int a, b;
        cin >> a >> b;
        nex[a][0] = min(nex[a][0], b);
    }

    for (int i = (MX)-1; i >= (1); i--) {
        if (i > 0) {
            nex[i - 1][0] = min(nex[i - 1][0], nex[i][0]);
        }
    }

    for (int j = (1); j < (20); j++) {
        for (int i = 0; i < (MX); i++) {
            nex[i][j] = nex[nex[i][j - 1]][j - 1];
        }
    }

    for (int i = 0; i < (q); i++) {
        int a, b;
        cin >> a >> b;

        int ans = 0;
        for (int j = (20) - 1; j >= 0; j--) {
            if (nex[a][j] <= b) {
                ans ^= 1 << j;
                a = nex[a][j];
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
