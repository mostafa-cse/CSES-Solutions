#include <bits/stdc++.h>
#define int long long
using namespace std;
string manachar(const string &s) {
    int n = s.size();
    int left = 0, right = 0;
    int pos = 0;
    vector<int> len(n);
    for (int i = 0; i < n; i++) {
        int l = 1;
        if (i <= right) {
            l = min(right - i + 1, len[left + right - i]);
        }
        while (i - l >= 0 and i + l < n and s[i - l] == s[i + l]) {
            l++;
            left = i - l + 1;
            right = i + l - 1;
        }
        len[i] = l;
        if (l > len[pos]) pos = i;
    }
    return s.substr(pos - len[pos] + 1, 2 * len[pos] - 1);
}
signed main() {
    string s;
    cin >> s;

    int n = s.size();
    string input = string(2 * n + 1, '*');
    for (int i = 0; i < n; i++) {
        input[i * 2 + 1] = s[i];
    }
    string output = manachar(input);
    for (int i = 1; i < output.size(); i += 2) {
        cout << output[i];
    }
    return 0;
}
