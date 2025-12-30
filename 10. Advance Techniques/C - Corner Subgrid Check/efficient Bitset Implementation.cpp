#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3001;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;

    string s;
    bitset<MAXN> v[26][MAXN];
    bool ans[26] = {0};
    for (int i = 0; i < n; ++i) {
        cin >> s;
        bitset<MAXN> c[26];
        for (int j = 0; j < n; ++j)
        {
            int ch = s[j] - 'A';
            if (ans[ch]) {
                continue;
            }
            if ((v[ch][j] & c[ch]).any())
            {
                ans[ch] = true;
            }
            v[ch][j] |= c[ch];
            c[ch].set(j);
        }
    }
    for (int c = 0; c < k; ++c) {
        cout << (ans[c] ? "YES\n" : "NO\n");
    }
    return 0;
}
