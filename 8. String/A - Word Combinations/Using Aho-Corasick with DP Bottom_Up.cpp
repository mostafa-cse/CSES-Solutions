/*
    Bottom-up DP with Aho-Corasick
    dp[i] = number of ways to cover text[0..i-1]
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int Mod = 1e9 + 7;

struct AhoCorasick {
    vector<array<int, 26>> next;
    vector<int> link;
    vector<vector<int>> out;
    vector<int> out_link;

    AhoCorasick() {
        new_node();            // root = 0
    }

    int new_node() {
        next.push_back({});
        next.back().fill(0);
        link.push_back(0);
        out.push_back({});
        out_link.push_back(-1);
        return (int)next.size() - 1;
    }

    void insert(const string &s, int idx) {
        int u = 0;
        for (char c : s) {
            int i = c - 'a';
            if (next[u][i] == 0) next[u][i] = new_node();
            u = next[u][i];
        }
        out[u].push_back(idx);
    }

    void build() {
        queue<int> q;
        // initialize children of root
        for (int c = 0; c < 26; c++) {
            int v = next[0][c];
            if (v) {
                link[v] = 0;
                q.push(v);
            }
        }
        // BFS
        while (!q.empty()) {
            int u = q.front(); q.pop();
            int f = link[u];

            // output link
            out_link[u] = !out[f].empty() ? f : out_link[f];

            // transitions
            for (int c = 0; c < 26; c++) {
                int v = next[u][c];
                if (v) {
                    link[v] = next[f][c];
                    q.push(v);
                } else {
                    next[u][c] = next[f][c]; // automaton transition
                }
            }
        }
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string text;
    cin >> text;

    int q;
    cin >> q;

    AhoCorasick ac;
    vector<int> len(q);
    for (int i = 0; i < q; i++) {
        string pat;
        cin >> pat;
        len[i] = (int)pat.size();
        ac.insert(pat, i);
    }
    ac.build();

    int n = (int)text.size();
    vector<int> dp(n + 1, 0);
    dp[0] = 1;

    int u = 0; // current automaton state
    for (int pos = 0; pos < n; pos++) {
        int c = text[pos] - 'a';
        u = ac.next[u][c]; // already includes failure transitions

        // from prefix end at pos, transitions to future positions
        int v = u;
        while (v != -1) {
            for (int id : ac.out[v]) {
                int L = len[id];
                int start = pos - L + 1;  // starting index of match
                if (start >= 0) {
                    // we extend any covering of prefix [0..start-1]
                    dp[start + L] += dp[start];
                    if (dp[start + L] >= Mod) dp[start + L] -= Mod;
                }
            }
            v = ac.out_link[v];
        }
    }

    cout << dp[n] % Mod << '\n';
    return 0;
}
