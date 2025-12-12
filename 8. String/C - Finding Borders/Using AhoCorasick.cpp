#include <bits/stdc++.h>
using namespace std;
struct AhoCorasick {
    static constexpr int K = 26;

    vector<array<int, K>> nxt;
    vector<int> link;          // failure link
    vector<int> out_link;      // next terminal node in failure chain
    vector<vector<int>> out;   // pattern ids ending here

    AhoCorasick() { new_node(); } // root = 0

    static int get_idx(char c) { return c - 'a'; }

    int new_node() {
        nxt.push_back({});
        nxt.back().fill(0);
        link.push_back(0);
        out_link.push_back(-1);
        out.push_back({});
        return (int)nxt.size() - 1;
    }

    void insert(const string &s, int id) {
        int u = 0;
        for (char c : s) {
            int i = get_idx(c);
            if (!nxt[u][i]) {
                int v = new_node();
                nxt[u][i] = v;
            }
            u = nxt[u][i];
        }
        out[u].push_back(id);
    }

    void build() {
        queue<int> q;

        // root transitions
        for (int i = 0; i < K; i++) {
            int v = nxt[0][i];
            if (v) q.push(v), link[v] = 0;
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            int f = link[u];


            out_link[u] = (!out[f].empty() ? f : out_link[f]);

            for (int i = 0; i < K; i++) {
                int v = nxt[u][i];
                if (v) {
                    link[v] = nxt[f][i];
                    q.push(v);
                } else {
                    nxt[u][i] = nxt[f][i];
                }
            }
        }
    }
};

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string text;
    cin >> text;

    AhoCorasick ac;

    //  we only insert one string, Node `i` will represent the prefix of length `i`.
    ac.insert(text, 0);
    ac.build();

    int curr = text.size();
    vector<int> ans;
    // Traverse the failure links from the end of the string back to the root.
    // ac.link[curr] gives us the longest proper suffix that is also a prefix.
    while (curr > 0) {
        curr = ac.link[curr];
        if (curr > 0) {
            ans.push_back(curr);
        }
    }
    sort(ans.begin(), ans.end());
    for (int x : ans) {
        cout << x << " ";
    }
    return 0;
}
