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
auto computeLPS(string &line) {
    int n = line.size();
    vector<int> lps(n, 0);
    lps[0] = 0;
    int len = 0, i = 1;
    while (i < n) {
        if (line[i] == line[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    string s;
    cin >> s;

    for (int i : Z_algo(s)) {
        cout << i << " ";
    }
    cout << endl;


    for (int i : computeLPS(s)) {
        cout << i << " ";
    }
    return 0;
}

