/*
    Author : M0stafa
    Topic : String Algorithm
    Algorithm : Aho-Corasick 
*/
#include <bits/stdc++.h>
#define int long long
using namespace std;
#ifndef ONLINE_JUDGE
#define dout(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define dout(...)
#endif
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
    vector<pair<int,int>> find_all(string &text, const vector<int> len) {
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

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string text;
    cin >> text;
    int n;
    n = (int)text.size();

    string pat;
    cin >> pat;

    AhoCorasick ac;
    ac.insert(pat, 0);
    ac.build();

    auto ans = ac.find_all(text, {(int)pat.size()});
    cout << ans.size();
    return 0;
}
