#include <bits/stdc++.h>
using namespace std;
const int N = (int)2e5 + 5;
const int K = 30;
unsigned p[N][2], x[N], d[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    unsigned n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i][0];
    }
    for (int i = 0; i < q; ++i) {
        cin >> x[i] >> d[i];
    }
    
    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < q; ++j) {
            if ((1 << i) & d[j]) {
                x[j] = p[x[j]][i & 1];
            }
        }
        // Update the binary lifting table for the next level using the previous level's information
        for (int j = 1; j <= n; ++j) {
            p[j][~i & 1] = p[p[j][i & 1]][i & 1];
        }
    }

    for (int i = 0; i < q; ++i) {
        cout << x[i] << '\n';
    }
    return 0;
}
