#include <bits/stdc++.h>
#define int long long
using namespace std;

const int Mod = 1e9 + 7;
auto kmp_automata(string &s) {
    int n = s.size();
    vector<int> pi(n);
    vector<vector<int>> automata(n + 1, vector<int>(26));

    for (int i = 0; i <= n; i++) {
        for (int c = 0; c < 26; c++) {
            if (i < n and c == s[i] - 'a') {
                automata[i][c] = i + 1;
            } else if (i > 0) {
                automata[i][c] = automata[pi[i - 1]][c];
            } else {
                automata[i][c] = 0;
            }
        }
        if (i > 0 and i < n) {
            pi[i] = automata[pi[i - 1]][s[i] - 'a'];
        }
    }
    return automata;
}
signed main() {
    ios::sync_with_stdio(0); cin.tie(0); // Fast I/O
    int n;
    cin >> n;

    string s;
    cin >> s;

    for (int i = 0; i < s.size(); i++) {
        s[i] = tolower(s[i]);
    }

    int m = s.size();
    auto automata = kmp_automata(s);

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int c = 0; c < 26; c++) {
                int next_state = automata[j][c];
                dp[i][next_state] = (dp[i][next_state] + dp[i - 1][j]) % Mod;
            }
        }
        dp[i][m] = (dp[i][m] + 26 * dp[i - 1][m]) % Mod;
    }
    cout << dp[n][m] << endl;
    return 0;
}
