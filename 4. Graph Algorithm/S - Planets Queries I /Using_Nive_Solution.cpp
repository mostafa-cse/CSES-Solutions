#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> teleporter(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> teleporter[i];
    }

    while (q--) {
        int x, k;
        cin >> x >> k;
        while (k--) {
            x = teleporter[x];
        }
        cout << x << '\n';
    }
    return 0;
}
