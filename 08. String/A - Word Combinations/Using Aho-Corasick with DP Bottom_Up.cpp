/*
    Top-down DP with memoization + Aho-Corasick
    solve(pos) = ways to cover text[pos..]
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

    AhoCorasick() { new_node(); }

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
        for (int c = 0; c < 26; c++) {
            int v = next[0][c];
            if (v) {
                link[v] = 0;
                q.push(v);
            }
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            int f = link[u];

            out_link[u] = !out[f].empty() ? f : out_link[f];

            for (int c = 0; c < 26; c++) {
                int v = next[u][c];
                if (v) {
                    link[v] = next[f][c];
                    q.push(v);
                } else {
                    next[u][c] = next[f][c];
                }
            }
        }
    }

    // same as your find_all
    vector<pair<int,int>> find_all(string &text, const vector<int> &len) {
        vector<pair<int,int>> ans;
        int u = 0;
        for (int pos = 0; pos < (int)text.size(); pos++) {
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

string text;
int n;
vector<int> lenPat;
vector<vector<int>> starts_at;
vector<int> memo;
vector<char> vis;

int solve(int pos) {
    if (pos == n) return 1;    
    if (vis[pos]) return memo[pos];
    vis[pos] = 1;

    long long res = 0;
    for (int id : starts_at[pos]) {
        int L = lenPat[id];
        int nxt = pos + L;
        if (nxt <= n) {
            res += solve(nxt);
            if (res >= Mod) res -= Mod;
        }
    }
    memo[pos] = (int)res;
    return memo[pos];
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> text;
    n = (int)text.size();

    int q;
    cin >> q;

    AhoCorasick ac;
    lenPat.assign(q, 0);
    for (int i = 0; i < q; i++) {
        string t;
        cin >> t;
        lenPat[i] = (int)t.size();
        ac.insert(t, i);
    }
    ac.build();

    vector<pair<int,int>> matches = ac.find_all(text, lenPat);
    starts_at.assign(n, {});
    for (auto [l, idx] : matches) {
        if (l >= 0 && l < n) {
            starts_at[l].push_back(idx);
        }
    }

    memo.assign(n + 1, 0);
    vis.assign(n + 1, 0);

    cout << solve(0) % Mod << '\n';
    return 0;
}
