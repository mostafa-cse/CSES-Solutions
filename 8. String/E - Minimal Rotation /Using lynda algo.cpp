#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    s = s + s;

    int pos = 0;
    int cur = 1;
    while (cur < n) {
        int k = 0;
        while (k < n && s[pos + k] == s[cur + k]) k++;
        if (s[pos + k] <= s[cur + k]) {
            cur += k + 1;
        } else {
            pos = max(pos + k + 1, cur);
            cur = pos + 1;
        }
    }

    cout << s.substr(pos, n) << "\n";
}
