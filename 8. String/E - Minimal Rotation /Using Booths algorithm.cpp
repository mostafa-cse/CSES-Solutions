#include <bits/stdc++.h>
#define int long long
using namespace std;
int least_rotation(const string &s) {
    int n = (int)s.size();
    vector<int> f(2 * n, -1);
    int k = 0;
    for (int j = 1; j < 2 * n; j++) {
        int i = f[j - k - 1];
        while (i != -1 && s[j % n] != s[(k + i + 1) % n]) {
            if (s[j % n] < s[(k + i + 1) % n]) {
                k = j - i - 1;
            }
            i = f[i];
        }
        if (i == -1 && s[j % n] != s[(k + i + 1) % n]) {
            if (s[j % n] < s[(k + i + 1) % n]) {
                k = j;
            }
            f[j - k] = -1;
        } else {
            f[j - k] = i + 1;
        }
    }
    return k;
}

signed main() {
    string s;
    cin >> s;

    int pos = least_rotation(s);
    cout << s.substr(pos) + s.substr(0, pos) << endl;
    return 0;
}
