/*
    Author : M0stafa
    Topic : String Algorithm
    Algorithm : Aho-Corasick with DP
    DP trick : Top-Down approach
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
        new_node();
    }
    int get_index(char c) {
        return c - 'a';
    }
    int new_node () {
        next.push_back({});
        next.back().fill(0);
        link.push_back(0);
        out.push_back({});
        out_link.push_back(-1);
        return next.size() - 1;
    }
    void insert(string &s, int idx) {
        int u = 0;
        for (auto c : s) {
            int i = c - 'a';
            if (next[u][i] == 0) {
                next[u][i] = new_node();
            }
            u = next[u][i];
        }
        out[u].push_back(idx);
    }
    void build() {
        queue<int> q;
        for (int i = 0; i < 26; i++) {
            int v = next[0][i];
            if (v) {
                q.push(v);
                link[v] = 0;
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            int f = link[u];

            out_link[u] = !out[f].empty() ? f : out_link[f];
            for (int i = 0; i < 26; i++) {
                int v = next[u][i];
                if (v) {
                    link[v] = next[f][i];
                    q.push(v);
                } else {
                    next[u][i] = next[f][i];
                }
            }
        }
    }
    vector<pair<int ,int>> find_all(string &text, vector<int> len) {
        vector<pair<int ,int>> ans;
        int u = 0;
        for (int pos = 0; pos < text.size(); pos++) {
            int i = text[pos] - 'a';
            u = next[u][i];

            int v = u;
            while (v != -1) {
                for (int id : out[v]) {
                    int start = pos - len[id] + 1;
                    ans.emplace_back(start, id);
                }
                v = out_link[v];
            }
        }
        return ans;
    }
};
signed main() {
    string text;
    cin >> text;


    AhoCorasick ac;
    int q;
    cin >> q;

    vector<int> len(q);
    for (int i = 0; i < q; i++) {
        string t;
        cin >> t;
        len[i] = t.size();
        ac.insert(t, i);
    }
    ac.build();

    vector<pair<int, int>> ans = ac.find_all(text, len);
    vector<int> dp(text.size() + 1, 0);
    dp[0] = 1;
    for (auto [l, idx] : ans) {
        dp[l + len[idx]] += dp[l];
        dp[l + len[idx]] %= Mod;
    }
    cout << dp[text.size()];
    return 0;
}
