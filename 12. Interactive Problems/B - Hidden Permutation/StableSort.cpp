#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()

signed main() {
    int n;
    cin >> n;

    vector<int> idx(n);
    for (int i = 0; i < n; i++) {
        idx[i] = i;
    }

    stable_sort(all(idx), [](int x, int y) {
        cout << "? " << x + 1 << " " << y + 1 << endl;

        string s;
        cin >> s;
        return s == "YES";
    });

    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        ans[idx[i]] = i + 1;
    }

    cout << "! ";
    for (int i : ans) {
        cout << i << " ";
    }
    return 0;
}
