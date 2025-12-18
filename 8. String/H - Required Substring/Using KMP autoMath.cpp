#include <bits/stdc++.h>
#define int long long
using namespace std;
const int Mod = 1e9 + 7;
vector<int> computeLPS(string pattern) {
    int n = pattern.size();
    vector<int> lps(n, 0);

    lps[0] = 0;
    int len = 0, i = 1;
    while (i < n) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else  {
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
    int n;
    cin >> n;

    string s;
    cin >> s;

    auto lps = computeLPS(s);
    int m = s.size();

    // make automaton
    vector<vector<int>> state(m + 1, vector<int>(26, 0));
    for (int i = 0; i < m; i++) {
        for (int c = 0; c < 26; c++) {
            if (s[i] - 'A' == c) {
                state[i][c] = i + 1;
            } else if (i > 0) {
                state[i][c] = state[lps[i - 1]][c];
            }
        }
    }
    for (int i = 0; i < 26; i++) {
        state[m][i] = m;
    }

    vector<vector<int>> ways(n + 1, vector<int>(m + 1, 0));
    ways[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int c = 0; c < 26; c++) {
                ways[i + 1][state[j][c]] = (ways[i + 1][state[j][c]] + ways[i][j]) % Mod;
            }
        }
    }
    cout << ways[n][m] << endl;
    return 0;
}
