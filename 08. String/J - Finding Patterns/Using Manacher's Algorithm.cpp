#include <bits/stdc++.h>
using namespace std;

struct AhoCorasick {
    struct Node {
        int nxt[26];
        int fail = 0;
        int count = 0;

        Node() {
            memset(nxt, 0, sizeof(nxt));
        }
    };

    vector<Node> t;
    vector<int> pattern_end_node;
    vector<int> bfs_order;

    AhoCorasick() {
        t.emplace_back();
    }

    void insert(const string &s, int id) {
        int u = 0;
        for (char c : s) {
            int i = c - 'a';
            if (!t[u].nxt[i]) {
                t[u].nxt[i] = t.size();
                t.emplace_back();
            }
            u = t[u].nxt[i];
        }
        if (id >= pattern_end_node.size()) {
            pattern_end_node.resize(id + 1);
        }
        pattern_end_node[id] = u;
    }

    void build() {
        queue<int> q;
        for (int i = 0; i < 26; i++) {
            if (t[0].nxt[i]) {
                q.push(t[0].nxt[i]);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            bfs_order.push_back(u);

            for (int i = 0; i < 26; i++) {
                if (t[u].nxt[i]) {
                    t[t[u].nxt[i]].fail = t[t[u].fail].nxt[i];
                    q.push(t[u].nxt[i]);
                } else {
                    t[u].nxt[i] = t[t[u].fail].nxt[i];
                }
            }
        }
    }

    void solve_counts(const string &text) {
        int u = 0;
        for (char c : text) {
            u = t[u].nxt[c - 'a'];
            t[u].count++;
        }

        for (int i = bfs_order.size() - 1; i >= 0; i--) {
            int u = bfs_order[i];
            int f = t[u].fail;
            t[f].count += t[u].count;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    int q;
    cin >> q;

    AhoCorasick ac;
    for (int i = 0; i < q; i++) {
        string p;
        cin >> p;
        ac.insert(p, i);
    }

    ac.build();
    ac.solve_counts(s);

    for (int i = 0; i < q; i++) {
        int node_idx = ac.pattern_end_node[i];
        if (ac.t[node_idx].count > 0) { // koto bar occur korse 
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
