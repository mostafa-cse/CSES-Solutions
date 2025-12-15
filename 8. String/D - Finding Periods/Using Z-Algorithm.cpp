#include <bits/stdc++.h>
#define int long long
using namespace std;
#define all(x) x.begin(), x.end()
vector<int> Z_algo(string &s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) { // inside the block
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n and s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    string s;
    cin >> s;

    vector<int> z = Z_algo(s);
    for (int i = 1; i < s.size(); i++) {
        if (z[i] == s.size() - i) {
            cout << i << " ";
        }
        // if (z[i] + i == s.size()) {
        //     cout << i << " ";
        // }
    }
    cout << s.size() << endl;
    return 0;
}
