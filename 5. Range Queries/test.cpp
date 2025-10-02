#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main() {
    int n, q;
    cin >> n >> q;

    vector<pair<int, int>> a(n);
    vector<int> sum(12, 0);
    for (auto &[f,s] : a) {
        cin >> f >> s;
        sum[f]++;
        sum[s + 1]--;
    }
    for (int i = 1; i <= 10; i++) {
        sum[i] += sum[i - 1];
    }

    for (int i = 1; i <= 10; i++) {
        cout << sum[i] << " ";
    }

    return 0;
}
